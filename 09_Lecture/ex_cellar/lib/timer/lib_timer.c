/*
 * Author: Cristian Merli
 * Code title: Timer library
 * Code version: 3.0
 * Creation date: 04/05/2021
 * Last mod. date: 04/05/2021
 */


/* Libraries */
#include "lib_timer.h"                                                                                      // Import timer library header file


/* Functions */
void delay(const long time_ms){                                                                             // Delay [ms] function
  /* Body */
  clock_t start_time = clock();                                                                             // Start time = software execution time
  while ((clock() - start_time) < (time_ms * (CLOCKS_PER_SEC / 1000)));                                     // Check if elapsed time [ms] (time - start_time) is greater or equal to pause time, pause time calculated considering the number of clocks per second
}
