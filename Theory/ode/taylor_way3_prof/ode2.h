/*
 * header file per il problema
 *
 * y'   = x * exp( y )  -y
 * y(0) = 1
 *
 */

typedef double real_type;

// serie di Taylor modo 3

extern real_type D1(real_type x, real_type y);
extern real_type D2(real_type x, real_type y, real_type yp);
extern real_type D3(real_type x, real_type y, real_type yp, real_type ypp);
extern real_type D4(real_type x, real_type y, real_type yp, real_type ypp, real_type yppp);

// avanzamento
extern real_type Phi(real_type x, real_type y, real_type h);
