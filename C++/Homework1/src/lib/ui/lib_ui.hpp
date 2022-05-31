/*
 * Author: Cristian Merli
 * Code title: UI (terminal I/O) library header file
 * Code version: 3.0
 * Creation date: 07/04/2022
 * Last mod. date: 06/05/2022 
 */


/* Include guards */
#pragma once                                                                                                // Avoid multiple inclusions
#ifndef _UI_HPP_                                                                                            // Avoid multiple inclusions (old-alternative start)
#define _UI_HPP_                                                                                            // Avoid multiple inclusions (old-alternative)


/* Libraries */
#include <iostream>                                                                                         // I/O library inclusion (for cin, cout ecc.)
#include <iomanip>                                                                                          // I/O mainp library inclusion (for setw ecc.)
#include <type_traits>                                                                                      // Type-traits library inclusion (for template ecc.)
#include <complex>                                                                                          // Complex-numbers library inclusion (for real, imag ecc.)
#include <limits>                                                                                           // Limits library inclusion (for numeric_limits ecc.)
#include <cctype>                                                                                           // C-ctype library inclusion (for tolower ecc.)
#include <sys/ioctl.h>                                                                                      // System I/O control library inclusion (for ioctl ecc.)
#include <unistd.h>                                                                                         // UniStd library inclusion (for stdout ecc.)


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
#define PRINT_VAL_1_1(STR, VAL) \
std::cout << GN << ">>> " << PU << STR << ": " << LBU << VAL << std::endl << ER                             // Terminal value printing macro (1 val, 1 str)
#define PRINT_VAL_1_2(STR1, VAL, STR2) \
std::cout << GN << ">>> " << PU << STR1 << ": " << LBU << VAL << SP << STR2 << std::endl << ER              // Terminal value printing macro (1 val, 2 str)
#define PRINT_VAL_COUNT_ARGS(arg1, arg2, arg3, arg4, ...) arg4                                              // Macro to count PRINT_VAL() arguments (number of args + 1)
#define PRINT_VAL_MACRO_CALL(...) PRINT_VAL_COUNT_ARGS(__VA_ARGS__, PRINT_VAL_1_2, PRINT_VAL_1_1, )         // Macro to choose PRINT_VAL() by param num
#define TERM_PRINT_VAL(...) PRINT_VAL_MACRO_CALL(__VA_ARGS__)(__VA_ARGS__)                                  // Macro to call TERM_PRINT_VAL()

#define TERM_ACQ_CYCLE(TXT, TYP, VAR, ERR_COND, ERR_TXT) \
do { \
  term_get_val(TXT, TYP, &VAR); \
  if (ERR_COND) term_print(ERR_TXT, ERR); else break; \
} while (true)                                                                                              // Terminal acquisition cycle macro

#define TERM_NL(N) \
for (Byte z=0; z<N; ++z) std::cout << std::endl                                                             // Terminal new lines printing macro

#define REAL_EQ_Z(VAL) \
fabs(VAL) < REAL_EPSILON                                                                                    // Chk if real val is equal to zero

#define REAL_DF_Z(VAL) \
fabs(VAL) > REAL_EPSILON                                                                                    // Chk if real val is different from zero

#define MIN(VAL1, VAL2) \
((VAL1 < VAL2) ? VAL1 : VAL2)                                                                               // Min element macro

#define MAX(VAL1, VAL2) \
((VAL1 > VAL2) ? VAL1 : VAL2)                                                                               // Max element macro

#define SWAP(EL1, EL2, TYP) \
TYP tmp=EL1; \
EL1=EL2; \
EL2=tmp                                                                                                     // Elements swappin' macro

#define S(VAL) \
std::to_string(VAL)                                                                                         // Value to string conv macro

#define ARRAY_SZ(ARR) \
sizeof(ARR)/sizeof(ARR[1])                                                                                  // Array size macro

#define ALLOC(TYP, PTR, SZ) \
TYP *PTR=new (std::nothrow) TYP[SZ]; if (PTR==NULL) close_err("Error in dynamic memory allocation!")        // Dyn-memo alloc macro

#define DEALLOC(PTR) \
(PTR!=NULL) ? (delete[] PTR) : (term_print("Error, can't deallocate NULL ptr from dynamic memory!", ERR))   // Dyn-memo dealloc macro


/* Data-type limits */
#undef REAL_EPSILON                                                                                         // Avoid macro-redef
#define REAL_EPSILON __DBL_EPSILON__                                                                        // Real epsilon
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
typedef __int8_t                  Character;                                                                // Character alias
typedef const __int8_t            C_character;                                                              // const Character alias
typedef std::string               String;                                                                   // String alis
typedef const std::string         C_string;                                                                 // const String alias


/* Enums */
enum Fbk {FBK,REQ,ERR};                                                                                     // Fbk-typ enum
enum Data {REAL,INTEGER,SHORT,BYTE,STRING,CHARACTER};                                                       // Data-typ enum


/* Public vars */
extern Integer unused;                                                                                      // Unused var


/* Library functions */
void term_title(CU_short &start_sp, C_string &txt, C_string &txt_col, C_byte &bkg_chr, C_string &bkg_col);  // Funct to print responsive-title
void term_print(C_string &fbk_str, const Fbk &typ=FBK);                                                     // Funct to print on terminal (default=FBK)
void term_get_val(C_string &req_str, const Data &typ, void *const val);                                     // Funct impl to get user input value from terminal
Boolean chk_num_str(C_string &str, C_string &err_str);                                                      // Funct to check numeric string (return err flg)
void close_err(C_string &err_str="");                                                                       // Funct to close software with error fbk
void close_bye(C_string &bye_str="");                                                                       // Funct to close software with bye fbk


#endif                                                                                                      // Avoid multiple inclusions (old-alternative end)
