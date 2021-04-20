/*
 * Author: Cristian Merli
 * Code title: Exercise 7 (Vectors 1) library
 * Code version: 3.0
 * Creation date: 20/04/2021
 * Last mod. date: 20/04/2021
 */


/* Libraries import */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <string.h>                                                                                         // String library inclusion (for strcpy ecc.)


/* Constants declaration and definition */
const char *R = "\033[0;31m";                                                                               // Red color
const char *B = "\033[0;34m";                                                                               // Blue color
const char *LB = "\033[1;34m";                                                                              // Light blue color
const char *P = "\033[0;35m";                                                                               // Purple color
const char *C = "\033[0;36m";                                                                               // Cyan color
const char *Y = "\033[1;33m";                                                                               // Yellow color
const char *O = "\033[0;33m";                                                                               // Orange color
const char *G = "\033[0;32m";                                                                               // Green color
const char *LGN = "\033[1;32m";                                                                             // Light green color
const char *LGY = "\033[0;37m";                                                                             // Light gray color
const char *E = "\033[0m";                                                                                  // End color


/* Enums declaration and definition */
enum coords                                                                                                 // Matrix/vectors enum
{
    v = 0,                                                                                                  // Vectors
    vow = 4                                                                                                 // Vowels
};


/* Data-types declaration and definition */
typedef unsigned char   byte;                                                                               // Unsigned char alias (byte)
typedef unsigned short  u_shrt;                                                                             // Unsigned short alias (u_shrt)
typedef short           shrt;                                                                               // Short alias (shrt)
typedef double          real;                                                                               // Double alias (real)


/* Functions declaration and definition */
static u_shrt iaddr(u_shrt i, u_shrt j, u_shrt lda){                                                        // Arrays/vectors memo addressing
  /* Function body */
  return (i*lda)+j;                                                                                         // Return index number
}

real vect_comp_sum(real *vect_sum, int size){                                                               // Vector components sum function
  /* Function body */
  real sum = *vect_sum;                                                                                     // Sum var declaration and defintion as first vect component val
  for (byte i = 1; i < size; ++i){                                                                          // Linear vectors components sum FOR cycle 
    sum += *(vect_sum+iaddr(v, i, size));                                                                   // Incremental add
  }
  if (sum >= 0){                                                                                            // Case positive sum (or null)
    return sum;                                                                                             // Return sum val
  } else {                                                                                                  // Case negative sum
    return -1;                                                                                              // Return -1 val
  }
}

void count_vowels(char *str_in, u_shrt size){                                                               // Count vowels in string function
  enum vowels { a, e, i, o, u };                                                                            // Vowels enum declaration and definition
  byte vow_cnt[iaddr(v, 5, 5)];                                                                             // Array of vowels counters declaration
  byte idx = 0;                                                                                             // While-loop iterations index declaration and definition
  char str_tmp[iaddr(vow, 16, 16)];                                                                         // Patrial output tmp string array
  char str_out[iaddr(v, size, size)];                                                                       // Output string

  for (byte j = 0; j < 5; ++j){                                                                             // Array of vowels counters reset FOR cycle
    *(vow_cnt+iaddr(v, j, 5)) = 0;                                                                          // Array of vowels counters, values init to 0
  }
  for (u_shrt j = 0; j < size; ++j){                                                                        // Output string value init
    *(str_out+iaddr(v, j, size)) = 0;                                                                       // Reset string memo
  }
  for (u_shrt j = 0; j < iaddr(vow, 16, 16); ++j){                                                          // Tmp vowels partial out strings in array value init
    *(str_tmp+iaddr(v, j, iaddr(vow, 16, 16))) = 0;                                                         // Reset string memo
  }

  while (*(vow_cnt+iaddr(v, idx, 5)) != '\n'){                                                              // Input syytring char array scan FOR cycle
    switch (*(str_in+iaddr(v, idx, 5))){                                                                    // Case depending on each string letter (not case-sensitive)
      case 'a':                                                                                             // Case letter 'a'
        ++*(vow_cnt+iaddr(v, a, 5));                                                                        // Increment letter 'a' counter in vowels counters array
        break;
      case 'A':                                                                                             // Case letter 'A'
        ++*(vow_cnt+iaddr(v, a, 5));                                                                        // Increment letter 'a' counter in vowels counters array
        break;
      case 'e':                                                                                             // Case letter 'e'
        ++*(vow_cnt+iaddr(v, e, 5));                                                                        // Increment letter 'e' counter in vowels counters array
        break;
      case 'E':                                                                                             // Case letter 'E'
        ++*(vow_cnt+iaddr(v, e, 5));                                                                        // Increment letter 'e' counter in vowels counters array
        break;
      case 'i':                                                                                             // Case letter 'i'
        ++*(vow_cnt+iaddr(v, i, 5));                                                                        // Increment letter 'i' counter in vowels counters array
        break;
      case 'I':                                                                                             // Case letter 'I'
        ++*(vow_cnt+iaddr(v, i, 5));                                                                        // Increment letter 'i' counter in vowels counters array
        break;
      case 'o':                                                                                             // Case letter 'o'
        ++*(vow_cnt+iaddr(v, o, 5));                                                                        // Increment letter 'o' counter in vowels counters array
        break;
      case 'O':                                                                                             // Case letter 'O'
        ++*(vow_cnt+iaddr(v, o, 5));                                                                        // Increment letter 'o' counter in vowels counters array
        break;
      case 'u':                                                                                             // Case letter 'u'
        ++*(vow_cnt+iaddr(v, u, 5));                                                                        // Increment letter 'u' counter in vowels counters array
        break;
      case 'U':                                                                                             // Case letter 'U'
        ++*(vow_cnt+iaddr(v, u, 5));                                                                        // Increment letter 'u' counter in vowels counters array
    }
    ++idx;                                                                                                  // While-loop iterations index val upd
  }

  for (u_shrt j = size-1; j > 1; --j){                                                                      // Scan input string to remove '\n' char FOR cycle
    if (*(str_in+iaddr(v, j, size)) == '\n'){                                                               // If current string char is equal to '\n'
      *(str_in+iaddr(v, j, size)) = 0;                                                                      // Remove char
      break;                                                                                                // Exit FOR cycle
    }
  }

  if (*(vow_cnt+iaddr(v, a, 5)) != 0)                                                                       // Case a counter != 0
      snprintf((str_tmp+iaddr(a, 0, 16)), 16, " %hu A,", *(vow_cnt+iaddr(v, a, 5)));                        // Popolate tmp 'a' partial out string in array
  if (*(vow_cnt+iaddr(v, e, 5)) != 0)                                                                       // Case e counter != 0
      snprintf((str_tmp+iaddr(e, 0, 16)), 16, " %hu E,", *(vow_cnt+iaddr(v, e, 5)));                        // Popolate tmp 'e' partial out string in array
  if (*(vow_cnt+iaddr(v, i, 5)) != 0)                                                                       // Case i counter != 0
      snprintf((str_tmp+iaddr(i, 0, 16)), 16, " %hu I,", *(vow_cnt+iaddr(v, i, 5)));                        // Popolate tmp 'i' partial out string in array
  if (*(vow_cnt+iaddr(v, o, 5)) != 0)                                                                       // Case o counter != 0
      snprintf((str_tmp+iaddr(o, 0, 16)), 16, " %hu O,", *(vow_cnt+iaddr(v, o, 5)));                        // Popolate tmp 'o' partial out string in array
  if (*(vow_cnt+iaddr(v, u, 5)) != 0)                                                                       // Case o counter != 0
      snprintf((str_tmp+iaddr(u, 0, 16)), 16, " %hu U,", *(vow_cnt+iaddr(v, u, 5)));                        // Popolate tmp 'o' partial out string in array

  snprintf(str_out, sizeof(str_out), "Nella stringa \"%s\" ci sono%s%s%s%s%s", str_in,
           str_tmp+iaddr(a, 0, 16), str_tmp+iaddr(e, 0, 16), str_tmp+iaddr(i, 0, 16),
           str_tmp+iaddr(o, 0, 16), str_tmp+iaddr(u, 0, 16));                                               // Concatenate strings

  for (u_shrt j = size-1; j > 1; --j){                                                                      // Scan output string to remove last ',' char FOR cycle (starting from the end of the string)
    if (*(str_out+iaddr(v, j, size)) == ','){                                                               // If current output string char is equal to ','
      *(str_out+iaddr(v, j, size)) = 0;                                                                     // Remove char
      break;                                                                                                // Exit FOR cycle
    }
  }

  strcpy(str_in, str_out);                                                                                  // Copy out str in input str
}
