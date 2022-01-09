/*
 * Implementazione per il problema
 *
 * y'   = x * exp( y )  -y
 * y(0) = 1
 *
 */

#include "ode2.h"
#include <math.h>

// serie di Taylor modo 2

real_type D1(real_type x, real_type y) {
  return x*exp(y)-y;
}


real_type D2( real_type x, real_type y, real_type yp) {
  return exp(y)*(x*yp+1)-yp;
}

real_type D3(real_type x, real_type y, real_type yp, real_type ypp) {
  real_type t1 = yp*yp;
  real_type t6 = exp(y);
  real_type t8 = t6*(t1*x+x*ypp+2.0*yp)-ypp;
  return t8;
}


real_type D4(real_type x, real_type y, real_type yp, real_type ypp, real_type yppp) {
  real_type t1  = yp*yp;
  real_type t11 = exp(y);
  real_type t13 = t11*(t1*yp*x+3.0*x*yp*ypp+x*yppp+3.0*t1+3.0*ypp)-yppp;
  return t13;
}


// avanzamento
real_type Phi(real_type x, real_type y, real_type h) {
  real_type yp    = D1(x,y);
  real_type ypp   = D2(x,y,yp);
  real_type yppp  = D3(x,y,yp,ypp);
  real_type ypppp = D4(x,y,yp,ypp,yppp);
  // avanzamento, uso raccogliemento HORNER per risparmiare calcoli
  // a+b*x+c*x^2+d*x^3 = a+x*(b+x*(c+x*d));
  return y+h*(yp+h/2*(ypp+h/3*(yppp+h/4*ypppp)));
}
