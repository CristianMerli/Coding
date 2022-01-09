/*
 * Author: Cristian Merli
 * Code title: Exercise6
 * Code version: 3.0
 * Creation date: 26/05/2021
 * Last mod. date: 26/05/2021
 */


/* Libraries */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <stdlib.h>                                                                                         // Standard library inclusion (EXIT_SUCCESS, EXIT_FAILURE)


/* Constants */
#define INITSZ  10                                                                                          // Initial vector size


/* Global vars */
//


/* Main routines */
static void delete_elems_from_vect(int vect[], int* size){                                                  // Routine to delete elements from vector
  /* Body */
  int incr_sum = 0;                                                                                         // Incremental sum tmp var init
  for (int i = 0; i < *size; ++i)                                                                           // Incremental sum calc FOR cycle
    incr_sum += vect[i];                                                                                    // Upd incremental sum val
  if (incr_sum % 2 == 0)                                                                                    // If the incremental sum val is an odd num
    incr_sum = 0;                                                                                           // Set incremental sum val to zero (del odd nums flg)
  else                                                                                                      // Else if the incremental sum val is an even num
    incr_sum = 1;                                                                                           // Set incremental sum val to one (del even nums flg)

  for (int j = 0; j < *size; ++j)                                                                           // Vector scrollin' FOR cycle
    if ((vect[j] % 2 == 0 && !incr_sum) || (vect[j] % 2 != 0 && incr_sum)){                                 // If focused element has to be removed
      for (int k = j+1; k < *size; ++k)                                                                     // Vect elems shift FOR cycle
        vect[k-1] = vect[k];                                                                                // Vect elems shiftin' oper
      --*size;  --j;                                                                                        // Upd vect size and decrement vector scrollin' idx val
    }
}


/* Main cycle */
int main(){
  /* Main vars */
  int vect[] = {0,1,2,3,4,5,6,7,8,9}, size = INITSZ;                                                        // Int vars for testin' the routine to delete elements from vector

  /* Code */
  delete_elems_from_vect(vect, &size);                                                                      // Delete elements from vector rotine call

  printf("\n-->  [  ");                                                                                     // Print first vect chr
  for (int i = 0; i < size; ++i)                                                                            // Vect print FOR cycle
    printf("%d  ", vect[i]);                                                                                // Print vect elems
  printf("]\n");                                                                                            // Print last vect chr

  return EXIT_SUCCESS;                                                                                      // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Fare una funzione che elimina dal vettore tutti gli elementi pari o dispari modificando size di conseguenza.
 * Pari se la somma degli elementi è pari e dispari se la somma è dispari.
 */
