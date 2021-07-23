/*
 * Author: Cristian Merli
 * Code title: UI (terminal I/O) library header file
 * Code version: 3.0
 * Creation date: 06/05/2021
 * Last mod. date: 13/07/2021 
 */


/*!
 * @page        page6 6 - UI library
 * @brief       User-interface-library info
 * 
 * ---
 * 
 * @section     section8 Library description:
 *              This library has the main purpose of managing user-interface terminal inputs/outputs (files lib_ui.h and lib_ui.c).
 * @subsection  subsection12 Library details:
 *              Library to securely manage terminal I/O operations, define terminal colors, define aliases for standard data-types and include most used libraries.<br/>
 *              * <b>Main library data-types:</b>
 *                * #Byte                       &nbsp;--> <i><b>unsigned char</b> alias (<b>Byte</b>).</i>
 *                * #Str                        &nbsp;--> <i><b>char*</b> alias (<b>Str</b>).</i>
 *                * #Cstr                       &nbsp;--> <i><b>const char*</b> alias (<b>Cstr</b>).</i>
 *                * #C_str                      &nbsp;--> <i><b>const char* const</b> alias (<b>C_str</b>).</i>
 *                * #Ptr                        &nbsp;--> <i><b>void*</b> alias (<b>Ptr</b>).</i>
 *                * #C_ptr                      &nbsp;--> <i><b>const void* const</b> alias (<b>C_ptr</b>).</i>
 *              * <b>Library public variables:</b>
 *                * #term_in_buff               &nbsp;--> <i>Terminal input buffer char array for scanf function, to read inputs from user (size defined using IN_BUFF_SIZE marco).</i>
 *                * #unused                     &nbsp;--> <i>Unused variable to catch unused returns from functions.</i>
 *              * <b>Main library public functions:</b>
 *                * #logo()                     &nbsp;--> <i>Function to print responsive-logo on terminal.</i>
 *                * #fbk_separator()            &nbsp;--> <i>Function to print responsive terminal-outputs separator.</i>
 *                * #press_enter()              &nbsp;--> <i>Function to ask <b>enter</b> key in order to continue (on terminal).</i>
 *                * #fbk_nl()                   &nbsp;--> <i>Function to print new line feedback on terminal.</i>
 *                * #fbk_gn_pu()                &nbsp;--> <i>Function to print green/purple feedback on terminal (generally used for request-feedbacks).</i>
 *                * #fbk_gn_cy()                &nbsp;--> <i>Function to print green/cyan feedback on terminal (generally used for operation-completed feedbacks).</i>
 *                * #fbk_gn_lbu_ye_real()       &nbsp;--> <i>Function to print green/light-blue/yellow #Real feedback on terminal.</i>
 *                * #fbk_err()                  &nbsp;--> <i>Function to print red error feedback on terminal.</i>
 *                * #read_term_in_min_chrs()    &nbsp;--> <i>Function to safely read user terminal-input.</i>
 *                * #read_term_in_int_inrange() &nbsp;--> <i>Function to safely read user terminal-input, making sure input value is in defined range.</i>
 *                * #read_term_in_confirm()     &nbsp;--> <i>Function to ask confirmation in order to continue (on terminal).</i>
 *                * #dbg_str()                  &nbsp;--> <i>Function to print debug string feedback on terminal (light-green/yellow/orange colored debug feedback).</i>
 *                * #close_err()                &nbsp;--> <i>Function to close software with error feedback printing on terminal.</i>
 *                * #close_fbk()                &nbsp;--> <i>Function to close software with goodbye feedback printing on terminal.</i>
 *                * #close_keyboard_interrupt() &nbsp;--> <i>Keyboard interrupt (ctrl+c) event-handler function: close software with specific feedback.</i>
 *              * <b>Library-defined terminal colors:</b>
 *                * #RD                         &nbsp;--> <i>Red color.</i>
 *                * #BU                         &nbsp;--> <i>Blue color.</i>
 *                * #LBU                        &nbsp;--> <i>Light-blue color.</i>
 *                * #PU                         &nbsp;--> <i>Purple color.</i>
 *                * #CY                         &nbsp;--> <i>Cyan color.</i>
 *                * #YE                         &nbsp;--> <i>Yellow color.</i>
 *                * #OG                         &nbsp;--> <i>Orange color.</i>
 *                * #GN                         &nbsp;--> <i>Green color.</i>
 *                * #LGN                        &nbsp;--> <i>Light-green color.</i>
 *                * #LGY                        &nbsp;--> <i>Light-gray color.</i>
 *                * #ER                         &nbsp;--> <i>End color.</i><br/><br/><br/>
 *              @image html terminal.png
 *              <br/><center>Icon made by <a href="https://flat-icons.com/">Flat Icons</a> from <a href="https://www.flaticon.com/free-icon/terminal_2621135?term=terminal&page=1&position=11&page=1&position=11&related_id=2621135&origin=search#">www.flaticon.com</a></center>
 * 
 * @file        lib_ui.h <i>Library header file of lib_ui.c.</i>
 * @brief       <b>User-interface-library header file</b>
 * 
 * @file        lib_ui.c <i>More info in <b><a href="page6.html">'UI library'</a></b> section inside doxygen <b>'Related pages'</b>.</i>
 * @brief       <b>User-interface-library code file</b>
 * 
 * @file        lib_ui.so <i>Library object file generated from lib_ui.c during compiling operations.</i>
 * @brief       <b>User-interface-library object file</b>
 */


/* Libraries */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <stdlib.h>                                                                                         // Standard library inclusion (for exit, atoi, dynamic memory ecc.)
#include <string.h>                                                                                         // String library inclusion (for strlen ecc.)
#include <sys/ioctl.h>                                                                                      // System I/O control library inclusion (for ioctl ecc.)
#include <unistd.h>                                                                                         // UniStd library inclusion (for stdout ecc.)
#include <stdarg.h>                                                                                         // Standard drag library inclusion (for variable number of function parameters)
#include <signal.h>                                                                                         // Signal library inclusion (SIGINT)


/* Constants */
/// <b>Macro description:</b> Max terminal-input strings length in chars <i>(63 + '\0')</i>, mainly used by scanf() function in terminal-input reading operations.
#define IN_BUFF_SIZE  64                                                                                    // Terminal inputs buffer size
/// <b>Macro description:</b> String to set terminal-color to red.
#define RD  "\033[0;31m"                                                                                    // Red color
/// <b>Macro description:</b> String to set terminal-color to blue.
#define BU  "\033[0;34m"                                                                                    // Blue color
/// <b>Macro description:</b> String to set terminal-color to light-blue.
#define LBU "\033[1;34m"                                                                                    // Light-blue color
/// <b>Macro description:</b> String to set terminal-color to purple.
#define PU  "\033[0;35m"                                                                                    // Purple color
/// <b>Macro description:</b> String to set terminal-color to cyan.
#define CY  "\033[0;36m"                                                                                    // Cyan color
/// <b>Macro description:</b> String to set terminal-color to yellow.
#define YE  "\033[1;33m"                                                                                    // Yellow color
/// <b>Macro description:</b> String to set terminal-color to orange.
#define OG  "\033[0;33m"                                                                                    // Orange color
/// <b>Macro description:</b> String to set terminal-color to green.
#define GN  "\033[0;32m"                                                                                    // Green color
/// <b>Macro description:</b> String to set terminal-color to light-green.
#define LGN "\033[1;32m"                                                                                    // Light-green color
/// <b>Macro description:</b> String to set terminal-color to light-gray.
#define LGY "\033[0;37m"                                                                                    // Light-gray color
/// <b>Macro description:</b> String to erase terminal-color.
#define ER  "\033[0m"                                                                                       // End color


/* Enums & data-types */
/*!
 * \var YES
 * Yes, confirm request.
 * \var NO
 * No, do not confirm request.
 * \var CANCEL
 * Cancel request.
 */
/// <b>Enum-typedef description:</b> Confirmation enum for #read_term_in_confirm() function.
typedef enum confirm {YES, NO, CANCEL} Confirm;                                                             // Confirmation enum typedef


/* Data-types */
/// <b>Typedef description:</b> unsigned char alias (Byte).
typedef unsigned char     Byte;                                                                             // Unsigned char alias (Byte)
/// <b>Typedef description:</b> unsigned short alias (U_shrt).
typedef unsigned short    U_shrt;                                                                           // Unsigned short alias (U_shrt)
/// <b>Typedef description:</b> unsigned int alias (U_int).
typedef unsigned int      U_int;                                                                            // Unsigned int alias (U_int)
/// <b>Typedef description:</b> unsigned long alias (U_long).
typedef unsigned long     U_long;                                                                           // Unsigned long alias (U_long)
/// <b>Typedef description:</b> double alias (Real).
typedef double            Real;                                                                             // Double alias (Real)
/// <b>Typedef description:</b> long double alias (L_real).
typedef long double       L_real;                                                                           // Long double alias (L_real)
/// <b>Typedef description:</b> char* alias (Str).
typedef char*             Str;                                                                              // Char* alias (Str)
/// <b>Typedef description:</b> void* alias (Ptr).
typedef void*             Ptr;                                                                              // Void* alias (Ptr)
/// <b>Typedef description:</b> const char alias (C_char).
typedef const char        C_char;                                                                           // Const char alias (C_char)
/// <b>Typedef description:</b> const unsigned short alias (C_byte).
typedef const Byte        C_byte;                                                                           // Const unsigned short alias (C_byte)
/// <b>Typedef description:</b> const int alias (C_int).
typedef const int         C_int;                                                                            // Const int alias (C_int)
/// <b>Typedef description:</b> const real alias (C_real).
typedef const Real        C_real;                                                                           // Const real alias (C_real)
/// <b>Typedef description:</b> const long double alias (Cl_real).
typedef const long double Cl_real;                                                                          // Const long double alias (Cl_real)
/// <b>Typedef description:</b> const char* alias (Cstr).
typedef const Str         Cstr;                                                                             // Const char* alias (Cstr)
/// <b>Typedef description:</b> const char* const alias (C_str).
typedef Cstr const        C_str;                                                                            // Const char* const alias (C_str)
/// <b>Typedef description:</b> const unsigned short alias (CU_shrt).
typedef const U_shrt      Cu_shrt;                                                                          // Const unsigned short alias (CU_shrt)
/// <b>Typedef description:</b> const void* const alias (C_ptr).
typedef const void* const C_ptr;                                                                            // Const void* const alias (C_ptr)


/* Public vars */
extern char term_in_buff[IN_BUFF_SIZE];                                                                     // Terminal input buffer char array for scanf func
/// <b>Public-variable description:</b> Unused variabile to avoid compile-errors when a function has an unused return value, like scanf().
extern int unused;                                                                                          // Unused var


/* Library functions */
void logo(Cu_shrt start_sp, C_str txt, C_str txt_col, C_char bkg_chr, C_str bkg_col);                       // Print responsive-logo function

void fbk_separator(C_char chr, C_str col);                                                                  // Separator feedback function

void press_enter(C_str req_str);                                                                            // Press enter function

void fbk_nl(C_int num);                                                                                     // New lines feedback function

void fbk_spaces(C_int num);                                                                                 // Spces feedback function

void fbk_tabs(C_int num);                                                                                   // Tabs feedback function

void fbk_gn_pu(C_str fbk_str);                                                                              // Green-purple feedback function

void fbk_gn_cy(C_str fbk_str);                                                                              // Green-cyan feedback function

void fbk_gn_lbu_ye_int(C_str prfx_str_lbu, C_int val_ye);                                                   // Green-lightblue-yellow int val feedback function

void fbk_gn_lbu_ye_str(C_str prfx_str_lbu, C_str str_ye);                                                   // Green-lightblue-yellow str val feedback function

void fbk_gn_lbu_ye_real(C_str prfx_str_lbu, C_real val_ye);                                                 // Green-lightblue-yellow real val feedback function

void fbk_gn_lbu_ye_lreal(C_str prfx_str_lbu, Cl_real val_ye);                                               // Green-lightblue-yellow long real val feedback function

void fbk_gn_lbu_ye_ptr(C_str prfx_str_lbu, C_ptr val_ye);                                                   // Green-lightblue-yellow ptr val feedback function

void fbk_err(C_str fbk_str);                                                                                // Error feedback function

Str read_term_in();                                                                                         // Read terminal input function

void clr_term_in();                                                                                         // Clear terminal input buffer function

Str read_term_in_min_chrs(C_byte min_chrs, C_str req_str, C_str err_str);                                   // Read terminal input (min chars) function

Str read_term_in_min_chrs_exit_chr(C_byte min_chrs, C_str req_str, C_str err_str, C_char exit_chr);         // Read terminal input (min chars and exit char) function

int read_term_in_int();                                                                                     // Read terminal input INT function

int read_term_in_int_inrange(C_int min_val, C_int max_val, C_str req_str, C_str err_str);                   // Read terminal input INT (in-range) function

Confirm read_term_in_confirm(C_str req_str);                                                                // Read terminal input confirmation function

void dbg();                                                                                                 // Fast debug function 

void dbg_print(C_str str);                                                                                  // Debug print function

void dbg_str(C_str str, C_str val);                                                                         // Debug string val print function

void dbg_int(C_str str, C_int val);                                                                         // Debug int val print function

void dbg_real(C_str str, C_real val);                                                                       // Debug real val print function

void dbg_lreal(C_str str, Cl_real val);                                                                     // Debug long real val print function

void dbg_ptr(C_str str, C_ptr val);                                                                         // Debug ptr val print function

void close_err();                                                                                           // Close software with error function

void close_fbk();                                                                                           // Function to close software with error feedback

void close_keyboard_interrupt(C_int signal);                                                                // Function to close SW with fbk due to keyboard interrupt detected (ctrl+c)
