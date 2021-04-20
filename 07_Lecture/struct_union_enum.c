/*
 * Author: Cristian Merli
 * Code title: Struct, union and enum data types
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
//


/* Data-types declaration and definition */
typedef unsigned char   byte;                                                                               // Unsigned char alias (byte)
typedef unsigned short  u_shrt;                                                                             // Unsigned short alias (u_shrt)
typedef short           shrt;                                                                               // Short alias (shrt)
typedef double          real;                                                                               // Double alias (real)


/* Enums declaration */
struct person                                                                                               // Struct declaration
{
  int age;
  char initial;
  char name[20];
  char surname[20];
  double height;
  double weight;
};

struct people                                                                                               // Struct declaration and definition
{
  int age;
  char initial;
  char name[20];
  char surname[20];
  double height;
  double weight;
} Antonio, Marco;

struct {                                                                                                    // Struct definition - without name, can be used only 1 time
  double a;
  double b;
} unic;

struct person Giorgio;                                                                                      // Struct definition
struct person class[10];                                                                                    // -

struct person Luca = {45, 'L', "Luca", "Rossi", 175, 75};                                                   // Fast struct init

union generic                                                                                               // nion declaration and definition (allocates the size of the biggest data type, in this example double), then it can be used either as an int or as a double --> NOTE THAT IF I WRITE THE VARIABLE AS DOUBLE, I HAVE TO EVEN READ IT AS A DOUBLE AND NOT AS INT
{
  double  val_real;
  int     val_int;
} elem;

struct info                                                                                                 // Always allocate n*4 bytes (= n*32 bits) to increas , but size can be override
{
  unsigned f:4;                                                                                             // 4 bits unsigned int, DO NOT USE DOUBLE AND FLOAT
  signed g:2;                                                                                               // 2 bits signed int
  signed bool:1;                                                                                            // 1 bit bool value (0,1)
  unsigned u_bool:1;                                                                                        // 1 bit bool value (-1, 0)
};

enum var_type{                                                                                              // Enum values defined with MAIUSC (convention)
  FAST,
  SLOW
};





/* Global vars declaration and definition */
//


/* Functions declaration and definition */
static void logo(const byte start_sp, const char txt[], const char txt_col[], const char bkg_chr,           // Static function (readable only in this .c file) and const param (not modified in function --> SW optimization at compile-time)
                 const char bkg_col[]){                                                                     // Print responsive-logo function
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


/* Main cycle */
int main(){
  /* Vars declaration and definition */
  //

  /* Code */
  logo(4, "STRUCT, UNION AND ENUM", Y, '#', G);                                                             // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  Giorgio.age = 25;                                                                                         // -
  // Giorgio.name = "Giorgione";                                                                            // Wrong! Use funct below
  strcpy(Giorgio.name, "Giorgione");                                                                        // -
  struct person *el = &class[2];                                                                            // Extract second person memo addr in class array
  strcpy(el->name, "William");                                                                              // Write name "William" into pointed memo cell, using operator '->' to dereference the pointer *el
  strcpy((*el).name, "William");                                                                            // Equivalent as above
  el->age = 22;                                                                                             // -
  el->weight = 65;                                                                                          // -
  el->height = 172;                                                                                         // -
  strcpy(el->surname, "Bianchi");                                                                           // -
  el->age++;                                                                                                // Increment age

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Struct, union and enum data types lesson
 */
