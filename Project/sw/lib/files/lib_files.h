/*
 * Author: Cristian Merli
 * Code title: Files library header file
 * Code version: 3.0
 * Creation date: 07/05/2021
 * Last mod. date: 14/07/2021 
 */


/*!
 * @page        page7 7 - Files library
 * @brief       Files-library info
 * 
 * @section     section7 Library description:
 *              This library has the main purpose of managing files open/close and read/write operations (files lib_files.h and lib_files.c).
 * @subsection  subsection7 Library details:
 *              Library to manage files using <stdio.h> system-library and to give the possibility to wait a delay time during runtime.<br/>
 *              * <b>Library date/time structure:</b>
 *                * #date_time                    &nbsp;--> <i>Date/time personalized data-structure.</i>
 *              * <b>Library functions:</b>
 *                * #open_file()                  &nbsp;--> <i>Function to wait specified delay time in milliseconds.</i>
 *                * #write_int_on_file()          &nbsp;--> <i>Function to get current date/time.</i>
 *                * #write_str_on_file()          &nbsp;--> <i>Function to manually assign date/time values.</i>
 *                * #write_sep_on_file()          &nbsp;--> <i>Function to compare two dates/times.</i>
 *                * #write_nl_on_file()           &nbsp;--> <i>Function to print date/time feedback.</i>
 *                * #write_tab_on_file()          &nbsp;--> <i>Function to print date/time feedback.</i>
 *                * #read_from_file()             &nbsp;--> <i>Function to print date/time feedback.</i>
 *                * #get_substr_line_from_file()  &nbsp;--> <i>Function to print date/time feedback.</i>
 *                * #get_line_str_from_file()     &nbsp;--> <i>Function to print date/time feedback.</i>
 *                * #close_file()                 &nbsp;--> <i>Function to print date/time feedback.</i>
 * 
 * @file        lib_files.h <i>Library header file of lib_files.c.</i>
 * @brief       <b>Files-library header file</b>
 * 
 * @file        lib_files.c <i>More info in <b>'Files library'</b> section inside doxygen <b>'Related pages'</b>.</i>
 * @brief       <b>Files-library code file</b>
 * 
 * @file        lib_files.so <i>Library object file generated from lib_files.c during compiling operations.</i>
 * @brief       <b>Files-library object file</b>
 */


/* Libraries */
#include <stdio.h>                                                                                          // Standard I/O library inclusion (for files management ecc.)


/* Constants */
/// <b>Macro description:</b> Max file-input strings length in chars <i>(1023 + '\0')</i>, mainly used by fgets() function in file-reading operations.
#define FILE_IN_BUFF_SIZE 1024                                                                              // File input buffer char array size for fgets func


/* Data-types */
/// <b>Typedef description:</b> FILE* alias (Fl).
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



/* File open modes */
/*
 * "w"  = write (clear file or create if not existing)
 * "r"  = read only
 * "a"  = append (do not clear file, add text in write only, create if file doesn't exist)
 * "r+" = read/write (only if file exists)
 * "w+" = read/write (create file if not existing)
 * "a+" = read/write/append (create file if not existing)
 */
