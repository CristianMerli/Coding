/*
 * Author: Cristian Merli
 * Code title: Timer library header file
 * Code version: 3.0
 * Creation date: 04/05/2021
 * Last mod. date: 19/05/2021 
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
  int yy;                                                                                                   // Years
  int mn;                                                                                                   // Months
  int dd;                                                                                                   // Days
  int hh;                                                                                                   // Hours (+1)
  int mm;                                                                                                   // minutes (+1)
  int ss;                                                                                                   // Seconds (+1)
}date_time;


/* Library functions */
void delay(const long time_ms);                                                                             // Delay [ms] function

date_time get_date_time();                                                                                  // Get date/time function

int chk_date_in_range(const date_time date);                                                                // Check date/time in range
