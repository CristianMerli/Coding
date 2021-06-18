/*
 * Implementazione per il problema
 *
 * y'   = x * exp( y )  -y
 * y(0) = 1
 *
 */

#include "ode1.h"
#include <math.h>

// serie di Taylor modo 2

real_type D1(real_type x, real_type y) {
  return x*exp(y)-y;
}


real_type D2(real_type x, real_type y) {
  return exp(2*y)*x*x+(1-(1+y)*x)*exp(y)+y;
}


real_type D3(real_type x, real_type y) {
  real_type t1  = 3.0*y;
  real_type t3  = x*x;
  real_type t7  = 2.0*y;
  real_type t8  = exp(t7);
  real_type t10 = exp(t1);
  real_type t15 = pow(y+1.0,2.0);
  real_type t18 = exp(y);
  real_type t20 = t8*(t3*(-t1-2.0)+3.0*x)+2.0*t3*x*t10+t18*(x*t15-t7-1.0)-y;
  return t20;
}


real_type D4(real_type x, real_type y) {
  real_type t1 = y*y;
  real_type t5 = x*x;
  real_type t12 = exp(2.0*y);
  real_type t20 = 3.0*y;
  real_type t21 = exp(t20);
  real_type t24 = exp(4.0*y);
  real_type t25 = t5*t5;
  real_type t35 = exp(y);
  real_type t37 = t12*(3.0+t5*(7.0*t1+11.0*y+3.0)+(-14.0*y-7.0)*x)+
                  t21*(t5*x*(-12.0*y-7.0)+12.0*t5)+6.0*t25*t24+
                  t35*(x*(-t1*y-4.0*t1-t20-1.0)+3.0*t1+5.0*y+1.0)+y;
  return t37;
}


// avanzamento
real_type Phi(real_type x, real_type y, real_type h) {
  real_type yp    = D1(x,y);
  real_type ypp   = D2(x,y);
  real_type yppp  = D3(x,y);
  real_type ypppp = D4(x,y);
  // avanzamento, uso raccogliemento HORNER per risparmiare calcoli
  // a+b*x+c*x^2+d*x^3 = a+x*(b+x*(c+x*d));
  //return y+h*(yp+h/2*(ypp+h/3*(yppp+h/4*ypppp)));
  return y+h*(yp+h/2*ypp);
}
