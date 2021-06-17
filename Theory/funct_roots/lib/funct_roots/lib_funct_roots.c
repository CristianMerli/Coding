/*
 * Author: Cristian Merli
 * Code title: Function roots library
 * Code version: 3.0
 * Creation date: 14/06/2021
 * Last mod. date: 17/06/2021
 */


/* Libraries */
#include "lib_funct_roots.h"                                                                                // Import function roots library header file


/* Lib vars */
//


/* Functions */
static Real newtons_alg_step(Real xk, Real (*f_ptr) (C_real), Real (*df_ptr) (C_real)){                     // Newton's algorithm step
  return xk-f_ptr(xk)/df_ptr(xk);                                                                           // Return Xk+1
}


static Real halleys_alg_step(Real xk, Real (*f_ptr) (C_real),
                             Real (*df_ptr) (C_real), Real (*ddf_ptr) (C_real)){                            // Halley's algorithm step
  return xk-f_ptr(xk)*df_ptr(xk)/(df_ptr(xk)*df_ptr(xk)-0.5*f_ptr(xk)*ddf_ptr(xk));                         // Return Xk+1
}


static L_real halleys_alg_step_q(L_real xk_q, L_real (*f_ptr_q) (Cl_real),
                                 L_real (*df_ptr_q) (Cl_real), L_real (*ddf_ptr_q) (Cl_real)){              // Halley's (quad-precision) algorithm step
  /* Body */
  return xk_q-f_ptr_q(xk_q)*df_ptr_q(xk_q)/
         (df_ptr_q(xk_q)*df_ptr_q(xk_q)-0.5*f_ptr_q(xk_q)*ddf_ptr_q(xk_q));                                 // Return Xk+1
}


// static Real estimate_ord(Real ek, Real ek_minus_1, Real ek_minus_2){                                        // Function to estimate order (conv speed)
//   return log(fabs(ek)/fabs(ek_minus_1)) / log(fabs(ek_minus_1)/fabs(ek_minus_2));                           // Return estimated order (conv speed)
// }


// static Real estimate_ord_q(Real ek, Real ek_minus_1, Real ek_minus_2){                                      // Function to estimate order (conv speed) in quad-precision
//   return logl(fabsl(ek)/fabsl(ek_minus_1)) / logl(fabsl(ek_minus_1)/fabsl(ek_minus_2));                     // Return estimated order (conv speed) in quad-precision
// }


/* Public functions */
Real fnd_root_newton(C_real x0, Real (*f_ptr) (C_real), Real (*df_ptr) (C_real)){                           // Find funct root with Newton's algorithm
  /* Body */ 
  C_real lim_val = 1e-12;                                                                                   // Limit delta val btwn iters to stop funct's root calc iter cycle
  Real xk = x0;                                                                                             // Xk var init (x val at k iteration)
  Real xk_plus_1 = newtons_alg_step(xk, f_ptr, df_ptr);                                                     // Xk+1 var init (x val at k+1 iteration)
  // Iterations
  do {                                                                                                      // Iter cycle
    xk = xk_plus_1;                                                                                         // Xk var upd
    xk_plus_1 = newtons_alg_step(xk, f_ptr, df_ptr);                                                        // Xk+1 var upd (x val at k+1 iteration)
  } while(xk_plus_1-xk > lim_val || xk_plus_1-xk < -lim_val);                                               // Exit funct's root calc iter cycle when limit delta val btwn iters has been reached
  return xk;                                                                                                // Return Xk val (funct's root approx)
}


Real fnd_root_halley(C_real x0, Real (*f_ptr) (C_real), Real (*df_ptr) (C_real), Real (*ddf_ptr) (C_real)){ // Find funct root with Halley's algorithm
  /* Body */
  C_real lim_val = 1e-14;                                                                                   // Limit delta val btwn iters to stop funct's root calc iter cycle
  Real xk = x0;                                                                                             // Xk var init (x val at k iteration)
  Real xk_plus_1 = halleys_alg_step(xk, f_ptr, df_ptr, ddf_ptr);                                            // Xk+1 var init (x val at k+1 iteration)
  // Iterations
  do {                                                                                                      // Iter cycle
    xk = xk_plus_1;                                                                                         // Xk var upd
    xk_plus_1 = halleys_alg_step(xk, f_ptr, df_ptr, ddf_ptr);                                               // Xk+1 var upd (x val at k+1 iteration)
  } while(xk_plus_1-xk > lim_val || xk_plus_1-xk < -lim_val);                                               // Exit funct's root calc iter cycle when limit delta val btwn iters has been reached
  return xk;                                                                                                // Return Xk val (funct's root approx)
}


L_real fnd_root_halley_q(Cl_real x0_q, L_real (*f_ptr_q) (Cl_real),
                         L_real (*df_ptr_q) (Cl_real), L_real (*ddf_ptr_q) (Cl_real)){                      // Find funct root with Halley's (quad-precision) algorithm
  /* Body */
  Cl_real lim_val_q = 1e-18;                                                                                // Limit delta val btwn iters to stop funct's root calc iter cycle (quad-precision)
  L_real xk_q = x0_q;                                                                                       // Xk var init (x val at k iteration) in quad-precision
  L_real xk_plus_1_q = halleys_alg_step_q(xk_q, f_ptr_q, df_ptr_q, ddf_ptr_q);                              // Xk+1 var init (x val at k+1 iteration) in quad-precision
  // Iterations
  do {                                                                                                      // Iter cycle
    xk_q = xk_plus_1_q;                                                                                     // Xk var upd (quad-precision)
    xk_plus_1_q = halleys_alg_step_q(xk_q, f_ptr_q, df_ptr_q, ddf_ptr_q);                                   // Xk+1 var upd (x val at k+1 iteration) in quad-precision
  } while(xk_plus_1_q-xk_q > lim_val_q || xk_plus_1_q-xk_q < -lim_val_q);                                   // Exit funct's root calc iter cycle when limit delta val btwn iters has been reached (quad-precision)
  return xk_q;                                                                                              // Return Xk val (funct's root approx in quad-precision)
}


L_real fnd_root_newton_bisect_q(L_real a_q, L_real b_q, L_real (*f_ptr_q) (Cl_real),
                                L_real (*df_ptr_q) (Cl_real), Cl_real toll_q, C_int max_iter){              // Find funct root with Newton's-bisection hybrid algorithm
  /* Body */
  if (max_iter <= 1){                                                                                       // Check max iter param val
    fbk_err("Ops! Encountred error during function's root-searching with Newton's-bisection algorithm");    // Error fbk
    perror("Error in 'fnd_root_newton_bisect_q' function, 'max_iter' parameter must be greater than one!"); // print perror fbk
    close_err();                                                                                            // Close software with error function call
  }
  L_real c_q = 0.0;                                                                                         // New approx pt var init
  int iter = 0;                                                                                             // Number of iterations cnt
  do {                                                                                                      // Iteration cycle
    // Newton's method
    if (fabsl(f_ptr_q(a_q)) < fabsl(f_ptr_q(b_q)))                                                          // Apply newton on funct val closer to ZERO (eval in interval delimitin' pts), case 'a'
      c_q = a_q-f_ptr_q(a_q)/df_ptr_q(a_q);                                                                 // New approx pt upd usin' Newton's method on interval startin' pt
    else                                                                                                    // Apply newton on funct val closer to ZERO (eval in interval delimitin' pts), case 'b'
      c_q = b_q-f_ptr_q(b_q)/df_ptr_q(b_q);                                                                 // New approx pt upd usin' Newton's method on interval endin' pt
    // Bisection's method   -->   |----------|----------|
    //                            a          c          b
    if (c_q <= a_q || c_q >= b_q)                                                                           // If Newton's method ended out of [a,b] interval set new pt back in mean interval pt
      c_q = (a_q+b_q)/2;                                                                                    // Calc mean interval pt
    if (f_ptr_q(a_q)*f_ptr_q(c_q) < 0)                                                                      // If there's a root in [a,c] interval
      b_q = c_q;                                                                                            // Upd interval endin' pt
    else                                                                                                    // Else if there's a root in [c,b] interval
      a_q = c_q;                                                                                            // Upd interval startin' pt
    ++iter;                                                                                                 // Number of iterations cnt val upd
  } while((fabsl(a_q-b_q) > toll_q) && (iter < max_iter));                                                  // Cycle 'till err is lower than max spec val or 'till spec iter limit val has been reached
  if (iter >= max_iter)                                                                                     // If spec max num of iter has been reached
    fbk_err("Specified max number of iterations reached, solution might not be correct!");                  // Print error fbk
  return c_q;                                                                                               // Return new approx pt
}
