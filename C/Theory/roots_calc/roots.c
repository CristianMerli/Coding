/*
 * Author: Cristian Merli
 * Code title: Roots
 * Code version: 3.0
 * Creation date: 12/06/2021
 * Last mod. date: 13/06/2021
 * 
 * 
 * // Compile-commands:
 * gccW99_lib lib/roots/lib_roots.so lib/roots/lib_roots.c          --> Create ROOTS dynamic library object file
 * gccW99_lib lib/ui/lib_ui.so lib/ui/lib_ui.c                      --> Create UI (TERMINAL I/O) dynamic library object file
 * gccW99_c roots.c                                                 --> Create SOFTWARE object file
 * 
 * // Link-command:
 * gccW99_o roots roots.o lib/roots/lib_roots.so lib/ui/lib_ui.so   --> LINK software and dynamic libraries object files to executable
 * 
 * // Aliases:
 * alias gccW99_o="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -o"
 * alias gccW99_c="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -c"
 * alias gccW99_lib="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -fpic -shared -o"
 */


/* Libraries */
#include "lib/roots/lib_roots.h"                                                                            // Import roots library header file


/* Constants */
//


/* Global vars */
C_real a = 2.0;                                                                                             // Val to calc root and newton algorithm startin' pt var init
C_int n = 2;                                                                                                // n-th root val var init


/* Main routines */
static void terminate_keyboard(int signal){                                                                 // Manage program exit from keyboard ctrl+c shortcut
  /* Body */
  close_keyboard_interrupt(signal);                                                                         // Close SW with fbk due to keyboard interrupt detected (ctrl+c)
}


/* Main cycle */
int main(){                                                                                                 // SW main cycle
  /* Main vars */
  //
  
  /* Code */
  signal(SIGINT, terminate_keyboard);                                                                       // Manage program exit from keyboard ctrl+c shortcut
  logo(6, "ROOTS CALCULATION LIBRARY TEST SOFTWARE", YE, '#', GN);                                          // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  press_enter("Hi");                                                                                        // Press enter to start SW fbk

  // Root calc
  fbk_nl(2);  fbk_gn_pu("Goin' to calculate test value's root...");                                         // Goin' to calc test val root fbk
  Real root_val = root_calc(a, n);                                                                          // Calc 'a' val 'n-th' root with newton algorithm, startin' from 'a' pt
  fbk_nl(1);  fbk_gn_cy("Root correctly calculated!");                                                      // Root correctly calc fbk
  fbk_nl(1);  fbk_gn_lbu_ye_real("Root value", root_val);                                                   // Print root val fbk
  
  close_fbk();                                                                                              // Close SW with fbk
  return EXIT_SUCCESS;                                                                                      // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/* 
 * Roots lib test SW
 */
