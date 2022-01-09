/*
 * Author: Cristian Merli
 * Code title: Exercise 3 (es_sol_strutture) library header file
 * Code version: 3.0
 * Creation date: 21/04/2021
 * Last mod. date: 21/04/2021 
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
typedef double          real;                                                                               // Double alias (real)


/* Enums declaration and definition */
enum traction{ ELECTIC, DIESEL };                                                                           // Train traction enum declaration and definition
const char *traction_str[] = { "ELECTIC", "DIESEL" };                                                       // Train traction strings vector associated to the train traction enum declaration and definition


/* Structs declaration */
struct train                                                                                                // Train struct declaration
{
  int wag_num;                                                                                              // Train wagons number val
  enum traction tr_tract;                                                                                   // Train traction type enum
};


/* Libraries function declaration */
void logo(const byte start_sp, const char *txt, const char *txt_col,
          const char bkg_chr, const char *bkg_col);                                                         // Print responsive-logo function

void wag_add(struct train *tr);                                                                             // Wagon add funtion (in train struct)

void wag_rmv(struct train *tr);                                                                             // Wagon remove funtion (in train struct)

void train_trac_typ(struct train *tr, const enum traction trc_typ);                                         // Train traction type definition funtion (in train struct)

void trains_join(struct train *tr1, struct train *tr2);                                                     // Trains join function (add the second train's wagons to the first train struct and reset second train wagons number)
