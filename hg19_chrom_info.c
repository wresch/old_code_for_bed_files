/* C code produced by gperf version 3.0.4 */
/* Command-line: gperf -d -I -t -N get_chrom_info hg19_chrom_info.keys  */
/* Computed positions: -k'4-5,13-14' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 1 "hg19_chrom_info.keys"
struct chrom_info {
    const char *name;
    long        length;
};
#include <string.h>

#define TOTAL_KEYWORDS 93
#define MIN_WORD_LENGTH 4
#define MAX_WORD_LENGTH 21
#define MIN_HASH_VALUE 4
#define MAX_HASH_VALUE 235
/* maximum key range = 232, duplicates = 0 */

static unsigned int
hash (str, len)
     register const char *str;
     register unsigned int len;
{
  static unsigned char asso_values[] =
    {
      236, 236, 236, 236, 236, 236, 236, 236, 236, 236,
      236, 236, 236, 236, 236, 236, 236, 236, 236, 236,
      236, 236, 236, 236, 236, 236, 236, 236, 236, 236,
      236, 236, 236, 236, 236, 236, 236, 236, 236, 236,
      236, 236, 236, 236, 236, 236, 236, 236,   5,   0,
        5,  25,  15,   2, 105,  42,  75,  45, 112,  72,
       34,   4, 236, 236, 236, 236, 236, 236, 236, 236,
      236, 236, 236, 236, 236, 236, 236,  35, 236, 236,
      236, 236, 236, 236, 236,   0, 236, 236,  20,  10,
      236, 236, 236, 236, 236, 236, 236,   5, 236,  30,
      236, 236, 236, 236, 236, 236, 236, 236, 236, 236,
      236, 236,   0, 236, 236, 236,   0, 236, 236, 236,
      236, 236, 236, 236, 236, 236, 236, 236, 236, 236,
      236, 236, 236, 236, 236, 236, 236, 236, 236, 236,
      236, 236, 236, 236, 236, 236, 236, 236, 236, 236,
      236, 236, 236, 236, 236, 236, 236, 236, 236, 236,
      236, 236, 236, 236, 236, 236, 236, 236, 236, 236,
      236, 236, 236, 236, 236, 236, 236, 236, 236, 236,
      236, 236, 236, 236, 236, 236, 236, 236, 236, 236,
      236, 236, 236, 236, 236, 236, 236, 236, 236, 236,
      236, 236, 236, 236, 236, 236, 236, 236, 236, 236,
      236, 236, 236, 236, 236, 236, 236, 236, 236, 236,
      236, 236, 236, 236, 236, 236, 236, 236, 236, 236,
      236, 236, 236, 236, 236, 236, 236, 236, 236, 236,
      236, 236, 236, 236, 236, 236, 236, 236, 236, 236,
      236, 236, 236, 236, 236, 236, 236, 236, 236, 236
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[13]+4];
      /*FALLTHROUGH*/
      case 13:
        hval += asso_values[(unsigned char)str[12]];
      /*FALLTHROUGH*/
      case 12:
      case 11:
      case 10:
      case 9:
      case 8:
      case 7:
      case 6:
      case 5:
        hval += asso_values[(unsigned char)str[4]+2];
      /*FALLTHROUGH*/
      case 4:
        hval += asso_values[(unsigned char)str[3]];
        break;
    }
  return hval;
}

struct chrom_info *
get_chrom_info (str, len)
     register const char *str;
     register unsigned int len;
{
  static struct chrom_info wordlist[] =
    {
      {""}, {""}, {""}, {""},
#line 6 "hg19_chrom_info.keys"
      {"chr1",   249250621} /* hash value = 4, index = 4 */,
      {""},
#line 10 "hg19_chrom_info.keys"
      {"chr5",   180915260} /* hash value = 6, index = 6 */,
#line 19 "hg19_chrom_info.keys"
      {"chr13",   115169878} /* hash value = 7, index = 7 */,
      {""},
#line 7 "hg19_chrom_info.keys"
      {"chr2",   243199373} /* hash value = 9, index = 9 */,
#line 16 "hg19_chrom_info.keys"
      {"chr10",   135534747} /* hash value = 10, index = 10 */,
      {""}, {""}, {""},
#line 26 "hg19_chrom_info.keys"
      {"chrY",   59373566} /* hash value = 14, index = 14 */,
#line 25 "hg19_chrom_info.keys"
      {"chr20",   63025520} /* hash value = 15, index = 15 */,
#line 55 "hg19_chrom_info.keys"
      {"chrUn_gl000211",   166566} /* hash value = 16, index = 16 */,
      {""},
#line 49 "hg19_chrom_info.keys"
      {"chrUn_gl000219",   179198} /* hash value = 18, index = 18 */,
#line 9 "hg19_chrom_info.keys"
      {"chr4",   191154276} /* hash value = 19, index = 19 */,
#line 18 "hg19_chrom_info.keys"
      {"chr12",   133851895} /* hash value = 20, index = 20 */,
#line 60 "hg19_chrom_info.keys"
      {"chrUn_gl000221",   155397} /* hash value = 21, index = 21 */,
      {""},
#line 95 "hg19_chrom_info.keys"
      {"chrUn_gl000229",   19913} /* hash value = 23, index = 23 */,
#line 13 "hg19_chrom_info.keys"
      {"chrX",   155270560} /* hash value = 24, index = 24 */,
#line 28 "hg19_chrom_info.keys"
      {"chr22",   51304566} /* hash value = 25, index = 25 */,
      {""}, {""}, {""},
#line 8 "hg19_chrom_info.keys"
      {"chr3",   198022430} /* hash value = 29, index = 29 */,
#line 17 "hg19_chrom_info.keys"
      {"chr11",   135006516} /* hash value = 30, index = 30 */,
#line 73 "hg19_chrom_info.keys"
      {"chrUn_gl000241",   42152} /* hash value = 31, index = 31 */,
      {""},
#line 84 "hg19_chrom_info.keys"
      {"chrUn_gl000249",   38502} /* hash value = 33, index = 33 */,
#line 57 "hg19_chrom_info.keys"
      {"chrUn_gl000220",   161802} /* hash value = 34, index = 34 */,
#line 29 "hg19_chrom_info.keys"
      {"chr21",   48129895} /* hash value = 35, index = 35 */,
#line 38 "hg19_chrom_info.keys"
      {"chr4_ctg9_hap1",   590426} /* hash value = 36, index = 36 */,
      {""}, {""},
#line 96 "hg19_chrom_info.keys"
      {"chrM",   16571} /* hash value = 39, index = 39 */,
      {""},
#line 94 "hg19_chrom_info.keys"
      {"chrUn_gl000231",   27386} /* hash value = 41, index = 41 */,
      {""},
#line 92 "hg19_chrom_info.keys"
      {"chrUn_gl000239",   33824} /* hash value = 43, index = 43 */,
#line 75 "hg19_chrom_info.keys"
      {"chrUn_gl000240",   41933} /* hash value = 44, index = 44 */,
      {""},
#line 12 "hg19_chrom_info.keys"
      {"chr7",   159138663} /* hash value = 46, index = 46 */,
#line 21 "hg19_chrom_info.keys"
      {"chr15",   102531392} /* hash value = 47, index = 47 */,
#line 58 "hg19_chrom_info.keys"
      {"chrUn_gl000218",   161147} /* hash value = 48, index = 48 */,
#line 15 "hg19_chrom_info.keys"
      {"chr9",   141213431} /* hash value = 49, index = 49 */,
#line 23 "hg19_chrom_info.keys"
      {"chr17",   81195210} /* hash value = 50, index = 50 */,
      {""}, {""},
#line 62 "hg19_chrom_info.keys"
      {"chrUn_gl000228",   129120} /* hash value = 53, index = 53 */,
#line 70 "hg19_chrom_info.keys"
      {"chrUn_gl000230",   43691} /* hash value = 54, index = 54 */,
#line 64 "hg19_chrom_info.keys"
      {"chr1_gl000191_random",   106433} /* hash value = 55, index = 55 */,
#line 56 "hg19_chrom_info.keys"
      {"chrUn_gl000213",   164239} /* hash value = 56, index = 56 */,
      {""}, {""},
#line 51 "hg19_chrom_info.keys"
      {"chrUn_gl000215",   172545} /* hash value = 59, index = 59 */,
#line 39 "hg19_chrom_info.keys"
      {"chr1_gl000192_random",   547496} /* hash value = 60, index = 60 */,
#line 47 "hg19_chrom_info.keys"
      {"chrUn_gl000223",   180455} /* hash value = 61, index = 61 */,
      {""},
#line 82 "hg19_chrom_info.keys"
      {"chrUn_gl000248",   39786} /* hash value = 63, index = 63 */,
#line 40 "hg19_chrom_info.keys"
      {"chrUn_gl000225",   211173} /* hash value = 64, index = 64 */,
#line 37 "hg19_chrom_info.keys"
      {"chr17_ctg5_hap1",   1680828} /* hash value = 65, index = 65 */,
#line 93 "hg19_chrom_info.keys"
      {"chr21_gl000210_random",   27682} /* hash value = 66, index = 66 */,
      {""}, {""}, {""}, {""},
#line 72 "hg19_chrom_info.keys"
      {"chrUn_gl000243",   43341} /* hash value = 71, index = 71 */,
      {""},
#line 80 "hg19_chrom_info.keys"
      {"chrUn_gl000238",   39939} /* hash value = 73, index = 73 */,
#line 88 "hg19_chrom_info.keys"
      {"chrUn_gl000245",   36651} /* hash value = 74, index = 74 */,
      {""}, {""},
#line 27 "hg19_chrom_info.keys"
      {"chr19",   59128983} /* hash value = 77, index = 77 */,
      {""},
#line 14 "hg19_chrom_info.keys"
      {"chr8",   146364022} /* hash value = 79, index = 79 */,
#line 22 "hg19_chrom_info.keys"
      {"chr16",   90354753} /* hash value = 80, index = 80 */,
#line 68 "hg19_chrom_info.keys"
      {"chrUn_gl000233",   45941} /* hash value = 81, index = 81 */,
      {""}, {""},
#line 91 "hg19_chrom_info.keys"
      {"chrUn_gl000235",   34474} /* hash value = 84, index = 84 */,
#line 41 "hg19_chrom_info.keys"
      {"chr4_gl000194_random",   191469} /* hash value = 85, index = 85 */,
#line 53 "hg19_chrom_info.keys"
      {"chrUn_gl000217",   172149} /* hash value = 86, index = 86 */,
      {""}, {""},
#line 61 "hg19_chrom_info.keys"
      {"chrUn_gl000214",   137718} /* hash value = 89, index = 89 */,
      {""},
#line 63 "hg19_chrom_info.keys"
      {"chrUn_gl000227",   128374} /* hash value = 91, index = 91 */,
      {""}, {""},
#line 48 "hg19_chrom_info.keys"
      {"chrUn_gl000224",   179693} /* hash value = 94, index = 94 */,
#line 42 "hg19_chrom_info.keys"
      {"chr4_gl000193_random",   189789} /* hash value = 95, index = 95 */,
      {""}, {""}, {""},
#line 46 "hg19_chrom_info.keys"
      {"chr7_gl000195_random",   182896} /* hash value = 99, index = 99 */,
#line 90 "hg19_chrom_info.keys"
      {"chr9_gl000201_random",   36148} /* hash value = 100, index = 100 */,
#line 89 "hg19_chrom_info.keys"
      {"chrUn_gl000247",   36422} /* hash value = 101, index = 101 */,
#line 59 "hg19_chrom_info.keys"
      {"chr19_gl000209_random",   159169} /* hash value = 102, index = 102 */,
      {""},
#line 81 "hg19_chrom_info.keys"
      {"chrUn_gl000244",   39929} /* hash value = 104, index = 104 */,
#line 43 "hg19_chrom_info.keys"
      {"chr9_gl000200_random",   187035} /* hash value = 105, index = 105 */,
      {""}, {""}, {""},
#line 11 "hg19_chrom_info.keys"
      {"chr6",   171115067} /* hash value = 109, index = 109 */,
#line 20 "hg19_chrom_info.keys"
      {"chr14",   107349540} /* hash value = 110, index = 110 */,
#line 69 "hg19_chrom_info.keys"
      {"chrUn_gl000237",   45867} /* hash value = 111, index = 111 */,
      {""},
#line 86 "hg19_chrom_info.keys"
      {"chr17_gl000203_random",   37498} /* hash value = 113, index = 113 */,
#line 78 "hg19_chrom_info.keys"
      {"chrUn_gl000234",   40531} /* hash value = 114, index = 114 */,
      {""},
#line 50 "hg19_chrom_info.keys"
      {"chr17_gl000205_random",   174588} /* hash value = 116, index = 116 */,
#line 24 "hg19_chrom_info.keys"
      {"chr18",   78077248} /* hash value = 117, index = 117 */,
      {""},
#line 45 "hg19_chrom_info.keys"
      {"chrUn_gl000212",   186858} /* hash value = 119, index = 119 */,
      {""}, {""}, {""},
#line 34 "hg19_chrom_info.keys"
      {"chr6_apd_hap1",   4622290} /* hash value = 123, index = 123 */,
#line 44 "hg19_chrom_info.keys"
      {"chrUn_gl000222",   186861} /* hash value = 124, index = 124 */,
#line 31 "hg19_chrom_info.keys"
      {"chr6_mcf_hap5",   4833398} /* hash value = 125, index = 125 */,
#line 52 "hg19_chrom_info.keys"
      {"chrUn_gl000216",   172294} /* hash value = 126, index = 126 */,
      {""},
#line 32 "hg19_chrom_info.keys"
      {"chr6_cox_hap2",   4795371} /* hash value = 128, index = 128 */,
      {""}, {""},
#line 97 "hg19_chrom_info.keys"
      {"chrUn_gl000226",   15008} /* hash value = 131, index = 131 */,
#line 65 "hg19_chrom_info.keys"
      {"chr19_gl000208_random",   92689} /* hash value = 132, index = 132 */,
      {""},
#line 71 "hg19_chrom_info.keys"
      {"chrUn_gl000242",   43523} /* hash value = 134, index = 134 */,
      {""}, {""}, {""}, {""}, {""}, {""},
#line 85 "hg19_chrom_info.keys"
      {"chrUn_gl000246",   38154} /* hash value = 141, index = 141 */,
      {""}, {""},
#line 77 "hg19_chrom_info.keys"
      {"chrUn_gl000232",   40652} /* hash value = 144, index = 144 */,
#line 54 "hg19_chrom_info.keys"
      {"chr9_gl000199_random",   169874} /* hash value = 145, index = 145 */,
#line 67 "hg19_chrom_info.keys"
      {"chr17_gl000204_random",   81310} /* hash value = 146, index = 146 */,
      {""},
#line 36 "hg19_chrom_info.keys"
      {"chr6_dbb_hap3",   4610396} /* hash value = 148, index = 148 */,
      {""}, {""},
#line 74 "hg19_chrom_info.keys"
      {"chrUn_gl000236",   41934} /* hash value = 151, index = 151 */,
      {""}, {""}, {""}, {""},
#line 79 "hg19_chrom_info.keys"
      {"chr11_gl000202_random",   40103} /* hash value = 156, index = 156 */,
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""},
#line 87 "hg19_chrom_info.keys"
      {"chr8_gl000197_random",   37175} /* hash value = 172, index = 172 */,
      {""}, {""},
#line 66 "hg19_chrom_info.keys"
      {"chr9_gl000198_random",   90085} /* hash value = 175, index = 175 */,
      {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 76 "hg19_chrom_info.keys"
      {"chr17_gl000206_random",   41001} /* hash value = 183, index = 183 */,
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""},
#line 30 "hg19_chrom_info.keys"
      {"chr6_ssto_hap7",   4928567} /* hash value = 196, index = 196 */,
      {""}, {""},
#line 33 "hg19_chrom_info.keys"
      {"chr6_mann_hap4",   4683263} /* hash value = 199, index = 199 */,
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""},
#line 98 "hg19_chrom_info.keys"
      {"chr18_gl000207_random",   4262} /* hash value = 210, index = 210 */,
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 35 "hg19_chrom_info.keys"
      {"chr6_qbl_hap6",   4611984} /* hash value = 228, index = 228 */,
      {""}, {""}, {""}, {""}, {""}, {""},
#line 83 "hg19_chrom_info.keys"
      {"chr8_gl000196_random",   38914} /* hash value = 235, index = 235 */
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = wordlist[key].name;

          if (*str == *s && !strcmp (str + 1, s + 1))
            return &wordlist[key];
        }
    }
  return 0;
}
