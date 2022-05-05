/*
 * Author: Cristian Merli
 * Code title: Matrices library
 * Code version: 2.0
 * Creation date: 30/04/2022
 * Last mod. date: 05/05/2022
 */


/* Dependencies */
#include "lib_matrices.h"                                                                                   // Import matrices library header file


/* Public functions */
void matrix_print(C_matrix mat, C_integer &row, C_integer &col, C_integer &t){                              // Funct to print matrix on terminal
  std::cout << GN << ">>> " << PU << "mat["<< row << "][" << col << "]: " << std::endl << ER;               // Print matrix size
  for (Integer i=0; i<row; ++i){                                                                            // Matrix rows printin' cycle
    for (Integer j=0; j<col; ++j)                                                                           // Matrix columns printin' cycle
      std::cout << LBU << std::setw(t) << mat[i][j] << ER;                                                  // Matrix elements printin'
    TERM_NL(1);                                                                                             // New-line fbk
  }
}


Matrix matrix_alloc(C_integer &row, C_integer &col){                                                        // Funct to alloc matrix (alloc in dyn-memo)
  Matrix mat=new (std::nothrow) Vector[row];                                                                // Allocate matrix rows-vector in dyn-memo
  if (mat==NULL) close_err("Error in matrix rows-vector dynamic memory allocation!");                       // If it ain't been allocated close SW with ERR fbk
  for (Integer i=0; i<row; ++i){                                                                            // Foreach ptr element in matrix rows-vector
    mat[i]=new (std::nothrow) Real[col];                                                                    // Allocate matrix column-vectors in dyn-memo
    if (mat[i]==NULL) close_err("Error in matrix column-vectors dynamic memory allocation!");               // If it ain't been allocated close SW with ERR fbk
  }
  return mat;                                                                                               // Return allocated matrix
}


Matrix matrix_def(Integer &row, Integer &col, C_integer &t){                                                // Funct to define matrix (alloc in dyn-memo)
  TERM_ACQ_CYCLE("Insert matrix rows number", INTEGER, row, (row<1), \
                 "Error, matrix rows number must be greater than 1!");                                      // Matrix rows def
  TERM_ACQ_CYCLE("Insert matrix columns number", INTEGER, col, (col<1), \
                 "Error, matrix columns number must be greater than 1!");                                   // Matrix columns def
  Matrix mat=matrix_alloc(row, col);                                                                        // Alloc matrix in dyn-memo
  for (Integer i=0; i<row; ++i)                                                                             // Matrix rows scrollin' cycle
    for (Integer j=0; j<col; ++j)                                                                           // Matrix columns scrollin' cycle
      term_get_val("Insert mat["+S(i+1)+"]["+S(j+1)+"]", REAL, &mat[i][j]);                                 // Matrix elements def
  term_print("Acquisition cycle completed, recap...");                                                      // Print acquisition completed fbk
  matrix_print(mat, row, col, t);                                                                           // Print matrix
  return mat;                                                                                               // Return allocated matrix
}


void matrix_dealloc(C_matrix mat, C_integer &row){                                                          // Funct to deallocate matrix (dealloc from dyn-memo)
  for (Integer i=0; i<row; ++i)                                                                             // Foreach ptr element in matrix rows-vector
    (mat[i]!=NULL) ? (delete[] mat[i]) : \
    term_print("Error, can't deallocate NULL matrix column-vectors from dyn-memo!", ERR);                   // Deallocate matrix column-vectors from dyn-memo
  (mat!=NULL) ? (delete[] mat) : \
  term_print("Error, can't deallocate NULL matrix rows-vector from dyn-memo!", ERR);                        // Deallocate matrix rows-vector from dyn-memo
}


void matrix_transp(Matrix mat, Integer &row, Integer &col){                                                 // Funct to apply matrix transposition
  C_integer max_row=MIN(row,col), max_col=MAX(row,col);                                                     // Define max rows and columns idxs in scrollin' cycles
  for (Integer i=0; i<max_row; ++i)                                                                         // Max size idx scrollin'
    for (Integer j=i+1; j<max_col; ++j){                                                                    // Min size idx scrollin'
      SWAP(mat[i][j], mat[j][i], Real);                                                                     // Elements swappin'
    }
  SWAP(row, col, Integer);                                                                                  // Sizes swappin'
}


Matrix matrix_multiply(C_matrix mat1, C_integer &row1, C_integer &col1, C_matrix mat2, \
                       C_integer &row2, C_integer &col2, Integer &row3, Integer &col3){                     // Funct to apply matrix multiplication (alloc in dyn-memo)
  if (col1==row2){                                                                                          // Check if the matrices are compatible: matrix-1-col=matrix-2-row
    row3=row1; col3=col2;                                                                                   // Def matrix-3 sizes
    Matrix mat3=matrix_alloc(row3, col3);                                                                   // Alloc matrix-3 in dyn-memo
    Real tmp_elem;                                                                                          // Declare matrix-3 element var
    for (Integer i=0; i<row1; ++i)                                                                          // Scroll matrix-1 rows
      for (Integer j=0; j<col2; ++j){                                                                       // Scroll matrix-2 col
        tmp_elem=0;                                                                                         // Rst matrix-3 element var
        for (Integer k=0; k<col1; ++k)                                                                      // Accumulation cycle
          tmp_elem+=mat1[i][k]*mat2[k][j];                                                                  // Update matrix-3 element var usin' accumulation
        mat3[i][j]=tmp_elem;                                                                                // Def (i-th,j-th) element in matrix-3
      }
    return mat3;                                                                                            // Return allocated matrix
  } else {                                                                                                  // Else in case of incompatible matrix
    close_err("Error in matrix multiplication, incompatible matrices! -- ["+ \
              S(row1)+"]["+S(col1)+"]x["+S(row2)+"]["+S(col2)+"]");                                         // Close SW with ERR fbk
    return NULL;                                                                                            // Return NULL ptr (not called, SW closed at previous line)
  }
}


void vector_print(C_vector vect, C_integer &sz, C_integer &t){                                              // Funct to print vector on terminal
  std::cout << GN << ">>> " << PU << "vect["<< sz << "]:" << std::endl << ER;                               // Print vector size
  for (Integer i=0; i<sz; ++i)                                                                              // Vector elements printin' cycle
    std::cout << LBU << std::setw(t) << *(vect+i) << ER;                                                    // Vector elements printin'
  TERM_NL(1);                                                                                               // New-line fbk
}


Vector vector_alloc(C_integer &sz){                                                                         // Funct to alloc vector (alloc in dyn-memo)
  Vector vect=new (std::nothrow) Real[sz];                                                                  // Allocate vector in dyn-memo
  if (vect==NULL) close_err("Error in vector dynamic memory allocation!");                                  // If it ain't been allocated close SW with ERR fbk
  return vect;                                                                                              // Return allocated vector
}


Vector vector_def(Integer &sz, C_integer &t){                                                               // Funct to define vector (alloc in dyn-memo)
  TERM_ACQ_CYCLE("Insert vector size", INTEGER, sz, (sz<1), \
                 "Error, vector size must be greater than zero!");                                          // Vector size def
  Vector vect=vector_alloc(sz);                                                                             // Vector dyn-alloc
  for (Integer i=0; i<sz; ++i)                                                                              // Vector elements scrollin' cycle
    term_get_val("Insert vect["+S(i+1)+"]", REAL, &vect[i]);                                                // Vector elements def
  term_print("Acquisition completed, recap...");                                                            // Print acq completed fbk
  vector_print(vect, sz, t);                                                                                // Print vector
  return vect;                                                                                              // Return allocated vector
}


void vector_dealloc(C_vector vect){                                                                         // Funct to deallocate vector (dealloc from dyn-memo)
 (vect!=NULL) ? (delete[] vect) : (term_print("Error, can't deallocate NULL vector from dyn-memo!", ERR));  // Deallocate vector from dyn-memo
}


Vector vector_concat(C_vector vect1, C_integer &sz1, C_vector vect2, C_integer &sz2, Integer &sz3){         // Funct to apply vector concatenation (alloc in dyn-memo dealloc old vectors)
  sz3=sz1+sz2;                                                                                              // Concatenated vector size def
  Vector vect3=vector_alloc(sz3);                                                                           // Concatenated vect dyn-alloc
  for (Integer i=0; i<sz3; ++i) vect3[i]=(i<sz1) ? vect1[i] : vect2[i-sz1];                                 // Populate concatenated vector
  vector_dealloc(vect1); vector_dealloc(vect2);                                                             // Deallocate old vectors
  return vect3;                                                                                             // Return concat vect ptr
}
