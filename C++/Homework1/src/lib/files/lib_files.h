/*
 * Author: Cristian Merli
 * Code title: Files I/O library header file
 * Code version: 3.0
 * Creation date: 30/04/2022
 * Last mod. date: 04/05/2022 
 */


/* Include guards */
#pragma once                                                                                                // Avoid multiple inclusions
#ifndef _FILES_H_                                                                                           // Avoid multiple inclusions (old-alternative start)
#define _FILES_H_                                                                                           // Avoid multiple inclusions (old-alternative)


/* Dependencies */
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file
#include "../matrices/lib_matrices.h"                                                                       // Import matrices library header file


/* Libraries */
#include <fstream>                                                                                          // I/O files library inclusion (for open, close ecc.)


/* Data-types */
typedef std::fstream  File;                                                                                 // File alias
typedef std::ifstream I_file;                                                                               // I_file alias
typedef std::ofstream O_file;                                                                               // O_file alias


/* Enums */
typedef const enum mode{R,W,A}  Mode;                                                                       // Files opening mode enum (Read/Write/Append)


/* Public functions */
void file_open(File &file, C_string &filename, Mode &mode);                                                 // Funct to open file
Matrix file_read_matrix(File &matfile, Integer &row, Integer &col, C_boolean &sq_flg);                      // Funct to read matrix from file (alloc in dyn-memo, sq_flg: ask for squared-matrix)
void file_write_matrix(File &matfile, C_matrix mat, C_integer &row, C_integer &col);                        // Funct to write matrix on file
Vector file_read_vector(File &vectfile, Integer &sz);                                                       // Funct to read vector from file (alloc in dyn-memo)
void file_write_vector(File &vectfile, C_vector vect, C_integer &sz);                                       // Funct to write vector on file
void file_close(File &file);                                                                                // Funct to close file


#endif                                                                                                      // Avoid multiple inclusions (old-alternative end)
