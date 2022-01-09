/*
 * Author: Cristian Merli
 * Code title: Exercise 2 (Pointers 2) library
 * Code version: 3.0
 * Creation date: 20/04/2021
 * Last mod. date: 21/04/2021
 */


/* Libraries import */
#include "libexercise2.h"                                                                                   // Library for exercise 2 import header file


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


u_shrt iaddr(const u_shrt i, const u_shrt j, const u_shrt lda){                                             // Arrays/vectors memo addressing
  /* Function body */
  return (i*lda)+j;                                                                                         // Return index number
}


int findchr_addr(char *str, const char chr, char **ptr){                                                    // Find char address function (*str passes the str array address, while chr creates a copy of the var --> if I modify the chr var in the funct, it 'll not be modified out of the function)
  /* Function body */                                                                                       // If I modify the *str with dereferentiation, it 'll be modified even out of the funct, **ptr is a pinter which will point to the address of another pointer --> Allows to modify the val inside the pointed val by (*ptr)
  int idx = 0;                                                                                              // While-loop idx
  int fnd = 0;                                                                                              // Found int val declaration and definition
  (*ptr) = 0;                                                                                               // Null address init into ptr var

  printf("\n\n\n%s>>>%s Scanning string trying to find %s'%c'%s char: %s", gn, pu, ye, chr, pu, ye);        // Scanning string fbk
  while (*(str+iaddr(V, idx, sizeof(str))) != '\0'){                                                        // Scan string 'till '\0' char
    printf("%d", idx);                                                                                      // Print string scanning idx fbk
    if (*(str+iaddr(V, idx, sizeof(str))) == chr){                                                          // In case of str char = to given chr
      (*ptr) = &*(str+iaddr(V, idx, sizeof(str)));                                                          // Seve detected char address memo cell addr into *ptr var
      fnd = 1;                                                                                              // Return OK code, negation at return (= 0), exit at first defined char detection
      printf("%s --> SET!%s", gn, er);                                                                      // Print found char fbk
      break;                                                                                                // Exit scanning while-loop
    }
    printf(",");                                                                                            // Print scanning idx separator fbk
    ++idx;                                                                                                  // While-loop idx upd
  }
  return !fnd;                                                                                              // Return code (0 = OK, 1 = NOT OK)
}
