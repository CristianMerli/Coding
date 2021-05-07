/*
 * Author: Cristian Merli
 * Code title: Dynamic memory management
 * Code version: 3.0
 * Creation date: 04/05/2021
 * Last mod. date: 04/05/2021
 */


/* Useful flags */
/*
 * https://linux.die.net/man/1/gcc                  --> gcc compiler flags
 * https://www.geeksforgeeks.org/type-conversion-c/ --> C implicit conversions
 * https://en.wikipedia.org/wiki/C_data_types       --> All data-types depending on C version (e.g. long logn only in c99)
 *
 * -Wall              --> Most useful warnings
 * -Wextra            --> Extra warnings not enabled by the -Wall flag
 * -Werror            --> Transform all warnings in errrors
 * -Wuninitialized    --> Use of decleared vars, but not initialized (in -Wall)
 * -Wconversion       --> Conversions warning (e.g. int to float/double conversion), should use cast syntax
 * -Wsign-compare     --> Sign/unsigned comparison (in -Wextra)
 * -Wfloat-equal      --> Float/double unsafe comparison ( == or != ) warnings, numerical precision problems
 *                        To avoid this, include "math.h" lib and use "fabs()" function, e.g. if(fabs(a-b)<0.001)...
 * -O2                --> Code optimization (possible scanf return ignored error, solution below)
 * -O2 (scanf err)    --> Avoid error creating an unused variable: "int unused __attribute__((unused));" and write "unused = scanf(...);"
 * -std=VERSION       --> Choose C VERSION=[c99, c11, c90, c89], e.g. "//" comments in c90 and c89 are not allowed, must use only "multi-line" comments
 * -pedantic          --> Flag to force complete use of a particular VERSION of C (see above flag), e.g. in c90, all the var init
 *                        must be in the first part of each code block
 * -predantic-errors  --> Transform all pedantic warnings in errors
 *
 * >>> Use alias to create gcc commands with specific flags:
 * alias gccW99_o="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -o"
 * alias gccW99_c="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -c"
 * alias gccW99_lib="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -fpic -shared -o"
 */


/* Libraries */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <string.h>                                                                                         // String library inclusion (for strlen ecc.)
#include <sys/ioctl.h>                                                                                      // System I/O control library inclusion (for ioctl ecc.)
#include <unistd.h>                                                                                         // UniStd library inclusion (for stdout ecc.)
#include <stdlib.h>                                                                                         // Standard library inclusion (for dynamic memory ecc.)


/* Constants */
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


/* Defines */
#define DIM 10                                                                                              // Define for dimensions


/* Data-types */
typedef unsigned char   byte;                                                                               // Unsigned char alias (byte)


/* Structs & typedefs */
typedef struct data {                                                                                       // Data-type struct to test malloc funct
  double d;                                                                                                 // Double var
  int i;                                                                                                    // Int var
  char str[DIM];                                                                                            // String var (DIM elements)
} data;


/* Functions */
static void logo(const byte start_sp, const char *txt, const char *txt_col, const char bkg_chr,             // Static function (readable only in this .c file) and const param (not modified in function --> SW optimization at compile-time)
                 const char *bkg_col){                                                                      // Print responsive-logo function
  /* Body */
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

static int *malloc_int(const int val){                                                                      // Dyn memo alloc (malloc) for int var funct
  /* Body */
  int *p = malloc(sizeof(int));                                                                             // Int ptr creation to point first allocated memo cell inside heap
  if (p == NULL) perror("Error in int malloc!"); else {                                                     // Check malloc funct output to detect allocation errors and print perror fbk
    (*p) = val;                                                                                             // Val definition in heap through pointer dereferencing
  }
  return p;                                                                                                 // Return first allocated memo cell addr inside heap (pointer)
}

static double *calloc_double(const int size, const int pos_offs, const double val){                         // Dyn memo alloc (calloc) for double var funct
  /* Body */
  double *p = calloc(size, sizeof(double));                                                                 // Double ptr creation to point first allocated memo cell inside heap
  if (p == NULL) perror("Error in double calloc!"); else {                                                  // Check calloc funct output to detect allocation errors and print perror fbk
    *(p+pos_offs) = val;                                                                                    // Val definition in heap through pointer dereferencing
  }
  return p;                                                                                                 // Return first allocated memo cell addr inside heap (pointer)
}

static double *realloc_double(double *vect, const int size){                                                // Dyn memo realloc for double var funct
  /* Body */
  double *p = realloc(vect, size*sizeof(double));                                                           // Double ptr creation to point first allocated memo cell inside heap
  if (p == NULL) perror("Error in double realloc!");                                                        // Check realloc funct output to detect allocation errors and print perror fbk
  return p;                                                                                                 // Return first allocated memo cell addr inside heap (pointer) or NULL in case of realloc error
}

static void print_doublevect(const double *vect, const int dim){                                            // Print double vector funct
  /* Body */
  int i = 0;                                                                                                // Idx for printin' operations
  printf("\n%s- Vector: %s[", og, bl);                                                                      // Print vector openin' symbol and txt
  for (;i < dim-1; ++i){                                                                                    // Vector elements print FOR cycle
    printf("%f,", vect[i]);                                                                                 // Print elements
  }
  printf("%f]%s\n", vect[i], er);                                                                           // Print last element with vector closin' symbol
}


/* Main cycle */
int main(){
  /* Main vars */
  int *a;                                                                                                   // Pointer var to access heap (dyn data memo)
  double v[DIM] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};                                                           // Double vector definition

  /* Code */
  logo(4, "DYNAMIC MEMORY MANAGEMENT", ye, '#', gn);                                                        // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  
  // Malloc, realloc and calloc functs need memo allocation size and return memo pointer
  // (might return NULL val, check condition)
  // Malloc doesn't initialize values to zero, calloc does
  // While free funct only needs memo pointer
  a = malloc(sizeof(int));                                                                                  // Dyn memo allocation --> pointer var is allocated in stack (static memo), but refers to heap memo cell (dynamic data memo)
  *(a) = 4;                                                                                                 // Write val into memo cell inside heap (dynamic memory can be accessed only through pointers)
  printf("\n%s- Number: %s%d%s\n", og, bl, *a, er);                                                         // Print dyn memo allocated var
  a = malloc_int(8);                                                                                        // Dyn memo alloc (malloc) for int var funct
  printf("\n%s- Number: %s%d%s\n", og, bl, *a, er);                                                         // Print dyn memo allocated var
  free(a);                                                                                                  // Clear dyn memo allocated for *a int var
  // If memo is reallocated and we try to use it, usually no error is prompted
  // only when a reserved area of the memory is accessed
  double *vect = malloc(DIM*sizeof(int));                                                                   // Allocates DIM doubles in dyn memo --> vectors allocation in heap
  vect[2] = 5;                                                                                              // Use vect syntax to write val (equivalent)
  *(vect+3) = 6;                                                                                            // Use pointer syntax to write val (equivalent)
  printf("\n%s- Number: %s%lf, %lf%s\n", og, bl, vect[2], *(vect+3), er);                                   // Print dyn memo allocated var (vector elements)
  print_doublevect(v, DIM);                                                                                 // Print double vector funct call
  free(vect);                                                                                               // Clear vect in heap

  struct data *ptr = malloc(sizeof(data));                                                                  // Malloc for struct dyn memo allocation through struct pointer
  ptr->d = 5.3;                                                                                             // Write val in struct allocated inside heap
  free(ptr);                                                                                                // Clear ptr in heap

  struct data *dd = malloc(DIM*sizeof(data));                                                               // Malloc for "data" structs vector
  dd[2].i = 5;                                                                                              // Write val in struct vector allocated inside heap (equivalent)
  (dd+2)->i = 5;                                                                                            // Write val in struct vector allocated inside heap (equivalent)
  (*(dd+2)).i = 5;                                                                                          // Write val in struct vector allocated inside heap (equivalent)
  free(dd);                                                                                                 // Clear dd in heap

  int *g = calloc(1,sizeof(int));                                                                           // Calloc(elm_num, size_elem) --> calloc sets to 0 allocated memo
  *g = 7;                                                                                                   // Set g value (equivalent)
  g[0] = 7;                                                                                                 // Set g value (equivalent)
  free (g);                                                                                                 // Clear g in heap
  
  double *vv = calloc(DIM, sizeof(double));                                                                 // Calloc to allocate vv double vector of DIM elements
  print_doublevect(vv, DIM);                                                                                // Print double vector funct call
  free(vv);                                                                                                 // Clear vv in heap

  vv = calloc_double(DIM, 0, 9.8);                                                                          // Dyn memo alloc (calloc) for double var funct call
  print_doublevect(vv, DIM);                                                                                // Print double vector funct call

  double *vv_new = realloc(vv, DIM*sizeof(vv)*2);                                                           // Reallocate memo in heap, create a new pointer in heap with doubled size
                                                                                                            // (check null --> better usin' new vector to avoid NULL overwrite memo cell addr,
                                                                                                            // called memo leak - address might be different)
  
  if (vv_new == NULL) perror("Errore!"); else {                                                             // Check realloc output to detect realloc funct error
    vv = vv_new;                                                                                            // Make sure to complete realloc (in case vector is moved inside heap by realloc)
  }

  vv = realloc_double(vv, 2);                                                                               // Dyn memo realloc for double var funct call
  free(vv_new);                                                                                             // Clear vv_new in heap (vv is cleared in heap by realloc)

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Dynamic memory management (malloc, realloc, calloc, free) lesson
 */
