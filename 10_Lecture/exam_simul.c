#include <stdio.h>
#include <stdlib.h>

int
abs_sum( int v[], int dim ) {
  /* Inserisci il tuo codice */
  int res=0;
  for (int i=0; i<dim; ++i){
    res += abs(v[i]);
  }
  return res;
}

int
max_abs( int v[], int dim ) {
  /* Inserisci il tuo codice */
  int max_idx=0;
  for (int i=0; i<dim; ++i){
    if (abs(v[i]) > abs(v[max_idx])){
        max_idx = i;
    }
  }
  return v[max_idx];
}

void
divide( int v[], int dim, int res[] ) {
  /* Inserisci il tuo codice */
  for (int i=0; i<dim; ++i){
    if (v[2*i] == 0){
        res[i] = 2;
    } else {
        if ((v[(2*i)+1])%(v[2*i]) == 0){
            res[i] = 1;
        } else {
            res[i] = 0;
        }
    }
  }
}


/* Programma di testing non modificare! */

int
main() {
  int    dim;
  int    v[100];
  int    w[100];
  int    res;

  // legge il vettore
  scanf("%d",&dim);
  for ( int i = 0; i < dim; ++i ) scanf("%d",&v[i]);

  res = abs_sum( v, dim );
  printf("abs_sum: %d\n",res);

  res = max_abs( v, dim );
  printf("max_abs: %d\n",res);

  divide( v, dim, w );
  for ( int i = 0; i < dim/2; ++i ) {
    printf("w[%d]: %d\n",i,w[i]);
  }
  
  printf("All done folks!\n");
  return 0;
}



/* Task */
/* 
 * Exam simulation
 */
