/*
 * Author: Cristian Merli
 * Code title: Exercise 6 (Logical-Operations)
 * Code version: 3.0
 * Creation date: 30/03/2021
 * Last mod. date: 06/04/2021
 */


/* Libraries import */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <string.h>                                                                                         // String library inclusion (for strlen ecc.)


/* Constants declaration and definition */
const char R[] = "\033[0;31m";                                                                              // Red color
const char B[] = "\033[0;34m";                                                                              // Blue color
const char LB[] = "\033[1;34m";                                                                             // Light blue color
const char P[] = "\033[0;35m";                                                                              // Purple color
const char C[] = "\033[0;36m";                                                                              // Cyan color
const char Y[] = "\033[1;33m";                                                                              // Yellow color
const char O[] = "\033[0;33m";                                                                              // Orange color
const char G[] = "\033[0;32m";                                                                              // Green color
const char LGN[] = "\033[1;32m";                                                                            // Light green color
const char LGY[] = "\033[0;37m";                                                                            // Light gray color
const char E[] = "\033[0m";                                                                                 // End color


/* Functions declaration and definition */
void logo(unsigned char vthck, unsigned char lthck_vthik_r, unsigned char start_sp, unsigned char lsp,
          char txt[], const char txt_col[], char bkg_chr, const char bkg_col[]){                            // Print logo function
  /* Function body */
  printf("\n%s", bkg_col);                                                                                  // New line
  unsigned char len = 2*lthck_vthik_r*vthck+2*lsp+strlen(txt);                                              // Logo length calc
  for (unsigned char i = 0; i < (4*vthck+1); i++){                                                          // Logo lines print FOR cycle
    for (unsigned char j = 0; j < start_sp; j++){                                                           // Initial spaces print FOR cycle
      printf(" ");                                                                                          // Print initial spaces
    }
    if ((i < vthck || i > (3*vthck)) && (i != (4*vthck)/2)){                                                // Full bkg logo lines print cond
      for (unsigned char h = 0; h < len; h++){                                                              // Full bkg logo lines print FOR cycle
        printf("%c", bkg_chr);                                                                              // Bkg logo char print
      }
      printf("\n");                                                                                         // New line
    } else if ((i >= vthck && i <= (3*vthck)) && (i != (4*vthck)/2)) {                                      // Partial-empty bkg logo lines print cond
      for (unsigned char l = 0; l < lthck_vthik_r*vthck; l++){                                              // Partial-empty bkg logo lines, initial full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Partial-empty bkg logo lines, initial full part print
      }
      for (unsigned char m = 0; m < (len - 2*lthck_vthik_r*vthck); m++){                                    // Partial-empty bkg logo lines, central empty part print FOR cycle
        printf(" ");                                                                                        // Partial-empty bkg logo lines, central empty part print
      }
      for (unsigned char n = 0; n < lthck_vthik_r*vthck; n++){                                              // Partial-empty bkg logo lines, final full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Partial-empty bkg logo lines, final full part print
      }
      printf("\n");                                                                                         // New line
    } else if (i == ((4*vthck)/2)) {                                                                        // Text logo line initial full part print cond
      for (unsigned char o = 0; o < lthck_vthik_r*vthck; o++){                                              // Text logo line initial full part print FOR cycle
        printf("%C", bkg_chr);                                                                              // Text logo line initial full part print
      }
      for (unsigned char p = 0; p < lsp; p++){                                                              // Text logo line central empty part print FOR cycle
        printf(" ");                                                                                        // Text logo line central empty part print
      }
      printf("%s%s%s", txt_col, txt, bkg_col);                                                              // Text logo line central text part print
      for (unsigned char q = 0; q < lsp; q++){                                                              // Text logo line central empty part print FOR cycle
        printf(" ");                                                                                        // Text logo line central empty part print
      }
      for (unsigned char r = 0; r < lthck_vthik_r*vthck; r++){                                              // Text logo line final full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Text logo line final full part print
      }
      printf("\n");                                                                                         // New line
    }
  }
  printf("\033[0m\n");                                                                                      // New line and erase logo bkg color
}

int logic_check(int val1, int val2, int val3, int val4){                                                    // Logical check function (0=NOT-OK, 1=OK)
  /* Function body */
  if ((val1 <= val3) && (val1 <= val4) && (val2 <= val3) && (val2 <= val4)){                                // Logical conditions test (case ok)
      return 1;                                                                                             // Return condition ok
    } else {                                                                                                // Logical conditions test (case not-ok)
      return 0;                                                                                             // Return condition not-ok
    }
  }


/* Main cycle */
int main(){
  /* Vars declaration and definition */
  int a = 1, b = 2, c = 3, d = 4, e = 5, f = 5, g = 5, h = 5, i = 5, l = 10, m = 12, n = 12;                // Int vars declaration and definition

  /* Code */
  logo(5, 3, 6, 22, "LOGICAL CHECK", Y, 'X', G);                                                            // Print logo function call (vert_thick, lat_thick_vert_thick_ratio, start_spaces, lat_spaces, text, txt_color, background_char, bkgchr_color)
  printf("\n\n%s>>>%s Call 1:%s\n\n", G, P, E);                                                             // Call 1 fbk
  printf("%s-->%s Logic check: %s%d %d %d %d --> %d %s\n", O, C, B, a, b, c, d, logic_check(a, b, c, d), E);// Logical check function call (0=NOT-OK, 1=OK)
  printf("\n\n%s>>>%s Call 2:%s\n\n", G, P, E);                                                             // Call 2 fbk
  printf("%s-->%s Logic check: %s%d %d %d %d --> %d %s\n", O, C, B, e, f, g, h, logic_check(e, f, g, h), E);// Logical check function call (0=NOT-OK, 1=OK)
  printf("\n\n%s>>>%s Call 3:%s\n\n", G, P, E);                                                             // Call 3 fbk
  printf("%s-->%s Logic check: %s%d %d %d %d --> %d %s\n", O, C, B, i, l, m, n, logic_check(i, l, m, n), E);// Logical check function call (0=NOT-OK, 1=OK)

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Scrivi una funzione che prende 4 interi e ritorna 1 se i primi sono minori 
 * uguali dei secondi due (valore 0), i secondo è maggiori stretto del primo sono 
 * e il terzo e quarto sono diversi
 * Successivamente chiamare la funzione con 1 2 3 4 e con 5 5 5 5 e con 5 10 12 12
 */
