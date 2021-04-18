/*
 * Author: Cristian Merli
 * Code title: Functions read/write val from terminal
 * Code version: 3.0
 * Creation date: 13/04/2021
 * Last mod. date: 15/04/2021
 */


/* Libraries import */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <string.h>                                                                                         // String library inclusion (for strlen ecc.)
#include <stdlib.h>                                                                                         // Standard library inclusion (for atoi ecc.)


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


/* Main cycle */
int main(){
  /* Vars declaration and definition */
  int c='1', i;                                                                                             // Int vars declaration and definition

  /* Code */
  logo(5, 3, 8, 22, "FUNCTIONS", Y, 'X', G);                                                                // Print logo function call (vert_thick, lat_thick_vert_thick_ratio, start_spaces, lat_spaces, text, txt_color, background_char, bkgchr_color)
  printf("\n\n%s>>>%s Reading/writing values from terminal...\n%s", G, P, E);                               // Reading values from terminal fbk

  // Read data from terminal using chr=GETCHAR(), ENTER PROBLEM and print using PUTS(str) PUTCHAR(chr)
  printf("\n%s-->%s Value printed with putchar: %s", O, C, E);                                              // Value printed with putchar fbk (Simple char print)
  putchar(c);                                                                                               // Print val with putchar
  printf("\n%s-->%s String printed with puts: %s", O, C, E);                                                // String printed with puts fbk (Simple string print)
  puts("Hi!! ;)");                                                                                          // String print with puts
  fflush(stdout);                                                                                           // Force print buffer clear (flush) --> USE WHEN PRINTF DOESN'T WORK
  do {                                                                                                      // Repeat input request 'till specified value has been red from terminal
    printf("\n%s-->%s Waiting '%s.%s' char input with getchar (ENTER PROBLEM): %s", O, C, G, C, E);         // Expecting specific chr from terminal with getchar fbk
    c = getchar();                                                                                          // Read chr from terminal with getchar (SPACE PROBLEM)
  } while (c != '.');                                                                                       // Exit when red char is '.'
  while ((c = getchar()) != '\n' && c != EOF);                                                              // Instruction to clear input buffer

  // Read data from terminal using FGETS(buff, buff_size, stdin)
  // and convert STRING to INT using num_int=ATOI(str)
  char buffer[256];                                                                                         // Input chars buffer chr array
  printf("\n%s-->%s Read random char with fgets: %s", O, C, E);                                             // Read random chr from terminal with fgets fbk
  fgets(buffer, 256, stdin);                                                                                // Save input string in str var (char buffer array)
  i = atoi(buffer);                                                                                         // Convert string to int (ASCII to INT conv), stdlib library NEEDED

  // Read data from terminal using SCANF("%id", var)
  printf("\n%s-->%s Read random char with scanf: %s", O, C, E);                                             // Read random chr from terminal with scanf fbk
  scanf("%d", &i);                                                                                          // Save input string into int var (no need to use ATOI)

  // Read data from terminal using scanf --> error in case of expecting int val and gettin' char: avoid usin' "scanf("%*[^\n]");" --> avoid endless-loop
  do {
    scanf("%*[^\n]");                                                                                       // Clear input buffer 'till '\n' char
    printf("\n%s-->%s Waiting '%s1%s' char input with scanf: %s", O, C, G, C, E);                           // Expecting specific chr from terminal with scanf fbk
    scanf("%d", &i);                                                                                        // Scanf input val
  } while (i != 1);                                                                                         // Exit when red val is 1

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * -
 */
