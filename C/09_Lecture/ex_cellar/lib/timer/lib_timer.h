/*
 * Author: Cristian Merli
 * Code title: Timer library header file
 * Code version: 3.0
 * Creation date: 04/05/2021
 * Last mod. date: 20/05/2021 
 */


/* Libraries */
#include <time.h>                                                                                           // Time library inclusion (for delay function creation ecc.)


/* Constants */
#define DATE_TIME_STR_LEN   20                                                                              // Date/time string length
#define DATE_DELIM_CHR      '/'                                                                             // Date delimiter char
#define DATE_TIME_DELIM_CHR ' '                                                                             // Date/time delimiter char
#define TIME_DELIM_CHR      ':'                                                                             // Time delimiter char
#define MAX_YY              2025                                                                            // Max years val
#define MIN_YY              2015                                                                            // Min years val
#define MAX_MN              12                                                                              // Max months val
#define MIN_MN              1                                                                               // Min months val
#define MAX_DD              31                                                                              // Max days val
#define MIN_DD              1                                                                               // Min days val
#define MAX_HH              24                                                                              // Max hours val (+1)
#define MIN_HH              1                                                                               // Min hours val (+1)
#define MAX_MM              60                                                                              // Max minutes val (+1)
#define MIN_MM              1                                                                               // Min minutes val (+1)
#define MAX_SS              60                                                                              // Max seconds val (+1)
#define MIN_SS              1                                                                               // Min seconds val (+1)


/* Enums & data-types */
typedef struct date_time {                                                                                  // Date/time typedef (yy/mn/dd, hh:mm:ss)
  int yyyy;                                                                                                 // Years
  int mn;                                                                                                   // Months
  int dd;                                                                                                   // Days
  int hh;                                                                                                   // Hours (+1)
  int mm;                                                                                                   // minutes (+1)
  int ss;                                                                                                   // Seconds (+1)
} date_time;

typedef enum date_cmp {OLDER, NEWER} date_cmp;                                                              // Date/time compare enum

typedef enum cmp_res{OK, NOT_OK} cmp_res;                                                                   // Date/time compare result enum


/* Library functions */
void delay(const long time_ms);                                                                             // Delay [ms] function

date_time get_date_time();                                                                                  // Get date/time function

date_time assign_date_time(const int yyyy, const int mn, const int dd,
                           const int hh, const int mm, const int ss);                                       // Assign date/time function

cmp_res cmp_date_time(date_time *const date1, const date_cmp cmp_typ, date_time *const date2);              // Compare date/time function

cmp_res chk_date_in_range(const date_time date);                                                            // Check date/time in range function

void fbk_gn_lbu_date_time(const char *const prfx_str_lbu,  const date_time *const date);                    // Green-lightblue-yellow date/time val feedback function



/* Date/time fromat */
/*
 * (YYYY) + date_sep + (MN) + date_sep + (DD) + date_time_sep + (HH+1) + time_sep + (MM+1) + time_sep + (SS+1)
 */
