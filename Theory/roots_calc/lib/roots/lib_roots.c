/*
 * Author: Cristian Merli
 * Code title: Roots library
 * Code version: 3.0
 * Creation date: 12/06/2021
 * Last mod. date: 13/06/2021
 */


/* Libraries */
#include "lib_roots.h"                                                                                      // Import roots library header file


/* Lib vars */
//


/* Functions */
//


/* Public functions */
Real root_calc(C_real a, C_int n){                                                                          // Funct to calc the 'a' val 'n-th' root with newton algorithm, startin' from 'a' pt
  /* Body */
  C_real lim_val = 1e-12;                                                                                   // Limit delta val btwn iterations to stop root calc cycle
  Real xk_plus_1 = a, xk = a;                                                                               // Xk+1 and Xk vars init
  if (n > 1){                                                                                               // Check 'n' funct param val, if OK, calc root
    do {                                                                                                    // Root calc iter cycle
      xk = xk_plus_1;                                                                                       // Xk val upd
      Real xk_pow_1 = 1;                                                                                    // Xk^(n-1) val var init
      for (int j = 0; j < n-1; ++j)                                                                         // Xk^(n-1) power calc FOR cycle
        xk_pow_1 *= xk;                                                                                     // Ck power calc
      Real xk_pow = xk_pow_1*xk;                                                                            // Xk^n power calc
      xk_plus_1 = (xk-(xk_pow-a)/(n*xk_pow_1));                                                             // Xk+1 calc
    } while(xk_plus_1-xk > lim_val || xk_plus_1-xk < -lim_val);                                             // Exit result calc iter cycle when limit delta val btwn iterations has been reached
  } else {                                                                                                  // Else if 'n' funct param val ain't OK, print error fbks and clore SW with error
    fbk_err("Ops! Error encountred during root calculation!");                                              // Print error fbk
    perror("Invalid parameter's value passed to 'root_calc' function! 'n' parameter must be > 1");          // Print perror fbk
    close_err();                                                                                            // Close SW with error fbk
  }
  return xk;                                                                                                // Return root result
}
