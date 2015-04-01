#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "gsl/gsl_rng.h"

const int BUFFSIZE = 1024;

void usage ()
{
    printf("sample-bed\n"
           "--------------------------------------------\n"
           "Usage:\n"
           "   sample-bed bedfile s\n\n"
           "Take a random sample of size s from bed file\n"
           "Writes to stdout\n");
}

typedef enum rc {
    FAIL = -1,
    OK
} rc_t;


uint32_t count_lines(FILE *f) {
    int c=0,b;
    // ascii 10 is CR
    while ((b=fgetc(f))!=EOF) {
        c+=(b==10)?1:0;
    }
    fseek(f,0,SEEK_SET);
    return c;
}

rc_t filter_file(FILE *f, double fraction, uint32_t *n_sampled) {
    /* set up RNG */
    const gsl_rng_type * T = gsl_rng_default;
    gsl_rng * r            = gsl_rng_alloc(T);
    if (r == NULL) {
        fprintf(stderr, "[E] could not allocate GSL RNG\n");
        exit(1);
    }
    gsl_rng_set(r, time(NULL));

    /* cutoff for inclusion in output */    
    rc_t status = OK;
    *n_sampled = 0;

    char buffer[BUFFSIZE + 1];
    while (fgets(buffer, BUFFSIZE, f) != NULL) {
        if (gsl_rng_uniform(r) <= fraction) {
            fputs(buffer, stdout);
            (*n_sampled)++;
        }
    } 
        
    gsl_rng_free (r);
    return status;
}

int
main (int argc, char **argv)
{
    if (argc != 3) {
        usage ();
        return 1;
    } 
    char *infile_name    = argv[1];
    uint32_t sample_size = (uint32_t)strtol(argv[2], NULL, 0);
    if (sample_size == 0) {
        fprintf(stderr, "[E] Bad sample size: %s", argv[2]);
        return 1;
    }

    FILE *infile = fopen(infile_name, "r");
    if (infile == NULL) {
        fprintf(stderr, "[E] Could not open infile %s\n", infile_name);
        return 1;
    }
    uint32_t n_lines = count_lines(infile);
    if (n_lines == 0) {
        fprintf(stderr, "[E] File %s contained 0 lines\n", infile_name);
        return 1;
    }
    fprintf(stderr, "[I] Total number of lines: %9d\n", n_lines);
    fprintf(stderr, "[I] target sample size:    %9d\n", sample_size);
    
    double fraction = (double)sample_size / (double)n_lines;
    fprintf(stderr, "[I] fraction:              %9f\n", fraction);
    fflush(stderr);
    if (n_lines <= sample_size) {
        fprintf(stderr, "[E] sample size is not smaller than total number of lines\n");
        return 1;
    }
    uint32_t n_sampled;
    rc_t status = filter_file(infile, fraction, &n_sampled);
    fprintf(stderr, "[I] SUCCESS\n");
    fprintf(stderr, "[I] actual sample size:    %9d\n", n_sampled);
    return status;
}
