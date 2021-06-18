// plot "data0.txt" with linespoints, "data1.txt" with linespoints, "data2.txt" with linespoints, "data3.txt" with linespoints, "esatta.txt" with lines linewidth 4

#include "ode1.h"
#include <stdio.h>

typedef int integer;

int
main() {
  real_type a  = 0;
  real_type b  = 1.2;
  real_type x0 = a;
  real_type y0 = 1;
  integer nn[] = { 4, 8, 16, 32 };

  for ( integer ii = 0; ii < 4; ++ii ) {
    char fname[100];
    sprintf( fname, "data%d.txt", ii );
    FILE * fd = fopen(fname,"w");
    integer   n  = nn[ii];
    real_type h  = (b-a)/n;

    real_type x = x0;
    real_type y = y0;
    fprintf( fd, "%g\t%g\n", x, y );
    for ( integer k=0; k < n; ++k ) {
      // avanzamento
      y  = Phi( x, y, h );
      x += h;
      fprintf( fd, "%g\t%g\n", x, y );
    }
    fclose( fd );
  }
  printf("All done folks\n");
  return 0;
}
