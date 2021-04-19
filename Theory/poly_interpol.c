/*
 * Author: Cristian Merli
 * Code title: Polynomial interpolation with Newton algorithm and divided-differences
 * Code version: 3.0
 * Creation date: 12/04/2021
 * Last mod. date: 19/04/2021
 */


/* Libraries import */
#include <stdio.h>                                                                                          // Standard I/O library inclusion (for printf ecc.)
#include <string.h>                                                                                         // String library inclusion (for strlen ecc.)
#include <stdlib.h>                                                                                         // Standard library inclusion (for atof ecc.)
#include <math.h>                                                                                           // Math library inclusion (for fabs func ecc.)
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
    v2= 1,                                                                                                  // 2-vectors matrix
    x = 0,                                                                                                  // x-coord = 0 (interpolation points)
    y = 1                                                                                                   // y-coord = 1 (interpolation points)
};


/* Data-types declaration and definition */
typedef unsigned char   byte;                                                                               // Unsigned char alias (byte)
typedef unsigned short  u_shrt;                                                                             // Unsigned short alias (u_shrt)
typedef short           shrt;                                                                               // Short alias (shrt)
typedef double          real;                                                                               // Double alias (real)


/* Public vars declaration and definition */
char in_buff[25];                                                                                           // Input buffer char array for fgets func


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

u_shrt iaddr(u_shrt i, u_shrt j, u_shrt lda){                                                               // Arrays/vectors memo addressing
  /* Function body */
  return (i*lda)+j;                                                                                         // Return index number
}

static void mat_vect_init(real *pts, real *ohm, real *dd, real *p, real *eval, real *deriv, const byte n){  // Matrix and vectors initialization (definition) function
  /* Function body */
  printf("\n");                                                                                             // New line fbk
  for (byte i = 0; i < n; ++i){                                                                             // Matrix and (linear) vectors columns definition FOR cycle
  byte flg;                                                                                                 // While-loop rst flag declaration
    do {                                                                                                    // X-coord input while loop (to avoid x-coord duplicates --> Errors in interpol poly coeff calc)
      flg = 1;                                                                                              // While-loop rst flag definition
      printf("%s-->%s Define the %sx-coord%s of the %s%d°%s val in interpol pts matrix: %s",
             O, C, B, C, B, i+1, C, E);                                                                     // Matrix elements definition (interpolation points x-coods)
      fgets(in_buff, 25, stdin);                                                                            // Save matrix elements (interpolation points x-coods) value into buffer char array --> fgets to avoid char-loop problem associated with scanf --> return 0 in case of char input
      *(pts+iaddr(x, i, n)) = atof(in_buff);                                                                // Convert to double and copy buffer char array val into matrix elements (interpolation points x-coods)
      
      for (byte k = 0; k < i; ++k){                                                                         // Interpolation points x-coods douplicates detection FOR cycle
        if (*(pts+iaddr(x, i, n)) == *(pts+iaddr(x, k, n))){                                                // In case of inserted x-coord alreay present in pts array for another interpolation point
          flg++;                                                                                            // Increment flag value
        }
      }
      if (flg == 1){                                                                                        // In case of flag value not incremented (no x-cood douplicates detected)
        flg = 0;                                                                                            // Reset while-loop flag to continue
      } else {                                                                                              // While, in case of x-coord duplicates detected
        printf("%s    Inserted x-coord value already exists for another interpolation point!%s Retry!%s\n",
               R, LB, E);                                                                                   // Print x-coord duplicates detected fbk
      }
    } while (flg);                                                                                          // X-coord input while loop exit cond (flag rst)
    printf("%s-->%s Define the %sy-coord%s of the %s%d°%s val in interpol pts matrix: %s",
           O, C, B, C, B, i+1, C, E);                                                                       // Matrix elements definition (interpolation points y-coods)
    fgets(in_buff, 25, stdin);                                                                              // Save matrix elements (interpolation points x-coods) value into buffer char array --> fgets to avoid char-loop problem associated with scanf --> return 0 in case of char input
    *(pts+iaddr(y, i, n)) = atof(in_buff);                                                                  // Convert to double and copy buffer char array val into matrix elements (interpolation points y-coods)
    printf("\n");                                                                                           // New line fbk
    *(dd+iaddr(v, i, n)) = *(pts+iaddr(y, i, n));                                                           // Divided-differences vector elements value init
    *(eval+iaddr(v, i, n)) = 0;                                                                             // Poly eval vector elements value init
    *(deriv+iaddr(v, i, n)) = 0;                                                                            // Poly (derivate) vector elements value init
    if (i == 0){                                                                                            // Ohmega poly coefficients vector init (case fist coeff)
      *(ohm+iaddr(v, i, n)) = 1;                                                                            // First ohmega poly coefficient value init to 1
      *(p+iaddr(v, i, n)) = *(pts+iaddr(y, i, n));                                                          // First interpol poly coefficients vector value init to Y0
    } else {                                                                                                // Ohmega poly coefficients vector init (case not-fist coeff)
      *(ohm+iaddr(v, i, n)) = 0;                                                                            // Other ohmega poly coefficients value init to 0
      *(p+iaddr(v, i, n)) = 0;                                                                              // Other interpol poly coefficients vector value init to 0
    }
  }
}

static void mat_print(const real *pts, const byte n){                                                       // Matrix print function
  /* Function body */
  printf("\n\n%s--> %s2x%d%s interpolation points coord matrix: %s\n", O, B, n, C, E);                      // Print mat info
  printf("%s +-------+--------------+--------------+%s\n", Y, E);                                           // Top-line of the table
  printf("%s | %4s  | %7s      | %7s      |%s\n", Y, "Pts", "X", "Y", E);                                   // First line of the table (column identification)
  printf("%s +-------+--------------+--------------+%s\n", Y, E);                                           // Top-line of data in the table
  for (byte j = 0; j < n; ++j){                                                                             // Mat columns idx print FOR cycle
    printf("%s | %s%3d%s   | %s%12lf%s | %s%12lf%s |\n",
           Y, B, j, Y, LB, *(pts+iaddr(x, j, n)), E, LB, *(pts+iaddr(y, j, n)), E);                         // Mat elements print --> | point_idx | X | Y |
    printf("%s +-------+%s--------------+--------------+\n", Y, E);                                         // Bootom-line of data in the table
  }
}

static void poly_interpol(real *pts, real *ohm, real *dd, real *p, const byte n){                           // Poly interpolation function
  /* Function body */
  for (byte k = 1; k < n; ++k){                                                                             // Offset FOR cycle to calculate divided-differences, ohmega and poly vectors
    *(ohm+iaddr(v, k, n)) = *(ohm+iaddr(v, k-1, n));                                                        // Ohmega vector's val shift
    for (byte j = k-1; j >= 1; --j){                                                                        // Ohmega update calc FOR cycle
      *(ohm+iaddr(v, j, n)) = *(ohm+iaddr(v, j-1, n)) - (*(ohm+iaddr(v, j, n)) *
                              (*(pts+iaddr(x, k-1, n))));                                                   // Ohmega update
    }
    *(ohm+iaddr(v, 0, n)) *= -(*(pts+iaddr(x, k-1, n)));                                                    // Ohmega update
    for (byte j = n-1; j >= k; j--){                                                                        // Divided-differences calc FOR cycle
      *(dd+iaddr(v, j, n)) = (*(dd+iaddr(v, j, n)) - *(dd+iaddr(v, j-1, n))) /
                             (*(pts+iaddr(x, j, n)) - *(pts+iaddr(x, j-k, n)));                             // Divided-differences calc
    }
    for (byte j = 0; j <= k; ++j){                                                                          // Poly coefficients cakc FOR cycle
      *(p+iaddr(v, j, n)) += (*(dd+iaddr(v, k, n)) * (*(ohm+iaddr(v, j, n))));                              // Poly coefficients calc
    }
  }
}

static void poly_print(const real *poly, const byte n){                                                     // Poly print function
  /* Function body */
  if (*poly > 0){                                                                                           // If constant poly coeff is > 0
    printf("+%.3lf", *poly);                                                                                // Print positive constant poly coeff
  } else if (*poly < 0){                                                                                    // Else if constant poly coeff is < 0
    printf("-%.3lf", -*poly);                                                                               // Print negative constant poly coeff
  }
  double sum = *poly;                                                                                       // Define poly coeff sum to determine whether the poly is = 0, to print null poly fbk (define init val as const poly coeff)
  for (byte j = 1; j < n; ++j){                                                                             // Poly print FOR cycle (constant coeff excluded) 
    if (*(poly+iaddr(v, j, n)) < 0){                                                                        // In case of negative poly coeff
      printf("-%.3lf*(x^%d)", -(*(poly+iaddr(v, j, n))), j);                                                // Print negative val in poly
    } else if (*(poly+iaddr(v, j, n)) > 0){                                                                 // In case of positive poly coeff
      printf("+%.3lf*(x^%d)", *(poly+iaddr(v, j, n)), j);                                                   // Print positive val in poly
    } else {                                                                                                // In case of null poly coeff
      continue;                                                                                             // Skip poly coeff print
    }
    sum += *(poly+iaddr(v, j, n));                                                                          // Poly coeff sum val upd
  }
  if (sum == 0){                                                                                            // Check whether poly is = 0
    printf("%s0%s\n", Y, E);                                                                                // print null poly fbk
  } else {                                                                                                  // Else, if poly is != 0
    printf("\n");                                                                                           // New line fbk (Poly already printed)
  }
}

static void poly_eval(const real *pts, const real *p, real *eval, const byte n){                            // Poly evaluation function (Horner roule)
  /* Function body */
  for (byte k = 0; k < n; ++k){                                                                             // Poly eval in each given point FOR cycle
    *(eval+iaddr(v, k, n)) = *(p+iaddr(v, n-1, n));                                                         // Poly eval val update
    for (shrt j = n-2; j >= 0; --j){                                                                        // Poly eval FOR cycle
      *(eval+iaddr(v, k, n)) *=  *(pts+iaddr(x, k, n));                                                     // Poly eval val update
      *(eval+iaddr(v, k, n)) += *(p+iaddr(v, j, n));                                                        // Poly eval val update
    }
    printf("\n p(%sx%d%s) = p(%s%lf%s) = %s%lf%s",
           B, k, E, LB, *(pts+iaddr(x, k, n)), E, LB, *(eval+iaddr(v, k, n)), E);                           // Print poly eval val
    if (fabs((*(eval+iaddr(v, k, n)) - *(pts+iaddr(y, k, n)))) < 0.0001){                                   // Check poly interpol (case OK) --> [with aprox to zero]
      printf("%s  -->%s  (=%sy0%s) OK!%s", O, G, B, G, E);                                                  // Print interpolation OK fbk
    } else {                                                                                                // Check poly interpol (case NOT-OK)
      printf("%s  -->%s  (!=%sy0%s) NOT OK!%s", O, R, B, R, E);                                             // Print interpolation NOT-OK fbk
    }
  }
  printf("\n");                                                                                             // New line fbk
}

static void poly_deriv(const real *poly, real *deriv, const byte n){                                        // Poly derivation function
  /* Function body */
  for (byte k = 1; k < n; ++k){                                                                             // Poly derivate calc FOR cycle
    *(deriv+iaddr(v, k-1, n)) = k * (*(poly+iaddr(v, k, n)));                                               // Poly derivate calc
  }
  *(deriv+iaddr(v, n-1, n)) = 0;                                                                            // Set to 0 last degree coeff
}


/* Main cycle */
int main(){
  /* Main vars declaration and definition */
  byte n;                                                                                                   // Number of interpolation points (= poly degree + 1) declaration
  byte n_minval = 1;                                                                                        // Input val n, min val range limit
  byte n_maxval = 170;                                                                                      // Input val n, max val range limit
  shrt tmp_chk = 0;                                                                                         // Tmp var to check n input val from terminal in allowed range

  /* Code */
  logo(4, "POLYNOMIAL INTERPOLATION WITH NEWTON ALGORITHM", Y, '#', G);                                     // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  do {                                                                                                      // Expect input val in range while-loop
    printf("\n\n%s>>>%s Specify the number of interpolation points (val between %hu and %hu): %s",
           G, P, n_minval, n_maxval, E);                                                                    // Number of interpolation points (= poly degree + 1) definition request fbk
    fgets(in_buff, 25, stdin);                                                                              // Save input val from terminal into buffer char array --> fgets to avoid char-loop problem associated with scanf
    tmp_chk = atof(in_buff);                                                                                // Convert to double and copy buffer char array val into tmp var
    if (tmp_chk >= n_minval && tmp_chk <= n_maxval){                                                        // Tmp var check (case in range)
      n = tmp_chk;                                                                                          // Number of interpolation points (= poly degree + 1) val definition
    } else {                                                                                                // Tmp var check (case out of range)
      printf("%sInput val error! The value must be between %hu and %hu. %sRetry!%s",
             R, n_minval, n_maxval, C, E);                                                                  // Print error fbk
    }
  } while ((tmp_chk < n_minval || tmp_chk > n_maxval));                                                     // Expect input val in range while-loop exit cond

  real pts[iaddr(v2, n, n)];                                                                                // Points to interpolate coords matrix declaration (in execution)
  real ohm[iaddr(v, n, n)];                                                                                 // Ohmega poly coefficients vector declaration (in execution)
  real dd[iaddr(v, n, n)];                                                                                  // Divided-defferences vector declaration (in execution)
  real p[iaddr(v, n, n)];                                                                                   // Interpol poly coefficients vector declaration (in execution)
  real eval[iaddr(v, n, n)];                                                                                // Interpol poly evaluation in each given point vector declaration (in execution)
  real deriv[iaddr(v, n, n)];                                                                               // Interpol poly derivation vector declaration (in execution)

  mat_vect_init(pts, ohm, dd, p, eval, deriv, n);                                                           // Matrix and vectors initialization (definition) function call
  printf("\n%s>>>%s Defined points coord matrix:%s", G, P, E);                                              // Defined matrix fbk
  mat_print(pts, n);                                                                                        // Matrix print function call
  poly_interpol(pts, ohm, dd, p, n);                                                                        // Poly interpolation function call
  printf("\n\n%s>>>%s Points interpolation poly: %s", G, P, E);                                             // Points interpolation poly fbk
  poly_print(p, n);                                                                                         // Poly print function call
  printf("\n\n%s>>>%s Poly evaluation in given points: %s", G, P, E);                                       // Poly evaluation in given points fbk
  poly_eval(pts, p, eval, n);                                                                               // Poly evaluation function call (Horner roule)
  poly_deriv(p, deriv, n);                                                                                  // Poly derivation function call
  printf("\n\n%s>>>%s Derivated poly: %s", G, P, E);                                                        // Poly derivation fbk
  poly_print(deriv, n);                                                                                     // Poly (derivate) print function call
  printf("\n\n%s>>>%s Done! %s;)%s\n", G, P, C, E);                                                         // Final line fbk

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Polynomial interpolation C code --> Newton algorithm with divided-differences
 */
