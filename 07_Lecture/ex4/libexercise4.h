/*
 * Author: Cristian Merli
 * Code title: Exercise 4 (es_strutture_2) library header file
 * Code version: 3.0
 * Creation date: 21/04/2021
 * Last mod. date: 29/04/2021 
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

enum order{ CREASING, DECREASING };                                                                         // Creasing/decreasing order enum


/* Structs declaration */
struct dim                                                                                                  // Dimensions struct declaration
{
  real x;                                                                                                   // X dimenion (length mm)
  real y;                                                                                                   // Y dimenion (width mm)
  real z;                                                                                                   // Z dimenion (height mm)
};

struct vehicle                                                                                              // Vehicle struct declaration
{
  real weight;                                                                                              // Vehicle weight
  struct dim dimens;                                                                                        // Vehicle dimensions
};

struct garage                                                                                               // Garage struct declaration
{
  real found_strngth;                                                                                       // Garage concrete foundation compressive strength
  struct dim dimens;                                                                                        // Garage dimensions
  struct vehicle parked_vehicle;                                                                            // Parked vehicle in Garage
};

struct overdim_space_weight                                                                                 // Overdimensioning parameters of the garage: space (x, y, z) to allow vehicle-parking operations and weight factor of safety (security coefficient)
{
  struct dim dimens;                                                                                        // Garage overdimensioning space (x, y, z) to allow vehicle-parking operations
  real weight_fos;                                                                                          // Weight factor of safety (security coefficient)
};


/* Libraries function declaration */
void logo(const byte start_sp, const char *txt, const char *txt_col,
          const char bkg_chr, const char *bkg_col);                                                         // Print responsive-logo function

int vehic_garage_chk(const struct vehicle vehic, const struct garage gar,
                    const struct overdim_space_weight ovrdim_sp_wght);                                      // Vehicle-garage check function (compare vehicle dimensions and weight with garage dimensions and concrecte foundations max strength, considering space overdimensioning to allow vehicle-parking operations and weight factor of safety - sicurity coefficient)

struct vehicle heaviest_vehic(struct vehicle *vehics, const shrt vehics_num);                               // Find heaviest vehicle in vehicles vector

struct vehicle biggest_vehic(struct vehicle *vehics, const shrt vehics_num);                                // Find biggest vehicle in vehicles vector (volume)

void vehic_garage_assign(const struct vehicle vehic, struct garage *gar,
                        struct overdim_space_weight ovrdim_sp_wght);                                        // vehicle-garage assign function
