/*
 * Author: Cristian Merli
 * Code title: UI (terminal I/O) library header file
 * Code version: 3.0
 * Creation date: 06/05/2021
 * Last mod. date: 06/05/2021 
 */


/* Libraries */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <stdlib.h>                                                                                         // Standard library inclusion (for exit, atoi, dynamic memory ecc.)
#include <string.h>                                                                                         // String library inclusion (for strlen ecc.)
#include <sys/ioctl.h>                                                                                      // System I/O control library inclusion (for ioctl ecc.)
#include <unistd.h>                                                                                         // UniStd library inclusion (for stdout ecc.)


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


/* Data-types */
typedef unsigned char   byte;                                                                               // Unsigned char alias (byte)
typedef unsigned short  u_shrt;                                                                             // Unsigned short alias (u_shrt)
typedef unsigned int    u_int;                                                                              // Unsigned int alias (u_int)
typedef unsigned long   u_long;                                                                             // Unsigned long alias (u_long)


/* Library functions */
void logo(const u_long start_sp, const char *txt, const char *txt_col,
          const char bkg_chr, const char *bkg_col);                                                         // Print responsive-logo function

void press_enter(const char *req_str);                                                                      // Press enter function

void fbk_nl(const int num);                                                                                 // New line feedback function

void fbk_gn_cy(const char *fbk_str);                                                                        // Green-cyan feedback function

void fbk_gn_pu(const char *fbk_str);                                                                        // Green-purple feedback function

void fbk_gn_lbu_ye_int(const char *prfx_str_lbu, int val_ye);                                               // Green-lightblue-yellow int val feedback function

void fbk_err(const char *fbk_str);                                                                          // Error feedback function

char *read_term_in();                                                                                       // Read terminal input function

char *read_term_in_min_chrs(const byte min_chrs, const char *req_str, const char *err_str);                 // Read terminal input (min chars) function

char *read_term_in_min_chrs_exit_chr(const byte min_chrs, const char *req_str,
                                     const char *err_str, const char exit_chr);                             // Read terminal input (min chars and exit char) function

int read_term_in_int();                                                                                     // Read terminal input INT function

int read_term_in_int_inrange(const int min_val, const int max_val,
                             const char *req_str, const char *err_str);                                     // Read terminal input INT (in-range) function

void clr_term_in();                                                                                         // Clear terminal input buffer function

void close_err();                                                                                           // Close software with error function

void close_fbk();                                                                                           // Close feedback function
