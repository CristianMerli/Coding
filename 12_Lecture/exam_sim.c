/*
 * Author: Cristian Merli
 * Code title: ExamSimulation
 * Code version: 3.0
 * Creation date: 29/06/2021
 * Last mod. date: 29/06/2021
 *
 * gccW99_o exam_sim exam_sim.c && ./exam_sim
 * 
 * // Aliases:
 * alias gccW99_o="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -o"
 */


/* Libraries */
#include <stdlib.h> // Standard library inclusion (EXIT_SUCCESS, EXIT_FAILURE)
#include <stdio.h>  // 2 include printf() and calloc() functs
#include <math.h>   // 2 include fabs() funct


#define VECT_SZ 20
#define VECT2_SZ 5


/* Main routines */
int divisori(int num, int d[]){
  int num_div = 0;
  for (int j = num-1; j > 1; --j){
    if ((num % j) == 0)
      d[num_div++] = j;
  }
  return num_div;
}


int vicino(double a, double b, double t){
  if (fabs(a-b) < t) return 1; else return 0;
}


int* shift(const int v[], unsigned int s, int k){
  if (s >= 1){
    int* v_ptr = calloc(s, sizeof(int));
    int tmp_lst = 0;
    for (int h = 0; h < (int)s; ++h)
      *(v_ptr+h) = v[h];
    for (int l = 0; l < k; ++l){
      tmp_lst = *(v_ptr+s-1);
      for (int m = (int)s-2; m >= 0; --m)
        *(v_ptr+m+1) = *(v_ptr+m);
      *(v_ptr) = tmp_lst;
    }
    return v_ptr;
  } else
    return NULL;
}


/* Main cycle */
int main(){
  /* Main vars */
  int tst_vect[VECT_SZ], num = 30;
  for (int i = 0; i < VECT_SZ; ++i)
    tst_vect[i] = 0;

  double a = 11.0, b = 12.0, t = 0.5;

  int tst_vect2[VECT2_SZ] = {1,2,3,4,5}, k = 4;

  /* Code */
  divisori(num, tst_vect);
  printf("\n");
  for (int k = 0; k < VECT_SZ; ++k)
    printf(" %d ", tst_vect[k]);
  printf("\n");

  printf("\n %d\n", vicino(a, b, t));

  int* v_ptr = shift(tst_vect2, VECT2_SZ, k);
  if (v_ptr != NULL && VECT2_SZ > 0){
    printf("\n");
    for (int n = 0; n < VECT2_SZ; ++n)
      printf(" %d ", *(v_ptr+n));
    printf("\n");
    free(v_ptr);
  } else
    printf("\n Errore, vettore nullo!\n");

  return EXIT_SUCCESS;  // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/* 
 * Exam simulation
 */
