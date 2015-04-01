#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <glib.h>
#include <gsl/gsl_histogram.h>

const int buffsize = 1024;
void usage ()
{
    printf("peak-summary\n"
           "--------------------------------------------\n"
           "Usage:\n"
           "   peak-summary peakfile binsize\n\n"
           "read a pipe-separated 3 column file (chr|pos|peakid)\n"
           "and bin each peak into binsize bins.  shift bins to center\n"
           "around max. value and generate accumulation plot\n\n"
           "data for plot are written to stdout.  in addition a file\n"
           "with 2 columns (peakid|peak_max) called `peakfile`.max\n"
           "is generated\n");
}




int
main (int argc, char **argv)
{
    if (argc < 3) {
        usage ();
        return 1;
    } 
    char *infile_name  = argv[1];
    char *outfile_name = malloc(strlen(infile_name) + 5);
    g_assert(outfile_name);
    sprintf(outfile_name, "%s.max", infile_name);
    int   bin_size     = atoi(argv[2]);
    fprintf(stderr, "reading from %s\nwriting peak maxima to %s\n", infile_name, outfile_name);

    FILE *infile = fopen(infile_name, "r");
    if (infile == NULL) {
        fprintf(stderr, "Could not open infile %s\n", infile_name);
        return 1;
    }
    
    int  error_code             = 0;
    int  converted              = 0;
    char buffer[buffsize + 1];
    char chrom[10];
    int  pos                    = 0;
    char peakid[10];
    int  readcount              = 0;
    int  peakcount              = 0;
    char current_peak[10]       = " ";
  
    while (fgets(buffer, buffsize, infile) != NULL) {
        converted = sscanf(buffer, "%9[^|]|%i|%9[^|]", chrom, &pos, peakid);
        if (converted != 3) {
            fprintf(stderr, "Could not parse line %s (converted %i fields)\n", buffer, converted);
            error_code = 1;
            goto cleanup;
        }
        readcount++;
        if (peakid != current_peak) {
            /* if it's not the first peak, process previous peak */
    }
    fprintf(stderr, "Processed %10i reads\n", readcount);

    cleanup:
        fprintf(stderr, "GTCleanup\n");
        fclose(infile);
        return error_code;
}
