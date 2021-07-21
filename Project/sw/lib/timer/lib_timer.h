/*
 * Author: Cristian Merli
 * Code title: Timer library header file
 * Code version: 3.0
 * Creation date: 04/05/2021
 * Last mod. date: 12/07/2021 
 */


/*!
 * @page        page8 8 - Timer library
 * @brief       Timer-library info
 * 
 * ---
 * 
 * @section     section10 Library description:
 *              This library has the main purpose of managing time's concerning operations (files lib_timer.h and lib_timer.c).
 * @subsection  subsection10 Library details:
 *              Library to manage date/time data structures from <time.h> system-library and to give the possibility to wait a delay time during runtime.<br/>
 *              * <b>Library data-types:</b>
 *                * #date_time                  &nbsp;--> <i>Date/time personalized data-structure.</i>
 *              * <b>Library public functions:</b>
 *                * #delay()                    &nbsp;--> <i>Function to wait specified delay time in milliseconds.</i>
 *                * #get_date_time()            &nbsp;--> <i>Function to get current date/time.</i>
 *                * #assign_date_time()         &nbsp;--> <i>Function to manually assign date/time values.</i>
 *                * #cmp_date_time()            &nbsp;--> <i>Function to compare two dates/times.</i>
 *                * #fbk_gn_lbu_ye_date_time()  &nbsp;--> <i>Function to print date/time feedback.</i>
 * 
 * @file        lib_timer.h <i>Library header file of lib_timer.c.</i>
 * @brief       <b>Timer-library header file</b>
 * 
 * @file        lib_timer.c <i>More info in <b><a href="page8.html">'Timer library'</a></b> section inside doxygen <b>'Related pages'</b>.</i>
 * @brief       <b>Timer-library code file</b>
 * 
 * @file        lib_timer.so <i>Library object file generated from lib_timer.c during compiling operations.</i>
 * @brief       <b>Timer-library object file</b>
 * 
 */


/* Libraries */
#include <time.h>                                                                                           // Time library inclusion (for delay function creation ecc.)


/* Constants */
/// <b>Macro description:</b> Date/time string length <i>(19 + '\0')</i>.
#define DATE_TIME_STR_LEN   20                                                                              // Date/time string length
/// <b>Macro description:</b> Date delimiter char.
#define DATE_DELIM_CHR      '/'                                                                             // Date delimiter char
/// <b>Macro description:</b> Date/time delimiter char.
#define DATE_TIME_DELIM_CHR ' '                                                                             // Date/time delimiter char
/// <b>Macro description:</b> Time delimiter char.
#define TIME_DELIM_CHR      ':'                                                                             // Time delimiter char
/// <b>Macro description:</b> Max allowed years value.
#define MAX_YY              2050                                                                            // Max years val
/// <b>Macro description:</b> Min allowed years value.
#define MIN_YY              1910                                                                            // Min years val
/// <b>Macro description:</b> Max allowed months value.
#define MAX_MN              12                                                                              // Max months val
/// <b>Macro description:</b> Min allowed months value.
#define MIN_MN              1                                                                               // Min months val
/// <b>Macro description:</b> Max allowed days value.
#define MAX_DD              31                                                                              // Max days val
/// <b>Macro description:</b> Min allowed days value.
#define MIN_DD              1                                                                               // Min days val
/// <b>Macro description:</b> Max allowed hours value <i>(hours+1)</i>.
#define MAX_HH              24                                                                              // Max hours val (+1)
/// <b>Macro description:</b> Min allowed hours value <i>(hours+1)</i>.
#define MIN_HH              1                                                                               // Min hours val (+1)
/// <b>Macro description:</b> Max allowed minutes value <i>(minutes+1)</i>.
#define MAX_MM              60                                                                              // Max minutes val (+1)
/// <b>Macro description:</b> Min allowed minutes value <i>(minutes+1)</i>.
#define MIN_MM              1                                                                               // Min minutes val (+1)
/// <b>Macro description:</b> Max allowed seconds value <i>(seconds+1)</i>.
#define MAX_SS              60                                                                              // Max seconds val (+1)
/// <b>Macro description:</b> Min allowed seconds value <i>(seconds+1)</i>.
#define MIN_SS              1                                                                               // Min seconds val (+1)


/* Structs & data-types */
/// <b>Struct-typedef description:</b> Date/time data-structure (yyyy/mn/dd, hh:mm:ss), defined using #get_date_time() or #assign_date_time() functions.<br/> Date/time exact format: <i>(yyyy) + #DATE_DELIM_CHR + (mn) + #DATE_DELIM_CHR + (dd) + #DATE_TIME_DELIM_CHR + (hh+1) + #TIME_DELIM_CHR + (mm+1) + #TIME_DELIM_CHR + (ss+1)</i>.
typedef struct date_time {                                                                                  // Date/time typedef (yyyy/mn/dd, hh:mm:ss)
  /// Years value. 
  int yyyy;                                                                                                 // Years
  /// Monts value.
  int mn;                                                                                                   // Months
  /// Days value.
  int dd;                                                                                                   // Days
  /// Hours value (+1).
  int hh;                                                                                                   // Hours (+1)
  /// Minutes value (+1).
  int mm;                                                                                                   // minutes (+1)
  /// Seconds value (+1).
  int ss;                                                                                                   // Seconds (+1)
} Date_time;


/* Enums & data-types */
/*!
 * \var OLDER
 * Strictly older comparison type.
 * \var NEWER
 * Strictly newer comparison type.
 */
/// <b>Enum-typedef description:</b> Date compare enum for #cmp_date_time() function.
typedef enum date_cmp {OLDER, NEWER} Date_cmp;                                                              // Date/time compare enum

/*!
 * \var OK
 * Comparison result ok.
 * \var NOT_OK
 * Comparison result not ok.
 */
/// <b>Enum-typedef description:</b> Compare result enum for #cmp_date_time() function using #chk_date_in_range() and #val_in_rage().
typedef enum cmp_res{NOT_OK, OK} Cmp_res;                                                                   // Date/time compare result enum


/* Library functions */
void delay(const long time_ms);                                                                             // Delay [ms] function

Date_time get_date_time();                                                                                  // Get date/time function

Date_time assign_date_time(const int yyyy, const int mn, const int dd,
                           const int hh, const int mm, const int ss);                                       // Assign date/time function

Cmp_res cmp_date_time(Date_time *const date1, const Date_cmp cmp_typ, Date_time *const date2);              // Compare date/time function

void fbk_gn_lbu_ye_date_time(const char *const prfx_str_lbu,  const Date_time *const date);                 // Green-lightblue-yellow date/time val feedback function



/* Date/time fromat */
/*
 * (YYYY) + date_sep + (MN) + date_sep + (DD) + date_time_sep + (HH+1) + time_sep + (MM+1) + time_sep + (SS+1)
 */
