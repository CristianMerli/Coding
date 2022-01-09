/*
 * Author: Cristian Merli
 * Code title: Function roots library header file
 * Code version: 3.0
 * Creation date: 14/06/2021
 * Last mod. date: 17/06/2021 
 */


/* Avoid multiple inclusions */
#ifndef LIB_FUNCT_ROOTS                                                                                     // Avoid multiple inclusion
#define LIB_FUNCT_ROOTS                                                                                     // Avoid multiple inclusion


/* Libraries */
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file
#include <math.h>                                                                                           // Import math library


/* Constants */
//


/* Data-types */
//


/* Lib vars */
//


/* Structs & data-types */
//


/* Enums & data-types */
//


/* Library functions */
Real fnd_root_newton(C_real x0, Real (*f_ptr) (C_real), Real (*df_ptr) (C_real));                           // Find funct root with Newton's algorithm

Real fnd_root_halley(C_real x0, Real (*f_ptr) (C_real), Real (*df_ptr) (C_real), Real (*ddf_ptr) (C_real)); // Find funct root with Halley's algorithm

L_real fnd_root_halley_q(Cl_real x0_q, L_real (*f_ptr_q) (Cl_real),
                         L_real (*df_ptr_q) (Cl_real), L_real (*ddf_ptr_q) (Cl_real));                      // Find funct root with Halley's (quad-precision) algorithm

L_real fnd_root_newton_bisect_q(Cl_real a_q, Cl_real b_q, L_real (*f_ptr_q) (Cl_real),
                                L_real (*df_ptr_q) (Cl_real), Cl_real toll_q, C_int max_iter);              // Find funct root with Newton's-bisection hybrid algorithm


#endif /* !LIB_FUNCT_ROOTS */                                                                               // Avoid multiple inclusion
