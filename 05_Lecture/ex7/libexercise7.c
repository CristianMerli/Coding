/*
 * Author: Cristian Merli
 * Code title: Exercise 7 (Vectors 1) library
 * Code version: 3.0
 * Creation date: 20/04/2021
 * Last mod. date: 20/04/2021
 */


/* Libraries import */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <stdlib.h>                                                                                         // Standard library inclusion (for atof ecc.)
#include <string.h>                                                                                         // String library inclusion (for strcpy ecc.)
#include <sys/ioctl.h>                                                                                      // System I/O control library inclusion (for ioctl ecc.)
#include <unistd.h>                                                                                         // UniStd library inclusion (for stdout ecc.)
#include "libexercise7.h"                                                                                   // Library for exercise 7 import header file


/* Functions declaration and definition */
void logo(const byte start_sp, const char *txt, const char *txt_col, const char bkg_chr,
          const char *bkg_col){                                                                             // Print responsive-logo function
  /* Function body */
  struct winsize w;                                                                                         // Window-size struct declaration
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);                                                                     // Save the number of terminal's rows/cloumns in window-size struct
  byte vthck = (w.ws_row / 5);                                                                              // Logo bkg vertical thickness calc
  byte lthck = (w.ws_col / 6);                                                                              // Logo bkg lateral thickness calc
  byte lsp = (w.ws_col - 2*lthck - 2*start_sp - strlen(txt)) / 2;                                           // Logo internal lateral spaces calc
  byte len = 2*lthck+2*lsp+strlen(txt);                                                                     // Logo length calc

  printf("\n%s", bkg_col);                                                                                  // New line fbk
  for (byte i = 0; i < (4*vthck+1); ++i){                                                                   // Logo lines print FOR cycle
    for (byte j = 0; j < start_sp; ++j){                                                                    // Initial spaces print FOR cycle
      printf(" ");                                                                                          // Print initial spaces
    }
    if ((i < vthck || i > (3*vthck)) && (i != (4*vthck)/2)){                                                // Full bkg logo lines print cond
      for (byte h = 0; h < len; ++h){                                                                       // Full bkg logo lines print FOR cycle
        printf("%c", bkg_chr);                                                                              // Bkg logo char print
      }
      printf("\n");                                                                                         // New line fbk
    } else if ((i >= vthck && i <= (3*vthck)) && (i != (4*vthck)/2)) {                                      // Partial-empty bkg logo lines print cond
      for (byte l = 0; l < lthck; ++l){                                                                     // Partial-empty bkg logo lines, initial full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Partial-empty bkg logo lines, initial full part print
      }
      for (byte m = 0; m < (len - 2*lthck); ++m){                                                           // Partial-empty bkg logo lines, central empty part print FOR cycle
        printf(" ");                                                                                        // Partial-empty bkg logo lines, central empty part print
      }
      for (byte n = 0; n < lthck; ++n){                                                                     // Partial-empty bkg logo lines, final full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Partial-empty bkg logo lines, final full part print
      }
      printf("\n");                                                                                         // New line fbk
    } else if (i == ((4*vthck)/2)) {                                                                        // Text logo line initial full part print cond
      for (byte o = 0; o < lthck; ++o){                                                                     // Text logo line initial full part print FOR cycle
        printf("%C", bkg_chr);                                                                              // Text logo line initial full part print
      }
      for (byte p = 0; p < lsp; ++p){                                                                       // Text logo line central empty part print FOR cycle
        printf(" ");                                                                                        // Text logo line central empty part print
      }
      printf("%s%s%s", txt_col, txt, bkg_col);                                                              // Text logo line central text part print
      for (byte q = 0; q < lsp; ++q){                                                                       // Text logo line central empty part print FOR cycle
        printf(" ");                                                                                        // Text logo line central empty part print
      }
      for (byte r = 0; r < lthck; ++r){                                                                     // Text logo line final full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Text logo line final full part print
      }
      printf("\n");                                                                                         // New line fbk
    }
  }
  printf("\033[0m\n");                                                                                      // New line fbk and erase logo bkg color
}


u_shrt iaddr(u_shrt i, u_shrt j, u_shrt lda){                                                               // Arrays/vectors memo addressing
  /* Function body */
  return (i*lda)+j;                                                                                         // Return index number
}


real vect_comp_sum(real *vect_sum, int size){                                                               // Vector components sum function
  /* Function body */
  real sum = *vect_sum;                                                                                     // Sum var declaration and defintion as first vect component val
  for (byte i = 1; i < size; ++i){                                                                          // Linear vectors components sum FOR cycle 
    sum += *(vect_sum+iaddr(V, i, size));                                                                   // Incremental add
  }
  if (sum >= 0){                                                                                            // Case positive sum (or null)
    return sum;                                                                                             // Return sum val
  } else {                                                                                                  // Case negative sum
    return -1;                                                                                              // Return -1 val
  }
}


void count_vowels(char *str_in, u_shrt size){                                                               // Count vowels in string function
  /* Function body */
  enum vowels { A, E, I, O, U };                                                                            // Vowels enum declaration and definition
  byte vow_cnt[iaddr(V, 5, 5)];                                                                             // Array of vowels counters declaration
  byte idx = 0;                                                                                             // While-loop iterations index declaration and definition
  char str_tmp[iaddr(VOW, 16, 16)];                                                                         // Patrial output tmp string array
  char str_out[iaddr(V, size, size)];                                                                       // Output string

  for (byte j = 0; j < 5; ++j)                                                                              // Array of vowels counters reset FOR cycle
    *(vow_cnt+iaddr(V, j, 5)) = 0;                                                                          // Array of vowels counters, values init to 0
  for (u_shrt j = 0; j < size; ++j)                                                                         // Output string value init
    *(str_out+iaddr(V, j, size)) = 0;                                                                       // Reset string memo
  for (u_shrt j = 0; j < iaddr(VOW, 16, 16); ++j)                                                           // Tmp vowels partial out strings in array value init
    *(str_tmp+iaddr(V, j, iaddr(VOW, 16, 16))) = 0;                                                         // Reset string memo

  while (*(vow_cnt+iaddr(V, idx, 5)) != '\n'){                                                              // Input syytring char array scan FOR cycle
    switch (*(str_in+iaddr(V, idx, 5))){                                                                    // Case depending on each string letter (not case-sensitive)
      case 'a':                                                                                             // Case letter 'a'
        ++*(vow_cnt+iaddr(V, A, 5));                                                                        // Increment letter 'a' counter in vowels counters array
        break;
      case 'A':                                                                                             // Case letter 'A'
        ++*(vow_cnt+iaddr(V, A, 5));                                                                        // Increment letter 'a' counter in vowels counters array
        break;
      case 'e':                                                                                             // Case letter 'e'
        ++*(vow_cnt+iaddr(V, E, 5));                                                                        // Increment letter 'e' counter in vowels counters array
        break;
      case 'E':                                                                                             // Case letter 'E'
        ++*(vow_cnt+iaddr(V, E, 5));                                                                        // Increment letter 'e' counter in vowels counters array
        break;
      case 'i':                                                                                             // Case letter 'i'
        ++*(vow_cnt+iaddr(V, I, 5));                                                                        // Increment letter 'i' counter in vowels counters array
        break;
      case 'I':                                                                                             // Case letter 'I'
        ++*(vow_cnt+iaddr(V, I, 5));                                                                        // Increment letter 'i' counter in vowels counters array
        break;
      case 'o':                                                                                             // Case letter 'o'
        ++*(vow_cnt+iaddr(V, O, 5));                                                                        // Increment letter 'o' counter in vowels counters array
        break;
      case 'O':                                                                                             // Case letter 'O'
        ++*(vow_cnt+iaddr(V, O, 5));                                                                        // Increment letter 'o' counter in vowels counters array
        break;
      case 'u':                                                                                             // Case letter 'u'
        ++*(vow_cnt+iaddr(V, U, 5));                                                                        // Increment letter 'u' counter in vowels counters array
        break;
      case 'U':                                                                                             // Case letter 'U'
        ++*(vow_cnt+iaddr(V, U, 5));                                                                        // Increment letter 'u' counter in vowels counters array
    }
    ++idx;                                                                                                  // While-loop iterations index val upd
  }

  for (u_shrt j = size-1; j > 1; --j){                                                                      // Scan input string to remove '\n' char FOR cycle
    if (*(str_in+iaddr(V, j, size)) == '\n'){                                                               // If current string char is equal to '\n'
      *(str_in+iaddr(V, j, size)) = 0;                                                                      // Remove char
      break;                                                                                                // Exit FOR cycle
    }
  }

  if (*(vow_cnt+iaddr(V, A, 5)) != 0)                                                                       // Case a counter != 0
      snprintf((str_tmp+iaddr(A, 0, 16)), 16, " %hu A,", *(vow_cnt+iaddr(V, A, 5)));                        // Popolate tmp 'a' partial out string in array
  if (*(vow_cnt+iaddr(V, E, 5)) != 0)                                                                       // Case e counter != 0
      snprintf((str_tmp+iaddr(E, 0, 16)), 16, " %hu E,", *(vow_cnt+iaddr(V, E, 5)));                        // Popolate tmp 'e' partial out string in array
  if (*(vow_cnt+iaddr(V, I, 5)) != 0)                                                                       // Case i counter != 0
      snprintf((str_tmp+iaddr(I, 0, 16)), 16, " %hu I,", *(vow_cnt+iaddr(V, I, 5)));                        // Popolate tmp 'i' partial out string in array
  if (*(vow_cnt+iaddr(V, O, 5)) != 0)                                                                       // Case o counter != 0
      snprintf((str_tmp+iaddr(O, 0, 16)), 16, " %hu O,", *(vow_cnt+iaddr(V, O, 5)));                        // Popolate tmp 'o' partial out string in array
  if (*(vow_cnt+iaddr(V, U, 5)) != 0)                                                                       // Case o counter != 0
      snprintf((str_tmp+iaddr(U, 0, 16)), 16, " %hu U,", *(vow_cnt+iaddr(V, U, 5)));                        // Popolate tmp 'o' partial out string in array

  snprintf(str_out, sizeof(str_out), "Nella stringa \"%s\" ci sono%s%s%s%s%s", str_in,
           str_tmp+iaddr(A, 0, 16), str_tmp+iaddr(E, 0, 16), str_tmp+iaddr(I, 0, 16),
           str_tmp+iaddr(O, 0, 16), str_tmp+iaddr(U, 0, 16));                                               // Concatenate strings

  for (u_shrt j = size-1; j > 1; --j){                                                                      // Scan output string to remove last ',' char FOR cycle (starting from the end of the string)
    if (*(str_out+iaddr(V, j, size)) == ','){                                                               // If current output string char is equal to ','
      *(str_out+iaddr(V, j, size)) = 0;                                                                     // Remove char
      break;                                                                                                // Exit FOR cycle
    }
  }

  strcpy(str_in, str_out);                                                                                  // Copy out str in input str
}


void vect_init(char *in_buff, u_shrt buff_size, real *vect, const byte n){                                  // Vector initialization (definition) function
  /* Function body */
  printf("\n");                                                                                             // New line fbk
  for (shrt i = 0; i < n; ++i){                                                                             // Linear vectors columns definition FOR cycle 
    printf("%s-->%s Define the %s%d%s component of the vector: %s", og, cy, bl, i+1, cy, er);               // Vector components definition
    fgets(in_buff, buff_size, stdin);                                                                       // Save vector components value into buffer char array --> fgets to avoid char-loop problem associated with scanf
    *(vect+iaddr(V, i, n)) = atof(in_buff);                                                                 // Convert to double and copy buffer char array val into vector elements --> return 0 in case of char input
    printf("\n");                                                                                           // New line fbk
  }
}


void vect_print(real *vect, const byte n){                                                                  // Vector print function
  /* Function body */
  for (byte i = 0; i < n; ++i){                                                                             // Linear vectors elements print FOR cycle 
    printf(" %lf ", *(vect+iaddr(V, i, n)));                                                                // Vector elements print
  }
  printf("\n");                                                                                             // New line fbk
}


void str_init(char *str, u_shrt size){                                                                      // String initialization (definition) function
  /* Function body */
  for (u_shrt j = 0; j < size; ++j)                                                                         // Input buffer char array value init
    *(str+iaddr(V, j, size)) = 0;                                                                           // Reset string memo
}
