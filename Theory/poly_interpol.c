/*
 * Author: Cristian Merli
 * Code title: Polynomial interpolation with Newton algorithm and divided-differences
 * Code version: 2.0
 * Creation date: 12/04/2021
 * Last mod. date: 18/04/2021
 */


/* Libraries import */
#include <stdio.h>                                                                                          // Standard I/O library inclusion (for printf ecc.)
#include <string.h>                                                                                         // String library inclusion (for strlen ecc.)
#include <math.h>                                                                                           // -
#include <sys/ioctl.h>                                                                                      // -
#include <unistd.h>                                                                                         // -                                                                                       // Math library inclusion (for fabs func ecc.)


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
typedef double          real;                                                                               // Double alias (real)


/* Functions declaration and definition */
static void logo(const byte vthck, const byte lthck_vthik_r, const byte start_sp, const byte lsp,           // Static function (readable only in this .c file) and const param (not modified in function --> SW optimization at compile-time)
          const char txt[], const char txt_col[], const char bkg_chr, const char bkg_col[]){                // Print logo function
  /* Function body */
  struct winsize w;                                                                                         // -
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);                                                                     // -
  printf ("lines %d\n", w.ws_row);                                                                          // -
  printf ("columns %d\n", w.ws_col);                                                                        // -

  printf("\n%s", bkg_col);                                                                                  // New line
  byte len = 2*lthck_vthik_r*vthck+2*lsp+strlen(txt);                                                       // Logo length calc
  for (byte i = 0; i < (4*vthck+1); ++i){                                                                   // Logo lines print FOR cycle
    for (byte j = 0; j < start_sp; ++j){                                                                    // Initial spaces print FOR cycle
      printf(" ");                                                                                          // Print initial spaces
    }
    if ((i < vthck || i > (3*vthck)) && (i != (4*vthck)/2)){                                                // Full bkg logo lines print cond
      for (byte h = 0; h < len; ++h){                                                                       // Full bkg logo lines print FOR cycle
        printf("%c", bkg_chr);                                                                              // Bkg logo char print
      }
      printf("\n");                                                                                         // New line
    } else if ((i >= vthck && i <= (3*vthck)) && (i != (4*vthck)/2)) {                                      // Partial-empty bkg logo lines print cond
      for (byte l = 0; l < lthck_vthik_r*vthck; ++l){                                                       // Partial-empty bkg logo lines, initial full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Partial-empty bkg logo lines, initial full part print
      }
      for (byte m = 0; m < (len - 2*lthck_vthik_r*vthck); ++m){                                             // Partial-empty bkg logo lines, central empty part print FOR cycle
        printf(" ");                                                                                        // Partial-empty bkg logo lines, central empty part print
      }
      for (byte n = 0; n < lthck_vthik_r*vthck; ++n){                                                       // Partial-empty bkg logo lines, final full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Partial-empty bkg logo lines, final full part print
      }
      printf("\n");                                                                                         // New line
    } else if (i == ((4*vthck)/2)) {                                                                        // Text logo line initial full part print cond
      for (byte o = 0; o < lthck_vthik_r*vthck; ++o){                                                       // Text logo line initial full part print FOR cycle
        printf("%C", bkg_chr);                                                                              // Text logo line initial full part print
      }
      for (byte p = 0; p < lsp; ++p){                                                                       // Text logo line central empty part print FOR cycle
        printf(" ");                                                                                        // Text logo line central empty part print
      }
      printf("%s%s%s", txt_col, txt, bkg_col);                                                              // Text logo line central text part print
      for (byte q = 0; q < lsp; ++q){                                                                       // Text logo line central empty part print FOR cycle
        printf(" ");                                                                                        // Text logo line central empty part print
      }
      for (byte r = 0; r < lthck_vthik_r*vthck; ++r){                                                       // Text logo line final full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Text logo line final full part print
      }
      printf("\n");                                                                                         // New line
    }
  }
  printf("\033[0m\n");                                                                                      // New line and erase logo bkg color
}

u_shrt iaddr(u_shrt i, u_shrt j, u_shrt lda){                                                               // Arrays/vectors memo addressing
  /* Function body */
  return (i*lda)+j;                                                                                         // Return index number
}

static void mat_vect_init(real *pts, real *ohm, real *dd, real *p, real *eval, real *deriv, const byte n){  // Matrix and vectors initialization (definition) function
  /* Function body */
  printf("\n");                                                                                             // New line fbk
  for (byte i = 0; i < n; ++i){                                                                             // Matrix and (linear) vectors columns definition FOR cycle
    printf("%s-->%s Define the %sx-coord%s of the %s%d°%s val in interpol pts matrix: %s",
          O, C, B, C, B, i+1, C, E);                                                                        // Matrix elements definition (interpolation points x-coods)
    scanf("%lf", &*(pts+iaddr(x, i, n)));                                                                   // Matrix elements (interpolation points x-coods) value init
    printf("%s-->%s Define the %sy-coord%s of the %s%d°%s val in interpol pts matrix: %s",
          O, C, B, C, B, i+1, C, E);                                                                        // Matrix elements definition (interpolation points y-coods)
    scanf("%lf", &*(pts+iaddr(y, i, n)));                                                                   // Matrix elements (interpolation points y-coods) value init
    printf("\n");                                                                                           // New line fbk
    *(dd+iaddr(v, i, n)) = *(pts+iaddr(y, i, n));                                                           // Divided-differences vector elements value init
    *(eval+iaddr(v, i, n)) = 0;                                                                             // Poly eval vector elements value init
    *(deriv+iaddr(v, i, n)) = 0;                                                                            // -
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
  for (byte j = 0; j < n; ++j){                                                                             // Mat columns idx print FOR cycle                                                                                             // Other mat elements print cond
    printf("%s | %s%3d%s   | %s%12lf%s | %s%12lf%s |\n",
          Y, B, j+1, Y, LB, *(pts+iaddr(x, j, n)), E, LB, *(pts+iaddr(y, j, n)), E);                        // Mat elements print --> | point_idx | X | Y |
    printf("%s +-------+%s--------------+--------------+\n", Y, E);                                         // Bootom-line of data in the table
  }
}

static void poly_interpol(real *pts, real *ohm, real *dd, real *p, const byte n){                           // Poly interpolation function
  /* Function body */
  for (byte k = 1; k < n; ++k){                                                                             // Offset FOR cycle to calculate divided-differences, ohmega and poly vectors
    *(ohm+iaddr(v, k, n)) = *(ohm+iaddr(v, k-1, n));                                                        // Ohmega vector's val shift
    for (byte j = k-1; j >= 1; --j){                                                                        // Ohmega update FOR cycle
      *(ohm+iaddr(v, j, n)) = *(ohm+iaddr(v, j-1, n)) - (*(ohm+iaddr(v, j, n)) *
                              (*(pts+iaddr(x, k-1, n))));                                                   // Complete ohmega update
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
  if (*poly != 0){                                                                                          // If constant poly coeff is no null
    printf("%.2lf", *poly);                                                                                 // Print constant poly coeff
  }
  for (byte j = 1; j < n; ++j){                                                                             // Poly print FOR cycle (constant coeff excluded) 
    if (*(poly+iaddr(v, j, n)) < 0){                                                                        // In case of negative poly coeff
      printf("-%.3lfx^%d", -(*(poly+iaddr(v, j, n))), j);                                                   // Print negative val in poly
    } else if (*(poly+iaddr(v, j, n)) > 0){                                                                 // In case of positive poly coeff
      printf("+%.3lfx^%d", *(poly+iaddr(v, j, n)), j);                                                      // Print positive val in poly
    } else {                                                                                                // In case of null poly coeff
      continue;                                                                                             // Skip poly coeff print
    }
  }
}

static void poly_eval(const real *pts, const real *p, real *eval, const byte n){                            // Poly evaluation function
  /* Function body */
  for (byte k = 0; k < n; ++k){                                                                             // -
    for (byte j = 0; j < k; ++j){                                                                           // -
      *(eval+iaddr(v, k, n)) += ((*(p+iaddr(v, j, n))) * pow(*(pts+iaddr(x, j, n)), j));                    // -
    }
    printf(" %lf ", *(eval+iaddr(v, k, n)));                                                                // -
  }
}

static void poly_deriv(const real *poly, real *deriv, const byte n){                                        // Poly derivation function
  /* Function body */
  for (byte k = 0; k < n; ++k){                                                                             // -
    //
  }
}


/* Main cycle */
int main(){
  /* Main vars declaration and definition */
  byte n;                                                                                                   // Number of interpolation points (= poly degree + 1) declaration

  /* Code */
  logo(5, 3, 2, 15, "POLY INTERPOL WITH NEWTON ALGORITHM", Y, 'X', G);                                      // Print logo function call (vert_thick, lat_thick_vert_thick_ratio, start_spaces, lat_spaces, text, txt_color, background_char, bkgchr_color)
  printf("\n\n%s>>>%s Specify the number of interpolation points: %s", G, P, E);                            // Number of interpolation points (= poly degree + 1) definition request fbk
  scanf("%hhu", &n);                                                                                        // Number of interpolation points (= poly degree + 1) val definition
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
  poly_eval(pts, p, eval, n);                                                                               // Poly evaluation function call
  poly_deriv(p, deriv, n);                                                                                  // Poly derivation function call
  printf("\n\n%s>>>%s Derivated poly: %s", G, P, E);                                                        // Poly derivation fbk
  poly_print(deriv, n);                                                                                     // Poly (derivate) print function call
  printf("\n");                                                                                             // New line

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Polynomial interpolation C code --> Newton algorithm with divided-differences
 */
