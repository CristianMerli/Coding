/*
 * Author: Cristian Merli
 * Code title: Exercise2
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
int max_cons(int array[], int size){                                                                        // Max consecutives routine
  /* Body */
  if (size <= 0)                                                                                            // In case array size is negative/zero
    return 0;                                                                                               // Return zero
  else {                                                                                                    // Else if size is positive
    int max_val = 0, tmp_cnt = 0;;                                                                          // Max consecutives counter and tmp counter var init
    for (int i = 0; i < size-1; ++i){                                                                       // Array elements scrolling FOR cycle
      if (array[i] == array[i+1])                                                                           // Chech consecutive detecting cond
        ++tmp_cnt;                                                                                          // Increment tmp cnt
      else                                                                                                  // If the following num is different
        tmp_cnt = 0;                                                                                        // Rst counter
      if (tmp_cnt > max_val)                                                                                // If tmp counter is greater than the max counter
        max_val = tmp_cnt;                                                                                  // Upd max cnt val
    }
    return max_val+1;                                                                                       // Return max consecutives counter value (non-zero index)
  }
}


/* Main cycle */
int main(){
  /* Main vars */
  int test_array[] = {1, 2, 3, 3, 3, 4, 1, 4}, dim = 8, max = 0;                                            // Int vars for max consecutives routine test

  /* Code */
  max = max_cons(test_array, dim);                                                                          // Max consecutives routine call
  printf("\n- Max consecutives: %d\n", max);                                                                // Print max consecutives

  return EXIT_SUCCESS;                                                                                      // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Dato un vettore, ritorna la più lunga ricorrenza di un numero consecutivo
 */
