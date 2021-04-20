/*
 * Author: Cristian Merli
 * Code title: Exercise 2 (Pointers 2)
 * Code version: 1.0
 * Creation date: 20/04/2021
 * Last mod. date: 20/04/2021
 */


/* Libraries import */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <string.h>                                                                                         // String library inclusion (for strlen ecc.)
#include <stdlib.h>                                                                                         // Standard library inclusion (for atof ecc.)
#include <sys/ioctl.h>                                                                                      // System I/O control library inclusion (for ioctl ecc.)
#include <unistd.h>                                                                                         // UniStd library inclusion (for stdout ecc.)


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
};


/* Data-types declaration and definition */
typedef unsigned char   byte;                                                                               // Unsigned char alias (byte)
typedef unsigned short  u_shrt;                                                                             // Unsigned short alias (u_shrt)
typedef short           shrt;                                                                               // Short alias (shrt)
typedef double          real;                                                                               // Double alias (real)


/* Global vars declaration and definition */
char in_buff[20];                                                                                           // Input buffer char array for fgets func


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

int findchr_addr(char *str, char chr, char **ptr){                                                          // Find char address function (*str passes the str array address, while chr creates a copy of the var --> if I modify the chr var in the funct, it 'll not be modified ot of the function)
  /* Function body */                                                                                       // If I modify the *str with dereferentiation, it 'll be modified even out of the funct, **ptr is a pinter which will point to the address of another pointer --> Allow to modify the val inside the pointed val by (*ptr)
  int idx = 0;                                                                                              // While-loop idx
  int fnd = 0;                                                                                              // Found int val declaration and definition
  (*ptr) = 0;                                                                                               // Null address init into ptr var

  printf("\n\n\n%s>>>%s Scanning string tring to find char: %s", G, P, Y);                                  // Scanning string fbk
  while (*(str+iaddr(v, idx, sizeof(str))) != '\0'){                                                        // Scan string 'till '\0' char
    printf("%d", idx);                                                                                      // Print string scanning idx fbk
    if (*(str+iaddr(v, idx, sizeof(str))) == chr){                                                          // In case of str char = to given chr
      (*ptr) = &*(str+iaddr(v, idx, sizeof(str)));                                                          // Seve detected char address memo cell addr into *ptr var
      fnd = 1;                                                                                              // Return OK code, negation at return (= 0), exit at first defined char detection
      printf("%s --> SET!%s", G, E);                                                                        // Print found char fbk
      break;                                                                                                // Exit scanning while-loop
    }
    printf(",");                                                                                            // Print scanning idx separator fbk
    ++idx;                                                                                                  // While-loop idx upd
  }
  return !fnd;                                                                                              // Return code (0 = OK, 1 = NOT OK)
}


/* Main cycle */
int main(){
  /* Vars declaration and definition */
  char chr;                                                                                                 // Char var declaration
  char *ptr;                                                                                                // Ptr var declaration

  /* Code */
  logo(4, "FIND CHAR ADDRESS", Y, '#', G);                                                                  // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  printf("\n\n%s>>>%s Insert the string: %s", G, P, E);                                                     // String definition request fbk
  scanf("%19[^\n]", in_buff);                                                                               // Reads the string 'till '\n' char, avoidin' scanf stop at space char and saving '\n' chr (str var definition) --> avoid buffer overflow assigning max input str size to 20-1 for '\0' char
  while ((getchar()) != '\n');                                                                              // Instruction to clear input buffer when buffer overflow occurs, avoiding to save next char as new input
  printf("\n\n%s>>>%s Insert the char: %s", G, P, E);                                                       // Char definition request fbk
  scanf(" %c", &chr);                                                                                       // Reads the char 'till '\n' char, to avoid reading '\n' of the previous scanf, insert a space b4 %c in scanf --> ' %c' (char var definition)
  printf("\n\n%s>>>%s The inserted string is: %s%s", G, P, E, in_buff);                                     // Inserted string print fbk
  printf("\n\n\n%s>>>%s The inserted char is: %s%c", G, P, E, chr);                                         // Inserted char print fbk
  printf("\n\n\n%s>>>%s The first defined string memory address is: %s%p", G, P, E, in_buff);               // Print first defined string memory address fbk

  if (findchr_addr(in_buff, chr, &ptr) == 0){                                                               // Find char address function call and return val check (case OK = 0)
    printf("\n\n\n%s>>>%s The first defined char memory address is: %s%p", G, P, E, ptr);                   // Print first detected char memory address in string fbk
    printf("\n\n\n%s>>>%s The char is the number %s%lu%s inside the string.\n%s",
            G, P, E, ptr-in_buff+1, P, E);                                                                  // Print the first detected char number inside the string fbk
  } else {                                                                                                  // Find char address function return val check (case NOT-OK = 1)
    printf("\n\n\n%s>>>%s The defined char has not been fond inside the given string.\n%s", G, P, E);       // Print char not found fbk
  }

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Scrivere una libreria che continene una funzione che prende in ingresso
 * una stringa, un carattere, e un puntatore a carattere e ritorna un intero
 * La funzione deve cercare all'interno della stringa il carattere indicato ed assegnare
 * al puntatore (terzo parametro della funzione) l'indirizzo del carattere trovato.
 * La funzione torna zero se il carattere è contenuto nella stringa e 1 se il carattere
 * non è contenuto nella stringa.
 * Il main dovrà utilizzare la funzione scanf chiedendo di inserire una stringa e successivamente
 * il carattere da cercare.
 * Ed in fine stampare l'indirizzo del carattere trovato e la differenza tra l'indirizzo del vettore
 * e l'indirizzo del carattere (che corrisponde alla posizione del carattere nella stringa).
 */
