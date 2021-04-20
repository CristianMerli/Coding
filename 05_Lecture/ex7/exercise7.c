/*
 * Author: Cristian Merli
 * Code title: Exercise 7 (Vectors 1)
 * Code version: 3.0
 * Creation date: 19/04/2021
 * Last mod. date: 19/04/2021
 * 
 * Notes: Run software using the following command: "LD_LIBRARY_PATH=. ./exercise7"
 * the first part has the purpose of definin' env var for shared library path
 * --> To create shared libraries see: https://www.youtube.com/watch?v=Slfwk28vhws
 */


/* Libraries import */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <string.h>                                                                                         // String library inclusion (for strlen ecc.)
#include <stdlib.h>                                                                                         // Standard library inclusion (for atof ecc.)
#include <sys/ioctl.h>                                                                                      // System I/O control library inclusion (for ioctl ecc.)
#include <unistd.h>                                                                                         // UniStd library inclusion (for stdout ecc.)
#include "libexercise7.h"                                                                                   // Library for exercise 7 import


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


/* Global vars declaration and definition */
char in_buff[512];                                                                                          // Input buffer char array for fgets func


/* Functions declaration and definition */
static void logo(const byte start_sp, const char *txt, const char *txt_col, const char bkg_chr,             // Static function (readable only in this .c file) and const param (not modified in function --> SW optimization at compile-time)
                 const char *bkg_col){                                                                      // Print responsive-logo function
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

static u_shrt iaddr(u_shrt i, u_shrt j, u_shrt lda){                                                        // Arrays/vectors memo addressing
  /* Function body */
  return (i*lda)+j;                                                                                         // Return index number
}

static void vect_init(real *vect, const byte n){                                                            // Vector initialization (definition) function
  /* Function body */
  printf("\n");                                                                                             // New line fbk
  for (shrt i = 0; i < n; ++i){                                                                             // Linear vectors columns definition FOR cycle 
    printf("%s-->%s Define the %s%d%s component of the vector: %s", O, C, B, i+1, C, E);                    // Vector components definition
    fgets(in_buff, sizeof(in_buff), stdin);                                                                 // Save vector components value into buffer char array --> fgets to avoid char-loop problem associated with scanf
    *(vect+iaddr(v, i, n)) = atof(in_buff);                                                                 // Convert to double and copy buffer char array val into vector elements --> return 0 in case of char input
    printf("\n");                                                                                           // New line fbk
  }
}

static void vect_print(real *vect, const byte n){                                                           // Vector print function
  /* Function body */
  for (byte i = 0; i < n; ++i){                                                                             // Linear vectors elements print FOR cycle 
    printf(" %lf ", *(vect+iaddr(v, i, n)));                                                                // Vector elements print
  }
  printf("\n");                                                                                             // New line fbk
}

static void str_init(char *str){                                                                            // String initialization (definition) function
  for (u_shrt j = 0; j < sizeof(str); ++j){                                                                 // Input buffer char array value init
    *(str+iaddr(v, j, sizeof(str))) = 0;                                                                    // Reset string memo
  }
}


/* Main cycle */
int main(){
  /* Vars declaration and definition */
  byte n;                                                                                                   // Vector size declaration
  byte n_minval = 1;                                                                                        // Input val n, min val range limit (min u_char value - alias byte)
  byte n_maxval = 255;                                                                                      // Input val n, max val range limit (max u_char value - alias byte)
  shrt tmp_chk = 0;                                                                                         // Tmp var to check n input val from terminal in allowed range

  /* Code */
  logo(4, "VECTORS SUM AND VOWELS COUNTER", Y, '#', G);                                                     // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  str_init(in_buff);                                                                                        // String initialization (definition) function call for in_buff
  do {                                                                                                      // Expect input val in range while-loop
    printf("\n\n%s>>>%s Specify the number of vector components (val between %hu and %hu): %s",
           G, P, n_minval, n_maxval, E);                                                                    // Number of vector elements definition request fbk
    fgets(in_buff, sizeof(in_buff), stdin);                                                                 // Save input val from terminal into buffer char array --> fgets to avoid char-loop problem associated with scanf when detects char expecting numeric val
    tmp_chk = atof(in_buff);                                                                                // Convert to double and copy buffer char array val into tmp var
    if (tmp_chk >= n_minval && tmp_chk <= n_maxval){                                                        // Tmp var check (case in range)
      n = tmp_chk;                                                                                          // Number of vector elements val definition
    } else {                                                                                                // Tmp var check (case out of range)
      printf("%sInput val error! The value must be between %hu and %hu. %sRetry!%s",
             R, n_minval, n_maxval, C, E);                                                                  // Print error fbk
    }
  } while ((tmp_chk < n_minval || tmp_chk > n_maxval));                                                     // Expect input val in range while-loop exit cond

  real vect[iaddr(v, n, n)];                                                                                // Vector declaration (in execution)

  vect_init(vect, n);                                                                                       // Vector initialization (definition) function call
  printf("\n%s>>>%s Defined vector:%s", G, P, E);                                                           // Defined vector fbk
  vect_print(vect, n);                                                                                      // Vector print function call
  printf("\n\n%s>>>%s Vector components sum: %s%lf%s\n", G, P, Y, vect_comp_sum(vect, n), E);               // Vector components sum function call and value print
  printf("\n\n%s>>>%s Specify a string to count vowels: %s", G, P, E);                                      // String to count vowels definition request fbk
  fgets(in_buff, sizeof(in_buff), stdin);                                                                   // Reads the input string and save in input buffer char array
  count_vowels(in_buff, sizeof(in_buff));                                                                   // Count vowels in string function call
  printf("\n\n%s>>>%s Vowles count: %s%s\n", G, P, E, in_buff);                                             // Vowels count in input str print fbk
  printf("\n\n%s>>>%s Done! %s;)%s\n", G, P, C, E);                                                         // Done print fbk

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Scrivere una libreria che continene due funzioni 
 * La prima funzione:
 * dato una vettore di interi o double ritorna la somma di tutti i suoi elementi
 * nel caso sia positiva; se la somma è negativa torna sempre -1.
 * La seconda funzione:
 * prende una stringa e conta le ricorrenze di tutte le vocali
 * e ne stampa in numero scrivendo:
 * "Nella stringa "#STRINGA#" ci sono #N A, #N E, #N I, #N O, #N U
 * esempio:
 * Se passo la stringa "Io mi chiamo Gastone" il risultato è
 * "Nella stringa "Io mi chiamo Gastone" ci sono 2 A, 1 E, 3 I, 3 O
 * Se non vi sono vocali di quel tipo semplicemente non stampa quella vocale
 * come nell'esempio.
 * Compilare successivamente la libreria separatamente e utilizzarla all'interno
 * del programma main.
 */
