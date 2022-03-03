/*
 * Author: Cristian Merli
 * Code title: UI (terminal I/O) library header file
 * Code version: 3.0
 * Creation date: 03/02/2022
 * Last mod. date: 03/02/2022 
 */


/* Libraries */
#include <iostream>                                                                                         // Include I/O lib
#include <sys/ioctl.h>                                                                                      // System I/O control library inclusion (for ioctl ecc.)
#include <unistd.h>                                                                                         // UniStd library inclusion (for stdout ecc.)
#include <string.h>                                                                                         // String library inclusion (for strlen ecc.)


/* Constants */
#define RD  "\033[0;31m"                                                                                    // Red color
#define BU  "\033[0;34m"                                                                                    // Blue color
#define LBU "\033[1;34m"                                                                                    // Light-blue color
#define PU  "\033[0;35m"                                                                                    // Purple color
#define CY  "\033[0;36m"                                                                                    // Cyan color
#define YE  "\033[1;33m"                                                                                    // Yellow color
#define OG  "\033[0;33m"                                                                                    // Orange color
#define GN  "\033[0;32m"                                                                                    // Green color
#define LGN "\033[1;32m"                                                                                    // Light-green color
#define LGY "\033[0;37m"                                                                                    // Light-gray color
#define ER  "\033[0m"                                                                                       // End color


/* Data-types */
typedef const int         C_int;                                                                            // Const int alias (C_int)
typedef unsigned short    U_shrt;                                                                           // Unsigned short alias (U_shrt)
typedef const U_shrt      Cu_shrt;                                                                          // Const unsigned short alias (CU_shrt)
typedef const char        C_char;                                                                           // Const char alias (C_char)
typedef char*             Str;                                                                              // Char* alias (Str)
typedef const Str         Cstr;                                                                             // Const char* alias (Cstr)
typedef Cstr const        C_str;                                                                            // Const char* const alias (C_str)
typedef const std::string CStr;                                                                             // Const std::string alias (CStr)


/* Library functions */
void fbk_nl(C_int num);                                                                                     // Funct to print new-lines fbk
void logo(Cu_shrt start_sp, C_str txt, C_str txt_col, C_char bkg_chr, C_str bkg_col);                       // Funct to print responsive-logo
void fbk_gn_cy(CStr fbk_str);                                                                               // Funct to print green-cyan feedback
void close_err();                                                                                           // Funct to close software with error fbk
void close_bye();                                                                                           // Funct to close software with bye fbk
