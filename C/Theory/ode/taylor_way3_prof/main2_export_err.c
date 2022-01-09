#include "ode2.h"
// includere printf, fprintf, fopen
#include <stdio.h>
// sin, cos, pow
#include <math.h>
// per comando system
#include <stdlib.h>

typedef int integer;

/*
Avanza la soluzione numerica da (x,y(x)) a (x+h,y(x+h))
Inoltre avanza facendo nstep sottopassi di ampiezza h/nstep.
Serve per avere soluzione "esatta" di riferimento.
*/
real_type
Phi_multi( real_type x, real_type y, real_type h, integer nstep ) {
  for ( integer i = 0; i < nstep; ++i ) {
    y  = Phi( x, y, h );
    x += h;
  }
  return y;
}

/*
Calcolo soluzione completa sia con passo h e nstep passi
sia la soluzione "esatta" che per ogni passo della solzione
"non accurata" ne fa N di sottopassi.
Restituisce l'errore massimo ottenuto come differenza
tra la soluzione numerica e quella di riferimento "esatta".
*/

real_type
advance_with_error( 
  real_type x0,
  real_type y0,
  real_type h,
  integer   nstep,
  integer   N
) {
  real_type emax = 0;
  real_type x    = x0;
  real_type y    = y0;
  real_type ye   = y0;
  for ( integer k=0; k < nstep; ++k ) {
    // avanzamento
    y  = Phi( x, y, h );
    ye = Phi_multi( x, ye, h/N, N ); // soluzione "esatta"
    x += h;
    // stima errore
    real_type err = fabs(y-ye);
    if ( err > emax ) emax = err;
  }
  return emax;
}

int
main() {
  real_type a     = 0;
  real_type b     = 1;
  real_type x0    = a;
  real_type y0    = 1;
  integer   nn[]  = { 4, 8, 16, 32, 64, 128, 200, 400, 800, 1600, 2000 };
  integer   nmesh = sizeof(nn)/sizeof(nn[0]); // trucco per avere dimensione di nn
  real_type ee[sizeof(nn)/sizeof(nn[0])];
  real_type hh[sizeof(nn)/sizeof(nn[0])];

  FILE * fd = fopen("err_table.txt","w");
  for ( integer ii = 0; ii < nmesh; ++ii ) {
    integer N = 10000/nn[ii];
    hh[ii] = (b-a)/nn[ii];
    ee[ii] = advance_with_error( x0, y0, hh[ii], nn[ii], N );
    printf( "h = %g, err = %g\n", hh[ii], ee[ii]);
    fprintf( fd, "%10g\t%10g\n",hh[ii],ee[ii]);
  }
  fclose(fd);
  // salva triangolo riferimento ordine 4
  {
    real_type tmp, tmp2;
    fd = fopen("err_4.txt","w");
    tmp  = ee[nmesh-3]/10;
    tmp2 = hh[nmesh-3];
    fprintf( fd, "%10g\t%10g\n",2*tmp2,tmp*pow(2,4));
    fprintf( fd, "%10g\t%10g\n",tmp2,tmp);
    fprintf( fd, "%10g\t%10g\n",2*tmp2,tmp);
    fclose(fd);
    fd = fopen("err_2.txt","w");
    //tmp2 *= 2;
    fprintf( fd, "%10g\t%10g\n",2*tmp2,tmp*pow(2,2));
    fprintf( fd, "%10g\t%10g\n",tmp2,tmp);
    fprintf( fd, "%10g\t%10g\n",2*tmp2,tmp);
    fclose(fd);
    fd = fopen("err_1.txt","w");
    //tmp2 *= 2;
    fprintf( fd, "%10g\t%10g\n",2*tmp2,2*tmp);
    fprintf( fd, "%10g\t%10g\n",tmp2,tmp);
    fprintf( fd, "%10g\t%10g\n",2*tmp2,tmp);
    fclose(fd);
  }

  printf("Stima ordine\n");
  for ( integer ii = 1; ii < nmesh; ++ii ) {
    printf( "p = %g\n", log(ee[ii]/ee[ii-1])/log(hh[ii]/hh[ii-1]));
  }

  system("gnuplot -e \"load 'gplot1.cmd'; pause -1\"");
  printf("All done folks\n");
  return 0;
}
