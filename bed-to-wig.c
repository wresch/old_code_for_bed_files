#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <gsl/gsl_histogram.h>

const int buffsize = 2048;

/* these are from the gperf generated files for chromosome size lookup */
struct chrom_info {
    const char *name;
    long   length;
};
struct chrom_info* get_chrom_info (const char *str, unsigned int len);
/* gperf end */

void usage ()
{
    printf("bed-to-wig\n"
           "--------------------------------------------\n"
           "Usage:\n"
           "   bed-to-wig bedfile outfile binsize frag-size factor track_name\n\n"
           "Create a binned wiggle file for genome browser.i\n"
           "Factor, if given, determines the weight of each read\n");
}
gsl_histogram* get_hist_pointer(GHashTable *table, const char* chrom, int bin_size) 
{
    /* try to look up the histogram in the histogram table */
    gsl_histogram *hist = g_hash_table_lookup(table, chrom);
    /* If this chromosome has not been seen before */
    if (hist == NULL) {
        /* determine chromosome length and the number of bins in the histogram  */
        struct chrom_info *chromosome = get_chrom_info(chrom, strlen(chrom));
        if (chromosome == NULL) {
            fprintf(stderr, "Could not determine chromosome length for %s\n", chrom);
            return NULL;
        } 
        fprintf(stderr, "Seting up histogram for %s [%li nts]\n", chrom, chromosome->length);
        size_t number_of_bins = chromosome->length / bin_size + 1;
        double *ranges = malloc((number_of_bins + 1) * sizeof (double));
        g_assert(ranges != NULL);
        for (size_t i = 0; i < number_of_bins + 1; i++) 
            ranges[i] = (double)(i * bin_size);
        g_assert(ranges[number_of_bins] >= chromosome->length);
        
        /* setting up a new histogram */
        hist = gsl_histogram_alloc(number_of_bins);
        g_assert(hist != NULL);
        /* note: set_ranges resets all bins to 0 */
        gsl_histogram_set_ranges (hist, ranges, number_of_bins + 1);
        free(ranges);
        ranges = NULL;
        /* adding it to the hash table */ 
        g_hash_table_insert(table, g_strdup(chrom), hist);
    } 
    return hist;
}
void hist_hash_cleanup(gpointer chrom, gpointer hist, gpointer user_data)
{
    gsl_histogram *hist_c = hist;
    printf("Cleaning up item %s [%.0f total reads (scaled!)]\n", (char *)chrom, gsl_histogram_sum(hist_c));
    g_free((char *)chrom);
    gsl_histogram_free(hist_c);
}
void chrom_to_wig(gpointer chrom, gpointer hist, gpointer outfile)
{
    gsl_histogram *hist_cast    = (gsl_histogram *)hist;
    FILE          *outfile_cast = (FILE *)outfile;
    char          *chrom_cast   = (char *)chrom;
    /* get the binsize  */
    int bin_size = (int)(hist_cast->range[1] - hist_cast->range[0]);
    fprintf(outfile_cast, "variableStep chrom=%s span=%i\n", chrom_cast, bin_size);
    /* write only the bins that contain counts */
    double val   = 0.0;
    double lower = 0.0;
    double upper = 0.0;
    int retval   = 0;
    for (size_t i = 0; i < hist_cast->n; i++) {
        val = gsl_histogram_get(hist_cast, i);
        if (val > 0.0) {
            retval = gsl_histogram_get_range(hist_cast, i, &lower, &upper);
            /* Note: wiggle is 1-based! */
            fprintf(outfile_cast, "%i\t%.3f\n", (unsigned int)lower + 1, val);
        }
    }
}

int make_wiggle_file(GHashTable *histograms, const char *track_name, const char* outfile_name)
{
    /* try to open outfile name */
    FILE *outfile = fopen(outfile_name, "w");
    if (outfile == NULL) {
        fprintf(stderr, "Could not open %s for output\n", outfile_name);
        return 1;
    }
    /* track header */
    fprintf(outfile, "track type=wiggle_0 name=%s visibility=full alwaysZero=on\n", track_name);

    /* process each chromosome */
    g_hash_table_foreach(histograms, chrom_to_wig, (gpointer)outfile);
    fclose(outfile);
    return 0;
}


int
main (int argc, char **argv)
{
    if (argc < 7) {
        usage ();
        return 1;
    } 
    char *infile_name  = argv[1];
    char *outfile_name = argv[2];
    int   bin_size     = atoi(argv[3]);
    g_assert(bin_size > 0);
    int   frag_size    = atoi(argv[4]);
    int   shift_size   = frag_size / 2;

    printf("reading from %s\nwriting to %s\n", infile_name, outfile_name);
    printf("binsize: %i\n", bin_size);
    double factor = atof(argv[5]);
    char *track_name = argv[6];


    FILE *infile = fopen(infile_name, "r");
    if (infile == NULL) {
        printf("Could not open infile %s\n", infile_name);
        return 1;
    }
    
    char buffer[buffsize + 1];
    GHashTable *histograms = g_hash_table_new( g_str_hash, g_str_equal);
    gsl_histogram *hist = NULL;

    char chrom[10];
    unsigned int start0 = 0;
    unsigned int end1   = 0;
    unsigned int pos    = 0;
    char strand = 'x';
    int converted    = 0;
    int retval       = 0;
    int error_code   = 0;

    while (fgets(buffer, buffsize, infile) != NULL) {
        /* determine the chromosome and position*/
        converted = sscanf(buffer, "%s %u %u %*s %*s %c", chrom, &start0, &end1, &strand);
        /* ignore chrom M */
        if (strcmp(chrom, "chrM") == 0) {
            continue;
        }

        g_assert(converted == 4);
        if (strand == '+') {
            pos = start0 + shift_size;
        } else {
            if (strand == '-') {
                if (end1 > shift_size) {
                    pos = end1 - shift_size;
                } else {
                    continue;
                }
            } else {
                // bad strand!
                fprintf(stderr, "Bad strand identifier: %c", strand);
                exit(1);
            }
        }
     
        
        /* get a hist pointer for the chromosome and increment the bin by factor */
        hist = get_hist_pointer(histograms, chrom, bin_size);
        if (hist != NULL) {
            retval = gsl_histogram_accumulate(hist, (double)pos, factor);
            g_assert(retval == 0);
        } else {
            printf("Could not obtain histogram pointer\n");
            error_code = 1;
            goto cleanup;
        }
    }

    error_code = make_wiggle_file(histograms, track_name, outfile_name);

    cleanup:
        g_hash_table_foreach(histograms, hist_hash_cleanup, NULL);
        g_hash_table_destroy(histograms);
        fclose(infile);
        return error_code;
}
