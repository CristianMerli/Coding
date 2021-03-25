/*
 * Author: Cristian Merli
 * Code title: LU factorization
 * Code version 1.0
 * Creation date: 23/03/2021
 * Last mod. date: 23/03/2021
 */


/* Libraries import */
#include <stdio.h>                                                                                          // Standard I/O library inclusion (for printf ecc.)
#include <math.h>                                                                                           // Math library inclusion (for fabs func ecc.)
#include <string.h>                                                                                         // String library inclusion (for strlen ecc.)


/* Constants declaration and definition */
const unsigned char n = 5;                                                                                  // Number of matrix's rows and columns constant val declaration and definition
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

void mat_vect_init(double a[n][n], unsigned char p[n], double b[n], double x[n], unsigned char n){          // Matrix and vectors initialization (definition) function
  /* Function body */
  for (unsigned char i = 0; i < n; i++){                                                                    // Matrix lines definition FOR cycle
    for (unsigned char j = 0; j < n; j++){                                                                  // Matrix columns definition FOR cycle
      printf("%s-->%s Define the matrix element %s[%d][%d]%s: %s", O, C, B, i+1, j+1, C, E);                // Matrix elements definition request
      scanf("%lf", &a[i][j]);                                                                               // Matrix elements value init
    }
    printf("%s-->%s Define the known terms vector element %s[%d]%s: %s", O, C, B, i+1, C, E);               // Known terms vector elements definition request
    scanf("%lf", &b[i]);                                                                                    // Known terms vector elements value init
    p[i] = i+1;                                                                                             // Permutations vector elements init
  }
}

void print_mat_vect(double a[n][n], unsigned char p[n], double b[n], double x[n], unsigned char n){         // Matrix and vectors print function
  printf("\n\n%s--> %s%dx%d%s matrix and %s%dx1%s vectors: %s\n", O, B, n, n, C, B, n, C, E);               // Print mat and vect info
  for (unsigned char i = 0; i < n; i++){                                                                    // Mat and vect lines print FOR cycle
    for (unsigned char j = 0; j < n; j++){                                                                  // Mat columns print FOR cycle
      if ((j == n-1) && (i != j)){                                                                          // Last mat column and vect print cond (pivot excluded)
        printf("  %s%lf   %s%d         %sx%d=%lf%s         %lf%s\n",
              LB, a[i][j], Y, p[i], B, i+1, x[i], O, b[i], E);                                              // Last mat column and vect print (pivot excluded)
      } else if ((i == j) && (j == n-1)){                                                                   // Last mat column and vect print cond (with pivot)
        printf("  %s%lf   %s%d         %sx%d=%lf%s         %lf%s\n",
              R, a[i][j], Y, p[i], B, i+1, x[i], O, b[i], E);                                               // Last mat column and vect print (with pivot)
      } else if ((i == j) && (j != n-1)){                                                                   // Mat pivot print cond (excluded last column)
        printf("  %s%lf%s  ", R, a[i][j], E);                                                               // Mat pivot print (excluded last column)
      } else {                                                                                              // Other mat elements print cond
        printf("  %s%lf%s  ", LB, a[i][j], E);                                                              // Mat elements print (first,last column and pivots excluded)
      }
    }
  }
}

void lu_fact(double a[n][n], unsigned char p[n], unsigned char n){                                          // LU factorization function
  /* Function body */
  for (unsigned char i = 0; i < n-1; i++){                                                                  // Pivoting mat lines FOR cycle
    unsigned char maxval_lineidx = i;                                                                       // Max value line index for pivoting
    for (unsigned char j = i+1; j < n; j++){                                                                // Find mat max val line idx FOR cycle (lines/columns idx inverted to save one FOR cycle idx var)
      if (fabs(a[j][i]) > fabs(a[maxval_lineidx][i])){                                                      // Max val line idx updare det cond
        maxval_lineidx = j;                                                                                 // Max val line index for pivoting upds
      }
    }
    double tmp_xchg;                                                                                        // Tmp xchange var to store values
    for (unsigned char j = 0; j < n; j++){                                                                  // Pivoting lines exchange FOR cycle (lines/columns normal idx)
      tmp_xchg = a[i][j];                                                                                   // Store mat line element in tmp xchange var
      a[i][j] = a[maxval_lineidx][j];                                                                       // Lines element exchange for pivoting (mat)
      a[maxval_lineidx][j] = tmp_xchg;                                                                      // Lines element exchange for pivoting (mat)
      tmp_xchg = p[i];                                                                                      // Store perm vect value in tmp xchange var
      p[i] = p[maxval_lineidx];                                                                             // Lines element exchange for pivoting (perm vect)
      p[maxval_lineidx] = tmp_xchg;                                                                         // Lines element exchange for pivoting (perm vect)
    }
    for (unsigned char j = i+1; j < n; j++){                                                                // Li in mat FOR cycle (lines/columns idx inverted to save one FOR cycle idx var)
      a[j][i] /= a[i][i];                                                                                   // Li in mat creation
    }
    for (unsigned char k = i+1; k < n; k++){                                                                // Li*a mat calc lines FOR cycle
      for (unsigned char j = i+1; j < n; j++){                                                              // Li*a mat calc columns FOR cycle
        a[k][j] -= (a[k][i] * a[i][j]);                                                                     // Li*a mat calc
      }
    }
  }
}

void solve(double a[n][n], unsigned char p[n], double b[n], double x[n], unsigned char n){                  // Solve function
  for (unsigned char i = 0; i < n; i++){                                                                    // Apply permutations on known terms vector (p*b) FOR cycle and solve IT system (p*a*x=p*b) = (L*z=p*b) --> Solve Inferior-Triangular system lines FOR cycle
    x[i] = b[p[i]-1];                                                                                       // Apply permutations on known terms vector (p*b) --> Store p*b in x vector to save memo
    if (i >= 1){                                                                                            // After first line (z1 = b1), isolate the other zi stored in xi
      for (unsigned char j = 0; j < i; j++){                                                                // Solve IT system (p*a*x=p*b) = (L*z=p*b) --> Solve Inferior-Triangular system columns FOR cycle
        x[i] -= (a[i][j] * x[j]);                                                                           // Solve IT system (p*a*x=p*b) = (L*z=p*b) --> Solve Inferior-Triangular system and store z in x vector to save memo
      }
    }
  }
  x[n-1] /= a[n-1][n-1];                                                                                    // Solve ST system (u*x=z) --> Solve Superior-Triangular system lines FOR cycle, set xn coefficient to 1
  for (short i = n-2; i >= 0; i--){                                                                         // Solve ST system (u*x=z) --> Solve Superior-Triangular system lines FOR cycle
    for (unsigned char j = i+1; j < n; j++){                                                                // Solve ST system (u*x=z) --> Solve Superior-Triangular system columns FOR cycle
      x[i] -= (a[i][j] * x[j]);                                                                             // Solve ST system (u*x=z) --> Solve Superior-Triangular system, isolate xi
    }
    x[i] /= a[i][i];                                                                                        // Solve ST system (u*x=z) --> Solve Superior-Triangular system lines FOR cycle, set xi coefficient to 1
  }
}


/* Main cycle */
int main(){
  /* Vars declaration and definition */
  //double a[5][5] = {{0, 1, 0, 1, 2}, {6, 0, -1, 2, 3}, {1, 1, 0, 0, 1}, {0, -1, 1, 1, 0}, {-1, 0, 0, 2, 3}, };// Test matrix declaration and definition (b4 set n=5 and comment from line 79 to 84 included)
  //double b[5] = {4, 6, 4, 1, 2};                                                                              // Known terms test vector declaration and definition (b4 set n=5 and comment from line 79 to 84 included)
  double a[n][n];                                                                                           // Matrix declaration
  double b[n];                                                                                              // Known terms vector declaration
  double x[n];                                                                                              // Unknown terms vector declaration
  unsigned char p[n];                                                                                       // Permutations vector declaration

  /* Code */
  logo(5, 3, 6, 15, "LU FACTORIZATION ALGORITHM", Y, 'X', G);                                               // Print logo function call (vert_thick, lat_thick_vert_thick_ratio, start_spaces, lat_spaces, text, txt_color, background_char, bkgchr_color)
  mat_vect_init(a, p, b, x, n);                                                                             // Matrix and vectors initialization (definition) function call
  printf("\n\n%s>>>%s Defined matrix:%s", G, P, E);                                                         // Defined matrix fbk
  print_mat_vect(a, p, b, x, n);                                                                            // Matrix and vectors print function call
  lu_fact(a, p, n);                                                                                         // LU factorization function call
  printf("\n\n%s>>>%s Factorized matrix:%s", G, P, E);                                                      // Factorized matrix fbk
  print_mat_vect(a, p, b, x, n);                                                                            // Matrix and vectors print function call
  solve(a, p, b, x, n);                                                                                     // Solve function call
  printf("\n\n%s>>>%s Solved matrix:%s", G, P, E);                                                          // Solved matrix fbk
  print_mat_vect(a, p, b, x, n);                                                                            // Matrix and vectors print function call

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * LU factorization C codice algorithm, and system solver (ax=b)
 */
