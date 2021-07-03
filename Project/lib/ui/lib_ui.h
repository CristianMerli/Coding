/*
 * Author: Cristian Merli
 * Code title: UI (terminal I/O) library header file
 * Code version: 3.0
 * Creation date: 06/05/2021
 * Last mod. date: 03/07/2021 
 */


/* Libraries */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <stdlib.h>                                                                                         // Standard library inclusion (for exit, atoi, dynamic memory ecc.)
#include <string.h>                                                                                         // String library inclusion (for strlen ecc.)
#include <sys/ioctl.h>                                                                                      // System I/O control library inclusion (for ioctl ecc.)
#include <unistd.h>                                                                                         // UniStd library inclusion (for stdout ecc.)
#include <stdarg.h>                                                                                         // Standard drag library inclusion (for variable number of function parameters)
#include <signal.h>                                                                                         // Signal library inclusion (SIGINT)


/* Defines */
#define IN_BUFF_SIZE  31                                                                                    // Terminal inputs buffer size


/* Constants */
#define RD  "\033[0;31m"                                                                                    // Red color
#define BU  "\033[0;34m"                                                                                    // Blue color
#define LBU "\033[1;34m"                                                                                    // Light blue color
#define PU  "\033[0;35m"                                                                                    // Purple color
#define CY  "\033[0;36m"                                                                                    // Cyan color
#define YE  "\033[1;33m"                                                                                    // Yellow color
#define OG  "\033[0;33m"                                                                                    // Orange color
#define GN  "\033[0;32m"                                                                                    // Green color
#define LGN "\033[1;32m"                                                                                    // Light green color
#define LGY "\033[0;37m"                                                                                    // Light gray color
#define ER  "\033[0m"                                                                                       // End color


/* Enums & data-types */
typedef enum confirm {YES, NO, CANCEL} Confirm;                                                             // Confirmation enum typedef


/* Data-types */
typedef unsigned char     Byte;                                                                             // Unsigned char alias (Byte)
typedef unsigned short    U_shrt;                                                                           // Unsigned short alias (U_shrt)
typedef unsigned int      U_int;                                                                            // Unsigned int alias (U_int)
typedef unsigned long     U_long;                                                                           // Unsigned long alias (U_long)
typedef double            Real;                                                                             // Double alias (Real)
typedef long double       L_real;                                                                           // Long double alias (L_real)
typedef char*             Str;                                                                              // Char* alias (Str)
typedef void*             Ptr;                                                                              // Void* alias (Ptr)
typedef const char        C_char;                                                                           // Const char alias (C_char)
typedef const Byte        C_byte;                                                                           // Const unsigned short alias (C_byte)
typedef const int         C_int;                                                                            // Const int alias (C_int)
typedef const Real        C_real;                                                                           // Const real alias (C_real)
typedef const long double Cl_real;                                                                          // Const long double alias (Cl_real)
typedef C_char* const     C_str;                                                                            // Const char* const alias (C_str)
typedef const U_shrt      Cu_shrt;                                                                          // Const unsigned short alias (CU_shrt)
typedef const void* const C_ptr;                                                                            // Const void* const alias (C_ptr)


/* Global vars */
extern char term_in_buff[IN_BUFF_SIZE];                                                                     // Terminal input buffer char array for scanf func
extern int unused;                                                                                          // Unused var


/* Library functions */
void logo(Cu_shrt start_sp, C_str txt, C_str txt_col, C_char bkg_chr, C_str bkg_col);                       // Print responsive-logo function

void press_enter(C_str req_str);                                                                            // Press enter function

void fbk_nl(C_int num);                                                                                     // New line feedback function

void fbk_gn_cy(C_str fbk_str);                                                                              // Green-cyan feedback function

void fbk_gn_pu(C_str fbk_str);                                                                              // Green-purple feedback function

void fbk_gn_lbu_ye_int(C_str prfx_str_lbu, C_int val_ye);                                                   // Green-lightblue-yellow int val feedback function

void fbk_gn_lbu_ye_str(C_str prfx_str_lbu, C_str str_ye);                                                   // Green-lightblue-yellow str val feedback function

void fbk_gn_lbu_ye_real(C_str prfx_str_lbu, C_real val_ye);                                                 // Green-lightblue-yellow real val feedback function

void fbk_gn_lbu_ye_lreal(C_str prfx_str_lbu, Cl_real val_ye);                                               // Green-lightblue-yellow long real val feedback function

void fbk_gn_lbu_ye_ptr(C_str prfx_str_lbu, C_ptr val_ye);                                                   // Green-lightblue-yellow ptr val feedback function

void fbk_err(C_str fbk_str);                                                                                // Error feedback function

Str read_term_in();                                                                                         // Read terminal input function

Str read_term_in_min_chrs(C_byte min_chrs, C_str req_str, C_str err_str);                                   // Read terminal input (min chars) function

Confirm read_term_in_confirm(C_str req_str);                                                                // Read terminal input confirmation function

Str read_term_in_min_chrs_exit_chr(C_byte min_chrs, C_str req_str, C_str err_str, C_char exit_chr);         // Read terminal input (min chars and exit char) function

int read_term_in_int();                                                                                     // Read terminal input INT function

int read_term_in_int_inrange(C_int min_val, C_int max_val, C_str req_str, C_str err_str);                   // Read terminal input INT (in-range) function

void clr_term_in();                                                                                         // Clear terminal input buffer function

void dbg();                                                                                                 // Fast debug function 

void dbg_print(C_str str);                                                                                  // Debug print function

void dbg_str(C_str str, C_str val);                                                                         // Debug string val print function

void dbg_int(C_str str, C_int val);                                                                         // Debug int val print function

void dbg_real(C_str str, C_real val);                                                                       // Debug real val print function

void dbg_lreal(C_str str, Cl_real val);                                                                     // Debug long real val print function

void dbg_ptr(C_str str, C_ptr val);                                                                         // Debug ptr val print function

void close_err();                                                                                           // Close software with error function

void close_fbk();                                                                                           // Close feedback function

void close_keyboard_interrupt(C_int signal);                                                                // Function to close SW with fbk due to keyboard interrupt detected (ctrl+c)
