/*
 * Author: Cristian Merli
 * Code title: Homework1
 * Code version: 3.0
 * Creation date: 30/04/2022
 * Last mod. date: 05/05/2022
 * 
 * NOTES:
 * - The matrix convolution is applied on input matrix after ReLU operation (which modifies the matrix)!
 * - All the other operations are directly applied on input matrix.
 */


/* Dependencies */
#include "../lib/ui/lib_ui.hpp"                                                                             // Import UI (terminal I/O) library header file
#include "../lib/files/lib_files.hpp"                                                                       // Import files I/O library header file
#include "../lib/matrices/lib_matrices.hpp"                                                                 // Import matrices library header file
#include "../lib/cnn/lib_cnn.hpp"                                                                           // Import ConvNet library header file


/* Namespaces */
using namespace std;                                                                                        // Include std namespace


/* Enums */
enum Files{MAT,KER,MAXP,AVGP,RELU,CONVOL};                                                                  // Files enum (Matrix/Kernel/Output)


/* Global vars */
const String filename_str[]={"Matrix-file","Kernel-file","MaxPool-file", \
                             "AveragePool-file","ReLU-file","Convolution-file"};                            // Filenames str vect


/* Main routines */
static Boolean read_cl_param(C_integer &argc, char *const argv[], String param[], C_integer &param_sz){     // Routine to read command-line parameters (return oper fbk)
  term_print("Loading main command-line parameter(s)...");                                                  // Print oper fbk
  if (argc-1==param_sz){                                                                                    // Chk for expected num of main param, if ok
    for (Integer i=1; i<argc; ++i) param[i-1]=argv[i];                                                      // Scroll param (skip prg name) and def commands str vect
    return EXIT_SUCCESS;                                                                                    // Return OK code
  } else {                                                                                                  // Else in case wrong num of param
    term_print("Wrong param num in main funct-call: expecting "+S(param_sz)+", got "+S(argc-1)+"!", ERR);   // Print err fbk
    return EXIT_FAILURE;                                                                                    // Return ERR code
  }
}


/* Main cycle */
int main(const int argc, char *const argv[]){
  term_title(10, "Homework-1 Cristian Merli", YE, '#', GN);                                                 // Print responsive-title on terminal
  /* Code-start */


  // Load main parameters (filenames)
  String filenames[]={"","","","","",""}; C_byte filenames_sz=ARRAY_SZ(filenames);                          // Files vect declaration and num of expected param calc [adjust to define expected param num]
  if (!read_cl_param(argc,argv,filenames,filenames_sz)){                                                    // Command-line parameters management, in case of NO-ERR
    for (Byte i=0; i<filenames_sz; ++i) TERM_PRINT_VAL(filename_str[i], filenames[i]); TERM_NL(1);          // Print files
  } else {                                                                                                  // Else in case of ERR
    close_err("Expecting <"+filename_str[KER]+"> <"+filename_str[MAT]+"> <"+ \
              filename_str[MAXP]+"> <"+filename_str[AVGP]+"> <"+filename_str[RELU]+ \
              "> <"+filename_str[CONVOL]+"> as main parameters!");                                          // Close SW with err fbk
  }

  // Variables declaration
  File file_matrix, file_kernel, file_maxpool, file_avgpool, file_relu, file_convol;                        // Files declaration
  Integer mat_row, mat_col, ker_sz, pool_sz, relu_th, matpool_row, matpool_col;                             // Matrix-sizes and flt-vals declaration

  // Load matrix from file
  file_open(file_matrix, filenames[MAT], R);                                                                // Open matrix input-file (read mode)
  Matrix mat=file_read_matrix(file_matrix, mat_row, mat_col, false);                                        // Read matrix from input-file and allocate it in dyn-memo
  file_close(file_matrix);                                                                                  // Close matrix input-file

  // Apply max-pool and average-pool ConvNet functions to the matrix (export on file)
  TERM_ACQ_CYCLE("Insert max/average-pool filter size", INTEGER, pool_sz, (pool_sz<1), \
                 "Error, max/average-pool filter size must be greater than 1!");                            // Def pool filter size (squared-matrix)
  Matrix mat_maxpool=cnn_maxpool(mat, mat_row, mat_col, pool_sz, matpool_row, matpool_col);                 // Apply max-pool to the matrix allocating new matrix in dyn-memo
  file_open(file_maxpool, filenames[MAXP], W);                                                              // Open max-pool output-file (write mode)
  file_write_matrix(file_maxpool, mat_maxpool, matpool_row, matpool_col);                                   // Write result in dedicated output file
  file_close(file_maxpool);                                                                                 // Close max-pool output-file
  matrix_dealloc(mat_maxpool, matpool_row);                                                                 // Deallocate max-pool matrix from dyn-memo
  Matrix mat_avgpool=cnn_avgpool(mat, mat_row, mat_col, pool_sz, matpool_row, matpool_col);                 // Apply average-pool to the matrix allocating new matrix in dyn-memo
  file_open(file_avgpool, filenames[AVGP], W);                                                              // Open average-pool output-file (write mode)
  file_write_matrix(file_avgpool, mat_avgpool, matpool_row, matpool_col);                                   // Write result in dedicated output file
  file_close(file_avgpool);                                                                                 // Close average-pool output-file
  matrix_dealloc(mat_avgpool, matpool_row);                                                                 // Deallocate average-pool matrix from dyn-memo

  // Apply ReLU ConvNet function to the matrix (export on file)
  TERM_ACQ_CYCLE("Insert ReLU threshold value", INTEGER, relu_th, (relu_th<1), \
                 "Error, ReLU threshold value must be greater than 1!");                                    // Def ReLU threshold value
  cnn_relu(mat, mat_row, mat_col, relu_th);                                                                 // Apply ReLU to the input matrix
  file_open(file_relu, filenames[RELU], W);                                                                 // Open ReLU output-file (write mode)
  file_write_matrix(file_relu, mat, mat_row, mat_col);                                                      // Write result in dedicated output file
  file_close(file_relu);                                                                                    // Close ReLU output-file

  // Load kernel from file
  file_open(file_kernel, filenames[KER], R);                                                                // Open kernel input-file (read mode)
  Matrix ker=file_read_matrix(file_kernel, ker_sz, ker_sz, true);                                           // Read kernel from input-file and allocate it in dyn-memo
  file_close(file_kernel);                                                                                  // Close kernel input-file

  // Apply convolution ConvNet function to the matrix (export on file)
  Matrix feature_map=cnn_convolution(mat, mat_row, mat_col, ker, ker_sz);                                   // Apply convolution to the matrix allocating new matrix (feature map) in dyn-memo
  matrix_dealloc(ker, ker_sz);                                                                              // Deallocate kernel from dyn-memo
  matrix_dealloc(mat, mat_row);                                                                             // Deallocate matrix from dyn-memo
  file_open(file_convol, filenames[CONVOL], W);                                                             // Open convolution output-file
  file_write_matrix(file_convol, feature_map, mat_row, mat_col);                                            // Write result in dedicated output file
  file_close(file_convol);                                                                                  // Close convolution output-file
  matrix_dealloc(feature_map, mat_row);                                                                     // Deallocate convolution matrix (feature map) from dyn-memo


  /* Code-end */
  close_bye("Done, check output-files to see the results! Files are placed in 'src/output/' directory.");   // Print software closing fbk
}
