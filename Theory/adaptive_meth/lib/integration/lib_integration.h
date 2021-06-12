/*
 * Author: Cristian Merli
 * Code title: Adaptive integration methods library header file
 * Code version: 3.0
 * Creation date: 10/06/2021
 * Last mod. date: 12/06/2021 
 */


/* Avoid multiple inclusions */
#ifndef LIB_INTEGR                                                                                          // Avoid multiple inclusion
#define LIB_INTEGR                                                                                          // Avoid multiple inclusion


/* Libraries */
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file
#include <math.h>                                                                                           // Import math library


/* Constants */
//


/* Lib vars */
extern int interv_cnt;                                                                                      // Intervals counter


/* Structs & data-types */
//


/* Enums & data-types */
//


/* Library functions */
Real ad_integr_trap(C_real a, C_real fa, C_real b, C_real fb, C_real toll, Real (*f_ptr) (C_real));         // Adaptive integration with trapeziums method

Real ad_integr_simp(C_real a, C_real fa, C_real m, C_real fm,
                    C_real b, C_real fb, C_real toll, Real (*f_ptr) (C_real));                              // Adaptive integration with simpson method


#endif /* !LIB_INTEGR */                                                                                    // Avoid multiple inclusion
