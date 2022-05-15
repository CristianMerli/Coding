/*
 * Author: Cristian Merli
 * Code title: ConvNet library
 * Code version: 3.0
 * Creation date: 30/04/2022
 * Last mod. date: 05/05/2022
 */


/* Dependencies */
#include "lib_cnn.h"                                                                                        // Import ConvNet library header file


/* Private functions */
static void chk_def_pool_sizes(C_integer &row_i, C_integer &col_i, \
                               C_integer &pool_sz, Integer &row_o, Integer &col_o){                         // Funct to check pool-matrix sizes compatibility and define new output matrix sizes
  if (row_i%pool_sz==0 && col_i%pool_sz==0){                                                                // Check pool-matrix sizes compatibility
    row_o=row_i/pool_sz; col_o=col_i/pool_sz;                                                               // If OK: define new output matrix sizes (after poolin' operation)
  } else close_err("Error, matrix-pool size incompatibility detected! -- mat["+ \
                   S(row_i)+"]["+S(col_i)+"] and pool["+S(pool_sz)+"]["+S(pool_sz)+"]");                    // If NOT-OK: close SW with ERR fbk
}


static Real pool_max_val(C_matrix mat, C_integer &tl_row, C_integer &tl_col, C_integer &pool_sz){           // Funct to find max value inside pool (squared-matrix)
  Real max_val=mat[tl_row][tl_col];                                                                         // Max value tmp-var declaration and init
  C_integer br_row=tl_row+pool_sz, br_col=tl_col+pool_sz;                                                   // Calculate pool BottomRight-row and BottomRight-column idxs
  for (Integer i=tl_row; i<br_row; ++i)                                                                     // Pool rows scrollin' cycle
    for (Integer j=tl_col; j<br_col; ++j)                                                                   // Pool columns scrollin' cycle
      if (mat[i][j]>max_val) max_val=mat[i][j];                                                             // Max value upd
  return max_val;                                                                                           // Return max value in pool
}


static Real pool_avg_val(C_matrix mat, C_integer &tl_row, C_integer &tl_col, C_integer &pool_sz){           // Funct to calculate average value inside pool (squared-matrix)
  Real avg_val=0;                                                                                           // Average value tmp-var declaration and init
  C_integer br_row=tl_row+pool_sz, br_col=tl_col+pool_sz;                                                   // Calculate pool BottomRight-row and BottomRight-column idxs
  for (Integer i=tl_row; i<br_row; ++i)                                                                     // Pool rows scrollin' cycle
    for (Integer j=tl_col; j<br_col; ++j)                                                                   // Pool columns scrollin' cycle
      avg_val+=mat[i][j];                                                                                   // Accumulate values in pool
  return (avg_val/pow(pool_sz, 2));                                                                         // Return calculated average value in pool
}


static Real submat_convol(C_matrix mat, C_integer &row, C_integer &col, \
                          C_integer &tl_row, C_integer &tl_col, C_matrix ker, C_integer &ker_sz){           // Funct to apply submatrix convolution (with squared-matrix kernel)
  Real convol=0;                                                                                            // Convolution value tmp-var declaration and init
  C_integer br_row=tl_row+ker_sz, br_col=tl_col+ker_sz;                                                     // Calculate kernel BottomRight-row and BottomRight-column idxs
  for (Integer i=tl_row; i<br_row; ++i)                                                                     // Kernel and submatrix rows scrollin' cycle
    for (Integer j=tl_col; j<br_col; ++j)                                                                   // Kernel and submatrix columns scrollin' cycle
      convol+=((i<row && j<col) ? mat[i][j]*ker[i-tl_row][j-tl_col] : 0);                                   // Apply matrix-kernel convolution
  return convol;                                                                                            // Return convolution resulting value
}


/* Public functions */
Matrix cnn_maxpool(C_matrix mat, C_integer &row_i, C_integer &col_i, \
                   C_integer &pool_sz, Integer &row_o, Integer &col_o){                                     // Funct to apply ConvNet max-pool (alloc new matrix in dyn-memo)
  chk_def_pool_sizes(row_i, col_i, pool_sz, row_o, col_o);                                                  // Check pool size compatibility and define output matrix sizes
  Matrix mat_maxpool=matrix_alloc(row_o, col_o);                                                            // Allocate new matrix (max-pool output matrix)
  Integer tl_row __attribute__((unused)), tl_col __attribute__((unused));                                   // Pool TopLeft-row and TopLeft-column idxs declaration (avoid compilin' warning, passed by-ref to a static funct)
  for (Integer i=0, tl_row=0; i<row_o; ++i, tl_row+=pool_sz)                                                // Output matrix rows scrollin' cycle
    for (Integer j=0, tl_col=0; j<col_o; ++j, tl_col+=pool_sz)                                              // Output matrix columns scrollin' cycle
      mat_maxpool[i][j]=pool_max_val(mat, tl_row, tl_col, pool_sz);                                         // Find pool max value and save it inside output matrix
  return mat_maxpool;                                                                                       // Return allocated max-pool output matrix
}


Matrix cnn_avgpool(C_matrix mat, C_integer &row_i, C_integer &col_i, \
                   C_integer &pool_sz, Integer &row_o, Integer &col_o){                                     // Funct to apply ConvNet average-pool (alloc new matrix in dyn-memo)
  chk_def_pool_sizes(row_i, col_i, pool_sz, row_o, col_o);                                                  // Check pool size compatibility and define output matrix sizes
  Matrix mat_avgpool=matrix_alloc(row_o, col_o);                                                            // Allocate new matrix (avg-pool output matrix)
  Integer tl_row __attribute__((unused)), tl_col __attribute__((unused));                                   // Pool TopLeft-row and TopLeft-column idxs declaration (avoid compilin' warning, passed by-ref to a static funct)
  for (Integer i=0, tl_row=0; i<row_o; ++i, tl_row+=pool_sz)                                                // Output matrix rows scrollin' cycle
    for (Integer j=0, tl_col=0; j<col_o; ++j, tl_col+=pool_sz)                                              // Output matrix columns scrollin' cycle
      mat_avgpool[i][j]=pool_avg_val(mat, tl_row, tl_col, pool_sz);                                         // Calc pool average value and save it inside output matrix
  return mat_avgpool;                                                                                       // Return allocated avg-pool output matrix
}


void cnn_relu(Matrix mat, C_integer &row, C_integer &col, C_integer &th_val){                               // Funct to apply ConvNet ReLU to the input matrix
  for (Integer i=0; i<row; ++i)                                                                             // Rows scrollin' cycle
    for (Integer j=0; j<col; ++j)                                                                           // Columns scrollin' cycle
      mat[i][j]=(mat[i][j]>(Real)th_val ? th_val : (mat[i][j]<0.0 ? 0 : mat[i][j]));                        // Apply ReLU operation element-by-element
}


Matrix cnn_convolution(C_matrix mat, C_integer &row, C_integer &col, C_matrix ker, C_integer &ker_sz){      // Funct to apply ConvNet convolution (alloc new matrix in dyn-memo)
  if (row<ker_sz || col<ker_sz) close_err("Error, matrix must be bigger than kernel! -- mat["+ \
                                          S(row)+"]["+S(col)+"] and ker["+S(ker_sz)+"]["+S(ker_sz)+"]");    // Check kernel-matrix sizes compatibility and if NOT-OK: close SW with ERR fbk
  Matrix feature_map=matrix_alloc(row, col);                                                                // Allocate new matrix (feature map)
  for (Integer i=0; i<row; ++i)                                                                             // Feature map rows scrollin' cycle
    for (Integer j=0; j<col; ++j)                                                                           // Feature map columns scrollin' cycle
      feature_map[i][j]=submat_convol(mat, row, col, i, j, ker, ker_sz);                                    // Apply submatrix convolution and populate feature map
  return feature_map;                                                                                       // Return feature map output matrix
}
