/*
 * Author: Cristian Merli
 * Code title: Timer library
 * Code version: 3.0
 * Creation date: 04/05/2021
 * Last mod. date: 19/05/2021
 */


/* Libraries */
#include "lib_timer.h"                                                                                      // Import timer library header file


/* Functions */
void delay(const long time_ms){                                                                             // Delay [ms] function
  /* Body */
  clock_t start_time = clock();                                                                             // Start time = software execution time
  while ((clock() - start_time) < (time_ms * (CLOCKS_PER_SEC / 1000)));                                     // Check if elapsed time [ms] (time - start_time) is greater or equal to pause time, pause time calculated considering the number of clocks per second
}


date_time get_date_time(){                                                                                  // Get date/time function
  /* Body */
  date_time tmp_date_time;                                                                                  // Temporary date/time var to return
  time_t now = time(NULL);                                                                                  // Now timer
  struct tm tm = *localtime(&now);                                                                          // Get now date/time

  tmp_date_time.yy = 1900+tm.tm_year;                                                                       // Save years var
  tmp_date_time.mn = 1+tm.tm_mon;                                                                           // Save months var
  tmp_date_time.dd = tm.tm_mday;                                                                            // Save days var
  tmp_date_time.hh = tm.tm_hour+1;                                                                          // Save hours var (+1)
  tmp_date_time.mm = tm.tm_min+1;                                                                           // Save minutes var (+1)
  tmp_date_time.ss = tm.tm_sec+1;                                                                           // Save seconds var (+1)

  return tmp_date_time;                                                                                     // Return date/time
}


static int val_in_rage(int val_min, int val, int val_max){                                                  // Function to check val in range
  /* Body */
  if (val >= val_min && val <= val_max)                                                                     // If val is in range
    return 1;                                                                                               // Return 1
  else                                                                                                      // Else if val isn't in range
    return 0;                                                                                               // Return 0
}


int chk_date_in_range(const date_time date){                                                                // Check date/time in range
  /* Body */
  if (val_in_rage(MIN_YY, date.yy, MAX_YY) && val_in_rage(MIN_MN, date.mn, MAX_MN) &&
      val_in_rage(MIN_DD, date.dd, MAX_DD) && val_in_rage(MIN_HH, date.hh, MAX_HH) &&
      val_in_rage(MIN_MM, date.mm, MAX_MM) && val_in_rage(MIN_SS, date.ss, MAX_SS))                         // If date/time is in range
    return 1;                                                                                               // Return 1
  else                                                                                                      // Else if date/time isn't in range
    return 0;                                                                                               // Return 0
}
