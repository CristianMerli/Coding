/*
 * Author: Cristian Merli
 * Code title: LU factorization
 * Code version 1.0
 * Creation date: 23/03/2021
 * Last mod. date: 23/03/2021
 */


/* Libraries import */
#include <stdio.h>                                                              // Standard I/O library inclusion 


/* Constants declaration and definition */
const unsigned char n = 5;                                                      // Number of matrix's rows and columns constant val declaration and definition


/* Functions declaration and definition */
void mat_vect_init(double a[n][n], unsigned char p[n], unsigned char n){        // Matrix and vectors initialization (definition) function
  /* Function body */
  for (unsigned char i = 0; i < n; i++){                                        // Matrix lines definition FOR cycle
    for (unsigned char j = 0; j < n; j++){                                      // Matrix columns definition FOR cycle
      printf("--> Define the matrix [%d][%d] element: ", i+1, j+1);             // Matrix elements definition request
      scanf("%lf", &a[i][j]);                                                   // Matrix elements value init
    }
  }
  for (unsigned char i = 0; i < n; i++){                                        // Permutations vector lines initialization FOR cycle
    p[i] = i;                                                                   // Permutations vector elements init
  }
  printf("\n\n--> %dx%d matrix and %dx1 permutations vector: \n\n", n, n, n);   // Print mat and perm vect info
  for (unsigned char i = 0; i < n; i++){                                        // Mat and perm vect lines print FOR cycle
    for (unsigned char j = 0; j < n; j++){                                      // Mat columns print FOR cycle
      if (j == 0){                                                              // First mat column print cond
        printf(" |");                                                           // First mat column print
      }
      printf("  %lf  ", a[i][j]);                                               // Mat elements print (first and last column excluded)
      if (j == n-1){                                                            // Last mat column and perm vect print cond
        printf("|           |  %d  |\n", p[i]);                                 // Last mat column and perm vect print
      }
    }
  }
}

void lu_fact(double a[n][n], unsigned char p[n], unsigned char n){              // LU factorization function
  /* Function body */
  for (unsigned char i = 0; i < n-1; i++){                                      // Pivoting mat lines FOR cycle
    for (unsigned char j = i+1; j < n; j++)                                     // Pivoting mat columns FOR cycle
      if (){
        
      }                                                          
  }
}


/* Main cycle */
int main(){
  /* Vars declaration and definition */
  double a[n][n];                                                               // Matrix declaration
  unsigned char p[n];                                                           // Permutations vector declaration

  /* Code */
  printf("\n");                                                                 // New line
  mat_vect_init(a, p, n);                                                       // Matrix and vectors initialization (definition) function call
  lu_fact(a, p, n);                                                             // LU factorization function call
  return 0;                                                                     // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * LU factorization C codice algorithm
 */