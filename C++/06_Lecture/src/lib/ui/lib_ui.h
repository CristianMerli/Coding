/*
 * Author: Cristian Merli
 * Code title: UI (terminal I/O) library header file
 * Code version: 3.0
 * Creation date: 07/04/2022
 * Last mod. date: 21/05/2022 
 */


/* Include guards */
#pragma once                                                                                                // Avoid multiple inclusions
#ifndef _UI_H_                                                                                              // Avoid multiple inclusions (old-alternative start)
#define _UI_H_                                                                                              // Avoid multiple inclusions (old-alternative)


/* Libraries */
#include <iostream>                                                                                         // I/O library inclusion (for cin, cout ecc.)
#include <limits>                                                                                           // Limits library inclusion (for numeric_limits ecc.)
#include <unistd.h>                                                                                         // UniStd library inclusion (for stdout ecc.)
#include <sys/ioctl.h>                                                                                      // System I/O control library inclusion (for ioctl ecc.)
//#include <iomanip>                                                                                        // I/O mainp library inclusion (for setw ecc.)
//#include <cctype>                                                                                         // C-ctype library inclusion (for tolower ecc.)


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
#define REAL_EQ_Z(VAL)      fabs(VAL)<REAL_EPSILON                                                          // Chk if real val is equal to zero
#define REAL_DF_Z(VAL)      fabs(VAL)>REAL_EPSILON                                                          // Chk if real val is different from zero
#define MIN(VAL1, VAL2)     (VAL1<VAL2 ? VAL1 : VAL2)                                                       // Min element macro
#define MAX(VAL1, VAL2)     (VAL1>VAL2 ? VAL1 : VAL2)                                                       // Max element macro
#define S(VAL)              std::to_string(VAL)                                                             // Value to string conv macro
#define SWAP(EL1, EL2, TYP) TYP tmp=EL1; EL1=EL2; EL2=tmp                                                   // Elements swappin' macro
#define ARRAY_SZ(ARR)       sizeof(ARR)/sizeof(ARR[1])                                                      // Array size macro [MAIN-ONLY]
// Dyn-memo macros
#define MAE                 "Error in dynamic memory allocation!"                                           // Memory allocation error txt const
#define MDE                 "Error, can't deallocate NULL ptr from dynamic memory!"                         // Memory deallocation error txt const
#define ALLOC(TYP, PTR, SZ) TYP *PTR=new (std::nothrow) TYP[SZ]; if (PTR==NULL) term->close_err(MAE)        // Dyn-memo alloc macro
#define DEALLOC(PTR)        (PTR!=NULL) ? (delete[] PTR) : (term->print(MDE, ERR))                          // Dyn-memo dealloc macro
// Acquisition macro
#define TERM_ACQ_CYCLE(TYP_VAR, ACQ_METH, ERR_COND, ERR_TXT) \
do {TYP_VAR=term->ACQ_METH; if (ERR_COND) term->print(ERR_TXT, ERR); else break;} while (true)              // Terminal acquisition cycle macro


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
enum Print_typ {FBK, REQ, ERR};                                                                             // Terminal print typ enum
typedef const Print_typ C_print_typ;                                                                        // const Terminal-print-typ enum alias


/* Public classes */
class Term {                                                                                                // Terminal UI class
  public:                                                                                                   // Terminal class public section
    Term(C_string &title_txt, C_string &title_col, C_character &bkg_chr, C_string &bkg_col);                // Terminal class constructor method [TITLE-TXT, TITLE-COL, BKG-CHAR, BKG-COL]
    ~Term();                                                                                                // Terminal class destructor method
    void print(C_string &fbk_str, C_print_typ &typ=FBK) const;                                              // Terminal class method to perform terminal print (default print-typ=FBK)
    void print(C_string &fbk_str, C_real &val, C_string &fbk_str2="") const;                                // Terminal class method to print real user output val to terminal
    void print(C_string &fbk_str, C_integer &val, C_string &fbk_str2="") const;                             // Terminal class method to print integer user output val to terminal
    void print(C_string &fbk_str, C_short &val, C_string &fbk_str2="") const;                               // Terminal class method to print short user output val to terminal
    void print(C_string &fbk_str, C_character &val, C_string &fbk_str2="") const;                           // Terminal class method to print character user output to terminal
    void print(C_string &fbk_str, C_string &val, C_string &fbk_str2="") const;                              // Terminal class method to print string user output to terminal
    void print_nl(C_integer &n) const;                                                                      // Terminal class method to perform new-lines terminal print
    Real get_real(C_string &req_str) const;                                                                 // Terminal class method to get user input real val from terminal
    Integer get_integer(C_string &req_str) const;                                                           // Terminal class method to get user input integer val from terminal
    Short get_short(C_string &req_str) const;                                                               // Terminal class method to get user input short val from terminal
    String get_string(C_string &req_str) const;                                                             // Terminal class method to get user input string from terminal
    Character get_character(C_string &req_str) const;                                                       // Terminal class method to get user input character from terminal
    Boolean chk_numeric_str(C_string &str, C_string &err_str) const;                                        // Terminal class method to check numerical string (returns err flg)
    void close_err(C_string &err_str="") const;                                                             // Terminal class method to close software with error fbk
    void close_bye(C_string &bye_str="") const;                                                             // Terminal class method to close software with bye fbk
  private:                                                                                                  // Terminal class private section
    C_string fbk_col1=GN, fbk_col2=PU, fbk_col3=LBU;                                                        // Terminal fbk print-colors
    C_string req_col1=OG, req_col2=CY, req_col3=BU;                                                         // Terminal request print-colors
    C_string err_col1=YE, err_col2=RD;                                                                      // Terminal error print-colors
    String title_txt, title_col, bkg_col;                                                                   // Terminal title logo text, text-color and background-char-color
    Character bkg_chr;                                                                                      // Terminal title logo background char
    void print_responsive_title() const;                                                                    // Terminal class method to print responsive-title
};


/* Public object-ptrs */
typedef const Term *      Terminal;                                                                         // Terminal alias
typedef const Term *const C_terminal;                                                                       // const Terminal alias


#endif                                                                                                      // Avoid multiple inclusions (old-alternative end)
