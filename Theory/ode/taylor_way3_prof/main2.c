#include "ode2.h"
#include <stdio.h>

typedef int integer;

int
main() {
  real_type a  = 0;
  real_type b  = 1.2;
  real_type x0 = a;
  real_type y0 = 1;
  integer   n  = 100;
  real_type h  = (b-a)/n;

  real_type x = x0;
  real_type y = y0;
  printf("%g\t%g\n", x, y );
  for ( integer k=0; k < n; ++k ) {
    // avanzamento
    y  = Phi( x, y, h );
    x += h;
    printf("%g\t%g\n", x, y );
  }
  printf("All done folks\n");
  return 0;
}
