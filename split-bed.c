#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

const int buffsize = 1024;

void usage ()
{
    printf("split-bed\n"
           "--------------------------------------------\n"
           "Usage:\n"
           "   split-bed bedfile dest-dir\n\n"
           "Split bed file into separate files for each\n"
           "chromosome\n");
}
FILE* get_file_pointer(GHashTable *table, const char* chrom, const char* path) 
{
    FILE *file = g_hash_table_lookup(table, chrom);
    if (file == NULL) {
        char file_path[100]; 
        int untruncated_size = snprintf(file_path, 99, "%s/%s.bed", path, chrom);
        g_assert(untruncated_size < 100);
        printf("file %s does not exist yet - creating it now", file_path);
        file = fopen(file_path, "w");
        printf(" [%p]\n", (void *)file);
        if (file == NULL) {
            printf("could not create file %s\n", file_path);
        } else {
            g_hash_table_insert(table, g_strdup(chrom), file);
        }
    } 
    return file;
}
void files_hash_cleanup(gpointer chrom, gpointer file, gpointer user_data)
{
    printf("Cleaning up item %s --> %p\n", (char *)chrom, file);
    g_free((char *)chrom);
    fclose((FILE *)file);
}

int
main (int argc, char **argv)
{
    if (argc < 3) {
        usage ();
        return 1;
    } 
    char *infile_name  = argv[1];
    char *out_dir      = argv[2];
    printf("reading from %s\nwriting to %s\n", infile_name, out_dir);

    FILE *infile = fopen(infile_name, "r");
    if (infile == NULL) {
        printf("Could not open infile %s\n", infile_name);
        return 1;
    }
    int dir_test = 0;
    char cmd[buffsize + 1];
    int untruncated_size = 0;
    untruncated_size = snprintf(cmd, buffsize, 
            "test ! -d %s && mkdir %s", out_dir, out_dir);
    if (untruncated_size > buffsize) {
        printf("length of output dir path is too long\n");
        return 1;
    }
        
    dir_test = system(cmd);
    if (dir_test == 0)
        printf("created directory %s\n", out_dir);
    else
        printf("using existing directory %s\n", out_dir);
    int error_code = 0;
    char buffer[buffsize + 1];
    GHashTable *files = g_hash_table_new( g_str_hash, g_str_equal);
    FILE *file = NULL;
    while (fgets(buffer, buffsize, infile) != NULL) {
        /* determine the chromosome */
        int first_white = strcspn(buffer, " \t");
        g_assert(first_white < 6);
        char chrom[6] = "";
        strncat(chrom, buffer, first_white);
        
        /* get a file pointer for the chromosome */
        file = get_file_pointer(files, chrom, out_dir);
        if (file != NULL) {
            fprintf(file, buffer);
            //printf("%s --> %p\n", chrom, (void *)file);
        } else {
            printf("Could not obtain file pointer\n");
            error_code = 1;
            goto cleanup;
        }
    }

    cleanup:
        g_hash_table_foreach(files, files_hash_cleanup, NULL);
        g_hash_table_destroy(files);
        return error_code;
}
