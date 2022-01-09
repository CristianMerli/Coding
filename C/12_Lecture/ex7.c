/*
 * Author: Cristian Merli
 * Code title: Exercise7
 * Code version: 3.0
 * Creation date: 26/05/2021
 * Last mod. date: 27/05/2021
 * 
 * Compile-run command (-lm to specify math lib incl)   -->   gccW99_o ex7 ex7.c -lm && ./ex7 
 */


/* Libraries */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <stdlib.h>                                                                                         // Standard library inclusion (EXIT_SUCCESS, EXIT_FAILURE)
#include <math.h>                                                                                           // Math library inclusion (sqrt, pow ecc.)


/* Constants */
//


/* Structs & data-types */
typedef struct stat_param{                                                                                  // Statistical parameters structure typedef
    long double min;                                                                                        // Min of vals in vect
    long double max;                                                                                        // Max of vals in vect
    long double sum;                                                                                        // Sum of vals in vect
    long double mean;                                                                                       // Mean of vals in vect
    long double var;                                                                                        // Variance of vals in vect
    long double std_dev;                                                                                    // Standatd deviation of vals in vect
} Stat_param;

typedef struct stat_param *const Stat_param_ptr;                                                            // Statistical parameters structure const ptr typedef

typedef const long double *const Const_double_ptr;                                                          // Const long double ptr const typedef

typedef const int *const Const_int_ptr;                                                                     // Const int ptr const typedef


/* Global vars */
static Stat_param stat_param_vect1;                                                                         // Statistical parameters of vector 1 var


/* Main routines */
static void vect_stat(Const_double_ptr vect, Const_int_ptr size, Stat_param_ptr stat_param_vect){           // Vector statistical analisys routine
  /* Body */
  if (vect != NULL && size != NULL && *size > 0 && stat_param_vect != NULL){                                // If vect, size and statistical data ptrs ain't null and vect size is greater than zero
    stat_param_vect->min = vect[0]; stat_param_vect->max = vect[0]; stat_param_vect->sum = 0;               // Min/max/sum vect params init b4 vect scan cycle start
    stat_param_vect->mean = 0;  stat_param_vect->std_dev = 0; stat_param_vect->var = 0;                     // Mean/std-dev/var vect params init b4 vect scan cycle start
    for(int i = 0; i < *size; ++i){                                                                         // Vect scan FOR cycle (to calc and def stat params)
      if (vect[i] < stat_param_vect->min)                                                                   // Min val upd detectin' cond
        stat_param_vect->min = vect[i];                                                                     // Min val upd
      if (vect[i] > stat_param_vect->max)                                                                   // Max val upd detectin' cond
        stat_param_vect->max = vect[i];                                                                     // Max val upd
      stat_param_vect->sum += vect[i];                                                                      // Upd increm sum val
    }
    stat_param_vect->mean = stat_param_vect->sum / *size;                                                   // Mean val calc
    for (int j = 0; j < *size; ++j)                                                                         // Vect scan FOR cycle (to calc and def remanin' stat params)
      stat_param_vect->var += powl((vect[j]-stat_param_vect->mean), 2);                                     // Upd variance increm sum
    stat_param_vect->var /= *size-1;                                                                        // Variance val calc
    stat_param_vect->std_dev = sqrtl(stat_param_vect->var);                                                 // Std deviation calc
  } else {                                                                                                  // Else if routine in params ain't OK
    perror("Error! Wrong parameters passed to vector stat function!");                                      // Print perror fbk
    exit(1);                                                                                                // Close SW
  }
}


/* Main cycle */
int main(){
  /* Main vars */
  long double vect1[] = {1.5, 7.1, 2.25, 3.0, 9.4, 5.96, 6.88, 63.7, 8.23, 0.9};                            // Long double vect var init to test vector statistical analisys routine
  int size_vect1 = 10;                                                                                      // Int var init to test vector statistical analisys routine

  /* Code */
  vect_stat(vect1, &size_vect1, &stat_param_vect1);                                                         // Vector statistical analisys routine call
  // Print vect info
  printf("\n-> VECTOR INFO:");                                                                              // Print vect info fbk
  printf("\n - Vector1:                                 [");                                                // Print vect name and first chr
  for (int k = 0; k < size_vect1; ++k)                                                                      // Vect elems print FOR cycle
    printf(" %Lf ", vect1[k]);                                                                              // Print vect elems
  printf("]");                                                                                              // Print vect last chr
  printf("\n - Number of values in vector1:             %d", size_vect1);                                   // Print vector1 size fbk
  // Print vect stat params
  printf("\n\n-> VECTOR STATISTICAL PARAMETERS:");                                                          // Print vect stat params fbk
  printf("\n - Min value in vector1:                    %Lf", stat_param_vect1.min);                        // Print vector1 min val fbk
  printf("\n - Max value in vector1:                    %Lf", stat_param_vect1.max);                        // Print vector1 max val fbk
  printf("\n - Sum of values in vector1:                %Lf", stat_param_vect1.sum);                        // Print vector1 vals sum fbk
  printf("\n - Mean of values in vector1:               %Lf", stat_param_vect1.mean);                       // Print vector1 vals mean fbk
  printf("\n - Variance of values in vector1:           %Lf", stat_param_vect1.var);                        // Print vector1 vals var fbk
  printf("\n - Standard deviation of values in vector1: %Lf\n", stat_param_vect1.std_dev);                  // Print vector1 vals std-dev fbk

  return EXIT_SUCCESS;                                                                                      // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Data la struttura di cui sopra, creare una funzione che prende la struttura per puntatore e un vettore e inizializza la struttura
 * con il valore mininimo, valore massimo, la somma degli elementi, la media e la varianza.
 */
