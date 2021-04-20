/*
 * Author: Cristian Merli
 * Code title: Exercise 2 (Pointers 2) library header file
 * Code version: 3.0
 * Creation date: 20/04/2021
 * Last mod. date: 20/04/2021 
 */


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


/* Enums declaration and definition */
enum coords                                                                                                 // Matrix/vectors enum
{
    V = 0,                                                                                                  // Vectors
};


/* Data-types declaration and definition */
typedef unsigned char   byte;                                                                               // Unsigned char alias (byte)
typedef unsigned short  u_shrt;                                                                             // Unsigned short alias (u_shrt)
typedef short           shrt;                                                                               // Short alias (shrt)
typedef double          real;                                                                               // Double alias (real)


/* Libraries function declaration */
void logo(const byte start_sp, const char *txt, const char *txt_col,
          const char bkg_chr, const char *bkg_col);                                                         // Print responsive-logo function

u_shrt iaddr(const u_shrt i, const u_shrt j, const u_shrt lda);                                             // Arrays/vectors memo addressing

int findchr_addr(char *str, const char chr, char **ptr);                                                    // Find char address function
