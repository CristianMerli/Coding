// gcc -Wall main.c -lm && ./a.out
// metodo multistep non convergente fatto come es. pag. 6 lez. 29 --> esplosione approx anche dovuti ad errori fl.pt. amplificati dal metodo
// ordine 2 ma instabilità che si nota dopo un po di iterate che introduce una perturbazione (oscillazioni), non funziona sempre
// mentre metodo consistente e zero-stabile funziona sempre.

// includere printf, fprintf, fopen
#include <stdio.h>
// sin, cos, pow
#include <math.h>
// per comando system
#include <stdlib.h>

typedef double real_type;
typedef int    integer;

int
main() {
  integer   n  = 10000;
  // intervallo dove cerco soluzione
  real_type a  = 0;
  real_type b  = 100;
  real_type h  = (b-a)/n;
  // dato iniziale
  real_type x0 = 0;
  real_type y0 = 1;
  real_type x1, y1, x2, y2;
  FILE * fd; // descrittore file per salvare la soluzione

  // integro ode y' = -y, con y(0) = 1

  // inizializzo metodo multistep con Collatz
  y1 = y0 - (h/2)*y0; // mezzo passo Eulero in avanti
  y1 = y0 - h*y1;     // correzione di Collatz
  x1 = x0 + h;        // avanzamanto x

  // x0 e y0
  // x1 e y1
  // inizializzati posso avanzare con multistep

  fd = fopen("data.txt","w"); // apro file dati
  // salvo i primi duo punti con soluzione esatta
  // x y esatta
  fprintf( fd, "%10g\t%10g\t%10g\n",x0,y0,exp(-x0));
  fprintf( fd, "%10g\t%10g\t%10g\n",x1,y1,exp(-x1));
  for ( integer i = 1; i < n; ++i ) {
    y2 = y0 - 2*h*y1; // avanzo con multistep
    x2 = x1 + h;
    // salvo su file la solzione fin qui calcolata
    fprintf( fd, "%10g\t%10g\t%10g\n",x2,y2,exp(-x2));
    // shift dei punti
    x0 = x1; x1 = x2;
    y0 = y1; y1 = y2;
  }

  fclose(fd);

  system("gnuplot -e \"load 'gplot.cmd'; pause -1\"");
  printf("All done folks\n");
  return 0;
}
