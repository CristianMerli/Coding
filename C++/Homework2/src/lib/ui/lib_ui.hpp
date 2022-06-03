/*
 * Author: Cristian Merli
 * Code title: UI (terminal I/O) library header file
 * Code version: 3.0
 * Creation date: 07/04/2022
 * Last mod. date: 03/06/2022 
 */


/* Include guards */
#pragma once                                                                                                // Avoid multiple inclusions
#ifndef _UI_HPP_                                                                                            // Avoid multiple inclusions (old-alternative start)
#define _UI_HPP_                                                                                            // Avoid multiple inclusions (old-alternative)


/* Libraries */
#include <iostream>                                                                                         // I/O library inclusion (for cin, cout ecc.)
#include <vector>                                                                                           // Vector library inclusion (for std::vector ecc.)
#include <cmath>                                                                                            // Math library inclusion (for numeric_limits ecc.)
#include <limits>                                                                                           // Limits library inclusion (for fabs ecc.)
#include <unistd.h>                                                                                         // UniStd library inclusion (for stdout ecc.)
#include <sys/ioctl.h>                                                                                      // System I/O control library inclusion (for ioctl ecc.)
//#include <iomanip>                                                                                        // I/O mainp library inclusion (for setw ecc.) [UNUSED]
//#include <cctype>                                                                                         // C-ctype library inclusion (for tolower ecc.) [UNUSED]


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
#define S(VAL)  std::to_string(VAL)                                                                         // Val-to-str conv macro
#define TERM_ACQ_CYCLE(TXT, TYP, VAR, ERR_COND, ERR_TXT) \
do {VAR=term_get_val<TYP>(TXT); if (ERR_COND) term_print(ERR_TXT, ERR); else break;} while (true)           // Terminal acquisition cycle macro


/* Data-type limits */
#undef REAL_EPSILON                                                                                         // Avoid macro-redef
#define REAL_EPSILON __DBL_EPSILON__                                                                        // Real epsilon (FPN-precision)
// Real min-max vals
#undef REAL_MIN                                                                                             // Avoid macro-redef
#define REAL_MIN __DBL_MIN__                                                                                // Real min val
#undef REAL_MAX                                                                                             // Avoid macro-redef
#define REAL_MAX __DBL_MAX__                                                                                // Real max val
// Integer min-max vals
#undef INTEGER_MIN                                                                                          // Avoid macro-redef
#define INTEGER_MIN (-INTEGER_MAX - 1)                                                                      // Integer min val
#undef INTEGER_MAX                                                                                          // Avoid macro-redef
#define INTEGER_MAX __INT_MAX__                                                                             // Integer max val
// unsigned-Integer min-max vals
#undef UINTEGER_MAX                                                                                         // Avoid macro-redef
#define UINTEGER_MAX (INTEGER_MAX * 2U + 1U)                                                                // unsigned-Integer max val
#undef UINTEGER_MIN                                                                                         // Avoid macro-redef
#define UINTEGER_MIN 0                                                                                      // unsigned-Integer min val
// Short min-max vals
#undef SHORT_MIN                                                                                            // Avoid macro-redef
#define SHORT_MIN (-SHORT_MAX - 1)                                                                          // Short min val
#undef SHORT_MAX                                                                                            // Avoid macro-redef
#define SHORT_MAX __SHRT_MAX__                                                                              // Short max val
// unsigned Short min-max vals
#undef USHORT_MAX                                                                                           // Avoid macro-redef
#if __SHRT_MAX__ == __INT_MAX__                                                                             // In case of short and int with the same size
# define USHORT_MAX (SHORT_MAX * 2U + 1U)                                                                   // unsigned-Short max val (scale val like unsigned Integer)
#else                                                                                                       // Else in case of short and int with different size
# define USHORT_MAX (SHORT_MAX * 2 + 1)                                                                     // unsigned-Short max val (standard def)
#endif                                                                                                      // End-if
#undef USHORT_MIN                                                                                           // Avoid macro-redef
#define USHORT_MIN 0                                                                                        // unsigned-Short min val
// Byte min-max vals
#undef BYTE_MIN                                                                                             // Avoid macro-redef
#define BYTE_MIN (-BYTE_MAX - 1)                                                                            // Byte min val
#undef BYTE_MAX                                                                                             // Avoid macro-redef
#define BYTE_MAX __SCHAR_MAX__                                                                              // Byte max val
// unsigned Byte min-max vals
#undef UBYTE_MAX                                                                                            // Avoid macro-redef
#if __SCHAR_MAX__ == __INT_MAX__                                                                            // In case of signed-char and int with the same size
# define UBYTE_MAX (BYTE_MAX * 2U + 1U)                                                                     // unsigned-Byte max val (scale val like unsigned Integer)
#else                                                                                                       // Else in case of signed-char and int with different size
# define UBYTE_MAX (BYTE_MAX * 2 + 1)                                                                       // unsigned-Byte max val (standard def)
#endif                                                                                                      // End-if
#undef UBYTE_MIN                                                                                            // Avoid macro-redef
#define UBYTE_MIN 0                                                                                         // unsigned-Byte min val


/* Data-types */
typedef double            Real;                                                                             // Real alias
typedef const double      C_real;                                                                           // const Real alias
typedef __int32_t         Integer;                                                                          // Integer alias
typedef const __int32_t   C_integer;                                                                        // const Integer alias
typedef __uint32_t        U_integer;                                                                        // unsigned Integer alias
typedef const __uint32_t  CU_integer;                                                                       // const unsigned Integer alias
typedef __int16_t         Short;                                                                            // Short alias
typedef const __int16_t   C_short;                                                                          // const Short alias
typedef __uint16_t        U_short;                                                                          // unsigned Short alias
typedef const __uint16_t  CU_short;                                                                         // const unsigned Short alias
typedef __int8_t          Byte;                                                                             // Byte alias [AVOID ON TERMINAL]
typedef const __int8_t    C_byte;                                                                           // const Byte alias [AVOID ON TERMINAL]
typedef __uint8_t         U_byte;                                                                           // unsigned Byte alias [AVOID ON TERMINAL]
typedef const __uint8_t   CU_byte;                                                                          // const unsigned Byte alias [AVOID ON TERMINAL]
typedef bool              Boolean;                                                                          // Boolean alias
typedef const bool        C_boolean;                                                                        // const Boolean alias
typedef __int8_t          Character;                                                                        // Character alias
typedef const __int8_t    C_character;                                                                      // const Character alias
typedef std::string       String;                                                                           // String alis
typedef const std::string C_string;                                                                         // const String alias


/* Enums-types */
enum Print_typ {FBK, REQ, ERR}; typedef const Print_typ C_print_typ;                                        // Terminal print typ enum and const Terminal-print-typ enum alias


/* Color const-vars */
extern String fbk_col[];                                                                                    // Terminal fbk print-colors (for printing functions/templates - 3 colors)
extern String req_col[];                                                                                    // Terminal request print-colors (for printing functions/templates - 3 colors)
extern String err_col[];                                                                                    // Terminal error print-colors (for printing functions/templates - 2 colors)


/* Public functions */
Boolean read_cl_param(C_integer &argc, char *const argv[], Real param[], C_integer &param_sz);              // Funct to read Real command-line parameters (returns err flg)
Boolean read_cl_param(C_integer &argc, char *const argv[], String param[], C_integer &param_sz);            // Funct to read String command-line parameters (returns err flg)
void term_print_title(C_string &title_txt, C_string &title_col, C_character &bkg_chr, C_string &bkg_col);   // Funct to print responsive-title on terminal (title-txt, title-col, bkg-char, bkg-col)
void term_print(C_string &fbk_str, C_print_typ &typ=FBK);                                                   // Funct to perform terminal print (default print-typ=FBK)
void term_print_nl(C_integer &n=1);                                                                         // Funct to perform new-lines terminal print
void term_close_err(C_string &err_str="");                                                                  // Funct to close software terminal with error fbk
void term_close_bye(C_string &bye_str="");                                                                  // Funct to close software terminal with bye fbk
Boolean chk_numeric_str(C_string &str, C_string &err_str);                                                  // Funct to check numerical string (returns err flg)
Boolean real_eq(C_real &val1, C_real &val2);                                                                // Funct to check if real vals are equal
Boolean real_df(C_real &val1, C_real &val2);                                                                // Funct to check if real vals are different
Boolean real_eq_z(C_real &val);                                                                             // Funct to check if real val is equal to zero
Boolean real_df_z(C_real &val);                                                                             // Funct to check if real val is different from zero
void random_init();                                                                                         // Funct to initialize time-based random sequence (call b4 random_val() template - not in a loop)


/* Public templates */
template<typename T> extern void term_print(C_string &fbk_str, const T &val);                               // Template to print val on terminal
template<typename T> extern void term_print(C_string &fbk_str, const T &val, C_string &fbk_str2);           // Template to print val on terminal with details
template<typename T> extern T term_get_val(C_string &req_str);                                              // Template to get user input val from terminal
template<typename T> extern T* alloc(C_integer &sz);                                                        // Template to allocate dynamic-memo (vector)
template<typename T> extern void dealloc(const T *const ptr);                                               // Template to deallocate dynamic-memo (vector)
template<typename T> extern const T &max_val(const T &val1, const T &val2);                                 // Template to calculate max-val
template<typename T> extern const T &min_val(const T &val1, const T &val2);                                 // Template to calculate min-val
template<typename T> extern void swap_val(T &val1, T &val2);                                                // Template to swap values
template<typename T> extern const T random_val(const T &min_val, const T &max_val);                         // Template to get random values (funct random_init() should be called b4 this template)
template<typename T> extern Integer array_sz(const T &arr);                                                 // Template to calculate array size (not for pointers/references)


#include "lib_ui.tpp"                                                                                       // Import UI (terminal I/O) library templates file


#endif                                                                                                      // Avoid multiple inclusions (old-alternative end)
