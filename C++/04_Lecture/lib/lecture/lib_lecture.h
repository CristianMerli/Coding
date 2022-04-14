/*
 * Author: Cristian Merli
 * Code title: Lecture library header file
 * Code version: 3.0
 * Creation date: 07/04/2022
 * Last mod. date: 14/04/2022 
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
void def_mat(Real m[MAX_SZ][MAX_SZ], Integer sz[], C_string &mat_nm);                                       // Funct to define matrix (array)
void print_mat(C_real m[MAX_SZ][MAX_SZ], C_integer sz[], C_string &mat_nm, C_integer &lt, C_integer t);     // Funct to print matrix (array)
Integer mat_trasp(Real m[MAX_SZ][MAX_SZ], Integer sz[], C_string &mat_nm);                                  // Funct to apply matrix (array) transposition operation
Integer mat_multipl(C_real m1[MAX_SZ][MAX_SZ], C_integer sz1[], C_string &mat1_nm,
                    C_real m2[MAX_SZ][MAX_SZ], C_integer sz2[], C_string &mat2_nm,
                    Real m3[MAX_SZ][MAX_SZ], Integer sz3[], C_string &mat3_nm);                             // Funct to apply matrix (array) multiplication oper


#endif                                                                                                      // Avoid multiple inclusions (old-alternative end)
