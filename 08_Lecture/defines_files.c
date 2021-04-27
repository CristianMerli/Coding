/*
 * Author: Cristian Merli
 * Code title: Defines and files
 * Code version: 1.0
 * Creation date: 27/04/2021
 * Last mod. date: 27/04/2021
 */


/* Libraries import */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <string.h>                                                                                         // String library inclusion (for strlen ecc.)
#include <sys/ioctl.h>                                                                                      // System I/O control library inclusion (for ioctl ecc.)
#include <unistd.h>                                                                                         // UniStd library inclusion (for stdout ecc.)


/* Preprocessing directives */
#define NUM 10                                                                                              // Single-line deinfe
#define FUN(X) X*X                                                                                          // Function define to apply multiplication
#define FOR(X, Y) for(int i=0; i<X; ++i){Y}                                                                 // -
#define EXECUTE(F, A, B) A F B                                                                              // -
/*
#define TEXT \                                                                                              // Milti-line define (using '\')
printf("rerfeerr");\
printf("rerfeerdscdscsdsdr");
*/

/* Constants declaration and definition */
const char *rd = "\033[0;31m";                                                                              // Red color
const char *bl = "\033[0;34m";                                                                              // Blue color
const char *lb = "\033[1;34m";                                                                              // Light blue color
const char *pu = "\033[0;35m";                                                                              // Purple color
const char *cy = "\033[0;36m";                                                                              // Cyan color
const char *ye = "\033[1;33m";                                                                              // Yellow color
const char *og = "\033[0;33m";                                                                              // Orange color
const char *gn = "\033[0;32m";                                                                              // Green color
const char *lgn = "\033[1;32m";                                                                             // Light green color
const char *lgy = "\033[0;37m";                                                                             // Light gray color
const char *er = "\033[0m";                                                                                 // End color


/* Data-types declaration and definition */
typedef unsigned char byte;                                                                                 // Unsigned char alias (byte)


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


/* Main cycle */
int main(){
  /* Vars declaration and definition */
  char in_buff[20];                                                                                         // Input buffer char array for fgets func

  /* Code */
  logo(4, "DEFINES AND FILES", ye, '#', gn);                                                                // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  
  // Pre-processing directives command '#'
  // Compile only 'till pre-processing operation --> gcc -E defines_files.c -o defines_files.i
  // Compile also includes preprocessing step --> gcc -Wall defines_files.c -o defines_files
  // #define used to define constants, in code each constant will be
  // replaced by the constant vale (define resolution)
  // #define can also be used for functions
  int vett[NUM];                                                                                            // --> int vectt[10];
  int r = FUN(4);                                                                                           // --> int r = 4*4;
//  FOR(10, printf("%d\n", i););                                                                              // --> -
  EXECUTE(+, 4, 5);                                                                                         // --> -


  // FILES
  FILE *file;                                                                                               // Pointer to file object
  file = fopen("data", "w");                                                                                // File-open (filename, open_type)
                                                                                                            // open_type:
                                                                                                            // - w = write (clear file)
                                                                                                            // - r = read only
                                                                                                            // - a = append (do not clear file, add text, create if file doesn't exist)
                                                                                                            // - r+ = read/write (only if file exists)
                                                                                                            // - w+ = read&write (create file if not exists)
                                                                                                            // - a+ = read&write&append (create file if not exists)
  fprintf(file, "%d", 10);                                                                                  // Insert text in file
  fclose(file);                                                                                             // Close file

  file = fopen("data", "r");                                                                                // Open file in read-mode
  if (file == NULL) perror(); else {
    //
  }

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Defines and files lesson
 */
