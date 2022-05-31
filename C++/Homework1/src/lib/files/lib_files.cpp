/*
 * Author: Cristian Merli
 * Code title: Files I/O library
 * Code version: 3.0
 * Creation date: 30/04/2022
 * Last mod. date: 06/05/2022
 */


/* Dependencies */
#include "lib_files.hpp"                                                                                    // Import files I/O library header file


/* Private functions */
static void def_matrix_sizes(File &matfile, Integer &row, Integer &col, C_boolean &sq_flg){                 // Funct to define matrix sizes from input file (sq_flg: ask for squared-matrix)
  Real val;                                                                                                 // Real tmp-var to scan matrix file content (values)
  String line;                                                                                              // String tmp-var to store file lines content (values and spaces)
  Integer i=0, j=0, prev_j=0;                                                                               // Rows and columns idxs declaration and definition
  while (std::getline(matfile, line)){                                                                      // Cycle to scan file lines: read file line and save it inside a string tmp-var
    if (matfile.fail()) close_err("Fatal error occurred during matrix file scan!");                         // Catch matrix file scannin' error
    prev_j=j; j=0;                                                                                          // Prepare column idxs
    std::istringstream iss(line);                                                                           // Define input-string-stream from file-line tmp-string variable
    while (iss >> val){                                                                                     // Look for numerical values
      ++j;                                                                                                  // Upd column idx
      if (i==0) prev_j=j;                                                                                   // If it's the first iteration: upd previous columns number to match actual value
      if (j==1) ++i;                                                                                        // If it's the first iteration in this row, upd rows number
    }
    if (i!=1 && j!=prev_j)                                                                                  // Catch matrix file scannin' error (mismatch in columns number between rows)
      close_err("Error occurred during matrix file scan, columns number mismatch! Row "+ \
                S(i-1)+" has "+S(j)+" columns, previous had "+S(prev_j)+"!");                               // Catch matrix file scannin' error
  }
  if (sq_flg && i!=j) close_err("Error in matrix file scan, squared-matrix request not met! -- mat["+ \
                                S(i)+"]["+S(j)+"]");                                                        // Catch matrix file scannin' error (squared-matrix request)
  else if (i==0 || j==0) close_err("Error occurred during matrix file scan, file empty or contains text!"); // Catch matrix file scannin' error
  row=i; col=j;                                                                                             // Def matrix rows and columns number
  matfile.clear(); matfile.seekg(0);                                                                        // Set file ptr back to file-start
}


static void def_vector_size(File &vectfile, Integer &sz){                                                   // Funct to define vector size from input file
  Real val;                                                                                                 // Real tmp-var to scan vector file content (values)
  String line;                                                                                              // String tmp-var to store file lines content (values and spaces)
  Integer i=0, j=0;                                                                                         // Rows and columns idxs declaration and definition
  while (std::getline(vectfile, line)){                                                                     // Cycle to scan file lines: read file line and save it inside a string tmp-var
    if (vectfile.fail()) close_err("Fatal error occurred during vector file scan!");                        // Catch vector file scannin' error
    j=0;                                                                                                    // Prepare column idx
    std::istringstream iss(line);                                                                           // Define input-string-stream from file-line tmp-string variable
    while (iss >> val){                                                                                     // Look for numerical values
      if (j==0) ++i;                                                                                        // If it's the first iteration in this row, upd rows number
      ++j;                                                                                                  // Upd column idx
    }
  }
  if (i==0 || j==0) close_err("Error occurred during vector file scan, file empty or it contains text!");   // Catch vector file scannin' error
  else if (i>1) close_err("Error occurred during vector file scan, seems to be a matrix, not a vector!");   // Catch vector file scannin' error
  sz=j;                                                                                                     // Def vector size
  vectfile.clear(); vectfile.seekg(0);                                                                      // Set file ptr back to file-start
}


/* Public functions */
void file_open(File &file, C_string &filename, Mode &mode){                                                 // Funct to open file
  file.open(filename, mode==R ? std::ios::in : (mode==W ? std::ios::out : std::ios::out|std::ios::app));    // Manage file opening operation
  if (file.fail()) close_err("Error occurred during file opening: the file '"+filename+"' doesn't exist!"); // Catch file opening errors
}


Matrix file_read_matrix(File &matfile, Integer &row, Integer &col, C_boolean &sq_flg){                      // Funct to read matrix from file (alloc in dyn-memo, sq_flg: ask for squared-matrix)
  if (!matfile.is_open()) close_err("Error, the file must be opened before reading matrix from it!");       // Check if file has been opened and catch exception
  def_matrix_sizes(matfile, row, col, sq_flg);                                                              // Define matrix sizes befor allocatin' it in dyn-memo
  Matrix mat=matrix_alloc(row, col);                                                                        // Allocate matrix in dyn-memo
  for (Integer i=0; i<row; ++i)                                                                             // Matrix rows scrollin' cycle
    for (Integer j=0; j<col; ++j){                                                                          // Matrix columns scrollin' cycle
      matfile >> mat[i][j];                                                                                 // Def matrix elements reading from input file
      if (matfile.fail()) close_err("Error occurred during matrix reading from file!");                     // Catch matrix reading errors from file
    }
  return mat;                                                                                               // Return allocated matrix
}


void file_write_matrix(File &matfile, C_matrix mat, C_integer &row, C_integer &col){                        // Funct to write matrix on file
  if (!matfile.is_open()) close_err("Error, the file must be opened before writing matrix on it!");         // Check if file has been opened and catch exception
  for (Integer i=0; i<row; ++i){                                                                            // Matrix rows scrollin' cycle
    for (Integer j=0; j<col; ++j){                                                                          // Matrix columns scrollin' cycle
      matfile << mat[i][j] << " ";                                                                          // Save matrix elements on output file
      if (matfile.fail()) close_err("Error occurred during matrix writing on file!");                       // Catch matrix writing errors on file
    }
    matfile << std::endl;                                                                                   // Add new line in output file
  }
}


Vector file_read_vector(File &vectfile, Integer &sz){                                                       // Funct to read vector from file (alloc in dyn-memo)
  if (!vectfile.is_open()) close_err("Error, the file must be opened before reading vector from it!");      // Check if file has been opened and catch exception
  def_vector_size(vectfile, sz);                                                                            // Define vector size befor allocatin' it in dyn-memo
  Vector vect=vector_alloc(sz);                                                                             // Allocate vector in dyn-memo
  for (Integer i=0; i<sz; ++i){                                                                             // Vector elements scrollin' cycle
    vectfile >> vect[i];                                                                                    // Def vector elements reading from input file
    if (vectfile.fail()) close_err("Error occurred during vector reading from file!");                      // Catch vector reading errors from file
  }
  return vect;                                                                                              // Return allocated vector
}


void file_write_vector(File &vectfile, C_vector vect, C_integer &sz){                                       // Funct to write vector on file
  if (!vectfile.is_open()) close_err("Error, the file must be opened before writing vector on it!");        // Check if file has been opened and catch exception
  for (Integer i=0; i<sz; ++i){                                                                             // Vector columns scrollin' cycle
    vectfile << vect[i] << " ";                                                                             // Save vector elements on output file
    if (vectfile.fail()) close_err("Error occurred during vector writing on file!");                        // Catch vector writing errors on file
  }
}


void file_close(File &file){                                                                                // Funct to close file
  if (file.is_open()){                                                                                      // Check if file is opened
    file.close();                                                                                           // Close it
    if (file.fail()) close_err("Error occurred during file closing!");                                      // Catch file closing errors
  } else term_print("Error, can't close an already closed file!", ERR);                                     // Else if file ain't opened: print err fbk
}
