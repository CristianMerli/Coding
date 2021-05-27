/*
 * Author: Cristian Merli
 * Code title: Exercise1
 * Code version: 2.0
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
int* count(const int array[], const int *size){                                                             // Count routine
  /* Body */
  int* res = NULL;                                                                                          // Init result vect ptr
  if (*size > 0){                                                                                           // If size is positive
    res = calloc((size_t)*size, sizeof(int));                                                               // Allocate array inside heap
    for (int i = 0; i < *size; ++i)                                                                         // Input array elements scrolling FOR cycle
      for (int j = 0; j < *size; ++j)                                                                       // Output array elements definition FOR cycle
        if (array[i] == array[j])                                                                           // Counters in output vector upd cond
          ++res[i];                                                                                         // Upd counters in output vector
  }
  return res;                                                                                               // Return result vector
}


/* Main cycle */
int main(){
  /* Main vars */
  int *result = NULL, test_array[] = {1, 2, 3, 3, 4, 4, 1, 4}, dim = 8;                                     // Int vars for count routine test

  /* Code */
  result = count(test_array, &dim);                                                                         // Count routine call
  
  if (result != NULL){                                                                                      // Check if result vector ptr is not null
    printf("\n[ ");                                                                                         // Print array first char
    for (int i = 0; i < dim; ++i)                                                                           // Array elements print FOR cycle
      printf("%d ", result[i]);                                                                             // Print array elements
    printf("]\n");                                                                                          // Print array last char
    free(result);                                                                                           // Free allocated memo inside heap
  } else {                                                                                                  // Else if result vector ptr is null
    printf("\nVector is empty!\n");                                                                         // Print null vector error
  }

  return EXIT_SUCCESS;                                                                                      // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Funzione che conta le ricorrenze di ogni numero all'interno di un vettore e riempie un vettore posizionando le ricorrenze
 * nella posizione del numero corrispondente. La funzione ritorni un vettore allocato dinamicamente, NULL in caso il vettore in
 * ingresso sia vuoto ( es. [1,2,3,3,4,4,1,4] -> [2,1,2,2,3,3,2,3] )
 */
