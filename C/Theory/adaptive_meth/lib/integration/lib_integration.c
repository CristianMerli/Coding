/*
 * Author: Cristian Merli
 * Code title: Adaptive integration methods library
 * Code version: 3.0
 * Creation date: 10/06/2021
 * Last mod. date: 12/06/2021
 */


/* Libraries */
#include "lib_integration.h"                                                                                // Import integration library header file


/* Lib vars */
int interv_cnt = 0;                                                                                         // Intervals counter var init


/* Functions */
//


/* Public functions */
Real ad_integr_trap(C_real a, C_real fa, C_real b, C_real fb, C_real toll, Real (*f_ptr) (C_real)){         // Adaptive integration with trapeziums method
  /* Body */ 
  Real m = (a+b)/2;                                                                                         // Mean interval val calc (btwn a and b)
  Real fm = f_ptr(m);                                                                                       // Function mean interval pt eval calc
  Real i1 = (fa+fb)*(b-a)/2;                                                                                // Integral1 val calc (interval divided in 2 parts --> one trapezium)
  Real i2 = (fa+2*fm+fb)*(b-a)/4;                                                                           // Integral2 val calc (interval divided in 2*2=4 parts --> two trapeziums)
  Real ee = (i2-i1)/3;                                                                                      // Estimated error (area) calc
  // Cmp err/toll vals
  if (fabs(ee) <= toll){                                                                                    // Compare estimated-error/epsilon-tollerance, in case error in tollerance, create and define interval
    ++interv_cnt;                                                                                           // Upd intervals cnt
    return i2;                                                                                              // Ret integral2 val (interval divided in 2*2=4 parts --> two trapeziums)
  } else                                                                                                    // while in case of error not in tollerance, split interval to better redestrebute the error
    return ad_integr_trap(a, fa, m, fm, toll/2, f_ptr) + ad_integr_trap(m, fm, b, fb, toll/2, f_ptr);       // Split intervals 'till error is in tollerance
}


Real ad_integr_simp(C_real a, C_real fa, C_real m, C_real fm,
                    C_real b, C_real fb, C_real toll, Real (*f_ptr) (C_real)){                              // Adaptive integration with simpson method
  /* Body */ 
  Real m1 = (a+m)/2;                                                                                        // Mean interval1 val calc (btwn a and m)
  Real m2 = (m+b)/2;                                                                                        // Mean interval2 val calc (btwn m and b)
  Real fm1 = f_ptr(m1);                                                                                     // Function mean interval1 pt val eval
  Real fm2 = f_ptr(m2);                                                                                     // Function mean interval2 pt val eval
  Real i1 = (fa+4*fm+fb)*(b-a)/6;                                                                           // Integral1 val calc (interval divided in 1 part)
  Real i2 = (fa+4*fm1+2*fm+4*fm2+fb)*(b-a)/12;                                                              // Integral2 val calc (interval divided in 2 parts)
  Real ee = (i2-i1)/15;                                                                                     // Estimated error (area) calc
  // Cmp err/toll vals
  if (fabs(ee) <= toll){                                                                                    // Compare estimated-error/epsilon-tollerance, in case error in tollerance, create and define interval
    ++interv_cnt;                                                                                           // Upd intervals cnt
    return i2;                                                                                              // Ret integral2 val (interval divided in 2 parts)
  } else                                                                                                    // while in case of error not in tollerance, split interval to better redestrebute the error
    return ad_integr_simp(a, fa, m1, fm1, m, fm, toll/2, f_ptr) +
           ad_integr_simp(m, fm, m2, fm2, b, fb, toll/2, f_ptr);                                            // Split intervals 'till error is in tollerance
}
