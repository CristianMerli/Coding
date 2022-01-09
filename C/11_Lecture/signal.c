/*
 * Author: Cristian Merli
 * Code title: Signal lib management
 * Code version: 3.0
 * Creation date: 24/05/2021
 * Last mod. date: 24/05/2021
 */ 


/* Libraries */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <stdlib.h>                                                                                         // Standard library inclusion (EXIT_SUCCESS, EXIT_FAILURE)
#include <signal.h>                                                                                         // Signal library inclusion (SIGINT)


/* Main routines */
void terminate_keyboard(int signal){                                                                        // Manage program exit from keyboard ctrl+c shortcut
  /* Body */
  printf("\nProgram terminated from keyboard shortcut!\n");                                                 // Print closing fbk
  exit(signal);                                                                                             // Exit with signal
}


void division_zero(int signal){                                                                             // Manage by zero divisions (not working in forced c99 version)
  /* Body */
  printf("\nError, it's impossible to divide a number by zero! Terminating program!\n");                    // Print error fbk
  exit(signal);                                                                                             // Exit with signal
}


/* Main cycle */
int main(){
  /* Main vars */
  int z = 0;                                                                                                // Int var to test zero divisions management

  /* Code */
  signal(SIGINT, terminate_keyboard);                                                                       // Manage program exit from keyboard ctrl+c shortcut
  signal(SIGFPE, division_zero);                                                                            // Manage by zero divisions

  printf("%d", 6 / z);                                                                                      // Zero division to test zero divisions management (not working in forced c99 version)
  while(1);                                                                                                 // Endless loop to test program exit from keyboard ctrl+c shortcut
  
  //raise(SIGFPE);                                                                                            // Raise (by zero division) signal flg manually

  return EXIT_SUCCESS;                                                                                      // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Signal lib management
 */
