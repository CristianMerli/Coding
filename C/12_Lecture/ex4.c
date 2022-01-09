/*
 * Author: Cristian Merli
 * Code title: Exercise4
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
int find_median(const unsigned vect[], const unsigned size){                                                // Find median routine (done without sorting)
  /* Body */
  int half_size = (int)size/2, max_half_median = -1, flg_idx = 0;                                           // Half vector size, max half vector (median) and flag index
  unsigned* tmp_vect_flg = calloc(size, sizeof(unsigned));                                                  // Tmp vect flag var allocation inside heap
  // Find median-algorithm
  for (int i = 0; i <= half_size; ++i){                                                                     // Half vector scrolling FOR cycle ('till median val)
    max_half_median = -1;                                                                                   // Reset max half vector (median)
    flg_idx = 0;                                                                                            // Reset flag index
    for (int j = 0; j < (int)size; ++j){                                                                    // Whole vector scrolling FOR cycle to sort max val
      if ((int)vect[j] >= max_half_median && !tmp_vect_flg[j]){                                             // If the selected val is greater max val
        max_half_median = (int)vect[j];                                                                     // Upd max val
        flg_idx = j;                                                                                        // Save flag index to set already considered flag
      }
    }
    ++tmp_vect_flg[flg_idx];                                                                                // Set already considered value flag
  }
  free(tmp_vect_flg);                                                                                       // Free tmp vect flag allocated memo inside heap

  return max_half_median;                                                                                   // Return median val in vect
}


/* Main cycle */
int main(){
  /* Main vars */
  unsigned vect1[] = {1, 7, 1, 7, 7, 2, 4, 4, 3, 2}, size1 = 10;                                            // Int vars to test find median routine
  unsigned vect2[] = {1, 1, 2, 3, 4, 5, 7, 7, 7}, size2 = 9;                                                // Int vars to test find median routine
  int median = 0;                                                                                           // Median val in vect (int --> -1 in case of empy vect)

  /* Code */
  median = find_median(vect1, size1);                                                                       // Find median routine call
  printf("\n- Median val in vect1 is: %d\n", median);                                                       // Print median1 fbk
  median = find_median(vect2, size2);                                                                       // Find median routine call
  printf("\n- Median val in vect2 is: %d\n", median);                                                       // Print median2 fbk

  return EXIT_SUCCESS;                                                                                      // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Trovare numero mediano in un vettore di int senza segno,
 * se il vettore ha un numero pari di elementi ritorna il più piccolo indice (quello più a sx),
 * ritorna -1 se il vettore è vuoto
 * ( es. [1,7,1,7,7,2,4,4,3,2] -> 3 /oppure/ [1,1,2,3,4,5,7,7,7] -> 4 )
 */
