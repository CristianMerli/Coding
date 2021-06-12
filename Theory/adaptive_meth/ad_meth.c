/*
 * Author: Cristian Merli
 * Code title: Adaptive integration methods
 * Code version: 3.0
 * Creation date: 10/06/2021
 * Last mod. date: 12/06/2021
 * 
 * 
 * // Compile-commands:
 * gccW99_lib lib/integration/lib_integration.so lib/integration/lib_integration.c      --> Create INTEGRATION dynamic library object file (Integration with adaptive methods)
 * gccW99_lib lib/ui/lib_ui.so lib/ui/lib_ui.c                                          --> Create UI (TERMINAL I/O) dynamic library object file
 * gccW99_c ad_meth.c                                                                   --> Create SOFTWARE object file
 * 
 * // Link-command:
 * gccW99_o ad_meth ad_meth.o lib/integration/lib_integration.so lib/ui/lib_ui.so -lm   --> LINK software and dynamic libraries object files to executable (-lm to force math lib inclusion)
 * 
 * // Aliases:
 * alias gccW99_o="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -o"
 * alias gccW99_c="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -c"
 * alias gccW99_lib="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -fpic -shared -o"
 */


/* Libraries */
#include "lib/integration/lib_integration.h"                                                                // Import integration library header file


/* Constants */
//


/* Global vars */
C_real a = 1, b = 6, m = (a+b)/2, toll = 1e-8;                                                              // Integration parameters (interval and tollerance) vars init


/* Main routines */
static void terminate_keyboard(int signal){                                                                 // Manage program exit from keyboard ctrl+c shortcut
  /* Body */
  close_keyboard_interrupt(signal);                                                                         // Close SW with fbk due to keyboard interrupt detected (ctrl+c)
}


static Real test_funt(C_real x){                                                                            // Test function
  /* body */
  return x*exp(-x)+sin(3.0*x)-log(1+pow(x, 2));                                                             // Return test function eval
}


static Real test_funt_primitive(C_real x){                                                                  // Test function primitive
  /* body */
  return (-x-1.0)*exp(-x)-x*log(pow(x, 2)+1.0)+2.0*x-2.0*atan(x)-cos(3.0*x)/3.0;                            // Return test function primitive eval
}


/* Main cycle */
int main(){                                                                                                 // SW main cycle
  /* Main vars */
  Real res = 0, exact_res = 0;                                                                              // Integration results vars init

  /* Code */
  signal(SIGINT, terminate_keyboard);                                                                       // Manage program exit from keyboard ctrl+c shortcut
  logo(2, "ADAPTIVE INTEGRATION METHODS LIBRARY TEST SOFTWARE", YE, '#', GN);                               // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  press_enter("Hi");                                                                                        // Press enter to start SW fbk

  // Integration interval and tollerance
  fbk_nl(1);  fbk_gn_pu("Integration parameters:");                                                         // Integration params fbk
  fbk_nl(1);  fbk_gn_lbu_ye_real("Interval 'a' point", a);                                                  // Integration interval a pt fbk
  fbk_nl(1);  fbk_gn_lbu_ye_real("Interval 'b' point", b);                                                  // Integration interval b pt fbk
  fbk_nl(1);  fbk_gn_lbu_ye_real("Set tollerance", toll);                                                   // Integration tollerance fbk
  // Exact integral value
  fbk_nl(2);  fbk_gn_pu("Goin' to calculate test function exact integral value...");                        // Calc exact integr val fbk
  exact_res = test_funt_primitive(b)-test_funt_primitive(a);                                                // Calc exact integr val
  fbk_nl(1);  fbk_gn_cy("Exact integral value correctly calculated!");                                      // Integr val correctly calc fbk
  fbk_nl(1);  fbk_gn_lbu_ye_real("Exact integral value", exact_res);                                        // Print exact integr val fbk
  // Trapeziums adaptive integration method
  fbk_nl(2);  fbk_gn_pu("Goin' to calculate integral on test funtion usin' trapeziums method...");          // Calc integr val usin' trapeziums meth fbk
  interv_cnt = 0;                                                                                           // Make sure to have intervals counter to zero
  res = ad_integr_trap(a, test_funt(a), b, test_funt(b), toll, test_funt);                                  // Calc num integr val with trapeziums meth
  fbk_nl(1);  fbk_gn_cy("Numeric integral value correctly calculated!");                                    // Integr val correctly calc fbk
  fbk_nl(1);  fbk_gn_lbu_ye_real("Calculated numeric integral value", res);                                 // Print num integr val fbk
  fbk_nl(1);  fbk_gn_lbu_ye_real("Calculation error", res-exact_res);                                       // Print num integr calc err val fbk
  fbk_nl(1);  fbk_gn_lbu_ye_int("Number of intervals (mesh partitions)", interv_cnt);                       // Print number of intervals necessary to calc num integr in tollerance
  // Simpson adaptive integration method
  fbk_nl(2);  fbk_gn_pu("Goin' to calculate integral on test funtion usin' simpson method...");             // Calc integr val usin' simpson meth fbk
  interv_cnt = 0;                                                                                           // Make sure to have intervals counter to zero
  res = ad_integr_simp(a, test_funt(a), m, test_funt(m), b, test_funt(b), toll, test_funt);                 // Calc num integr val with simpson meth
  fbk_nl(1);  fbk_gn_cy("Numeric integral value correctly calculated!");                                    // Integr val correctly calc fbk
  fbk_nl(1);  fbk_gn_lbu_ye_real("Calculated numeric integral value", res);                                 // Print num integr val fbk
  fbk_nl(1);  fbk_gn_lbu_ye_real("Calculation error", res-exact_res);                                       // Print num integr calc err val fbk
  fbk_nl(1);  fbk_gn_lbu_ye_int("Number of intervals (mesh partitions)", interv_cnt);                       // Print number of intervals necessary to calc num integr in tollerance
  
  close_fbk();                                                                                              // Close SW with fbk
  return EXIT_SUCCESS;                                                                                      // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/* 
 * Adaptive integration methods lib test SW
 */
