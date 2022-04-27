/*
 * Author: Cristian Merli
 * Code title: Lecture library header file
 * Code version: 3.0
 * Creation date: 07/04/2022
 * Last mod. date: 27/04/2022 
 */


/* Include guards */
#pragma once                                                                                                // Avoid multiple inclusions
#ifndef _LECTURE_H_                                                                                         // Avoid multiple inclusions (old-alternative start)
#define _LECTURE_H_                                                                                         // Avoid multiple inclusions (old-alternative)


/* Dependencies */
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file


/* Libraries */
//


/* Constants */
#define MAX_SZ  10                                                                                          // Mat (arr) max size


/* Macros */
//


/* Public functions */
Real *def_vect(Integer &sz, C_string &vect_nm);                                                             // Funct to define vector
void print_vect(C_real *const v, C_integer &sz, C_string &vect_nm, C_integer &lt, C_integer &t);            // Funct to print vector
Real *vect_concat(C_real *const v1, C_integer &sz1, C_string &vect1_nm,
                  C_real *const v2, C_integer &sz2, C_string &vect2_nm,
                  Integer sz3, C_string &vect3_nm);                                                         // Funct to apply vector concatenation oper (delete old vectors)


#endif                                                                                                      // Avoid multiple inclusions (old-alternative end)
