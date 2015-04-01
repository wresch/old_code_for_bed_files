/* C code produced by gperf version 3.0.4 */
/* Command-line: gperf -I -t -N get_chrom_info mm9_chrom_info.keys  */
/* Computed positions: -k'$' */

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

#line 1 "mm9_chrom_info.keys"
struct chrom_info {
    const char *name;
    long        length;
};
#include <string.h>

#define TOTAL_KEYWORDS 22
#define MIN_WORD_LENGTH 4
#define MAX_WORD_LENGTH 5
#define MIN_HASH_VALUE 4
#define MAX_HASH_VALUE 35
/* maximum key range = 32, duplicates = 0 */

static unsigned int
hash (str, len)
     register const char *str;
     register unsigned int len;
{
  static unsigned char asso_values[] =
    {
      36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
      36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
      36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
      36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
      36, 36, 36, 36, 36, 36, 36, 36, 13,  8,
       3, 30, 25, 20, 15, 10,  5,  0, 36, 36,
      36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
      36, 36, 36, 36, 36, 36, 36, 23, 36, 36,
      36, 36, 36, 36, 36, 36, 36, 36, 18, 13,
      36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
      36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
      36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
      36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
      36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
      36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
      36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
      36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
      36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
      36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
      36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
      36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
      36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
      36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
      36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
      36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
      36, 36, 36, 36, 36, 36
    };
  return len + asso_values[(unsigned char)str[len - 1]];
}

struct chrom_info *
get_chrom_info (str, len)
     register const char *str;
     register unsigned int len;
{
  static struct chrom_info wordlist[] =
    {
      {""}, {""}, {""}, {""},
#line 14 "mm9_chrom_info.keys"
      {"chr9",   124076172},
#line 24 "mm9_chrom_info.keys"
      {"chr19",  61342430},
      {""},
#line 7 "mm9_chrom_info.keys"
      {"chr2",   181748087},
#line 17 "mm9_chrom_info.keys"
      {"chr12",  121257530},
#line 13 "mm9_chrom_info.keys"
      {"chr8",   131738871},
#line 23 "mm9_chrom_info.keys"
      {"chr18",  90772031},
      {""},
#line 6 "mm9_chrom_info.keys"
      {"chr1",   197195432},
#line 16 "mm9_chrom_info.keys"
      {"chr11",  121843856},
#line 12 "mm9_chrom_info.keys"
      {"chr7",   152524553},
#line 22 "mm9_chrom_info.keys"
      {"chr17",  95272651},
      {""},
#line 26 "mm9_chrom_info.keys"
      {"chrY",   15902555},
#line 15 "mm9_chrom_info.keys"
      {"chr10",  129993255},
#line 11 "mm9_chrom_info.keys"
      {"chr6",   149517037},
#line 21 "mm9_chrom_info.keys"
      {"chr16",  98319150},
      {""},
#line 25 "mm9_chrom_info.keys"
      {"chrX",   166650296},
      {""},
#line 10 "mm9_chrom_info.keys"
      {"chr5",   152537259},
#line 20 "mm9_chrom_info.keys"
      {"chr15",  103494974},
      {""},
#line 27 "mm9_chrom_info.keys"
      {"chrM",   16299},
      {""},
#line 9 "mm9_chrom_info.keys"
      {"chr4",   155630120},
#line 19 "mm9_chrom_info.keys"
      {"chr14",  125194864},
      {""}, {""}, {""},
#line 8 "mm9_chrom_info.keys"
      {"chr3",   159599783},
#line 18 "mm9_chrom_info.keys"
      {"chr13",  120284312}
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
