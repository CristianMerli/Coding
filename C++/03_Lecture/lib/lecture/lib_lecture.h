/*
 * Author: Cristian Merli
 * Code title: Lecture library header file
 * Code version: 3.0
 * Creation date: 31/03/2022
 * Last mod. date: 07/04/2022 
 */


/* Include guards */
#pragma once                                                                                                // Avoid multiple inclusions
#ifndef _LECTURE_H_                                                                                         // Avoid multiple inclusions (old-alternative start)
#define _LECTURE_H_                                                                                         // Avoid multiple inclusions (old-alternative)


/* Dependencies */
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file


/* Libraries */
#include <iomanip>                                                                                          // I/O mainp library inclusion (for setw ecc.)


/* Constants */
#define MAX_SZ  10                                                                                          // Vect or mat (arr) max size


/* Macros */
#define SWAP(EL1, EL2, TYP) \
TYP tmp=EL1; \
EL1=EL2; \
EL2=tmp                                                                                                     // Elements swappin' macro

#define MIN(VAL1, VAL2) \
((VAL1 < VAL2) ? VAL1 : VAL2)                                                                               // Min element macro

#define MAX(VAL1, VAL2) \
((VAL1 > VAL2) ? VAL1 : VAL2)                                                                               // Max element macro


/* Public functions */
void def_vect(Real v[], Integer &sz, C_string &vect_nm);                                                    // Funct to define vector
void print_vect(C_real v[], C_integer &sz, C_string &vect_nm);                                              // Funct to print vector
Integer vect_scalar(C_real v1[], C_integer &sz1, C_real v2[], C_integer &sz2, Real &res);                   // Funct to apply vector scalar operation
Integer add_vect_elem(C_real &elem, C_integer &idx, Real v[], Integer &sz, C_string &vect_nm);              // Funct to add element in vector at spec pos
void def_mat(Real m[MAX_SZ][MAX_SZ], Integer sz[], C_string &mat_nm);                                       // Funct to define matrix (array)
void print_mat(C_real m[MAX_SZ][MAX_SZ], C_integer sz[], C_string &mat_nm, C_integer &lt, C_integer t);     // Funct to print matrix (array)
Integer mat_trasp(Real m[MAX_SZ][MAX_SZ], Integer sz[], C_string &mat_nm);                                  // Funct to apply matrix (array) transposition operation


#endif                                                                                                      // Avoid multiple inclusions (old-alternative end)
