/*
 * Author: Cristian Merli
 * Code title: Files library header file
 * Code version: 3.0
 * Creation date: 07/05/2021
 * Last mod. date: 19/05/2021 
 */


/* Libraries */
#include <stdio.h>                                                                                          // Standard I/O library inclusion (for files management ecc.)


/* Constants */
#define FILE_IN_BUFF_SIZE 1024                                                                              // File input buffer char array size for fgets func


/* Data-types */
typedef FILE* fl;                                                                                           // File ptr data type


/* Global vars */
extern char file_in_buff[FILE_IN_BUFF_SIZE];                                                                // File input buffer char array for fgets func


/* Library functions */
fl open_file(const char *filename, const char *mode);                                                       // Open file function

void write_int_on_file(fl file, const int num);                                                             // Write int on file function

void write_str_on_file(fl file, const char *str);                                                           // Write string on file function

void write_sep_on_file(fl file, const char sep);                                                            // Write separator on file function

void write_nl_on_file(fl file);                                                                             // Write new line on file function

void write_tab_on_file(fl file);                                                                            // Write tab on file function

void read_from_file(fl file);                                                                               // Read from file function

void close_file(fl file);                                                                                   // Close file function



/* File open modes */
/*
 * "w" = write (clear file)
 * "r" = read only
 * "a" = append (do not clear file, add text in write only, create if file doesn't exist)
 * "r+" = read/write (only if file exists)
 * "w+" = read&write (create file if not exists)
 * "a+" = read&write&append (create file if not exists)
 */
