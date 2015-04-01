#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <glib.h>
#include <gsl/gsl_histogram.h>

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
    printf("frag-size-<genome>\n"
           "--------------------------------------------\n"
           "Usage:\n"
           "   frag-size-<genome> bedfile chromosome bin-size min_shift max_shift\n\n"
           "Determine fragment size based on information criterion\n"
           "Currently allowed genomes:  mm9\n");
}
double
shannon_entropy(const gsl_histogram *h, double total)
{
    double H = 0;
    double value = 0;
    for (size_t i=0; i < h->n; i++) {
        value = gsl_histogram_get(h, i) / total;
        if (value != 0.0)
            H += value*log2(value);
    }
    return -1 * H;
}

void
hist_head(const gsl_histogram *h)
{
    int count = 0;
    size_t i = 0;
    double val;
    double lower, upper; 
    fprintf(stderr, "------------------------------------------\n");
    while (count < 10 && i < h->n ) {
        val = gsl_histogram_get(h, i);
        if (val > 0) {
            gsl_histogram_get_range(h, i, &lower, &upper);
            fprintf(stderr, "%8.1f %8.1f %8.0f\n", lower, upper, val);
            count++;
        }
        i++;
    }
    fprintf(stderr, "------------------------------------------\n");
}

double
shift_and_get_entropy(const gsl_histogram *plus, const GArray *minus_a, int shift, double total)
{
    g_assert(shift >= 0);
    gsl_histogram *combined = gsl_histogram_clone(plus);

    /* add reads from GArray to cloned copy of plus strand reads,
     * shifting if required
     */
    double dshift = (double)shift; 
    for (unsigned int i = 0; i < minus_a->len; i++) {
        gsl_histogram_increment(combined, g_array_index(minus_a, double, i) - dshift);
    }
    
    double H = shannon_entropy(combined, total);
    gsl_histogram_free(combined);
    return H;
}

int
main (int argc, char **argv)
{
    if (argc < 6) {
        usage ();
        return 1;
    } 
    char *infile_name  = argv[1];
    char *chrom        = argv[2];
    int  bin_size      = atoi(argv[3]);
    int  min_shift     = atoi(argv[4]);
    int  max_shift     = atoi(argv[5]);
    if (bin_size == 0){
        fprintf(stderr, "%s is not a valid bin size\n", argv[4]);
        usage();
        return 1;
    }
    g_assert(max_shift > min_shift);

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
    GArray *minus_a;
    minus_a = g_array_sized_new(FALSE, TRUE, sizeof(double), 200000);
    g_assert(minus_a != NULL);

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
            g_array_append_val(minus_a, pos);
        } else {
            error_code=2;
            fprintf(stderr, "Strand identifier %c not allowed\n", strand);
            goto cleanup;
        }
    }

    /* overview of strands */
    double total_plus_reads = gsl_histogram_sum(plus);
    double total_minus_reads = (double)(minus_a->len);
    double total = total_plus_reads + total_minus_reads;
    fprintf(stderr, "plus strand reads: %.0lf\nminus strand reads: %.0lf\n",
            total_plus_reads,
            total_minus_reads);

    int entropy_min_shift = 0;
    double Hmin = 1000;
    double H;
    for (int i = min_shift; i <= max_shift; i++) {
        if (i % 50 == 0)
            fprintf(stderr, "%i  ", i);
        H = shift_and_get_entropy(plus, minus_a, i, total);    
        if (H < Hmin) {
            Hmin = H;
            entropy_min_shift = i;
        }

        printf("%i|%f|%s\n", i, H, chrom);
    }
    fprintf(stderr, "\nEntropy minimum at %i\n", entropy_min_shift);

    cleanup:
        gsl_histogram_free(plus);
        g_array_free(minus_a, TRUE);
        fclose(infile);
        return error_code;
}
