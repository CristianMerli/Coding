/*
 * Author: Cristian Merli
 * Code title: Files library
 * Code version: 3.0
 * Creation date: 07/05/2021
 * Last mod. date: 14/07/2021
 */


/* Libraries */
#include "lib_files.h"                                                                                      // Import files library header file
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file


/* Global vars */
char file_in_buff[FILE_IN_BUFF_SIZE] = "";                                                                  // File input buffer char array for fgets func


/* Functions */
Fl open_file(const char *const filename, const char *const mode){                                           // Function to open file
  /* Body */
  FILE *file;                                                                                               // Define file obj pointer
  file = fopen(filename, mode);                                                                             // Open defined file in specified mode (see the end of code)
  if (file == NULL){                                                                                        // Check open file operation result
    fbk_err("Ops! Encountred error during file open operation");                                            // Print error fbk
    perror("File open operation failed!");                                                                  // Print perror fbk
  }
  return file;                                                                                              // Return file pointer
}


void write_int_on_file(Fl file, C_int num){                                                                 // Function to write int on file
  /* Body */
  if (file != NULL){                                                                                        // Check file obj not null
    C_int res = fprintf(file, "%d", num);                                                                   // Insert number in file
    if (res < 1){                                                                                           // Check file write operation result
      fbk_err("Ops! Encountred error during int value file write operation");                               // Print error fbk
      perror("File write operation of int value, failed!");                                                 // Print perror fbk
    }
  } else {                                                                                                  // If file obj is null
    fbk_err("Ops! Null-file found during int value file write-operation");                                  // Print error fbk
    perror("File write operation of int value, failed!");                                                   // Print perror fbk
  }
}


void write_str_on_file(Fl file, const char *const str){                                                     // Function to write string on file
  /* Body */
  if (file != NULL){                                                                                        // Check file obj not null
    C_int res = fprintf(file, "%s", str);                                                                   // Insert string in file
    if (res < 1){                                                                                           // Check file write operation result
      fbk_err("Ops! Encountred error during string file write operation");                                  // Print error fbk
      perror("File write operation of string failed!");                                                     // Print perror fbk
    }
  } else {                                                                                                  // If file obj is null
    fbk_err("Ops! Null-file found during string file write-operation");                                     // Print error fbk
    perror("File write operation of string failed!");                                                       // Print perror fbk
  }
}


void write_sep_on_file(Fl file, C_char sep){                                                                // Function to write separator on file
  /* Body */
  if (file != NULL){                                                                                        // Check file obj not null
    C_int res = fprintf(file, "%c", sep);                                                                   // Insert separator in file
    if (res < 1){                                                                                           // Check file write operation result
      fbk_err("Ops! Encountred error during separator char file write operation");                          // Print error fbk
      perror("File write operation of separator char failed!");                                             // Print perror fbk
    }
  } else {                                                                                                  // If file obj is null
    fbk_err("Ops! Null-file found during separator char file-write operation");                             // Print error fbk
    perror("File write operation of separator char failed!");                                               // Print perror fbk
  }
}


void write_nl_on_file(Fl file){                                                                             // Function to write new line on file
  /* Body */
  if (file != NULL){                                                                                        // Check file obj not null
    C_int res = fprintf(file, "\n");                                                                        // Insert new line in file
    if (res < 1){                                                                                           // Check file write operation result
      fbk_err("Ops! Encountred error during new line file write operation");                                // Print error fbk
      perror("File write operation of new line failed!");                                                   // Print perror fbk
    }
  } else {                                                                                                  // If file obj is null
    fbk_err("Ops! Null-file found during new line file-write operation");                                   // Print error fbk
    perror("File write operation of new line failed!");                                                     // Print perror fbk
  }
}


void write_tab_on_file(Fl file){                                                                            // Function to write tab on file
  /* Body */
  if (file != NULL){                                                                                        // Check file obj not null
    C_int res = fprintf(file, "\t");                                                                        // Insert tab in file
    if (res < 1){                                                                                           // Check file write operation result
      fbk_err("Ops! Encountred error during tab file write operation");                                     // Print error fbk
      perror("File write operation of tab failed!");                                                        // Print perror fbk
    }
  } else {                                                                                                  // If file obj is null
    fbk_err("Ops! Null-file found during tab file-write operation");                                        // Print error fbk
    perror("File write operation of tab failed!");                                                          // Print perror fbk
  }
}


void read_from_file(Fl file){                                                                               // Function to read from file
  /* Body */
  if (file != NULL){                                                                                        // Check file obj not null
    fbk_nl(1);                                                                                              // New line fbk
    int line_num = 0;                                                                                       // Line number counter
    while ( fgets(file_in_buff, FILE_IN_BUFF_SIZE, file) != NULL ){                                         // In case of file found, scan lines 'till null line (last one)
      ++line_num;                                                                                           // Line number val upd
      printf("%s%d)\t%s%s", BU, line_num, OG, file_in_buff);                                                // Print line number and val fbk
    }
  } else {                                                                                                  // If file obj is null
    fbk_err("Ops! Null-file found during file-read operation");                                             // Print error fbk
    perror("File read operation failed!");                                                                  // Print perror fbk
  }
}


int get_substr_line_from_file(Fl file, const char *const tgt_str){                                          // Function to get sub-string line number from file (by target-string, returns -1 for no-match found or error)
  /* Body */
  if (file != NULL){                                                                                        // Check file obj not null
    int line_num = 0;                                                                                       // Line number counter
    while ( fgets(file_in_buff, FILE_IN_BUFF_SIZE, file) != NULL ){                                         // In case of file found, scan lines 'till null line (last one)
      ++line_num;                                                                                           // Line number val upd
      if (strstr(file_in_buff, tgt_str) != NULL)                                                            // Check if substring is in current line
        return line_num;                                                                                    // Return current line-number
    }
  } else {                                                                                                  // If file obj is null
    fbk_err("Ops! Null-file found during target-substring line number id operation");                       // Print error fbk
    perror("File target-substring line number id operation failed!");                                       // Print perror fbk
  }
  return -1;                                                                                                // Return -1 for no-match found or error
}


char* get_line_str_from_file(Fl file, C_int tgt_str_line_num){                                              // Function to get line-string from file (by target-string line number, returns NULL for no-match found or error)
  /* Body */
  if (file != NULL){                                                                                        // Check file obj not null
    int line_num = 0;                                                                                       // Line number counter
    while ( fgets(file_in_buff, FILE_IN_BUFF_SIZE, file) != NULL ){                                         // In case of file found, scan lines 'till null line (last one)
      ++line_num;                                                                                           // Line number val upd
      if (line_num == tgt_str_line_num)                                                                     // Scroll 'till target-string line number
        return file_in_buff;                                                                                // Return current line content as str
    }
  } else {                                                                                                  // If file obj is null
    fbk_err("Ops! Null-file found during line-string returning operation (by line number)");                // Print error fbk
    perror("File line-string returning operation (by line number) failed!");                                // Print perror fbk
  }
  return NULL;                                                                                              // Return NULL for no-match found or error
}


void close_file(Fl file){                                                                                   // Function to close file
  /* Body */
  if (file != NULL){                                                                                        // Check file obj not null
    C_int res = fclose(file);                                                                               // Close file
    if (res == EOF){                                                                                        // Check file close operation result
      fbk_err("Ops! Encountred error during file close operation");                                         // Print error fbk
      perror("File close operation failed!");                                                               // Print perror fbk
    }
  } else {                                                                                                  // If file obj is null
    fbk_err("Ops! Null-file found during file-close operation");                                            // Print error fbk
    perror("File close operation failed!");                                                                 // Print perror fbk
  }
}



/* File open modes */
/*
 * "w" = write (clear file)
 * "r" = read only
 * "a" = append (do not clear file, add text in write only, create if file doesn't exist)
 * "r+" = read/write (only if file exists)
 * "w+" = read&write (create file if not existing)
 * "a+" = read&write&append (create file if not existing)
 */
