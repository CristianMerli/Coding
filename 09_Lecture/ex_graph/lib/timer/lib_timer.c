/*
 * Author: Cristian Merli
 * Code title: Timer library
 * Code version: 3.0
 * Creation date: 04/05/2021
 * Last mod. date: 20/05/2021
 */


/* Libraries */
#include "lib_timer.h"                                                                                      // Import timer library header file
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file


/* Functions */
static int val_in_rage(int val_min, int val, int val_max){                                                  // Function to check val in range
  /* Body */
  if (val >= val_min && val <= val_max)                                                                     // If val is in range
    return 1;                                                                                               // Return 1
  else                                                                                                      // Else if val isn't in range
    return 0;                                                                                               // Return 0
}


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

  tmp_date_time.yyyy = 1900+tm.tm_year;                                                                     // Save years var
  tmp_date_time.mn = 1+tm.tm_mon;                                                                           // Save months var
  tmp_date_time.dd = tm.tm_mday;                                                                            // Save days var
  tmp_date_time.hh = tm.tm_hour+1;                                                                          // Save hours var (+1)
  tmp_date_time.mm = tm.tm_min+1;                                                                           // Save minutes var (+1)
  tmp_date_time.ss = tm.tm_sec+1;                                                                           // Save seconds var (+1)

  return tmp_date_time;                                                                                     // Return date/time
}


date_time assign_date_time(const int yyyy, const int mn, const int dd,
                           const int hh, const int mm, const int ss){                                       // Assign date/time function
  /* Body */
  date_time tmp_date_time;                                                                                  // Temporary date/time var to return
  
  tmp_date_time.yyyy = yyyy;                                                                                // Save years var
  tmp_date_time.mn = mn;                                                                                    // Save months var
  tmp_date_time.dd = dd;                                                                                    // Save days var
  tmp_date_time.hh = hh+1;                                                                                  // Save hours var (+1)
  tmp_date_time.mm = mm+1;                                                                                  // Save minutes var (+1)
  tmp_date_time.ss = ss+1;                                                                                  // Save seconds var (+1)

  if (chk_date_in_range(tmp_date_time) == NOT_OK){                                                          // Check date/time consistency (case NOT-OK)
    tmp_date_time.yyyy = 0;                                                                                 // Set years var to ZERO
    tmp_date_time.mn = 0;                                                                                   // Set months var to ZERO
    tmp_date_time.dd = 0;                                                                                   // Set days var to ZERO
    tmp_date_time.hh = 0;                                                                                   // Set hours var to ZERO
    tmp_date_time.mm = 0;                                                                                   // Set minutes var to ZERO
    tmp_date_time.ss = 0;                                                                                   // Set seconds var to ZERO
  }

  return tmp_date_time;                                                                                     // Return date/time var
}


cmp_res cmp_date_time(date_time *const date1, const date_cmp cmp_typ, date_time *const date2){              // Compare date/time function
  /* Body */
  int *date1_val_ptr = &date1->yyyy, *date2_val_ptr = &date2->yyyy;                                         // Date/time ptrs vals
  for (byte idx = 1; *date1_val_ptr == *date2_val_ptr && idx < 6; ++idx){                                   // Compare and redefine date1 and date2 ptr vals FOR cylce (cycle 'till years/months/days/hours/minutes/seconds are different)
    switch (idx)                                                                                            // Redefinition index switch-case
    {
    case 1:                                                                                                 // If years are equivalents, check months
      date1_val_ptr = &date1->mn;                                                                           // Redefine date1 ptr val to date1 months
      date2_val_ptr = &date2->mn;                                                                           // Redefine date2 ptr val to date2 months
      break;
    ///////
    case 2:                                                                                                 // If months are equivalents, check days
      date1_val_ptr = &date1->dd;                                                                           // Redefine date1 ptr val to date1 days
      date2_val_ptr = &date2->dd;                                                                           // Redefine date2 ptr val to date2 days
      break;
    ///////
    case 3:                                                                                                 // If days are equivalents, check hours
      date1_val_ptr = &date1->hh;                                                                           // Redefine date1 ptr val to date1 hours
      date2_val_ptr = &date2->hh;                                                                           // Redefine date2 ptr val to date2 hours
      break;
    ///////
    case 4:                                                                                                 // If hours are equivalents, check minutes
      date1_val_ptr = &date1->mm;                                                                           // Redefine date1 ptr val to date1 minutes
      date2_val_ptr = &date2->mm;                                                                           // Redefine date2 ptr val to date2 minutes
      break;
    ///////
    case 5:                                                                                                 // If minutes are equivalents, check seconds
      date1_val_ptr = &date1->ss;                                                                           // Redefine date1 ptr val to date1 seconds
      date2_val_ptr = &date2->ss;                                                                           // Redefine date2 ptr val to date2 seconds
      break;        
    }
  }
  if ((cmp_typ == OLDER && *date1_val_ptr < *date2_val_ptr) ||
      (cmp_typ == NEWER && *date1_val_ptr > *date2_val_ptr))                                                // Comparison conditions, if comparison is OK
    return OK;                                                                                              // Return compare OK
  else                                                                                                      // Else if comparison is NOT-OK
    return NOT_OK;                                                                                          // Return compare NOT-OK
}


cmp_res chk_date_in_range(const date_time date){                                                            // Check date/time in range function
  /* Body */
  if (val_in_rage(MIN_YY, date.yyyy, MAX_YY) && val_in_rage(MIN_MN, date.mn, MAX_MN) &&
      val_in_rage(MIN_DD, date.dd, MAX_DD) && val_in_rage(MIN_HH, date.hh, MAX_HH) &&
      val_in_rage(MIN_MM, date.mm, MAX_MM) && val_in_rage(MIN_SS, date.ss, MAX_SS))                         // If date/time is in range
    return OK;                                                                                              // Return OK
  else                                                                                                      // Else if date/time isn't in range
    return NOT_OK;                                                                                          // Return NOT-OK
}


void fbk_gn_lbu_date_time(const char *const prfx_str_lbu, const date_time *const date){                     // Green-lightblue-yellow date/time val feedback function
  /* Body */
  printf("%s>>>%s %s: %s%d%c%d%c%d%c%d%c%d%c%d%s",
          GN, LBU, prfx_str_lbu, YE, date->yyyy, DATE_DELIM_CHR, date->mn, DATE_DELIM_CHR, date->dd,
          DATE_TIME_DELIM_CHR, date->hh-1, TIME_DELIM_CHR, date->mm-1, TIME_DELIM_CHR, date->ss-1, ER);     // Print green-lightblue-yellow date/time val feedback
}
