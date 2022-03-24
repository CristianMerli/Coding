/*
 * Author: Cristian Merli
 * Code title: UI (terminal I/O) library header file
 * Code version: 3.0
 * Creation date: 03/02/2022
 * Last mod. date: 09/02/2022 
 */


/* Include guards */
#pragma once                                                                                                // Avoid multiple inclusions
#ifndef _UI_H_                                                                                              // Avoid multiple inclusions (old-alternative start)
#define _UI_H_                                                                                              // Avoid multiple inclusions (old-alternative)


/* Libraries */
#include <iostream>                                                                                         // Include I/O library inclusion (for cin, cout ecc.)
#include <type_traits>                                                                                      // Type-traits library inclusion (for template ecc.)
#include <sys/ioctl.h>                                                                                      // System I/O control library inclusion (for ioctl ecc.)
#include <unistd.h>                                                                                         // UniStd library inclusion (for stdout ecc.)
#include <limits>                                                                                           // Limits library inclusion (for numeric_limits ecc.)
#include <complex>                                                                                          // Complex-numbers library inclusion (for real, imag ecc.)


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
#define SP  ' '                                                                                             // Space


/* Macros */
#define FBK_NL(N) for (Byte i=0; i<N; ++i) std::cout << std::endl                                           // New lines printing macro

#define PRINT_VAL(STR1, VAL, STR2) \
std::cout << GN << ">>> " << PU << STR1 << ": " << LBU << VAL << SP << STR2 << std::endl << ER              // Value printing macro

#define ACQ_CYCLE(TXT, TYP, VAR, ERR_COND, ERR_TXT) \
do { \
get_val(TXT, TYP, &VAR); \
if (ERR_COND) term_print(ERR_TXT, ERR); else break; \
} while (true)                                                                                              // Acquisition cycle macro


/* Data-types */
typedef double                    Real;                                                                     // Real alias
typedef const double              C_real;                                                                   // const Real alias
typedef __int32_t                 Integer;                                                                  // Integer alias
typedef const __int32_t           C_integer;                                                                // const Integer alias
typedef __uint32_t                U_integer;                                                                // unsigned Integer alias
typedef const __uint32_t          CU_integer;                                                               // const unsigned Integer alias
typedef __int16_t                 Short;                                                                    // Short alias
typedef const __int16_t           C_short;                                                                  // const Short alias
typedef __uint16_t                U_short;                                                                  // unsigned Short alias
typedef const __uint16_t          CU_short;                                                                 // const unsigned Short alias
typedef __int8_t                  Byte;                                                                     // Byte alias
typedef const __int8_t            C_byte;                                                                   // const Byte alias
typedef __uint8_t                 U_byte;                                                                   // unsigned Byte alias
typedef const __uint8_t           CU_byte;                                                                  // const unsigned Byte alias
typedef bool                      Boolean;                                                                  // Boolean alias
typedef const bool                C_boolean;                                                                // const Boolean alias
typedef std::complex<Real>        Complex;                                                                  // Complex alias
typedef const std::complex<Real>  C_complex;                                                                // const Complex alias
typedef char                      Character;                                                                // Character alias
typedef const char                C_character;                                                              // const Character alias
typedef std::string               String;                                                                   // String alis
typedef const std::string         C_string;                                                                 // const String alias


/* Enums */
enum Fbk {FBK,REQ,ERR};                                                                                     // Fbk-typ enum
enum Data {REAL,INTEGER,STRING,CHARACTER};                                                                  // Fbk-typ enum


/* Public vars */
extern int unused;                                                                                          // Unused var


/* Library functions */
void title(CU_short start_sp, C_string txt, C_string txt_col, C_byte bkg_chr, C_string bkg_col);            // Funct to print responsive-title
void term_print(C_string fbk_str, const Fbk typ=FBK);                                                       // Funct to print on terminal (default=FBK)
void get_val(C_string req_str, const Data typ, void *const val);                                            // Funct impl to get user input value from terminal
void close_err(C_string err_str="");                                                                        // Funct to close software with error fbk
void close_bye(C_string bye_str="");                                                                        // Funct to close software with bye fbk


#endif                                                                                                      // Avoid multiple inclusions (old-alternative end)
