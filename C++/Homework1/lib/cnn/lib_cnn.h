/*
 * Author: Cristian Merli
 * Code title: ConvNet library header file
 * Code version: 3.0
 * Creation date: 30/04/2022
 * Last mod. date: 05/05/2022 
 */


/* Include guards */
#pragma once                                                                                                // Avoid multiple inclusions
#ifndef _CONVNET_H_                                                                                         // Avoid multiple inclusions (old-alternative start)
#define _CONVNET_H_                                                                                         // Avoid multiple inclusions (old-alternative)


/* Dependencies */
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file
#include "../matrices/lib_matrices.h"                                                                       // Import matrices library header file


/* Public functions */
Matrix cnn_maxpool(C_matrix mat, C_integer &row_i, C_integer &col_i, \
                   C_integer &pool_sz, Integer &row_o, Integer &col_o);                                     // Funct to apply ConvNet max-pool (alloc new matrix in dyn-memo)
Matrix cnn_avgpool(C_matrix mat, C_integer &row_i, C_integer &col_i, \
                   C_integer &pool_sz, Integer &row_o, Integer &col_o);                                     // Funct to apply ConvNet average-pool (alloc new matrix in dyn-memo)
void cnn_relu(Matrix mat, C_integer &row, C_integer &col, C_integer &th_val);                               // Funct to apply ConvNet ReLU to the input matrix
Matrix cnn_convolution(C_matrix mat, C_integer &row, C_integer &col, C_matrix ker, C_integer &ker_sz);      // Funct to apply ConvNet convolution (alloc new matrix in dyn-memo)


#endif                                                                                                      // Avoid multiple inclusions (old-alternative end)
