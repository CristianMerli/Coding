/*
 * Author: Cristian Merli
 * Code title: Function roots
 * Code version: 3.0
 * Creation date: 14/06/2021
 * Last mod. date: 17/06/2021
 * 
 * 
 * // Compile-commands:
 * gccW99_lib lib/funct_roots/lib_funct_roots.so lib/funct_roots/lib_funct_roots.c                        --> Create FUNCT_ROOTS dynamic library object file
 * gccW99_lib lib/ui/lib_ui.so lib/ui/lib_ui.c                                                            --> Create UI (TERMINAL I/O) dynamic library object file
 * gccW99_c funct_roots_calc.c                                                                            --> Create SOFTWARE object file
 * 
 * // Link-command:
 * gccW99_o funct_roots_calc funct_roots_calc.o lib/funct_roots/lib_funct_roots.so lib/ui/lib_ui.so -lm   --> LINK software and dynamic libraries object files to executable (-lm to force math lib inclusion)
 * 
 * // Aliases:
 * alias gccW99_o="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -o"
 * alias gccW99_c="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -c"
 * alias gccW99_lib="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -fpic -shared -o"
 */


/* Libraries */
#include "lib/funct_roots/lib_funct_roots.h"                                                                // Import function roots library header file


/* Constants */
//


/* Global vars */
C_real exact_root1 = 2.9178920259734737846639677779502982237485;                                                                  // Test funct exact root 1
C_real exact_root2 = -0.6523287325887866761309801162802854375064;                                                                 // Test funct exact root 2
C_real exact_root3 = 3.577539178951310716268076088982566212083629;                                                                // Test funct exact root 3
Cl_real exact_root1_q = 2.917892025973473784663967777950298223748596463679066966708622412933904951458487977102877636428391323;    // Test funct exact root 1 (quad-precision)
Cl_real exact_root2_q = -0.6523287325887866761309801162802854375064936427327122867242562820765304064984534618138022736015616836;  // Test funct exact root 2 (quad-precision)
Cl_real exact_root3_q = 3.577539178951310716268076088982566212083629052753465297763525657411230638888730750110084076380097862;    // Test funct exact root 3 (quad-precision)


/* Main routines */
static void terminate_keyboard(C_int signal){                                                               // Manage program exit from keyboard ctrl+c shortcut
  /* Body */
  close_keyboard_interrupt(signal);                                                                         // Close SW with fbk due to keyboard interrupt detected (ctrl+c)
}


static Real funct(C_real x){                                                                                // Test funct
  return exp(x)*(1+x)-(x*x*x*x);                                                                            // Return test funct eval
}


static Real funct_d(C_real x){                                                                              // Test funct 1st deriv
  return (x+2)*exp(x)-4*(x*x*x);                                                                            // Return test funct 1st deriv eval
}


static Real funct_dd(C_real x){                                                                             // Test funct 2nd deriv
  return (x+3)*exp(x)-12*(x*x);                                                                             // Return test funct 2nd deriv eval
}


static L_real funct_q(Cl_real x_q){                                                                         // Test funct (quad-precision)
  return expl(x_q)*(1+x_q)-(x_q*x_q*x_q*x_q);                                                               // Return test funct eval (quad-precision)
}


static L_real funct_d_q(Cl_real x_q){                                                                       // Test funct 1st deriv (quad-precision)
  return (x_q+2)*expl(x_q)-4*(x_q*x_q*x_q);                                                                 // Return test funct 1st deriv eval (quad-precision)
}


static L_real funct_dd_q(Cl_real x_q){                                                                      // Test funct 2nd deriv (quad-precision)
  return (x_q+3)*expl(x_q)-12*(x_q*x_q);                                                                    // Return test funct 2nd deriv eval (quad-precision)
}


/* Main cycle */
int main(){                                                                                                 // SW main cycle
  /* Main vars */
  Real funct_root = 0.0;                                                                                    // Funct's root var init
  L_real funct_root_q = 0.0;                                                                                // Funct's root var init (quad-precision)
  C_real x0 = 2.0;                                                                                          // Algorithms startin' pt to find funct's root (x0)
  Cl_real x0_q = 2.0, a_q = -2.0, b_q = +2.0, toll = 1e-18;                                                 // Algorithms startin' pt to find funct's root (x0) in quad-precision, Newton's-bisection hybrid algorithm interval [a,b] and max epsilon-tollerance error in quad-precision
  C_int max_iter = 10;                                                                                      // Max number of Newton's-bisection hybrid algorithm iterations

  /* Code */
  signal(SIGINT, terminate_keyboard);                                                                       // Manage program exit from keyboard ctrl+c shortcut
  logo(4, "FUNCTION ROOTS CALCULATION LIBRARY TEST SOFTWARE", YE, '#', GN);                                 // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  press_enter("Hi");                                                                                        // Press enter to start SW fbk

  // Funct's root calc with Newton's alg
  fbk_nl(1);  fbk_gn_pu("Goin' to find test function's root with Newton's algorithm...");                   // Goin' to find test funct's root with Newton's alg fbk
  funct_root = fnd_root_newton(x0, funct, funct_d);                                                         // Find test funct's root with Newton's alg
  fbk_nl(1);  fbk_gn_cy("Function's root found!");                                                          // Funct's root found fbk
  fbk_nl(1);  fbk_gn_lbu_ye_real("Function's root", funct_root);                                            // Print funct's root val fbk
  // Funct's root calc with Halleys's alg
  fbk_nl(1);  fbk_gn_pu("Goin' to find test function's root with Halleys's algorithm...");                  // Goin' to find test funct's root with Halleys's alg fbk
  funct_root = fnd_root_halley(x0, funct, funct_d, funct_dd);                                               // Find test funct's root with Halleys's alg
  fbk_nl(1);  fbk_gn_cy("Function's root found!");                                                          // Funct's root found fbk
  fbk_nl(1);  fbk_gn_lbu_ye_real("Function's root", funct_root);                                            // Print funct's root val fbk
  // Funct's root calc with Halleys's alg (quad-precision)
  fbk_nl(1);  fbk_gn_pu("Goin' to find test function's root with Halleys's algorithm, quad-precision...");  // Goin' to find test funct's root with Halleys's alg (quad-precision) fbk
  funct_root_q = fnd_root_halley_q(x0_q, funct_q, funct_d_q, funct_dd_q);                                   // Find test funct's root with Halleys's alg (quad-precision)
  fbk_nl(1);  fbk_gn_cy("Function's root found!");                                                          // Funct's root found fbk
  fbk_nl(1);  fbk_gn_lbu_ye_lreal("Function's root", funct_root_q);                                         // Print funct's root val fbk
  // Funct's root calc with Newton's-bisect hybrid alg (quad-precision)
  fbk_nl(1);  fbk_gn_pu("Goin' to find test function's root with Newton's-bisection hybrid algorithm...");  // Goin' to find test funct's root with Halleys's alg (quad-precision) fbk
  funct_root_q = fnd_root_newton_bisect_q(a_q, b_q, funct_q, funct_d_q, toll, max_iter);                    // Find test funct's root with Newton's-bisection hybrid alg (quad-precision)
  fbk_nl(1);  fbk_gn_cy("Function's root found!");                                                          // Funct's root found fbk
  fbk_nl(1);  fbk_gn_lbu_ye_lreal("Function's root", funct_root_q);                                         // Print funct's root val fbk
  
  close_fbk();                                                                                              // Close SW with fbk
  return EXIT_SUCCESS;                                                                                      // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/* 
 * Function roots lib test SW
 */
