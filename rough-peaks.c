#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <glib.h>
#include <gsl/gsl_histogram.h>
#include <gsl/gsl_cdf.h>

const int buffsize = 1024;

/* these are from the gperf generated files for chromosome size lookup */
struct chrom_info {
    const char *name;
    long   length;
};
struct chrom_info* get_chrom_info (const char *str, unsigned int len);
/* gperf end */

void usage ()
{
    printf("rough-peaks-<genome>\n"
           "--------------------------------------------\n"
           "Usage:\n"
           "   rough-peaks-<genome> bedfile chromosome bin-size \n\n"
           "Determine fragment size based on information criterion\n"
           "Currently allowed genomes:  mm9\n");
}
double print_peak(const gsl_histogram *bins, char strand, size_t first_bin, size_t last_bin)
{
    int s = bins->range[first_bin];
    int e = bins->range[last_bin+1];
    size_t b;
    double island_reads = 0.0;
    
    for (b=first_bin; b<last_bin+1; b++) {
        island_reads += gsl_histogram_get(bins, b);
    }
    printf("%i|%i|%c|%i\n", s, e, strand, (int)island_reads);
    return island_reads;
}

int
find_peaks(const gsl_histogram *bins, int cutoff, char strand)
{
    size_t first_bin     = 0;
    size_t last_bin      = 0;
    bool   in_peak       = false;
    double val           = 0.0;
    double all_ireads    = 0.0;
    int    nr_bins_above = 0;
    int    nr_peaks      = 0;
    /* find peaks (consecutive areas of bins above cutoff) */
    size_t bin;
    for (bin = 0; bin < bins->n; bin++) {
        val = gsl_histogram_get(bins, bin);
        /* is it a significant bin ? */
        if (val > cutoff) {
            nr_bins_above++;
            if (! in_peak) {
                /* start new peak */
                in_peak = true;
                first_bin = bin;
                last_bin = bin;
                nr_peaks++;
            } else {
                /* add to existing peak */
                last_bin = bin;
            }
        } else {
            if (in_peak && bin - last_bin > 1) {
                /* end of peak */
                all_ireads += print_peak(bins, strand, first_bin, last_bin);
                first_bin = 0;
                last_bin = 0;
                in_peak = false;
            }
        }
    }
    /* in case there is an unprocessed peak at the end */
    if (in_peak) {
        all_ireads += print_peak(bins, strand, first_bin, last_bin);
    }
    fprintf(stderr, "(%c) %5i bins above cutoff in %4i (almost) continuous peaks\n", strand, nr_bins_above, nr_peaks);
    fprintf(stderr, "    containing %i reads\n", (int)all_ireads);
    
    return 0;
}



int
main (int argc, char **argv)
{
    if (argc < 4) {
        usage ();
        return 1;
    } 
    char *infile_name  = argv[1];
    char *chrom        = argv[2];
    int  bin_size      = atoi(argv[3]);


    if (bin_size == 0){
        fprintf(stderr, "%s is not a valid bin size\n", argv[4]);
        usage();
        return 1;
    }

    /* determine chromosome length and the number of bins in the histogram*/
    struct chrom_info *chromosome = get_chrom_info(chrom, strlen(chrom));
    if (chromosome == NULL) {
        fprintf(stderr, "Could not determine chromosome length for %s\n", chrom);
        return 1;
    } 
    fprintf(stderr, "%s:  %li nts long\n", chrom, chromosome->length);
    size_t number_of_bins = chromosome->length / bin_size;
    double real_bin_size = (double)chromosome->length / number_of_bins;
    fprintf(stderr, "  divided into %i bins of width %.1f\n", (int)number_of_bins, real_bin_size);

    /* open the bed input file */
    FILE *infile = fopen(infile_name, "r");
    if (infile == NULL) {
        fprintf(stderr,"Could not open infile %s\n", infile_name);
        return 1;
    }
    gsl_histogram *plus;
    plus = gsl_histogram_alloc (number_of_bins);
    g_assert(plus != NULL);
    gsl_histogram_set_ranges_uniform (plus, 0, chromosome->length);

    gsl_histogram *minus;
    minus = gsl_histogram_alloc (number_of_bins);
    g_assert(minus != NULL);
    gsl_histogram_set_ranges_uniform (minus, 0, chromosome->length);

    int error_code = 0;
    char buffer[buffsize + 1];
    int converted;
    long start;
    long end;
    char strand;
    double pos;
    while (fgets(buffer, buffsize, infile) != NULL) {
        converted = sscanf(buffer, "%*6s %li %li %*s %*s %c", &start, &end, &strand);
        if (converted != 3) {
            error_code = 1;
            fprintf(stderr, "Could not parse line %s\n", buffer);
            goto cleanup;
        }
        if (strand == '+') {
            pos = (double)start;
            gsl_histogram_increment(plus, pos);
        } else if (strand == '-') {
            pos = (double)end;
            gsl_histogram_increment(minus, pos);
        } else {
            error_code=2;
            fprintf(stderr, "Strand identifier %c not allowed\n", strand);
            goto cleanup;
        }
    }

    /* overview of strands */
    unsigned int total_plus_reads = gsl_histogram_sum(plus);
    unsigned int total_minus_reads = gsl_histogram_sum(minus);
    fprintf(stderr, "plus strand reads:  %7i\nminus strand reads: %7i\n",
            total_plus_reads,
            total_minus_reads);
    double ep = (double)total_plus_reads / number_of_bins;
    double em = (double)total_minus_reads / number_of_bins;
    fprintf(stderr, "expected reads per bin: (+) %.3f (-) %.3f\n", ep, em);
    double p = 1.0 / number_of_bins;

    /* find cutoff using quantile function */
    unsigned int k;
    unsigned int cutoff = 0;
    char marker = ' ';
    fprintf(stderr, "given probability p = %E, the following relationship\nbetween cutoff and significance are given by binomial dist\n", p);
    fprintf(stderr, "cutoff | sig\n-------|----------\n");
    for (k=1; k < 20; k++) {
        double sig = gsl_cdf_binomial_Q(k, p, total_plus_reads);
        if (sig < 1e-6) {
            marker = '*';
            cutoff = k;
        }
        fprintf(stderr, "%6i | %9.7f %c\n", k, sig, marker);
        if (marker == '*') break;
    }
    fprintf(stderr, "using filter: nr_reads > %i\n\n", cutoff);
    /* find peaks in histograms */
    error_code = find_peaks(plus, cutoff, '+');
    if (error_code) goto cleanup;
    error_code = find_peaks(minus, cutoff, '-');
    if (error_code) goto cleanup;
    cleanup:
        gsl_histogram_free(plus);
        gsl_histogram_free(minus);
        fclose(infile);
        return error_code;
}
