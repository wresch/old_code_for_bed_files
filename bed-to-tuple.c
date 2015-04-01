#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <gsl/gsl_ntuple.h>

const int buffsize = 1024;
typedef unsigned int uint;
typedef struct _segment 
{
    char chrom[6];
    uint start;
    uint end;
    char strand;
} Segment;
void usage ()
{
    printf("bed-to-tuple\n"
           "--------------------------------------------\n"
           "Usage:\n"
           "   bed-to-tuple bedfile outfile\n\n"
           "Read in a bed file and save it as a (more\n"
           "efficient) tuple file for later processing\n");
}
void print_segment(const Segment *seg)
{
    printf("%6s %i %i %c\n", seg->chrom, seg->start, seg->end, seg->strand);
}

int
main (int argc, char **argv)
{
    if (argc < 3) {
        usage ();
        return 1;
    } 
    char *infile_name  = argv[1];
    char *outfile_name = argv[2];
    printf("reading from %s\nwriting to %s\n", infile_name, outfile_name);

    FILE *infile = fopen(infile_name, "r");
    if (infile == NULL) {
        printf("Could not open infile %s\n", infile_name);
        return 1;
    }
    char buffer[buffsize + 1];
    Segment seg;
    int nr_parsed_items = 0;
    gsl_ntuple *ntuple 
          = gsl_ntuple_create (outfile_name, &seg, sizeof (seg));

    while (fgets(buffer, buffsize, infile) != NULL) {
        /* parse the line */
        nr_parsed_items = sscanf(buffer, "%5s %u %u %*s %*s %c", seg.chrom, &(seg.start), &(seg.end), &(seg.strand));
        /* write the tuple */
        //print_segment(&seg);
        gsl_ntuple_write(ntuple);
    }
    gsl_ntuple_close(ntuple);

}
