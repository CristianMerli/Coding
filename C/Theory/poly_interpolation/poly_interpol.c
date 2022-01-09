/*!
 * \mainpage    Project description
 *              Polynomial interpolation C code mainly based on pointers.
 * 
 * @author      Cristian Merli
 * @date        12/04/2021
 * @version     3.0 - Completed 19/04/2021
 * @note        Important notes:
 *                - The algorithm supports interpolation 'till 170 points.
 *                - This software is composed by a single .c file and contains all the necessary functions (no pre-compiled libraries needed).
 * @warning     Pay attention, inpt buffer is only 25 chars long.
 * @bug         No known bugs.
 * 
 * \section     section1 Code title:
 *              Polynomial interpolation with Newton algorithm and divided-differences.
 * 
 * \subsection  subsection1 Code details:
 *              Polynomial interpolation C code --> Newton algorithm with divided-differences to interpolate 'till 170 points,
 *              polynomial evaluation in given points and derivate calculation.
 * 
 * @file        poly_interpol.c Polynomial interpolation C code.
 * @brief       Polynomial interpolation C code mainly based on pointers.
 */


/* Libraries import */
#include <stdio.h>                                                                                          // Standard I/O library inclusion (for printf ecc.)
#include <string.h>                                                                                         // String library inclusion (for strlen ecc.)
#include <stdlib.h>                                                                                         // Standard library inclusion (for atof ecc.)
#include <math.h>                                                                                           // Math library inclusion (for fabs func ecc.)
#include <sys/ioctl.h>                                                                                      // System I/O control library inclusion (for ioctl ecc.)
#include <unistd.h>                                                                                         // UniStd library inclusion (for stdout ecc.)


/* Constants declaration and definition */
/// Terminal colors constant char variables.
/// \var const char *rd
/// Red termianl color code.
/// \var const char *bl
/// Blue termianl color code.
/// \var const char *lb
/// Light-blue termianl color code.
/// \var const char *pu
/// Purple termianl color code.
/// \var const char *cy
/// Cyan termianl color code.
/// \var const char *ye
/// Yellow termianl color code.
/// \var const char *og
/// Orange termianl color code.
/// \var const char *gn
/// Green termianl color code.
/// \var const char *lgn
/// Light-green termianl color code.
/// \var const char *lgy
/// Light-gray termianl color code.
/// \var const char *er
/// Erase termianl color code.
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


/* Enums declaration and definition */
/// Coordinates enum, indexes for the iaddr() function.
/// \var V
/// Vectors addressing.
/// \var V2
/// 2d-matrix addressing (composed by 2 vectors).
/// \var X
/// 2d-matrix addressing (X coordinate) --> used for *pts vector to represent a 2d-matrix using the iaddr() function.
/// \var Y
/// 2d-matrix addressing (Y coordinate) --> used for *pts vector to represent a 2d-matrix using the iaddr() function.
enum coords                                                                                                 // Matrix/vectors enum
{
    V = 0,                                                                                                  // Vectors
    V2= 1,                                                                                                  // 2-vectors matrix
    X = 0,                                                                                                  // X-coord = 0 (interpolation points)
    Y = 1                                                                                                   // Y-coord = 1 (interpolation points)
};


/* Data-types declaration and definition */
/*! Typedef to define unsigned char as byte. */
typedef unsigned char   byte;                                                                               // Unsigned char alias (byte)
/*! Typedef to define unsigned short as u_shrt. */
typedef unsigned short  u_shrt;                                                                             // Unsigned short alias (u_shrt
/*! Typedef to define short as shrt. */
typedef short           shrt;                                                                               // Short alias (shrt)
/*! Typedef to define double as real. */
typedef double          real;                                                                               // Double alias (real)


/* Global vars declaration and definition */
/// Terminal chars input buffer.
/// \var char in_buff[25]
char in_buff[25];                                                                                           // Input buffer char array for fgets func


/* Functions declaration and definition */
/*!
 * @brief               Print logo routine.
 * 
 * \param[in] start_sp  Start (left) spaces in logo print - try to do the same on the right-side roundinc calc to int
 * \param[in] txt       Title text string
 * \param[in] txt_col   Title text color
 * \param[in] bkg_chr   Logo backgroung char
 * \param[in] bkg_col   Logo backgroung color
 * 
 * @return              None.
 */
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
  printf("\033[0m\n"  );                                                                                      // New line fbk and erase logo bkg color
}

/*!
 * @brief         Vectors, arrays and pointers addressing function (treat all as 1d array = vector).
 * 
 * \param[in] i   Line number (starting from 0 since C is a zero-index language)
 * \param[in] j   Column number (starting from 0 since C is a zero-index language)
 * \param[in] lda Leading-dimension (Max number of columns for each matrix line, since the C languace follows line-indexing to allocate memory cells for matrix)
 * 
 * @return        Vector/pointer index number.
 */
static u_shrt iaddr(u_shrt i, u_shrt j, u_shrt lda){                                                        // Arrays/vectors memo addressing
  /* Function body */
  return (i*lda)+j;                                                                                         // Return index number
}

/*!
 * @brief               Interpolation points matrix and vectors initialization routine (using pointers and vectors defined by the iaddre() function).
 * 
 * \param[in,out] pts   Points matrix containig defined points x and y coordinates
 * \param[in,out] ohm   Ohmega vector containing the ohmega polynomial coefficients
 * \param[in,out] dd    Divided-defferences vector containing divided-differences values
 * \param[in,out] p     Interpolation vector containing the interpolation polynomial coefficients
 * \param[in,out] eval  Evalutaion vector used to evaluate the polynomial in given points coordinates (through Horner's role) to check the interpolation, without modifying the interpolation polynomial
 * \param[in,out] deriv Derivate vector containing the polynomial coefficients of the interpolation polynomial's derivate
 * \param[in] n         Number of interpolation points (= Number of the interpolation polynomial coefficients), (= Degree of the interpolation polynomial + 1)
 * 
 * @return              None.
 */
static void mat_vect_init(real *pts, real *ohm, real *dd, real *p, real *eval, real *deriv, const byte n){  // Matrix and vectors initialization (definition) function
  /* Function body */
  printf("\n");                                                                                             // New line fbk
  for (byte i = 0; i < n; ++i){                                                                             // Matrix and (linear) vectors columns definition FOR cycle
  byte flg;                                                                                                 // While-loop rst flag declaration
    do {                                                                                                    // X-coord input while loop (to avoid x-coord duplicates --> Errors in interpol poly coeff calc)
      flg = 1;                                                                                              // While-loop rst flag definition
      printf("%s-->%s Define the %sx-coord%s of the %s%d°%s val in interpol pts matrix: %s",
             og, cy, bl, cy, bl, i+1, cy, er);                                                              // Matrix elements definition (interpolation points x-coods)
      fgets(in_buff, sizeof(in_buff), stdin);                                                               // Save matrix elements (interpolation points x-coods) value into buffer char array --> fgets to avoid char-loop problem associated with scanf
      *(pts+iaddr(X, i, n)) = atof(in_buff);                                                                // Convert to double and copy buffer char array val into matrix elements (interpolation points x-coods) --> return 0 in case of char input
      
      for (byte k = 0; k < i; ++k){                                                                         // Interpolation points x-coods douplicates detection FOR cycle
        if (*(pts+iaddr(X, i, n)) == *(pts+iaddr(X, k, n))){                                                // In case of inserted x-coord alreay present in pts array for another interpolation point
          flg++;                                                                                            // Increment flag value
        }
      }
      if (flg == 1){                                                                                        // In case of flag value not incremented (no x-cood douplicates detected)
        flg = 0;                                                                                            // Reset while-loop flag to continue
      } else {                                                                                              // While, in case of x-coord duplicates detected
        printf("%s    Inserted x-coord value already exists for another interpolation point!%s Retry!%s\n",
               rd, lb, er);                                                                                 // Print x-coord duplicates detected fbk
      }
    } while (flg);                                                                                          // X-coord input while loop exit cond (flag rst)
    printf("%s-->%s Define the %sy-coord%s of the %s%d°%s val in interpol pts matrix: %s",
           og, cy, bl, cy, bl, i+1, cy, er);                                                                // Matrix elements definition (interpolation points y-coods)
    fgets(in_buff, sizeof(in_buff), stdin);                                                                 // Save matrix elements (interpolation points x-coods) value into buffer char array --> fgets to avoid char-loop problem associated with scanf
    *(pts+iaddr(Y, i, n)) = atof(in_buff);                                                                  // Convert to double and copy buffer char array val into matrix elements (interpolation points y-coods) --> return 0 in case of char input
    printf("\n");                                                                                           // New line fbk
    *(dd+iaddr(V, i, n)) = *(pts+iaddr(Y, i, n));                                                           // Divided-differences vector elements value init
    *(eval+iaddr(V, i, n)) = 0;                                                                             // Poly eval vector elements value init
    *(deriv+iaddr(V, i, n)) = 0;                                                                            // Poly (derivate) vector elements value init
    if (i == 0){                                                                                            // Ohmega poly coefficients vector init (case fist coeff)
      *(ohm+iaddr(V, i, n)) = 1;                                                                            // First ohmega poly coefficient value init to 1
      *(p+iaddr(V, i, n)) = *(pts+iaddr(Y, i, n));                                                          // First interpol poly coefficients vector value init to Y0
    } else {                                                                                                // Ohmega poly coefficients vector init (case not-fist coeff)
      *(ohm+iaddr(V, i, n)) = 0;                                                                            // Other ohmega poly coefficients value init to 0
      *(p+iaddr(V, i, n)) = 0;                                                                              // Other interpol poly coefficients vector value init to 0
    }
  }
}

/*!
 * @brief         Interpolation points matrix print [as table] routine (using pointers and vectors defined by the iaddre() function).
 * 
 * \param[in] pts Points matrix containig defined points x and y coordinates
 * \param[in] n   Number of interpolation points (= Number of the interpolation polynomial coefficients), (= Degree of the interpolation polynomial + 1)
 * 
 * @return        None.
 */
static void mat_print(const real *pts, const byte n){                                                       // Matrix print function
  /* Function body */
  printf("\n\n%s--> %s2x%d%s interpolation points coord matrix: %s\n", og, bl, n, cy, er);                  // Print mat info
  printf("%s +-------+--------------+--------------+%s\n", ye, er);                                         // Top-line of the table
  printf("%s | %4s  | %7s      | %7s      |%s\n", ye, "Pts", "X", "Y", er);                                 // First line of the table (column identification)
  printf("%s +-------+--------------+--------------+%s\n", ye, er);                                         // Top-line of data in the table
  for (byte j = 0; j < n; ++j){                                                                             // Mat columns idx print FOR cycle
    printf("%s | %s%3d%s   | %s%12lf%s | %s%12lf%s |\n",
           ye, bl, j, ye, lb, *(pts+iaddr(X, j, n)), er, lb, *(pts+iaddr(Y, j, n)), er);                    // Mat elements print --> | point_idx | X | Y |
    printf("%s +-------+%s--------------+--------------+\n", ye, er);                                       // Bootom-line of data in the table
  }
}

/*!
 * @brief               Polynomial interpolation of given points routine (using pointers and vectors defined by the iaddre() function).
 * 
 * \param[in,out] pts   Points matrix containig defined points x and y coordinates
 * \param[in,out] ohm   Ohmega vector containing the ohmega polynomial coefficients
 * \param[in,out] dd    Divided-defferences vector containing divided-differences values
 * \param[in,out] p     Interpolation vector containing the interpolation polynomial coefficients
 * \param[in] n         Number of interpolation points (= Number of the interpolation polynomial coefficients), (= Degree of the interpolation polynomial + 1)
 * 
 * @return              None.
 */
static void poly_interpol(real *pts, real *ohm, real *dd, real *p, const byte n){                           // Poly interpolation function
  /* Function body */
  for (byte k = 1; k < n; ++k){                                                                             // Offset FOR cycle to calculate divided-differences, ohmega and poly vectors
    *(ohm+iaddr(V, k, n)) = *(ohm+iaddr(V, k-1, n));                                                        // Ohmega vector's val shift
    for (byte j = k-1; j >= 1; --j){                                                                        // Ohmega update calc FOR cycle
      *(ohm+iaddr(V, j, n)) = *(ohm+iaddr(V, j-1, n)) - (*(ohm+iaddr(V, j, n)) *
                              (*(pts+iaddr(X, k-1, n))));                                                   // Ohmega update
    }
    *(ohm+iaddr(V, 0, n)) *= -(*(pts+iaddr(X, k-1, n)));                                                    // Ohmega update
    for (byte j = n-1; j >= k; j--){                                                                        // Divided-differences calc FOR cycle
      *(dd+iaddr(V, j, n)) = (*(dd+iaddr(V, j, n)) - *(dd+iaddr(V, j-1, n))) /
                             (*(pts+iaddr(X, j, n)) - *(pts+iaddr(X, j-k, n)));                             // Divided-differences calc
    }
    for (byte j = 0; j <= k; ++j){                                                                          // Poly coefficients cakc FOR cycle
      *(p+iaddr(V, j, n)) += (*(dd+iaddr(V, k, n)) * (*(ohm+iaddr(V, j, n))));                              // Poly coefficients calc
    }
  }
}

/*!
 * @brief           Polynomial print routine (using pointers and vectors defined by the iaddre() function).
 * 
 * \param[in] poly  Interpolation vector containing the interpolation polynomial coefficients
 * \param[in] n     Number of interpolation points (= Number of the interpolation polynomial coefficients), (= Degree of the interpolation polynomial + 1)
 * 
 * @return          None.
 */
static void poly_print(const real *poly, const byte n){                                                     // Poly print function
  /* Function body */
  if (*poly > 0){                                                                                           // If constant poly coeff is > 0
    printf("+%.3lf", *poly);                                                                                // Print positive constant poly coeff
  } else if (*poly < 0){                                                                                    // Else if constant poly coeff is < 0
    printf("-%.3lf", -*poly);                                                                               // Print negative constant poly coeff
  }
  double sum = *poly;                                                                                       // Define poly coeff sum to determine whether the poly is = 0, to print null poly fbk (define init val as const poly coeff)
  for (byte j = 1; j < n; ++j){                                                                             // Poly print FOR cycle (constant coeff excluded) 
    if (*(poly+iaddr(V, j, n)) < 0){                                                                        // In case of negative poly coeff
      printf("-%.3lf*(x^%d)", -(*(poly+iaddr(V, j, n))), j);                                                // Print negative val in poly
    } else if (*(poly+iaddr(V, j, n)) > 0){                                                                 // In case of positive poly coeff
      printf("+%.3lf*(x^%d)", *(poly+iaddr(V, j, n)), j);                                                   // Print positive val in poly
    } else {                                                                                                // In case of null poly coeff
      continue;                                                                                             // Skip poly coeff print
    }
    sum += *(poly+iaddr(V, j, n));                                                                          // Poly coeff sum val upd
  }
  if (sum == 0){                                                                                            // Check whether poly is = 0
    printf("%s0%s\n", ye, er);                                                                              // print null poly fbk
  } else {                                                                                                  // Else, if poly is != 0
    printf("\n");                                                                                           // New line fbk (Poly already printed)
  }
}

/*!
 * @brief               Polynomial evaluation in given points coordinates (through Horner's role) to check interpolation routine (using pointers and vectors defined by the iaddre() function).
 * 
 * \param[in] pts       Points matrix containig defined points x and y coordinates
 * \param[in] poly      Interpolation vector containing the interpolation polynomial coefficients
 * \param[in, out] eval Evalutaion vector used to evaluate the polynomial in given points coordinates (through Horner's role) to check the interpolation, without modifying the interpolation polynomial
 * \param[in] n         Number of interpolation points (= Number of the interpolation polynomial coefficients), (= Degree of the interpolation polynomial + 1)
 * 
 * @return              None.
 */
static void poly_eval(const real *pts, const real *poly, real *eval, const byte n){                         // Poly evaluation function (Horner's roule)
  /* Function body */
  for (byte k = 0; k < n; ++k){                                                                             // Poly eval in each given point FOR cycle
    *(eval+iaddr(V, k, n)) = *(poly+iaddr(V, n-1, n));                                                      // Poly eval val update
    for (shrt j = n-2; j >= 0; --j){                                                                        // Poly eval FOR cycle
      *(eval+iaddr(V, k, n)) *=  *(pts+iaddr(X, k, n));                                                     // Poly eval val update
      *(eval+iaddr(V, k, n)) += *(poly+iaddr(V, j, n));                                                     // Poly eval val update
    }
    printf("\n p(%sx%d%s) = p(%s%lf%s) = %s%lf%s",
           bl, k, er, lb, *(pts+iaddr(X, k, n)), er, lb, *(eval+iaddr(V, k, n)), er);                       // Print poly eval val
    if (fabs((*(eval+iaddr(V, k, n)) - *(pts+iaddr(Y, k, n)))) < 0.0001){                                   // Check poly interpol (case OK) --> [with aprox to zero]
      printf("%s  -->%s  (=%sy0%s) OK!%s", og, gn, bl, gn, er);                                             // Print interpolation OK fbk
    } else {                                                                                                // Check poly interpol (case NOT-OK)
      printf("%s  -->%s  (!=%sy0%s) NOT OK!%s", og, rd, bl, rd, er);                                        // Print interpolation NOT-OK fbk
    }
  }
  printf("\n");                                                                                             // New line fbk
}

/*!
 * @brief               Interpolation polynomial's derivate calculation routine (using pointers and vectors defined by the iaddre() function).
 * 
 * \param[in] poly      Interpolation vector containing the interpolation polynomial coefficients
 * \param[in,out] deriv Derivate vector containing the polynomial coefficients of the interpolation polynomial's derivate
 * \param[in] n         Number of interpolation points (= Number of the interpolation polynomial coefficients), (= Degree of the interpolation polynomial + 1)
 * 
 * @return              None.
 */
static void poly_deriv(const real *poly, real *deriv, const byte n){                                        // Poly derivation function
  /* Function body */
  for (byte k = 1; k < n; ++k){                                                                             // Poly derivate calc FOR cycle
    *(deriv+iaddr(V, k-1, n)) = k * (*(poly+iaddr(V, k, n)));                                               // Poly derivate calc
  }
  *(deriv+iaddr(V, n-1, n)) = 0;                                                                            // Set to 0 last degree coeff
}


/* Main cycle */
/*!
 * @brief           Main routine, manage UI and functions/routines call
 *                  (using pointers and vectors defined by the iaddre() function).
 * @return          None.
 */
int main(){
  /* Main vars declaration and definition */
  byte n;                                                                                                   // Number of interpolation points (= poly degree + 1) declaration
  byte n_minval = 1;                                                                                        // Input val n, min val range limit
  byte n_maxval = 170;                                                                                      // Input val n, max val range limit
  shrt tmp_chk = 0;                                                                                         // Tmp var to check n input val from terminal in allowed range

  /* Code */
  logo(4, "POLYNOMIAL INTERPOLATION WITH NEWTON ALGORITHM", ye, '#', gn);                                   // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  do {                                                                                                      // Expect input val in range while-loop
    printf("\n\n%s>>>%s Specify the number of interpolation points (val between %hu and %hu): %s",
           gn, pu, n_minval, n_maxval, er);                                                                 // Number of interpolation points (= poly degree + 1) definition request fbk
    fgets(in_buff, sizeof(in_buff), stdin);                                                                 // Save input val from terminal into buffer char array --> fgets to avoid char-loop problem associated with scanf when detects char expecting numeric val
    tmp_chk = atof(in_buff);                                                                                // Convert to double and copy buffer char array val into tmp var
    if (tmp_chk >= n_minval && tmp_chk <= n_maxval){                                                        // Tmp var check (case in range)
      n = tmp_chk;                                                                                          // Number of interpolation points (= poly degree + 1) val definition
    } else {                                                                                                // Tmp var check (case out of range)
      printf("%sInput val error! The value must be between %hu and %hu. %sRetry!%s",
             rd, n_minval, n_maxval, cy, er);                                                               // Print error fbk
    }
  } while ((tmp_chk < n_minval || tmp_chk > n_maxval));                                                     // Expect input val in range while-loop exit cond

  real pts[iaddr(V2, n, n)];                                                                                // Points to interpolate coords matrix declaration (in execution)
  real ohm[iaddr(V, n, n)];                                                                                 // Ohmega poly coefficients vector declaration (in execution)
  real dd[iaddr(V, n, n)];                                                                                  // Divided-defferences vector declaration (in execution)
  real p[iaddr(V, n, n)];                                                                                   // Interpol poly coefficients vector declaration (in execution)
  real eval[iaddr(V, n, n)];                                                                                // Interpol poly evaluation in each given point vector declaration (in execution)
  real deriv[iaddr(V, n, n)];                                                                               // Interpol poly derivation vector declaration (in execution)

  mat_vect_init(pts, ohm, dd, p, eval, deriv, n);                                                           // Matrix and vectors initialization (definition) function call
  printf("\n%s>>>%s Defined points coord matrix:%s", gn, pu, er);                                           // Defined matrix fbk
  mat_print(pts, n);                                                                                        // Matrix print function call
  poly_interpol(pts, ohm, dd, p, n);                                                                        // Poly interpolation function call
  printf("\n\n%s>>>%s Points interpolation poly: %s", gn, pu, er);                                          // Points interpolation poly fbk
  poly_print(p, n);                                                                                         // Poly print function call
  printf("\n\n%s>>>%s Poly evaluation in given points: %s", gn, pu, er);                                    // Poly evaluation in given points fbk
  poly_eval(pts, p, eval, n);                                                                               // Poly evaluation function call (Horner's roule)
  poly_deriv(p, deriv, n);                                                                                  // Poly derivation function call
  printf("\n\n%s>>>%s Derivated poly: %s", gn, pu, er);                                                     // Poly derivation fbk
  poly_print(deriv, n);                                                                                     // Poly (derivate) print function call
  printf("\n\n%s>>>%s Done! %s;)%s\n", gn, pu, cy, er);                                                     // Final line fbk

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}
