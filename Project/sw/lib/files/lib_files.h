/*
 * Author: Cristian Merli
 * Code title: Files library header file
 * Code version: 3.0
 * Creation date: 07/05/2021
 * Last mod. date: 14/07/2021 
 */


/* Libraries */
#include <stdio.h>                                                                                          // Standard I/O library inclusion (for files management ecc.)


/* Constants */
#define FILE_IN_BUFF_SIZE 1024                                                                              // File input buffer char array size for fgets func


/* Data-types */
typedef FILE* Fl;                                                                                           // File ptr data type


/* Public vars */
extern char file_in_buff[FILE_IN_BUFF_SIZE];                                                                // File input buffer char array for fgets func


/* Library functions */
Fl open_file(const char *const filename, const char *const mode);                                           // Function to open file

void write_int_on_file(Fl file, const int num);                                                             // Function to write int on file

void write_str_on_file(Fl file, const char *const str);                                                     // Function to write string on file

void write_sep_on_file(Fl file, const char sep);                                                            // Function to write separator on file

void write_nl_on_file(Fl file);                                                                             // Function to write new line on file

void write_tab_on_file(Fl file);                                                                            // Function to write tab on file

void read_from_file(Fl file);                                                                               // Function to read from file

int get_substr_line_from_file(Fl file, const char *const tgt_str);                                          // Function to get sub-string line number from file (by target-string, returns -1 for no-match found or error)

char* get_line_str_from_file(Fl file, const int tgt_str_line_num);                                          // Function to get line-string from file (by target-string line number, returns NULL for no-match found or error)

void close_file(Fl file);                                                                                   // Function to close file



/* File-open modes */
/*
 * "w" = write (clear file)
 * "r" = read only
 * "a" = append (do not clear file, add text in write only, create if file doesn't exist)
 * "r+" = read/write (only if file exists)
 * "w+" = read&write (create file if not existing)
 * "a+" = read&write&append (create file if not existing)
 */
