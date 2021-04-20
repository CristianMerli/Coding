/*
 * Author: Cristian Merli
 * Code title: Exercise 7 (Vectors 1) library header file
 * Code version: 3.0
 * Creation date: 20/04/2021
 * Last mod. date: 20/04/2021
 */


/* Data-types declaration and definition */
typedef unsigned char   byte;                                                                               // Unsigned char alias (byte)
typedef unsigned short  u_shrt;                                                                             // Unsigned short alias (u_shrt)
typedef short           shrt;                                                                               // Short alias (shrt)
typedef double          real;                                                                               // Double alias (real)


/* Libraries import */
real vect_comp_sum(real *vect_sum, int size);                                                               // Vector components sum function (in library)
void count_vowels(char *str, u_shrt size);                                                                  // Count vowels in string function (in library)
