/*
 * Author: Cristian Merli
 * Code title: Exercise 5 (es_generico) library header file
 * Code version: 1.0
 * Creation date: 22/04/2021
 * Last mod. date: 22/04/2021 
 */


/* Libraries import */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <string.h>                                                                                         // String library inclusion (for strlen ecc.)
#include <sys/ioctl.h>                                                                                      // System I/O control library inclusion (for ioctl ecc.)
#include <unistd.h>                                                                                         // UniStd library inclusion (for stdout ecc.)


/* Constants declaration and definition */
const char *rd = "\033[0;31m";                                                                              // Red color
const char *bl = "\033[0;34m";                                                                              // Blue color
const char *lb = "\033[1;34m";                                                                              // Light blue color
const char *pu = "\033[0;35m";                                                                              // Purple color
const char *cy = "\033[0;36m";                                                                              // Cyan color
const char *ye = "\033[1;33m";                                                                              // Yellow color
const char *og = "\033[0;33m";                                                                              // Orange color
const char *gn = "\033[0;32m";                                                                              // Green color
const char *lgn = "\033[1;32m";                                                                             // Light green color
const char *lgy = "\033[0;37m";                                                                             // Light gray color
const char *er = "\033[0m";                                                                                 // End color


/* Data-types declaration and definition */
typedef unsigned char   byte;                                                                               // Unsigned char alias (byte)
typedef unsigned short  u_shrt;                                                                             // Unsigned short alias (u_shrt)
typedef short           shrt;                                                                               // Short alias (shrt)
typedef double          real;                                                                               // real alias (real)


/* Enums declaration and definition */
enum coords                                                                                                 // Matrix/vectors enum
{
  V = 0,                                                                                                    // Vectors
};


/* Structs declaration */
typedef struct street                                                                                       // Street (name and connection) typedef
{
  char name[25];                                                                                            // Street name
  union connection *con;                                                                                    // Connection to street (street or cross)
} street;


/* Unions declaration and definition */
typedef union connection                                                                                    // Street connection type (other street or cross) typedef
{
  street strt;                                                                                              // Street connection to other street
  street *cross;                                                                                            // Street connection to cross
} connection;


/* Libraries function declaration */
void logo(const byte start_sp, const char *txt, const char *txt_col,
          const char bkg_chr, const char *bkg_col);                                                         // Print responsive-logo function

shrt iaddr(const u_shrt i, const u_shrt j, const u_shrt lda);                                               // Arrays/vectors memo addressing

void assign_strt_to_crss(street strt, street *cross, const byte pos);                                       // Assign street to cross function

void print_crs_strt_nanes(const street *strt, const byte strts_in_cross);                                   // Print street names in cross function

void assign_conn_to_strt(street *strt, connection *con);                                                    // Assign connection to street function

void navigate(street *start_strt);                                                                          // Navigate through streets and crosses function
