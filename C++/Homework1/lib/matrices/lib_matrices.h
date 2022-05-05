/*
 * Author: Cristian Merli
 * Code title: Matrices library header file
 * Code version: 2.0
 * Creation date: 30/04/2022
 * Last mod. date: 04/05/2022 
 */


/* Include guards */
#pragma once                                                                                                // Avoid multiple inclusions
#ifndef _MATRICES_H_                                                                                        // Avoid multiple inclusions (old-alternative start)
#define _MATRICES_H_                                                                                        // Avoid multiple inclusions (old-alternative)


/* Dependencies */
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file


/* Data-types */
typedef Real**              Matrix;                                                                         // Matrix alias
typedef C_real*const*const  C_matrix;                                                                       // const Matrix alias
typedef Real*               Vector;                                                                         // Vector alias
typedef C_real*const        C_vector;                                                                       // const Vector alias


/* Public functions */
void matrix_print(C_matrix mat, C_integer &row, C_integer &col, C_integer &t);                              // Funct to print matrix on terminal
Matrix matrix_alloc(C_integer &row, C_integer &col);                                                        // Funct to alloc matrix (alloc in dyn-memo)
Matrix matrix_def(Integer &row, Integer &col, C_integer &t);                                                // Funct to define matrix (alloc in dyn-memo)
void matrix_dealloc(C_matrix mat, C_integer &row);                                                          // Funct to dealloc matrix (dealloc from dyn-memo)
void matrix_transp(Matrix mat, Integer &row, Integer &col);                                                 // Funct to apply matrix transposition
Matrix matrix_multiply(C_matrix mat1, C_integer &row1, C_integer &col1, C_matrix mat2, \
                       C_integer &row2, C_integer &col2, Integer &row3, Integer &col3);                     // Funct to apply matrix multiplication (alloc in dyn-memo)
void vector_print(C_vector vect, C_integer &sz, C_integer &t);                                              // Funct to print vector on terminal
Vector vector_alloc(C_integer &sz);                                                                         // Funct to alloc vector (alloc in dyn-memo)
Vector vector_def(Integer &sz, C_integer &t);                                                               // Funct to define vector (alloc in dyn-memo)
void vector_dealloc(C_vector vect);                                                                         // Funct to dealloc vector (dealloc from dyn-memo)
Vector vector_concat(C_vector vect1, C_integer &sz1, C_vector vect2, C_integer &sz2, Integer &sz3);         // Funct to apply vector concatenation (alloc in dyn-memo and dealloc old vectors)


#endif                                                                                                      // Avoid multiple inclusions (old-alternative end)
