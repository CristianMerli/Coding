/*
 * Author: Cristian Merli
 * Code title: Exercise3
 * Code version: 3.0
 * Creation date: 25/05/2021
 * Last mod. date: 25/05/2021
 */


/* Libraries */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <stdlib.h>                                                                                         // Standard library inclusion (EXIT_SUCCESS, EXIT_FAILURE)


/* Constants */
//


/* Global vars */
//


/* Main routines */
int* find_div(const int num, int *const size){                                                              // Find div routine
  /* Body */
  int* res = NULL;                                                                                          // Restul vector ptr init
  if (num != 0){                                                                                            // If the number to divide is not zero
    *size = 0;                                                                                              // Reset div vector size
    for (int div = 1; div <= num; ++div){                                                                   // Find num div FOR cycle
      if (num % div == 0){                                                                                  // Num div detecting cond
        ++*size;                                                                                            // Upd res vector size
        if (*size == 1)                                                                                     // If res vect size is 1
          res = calloc((size_t)*size, sizeof(int));                                                         // Allocate result vector inside heap
        else                                                                                                // Else if res vect size isn't 1
          res = realloc(res, (size_t)*size*sizeof(int));                                                    // Reallocate result vector inside heap
        res[*size-1] = div;                                                                                 // Add div val in res vect (in last vect pos)
      }
    }
  }
  return res;                                                                                               // Return result vector ptr
}


/* Main cycle */
int main(){
  /* Main vars */
  int *vect = NULL, dim = 0, num = 1024;                                                                    // Number to test find div routine

  /* Code */
  vect = find_div(num, &dim);                                                                               // Find div routine call

  printf("\n[ ");                                                                                           // Print array first char
  for (int i = 0; i < dim; ++i)                                                                             // Array elements print FOR cycle
    printf("%d ", vect[i]);                                                                                 // Print array elements
  printf("]\n");                                                                                            // Print array last char

  if (vect != NULL)                                                                                         // Check if vector ptr is not null
    free(vect);                                                                                             // Free allocated memo inside heap

  return EXIT_SUCCESS;                                                                                      // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Trovo tutti i divisori di un numero e lo ritorno in un vettore dinamico
 */
