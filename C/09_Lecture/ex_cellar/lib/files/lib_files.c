/*
 * Author: Cristian Merli
 * Code title: Files library
 * Code version: 3.0
 * Creation date: 07/05/2021
 * Last mod. date: 20/05/2021
 */


/* Libraries */
#include "lib_files.h"                                                                                      // Import files library header file
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file


/* Global vars */
char file_in_buff[FILE_IN_BUFF_SIZE] = "";                                                                  // File input buffer char array for fgets func


/* Functions */
fl open_file(const char *filename, const char *mode){                                                       // Open file function
  /* Body */
  FILE *file;                                                                                               // Define file obj pointer
  file = fopen(filename, mode);                                                                             // Open defined file in defined mode (see the end of code)

  if (file == NULL){                                                                                        // Check open file operation result
    fbk_err("Error! File open operation failed");                                                           // Error fbk
    perror("Error in file open!");                                                                          // Print perror fbk
    close_err();                                                                                            // Close software with error function call
  }
  return file;                                                                                              // Return file pointer
}


void write_int_on_file(fl file, const int num){                                                             // Write int on file function
  /* Body */
  if (file != NULL){                                                                                        // Check file obj not null
    int res = fprintf(file, "%d", num);                                                                     // Insert number in file
    if (res < 1){                                                                                           // Check file write operation result
      fbk_err("Error! Int value file write operation failed");                                              // Error fbk
      perror("Error during file write operation of int value!");                                            // Print perror fbk
    }
  } else {                                                                                                  // If file obj is null
    fbk_err("Error! Null file found during int value file write operation");                                // Error fbk
    perror("Null file found during file write operation of int value!");                                    // Print perror fbk
  }
}


void write_str_on_file(fl file, const char *str){                                                           // Write string on file function
  /* Body */
  if (file != NULL){                                                                                        // Check file obj not null
    int res = fprintf(file, "%s", str);                                                                     // Insert string in file
    if (res < 1){                                                                                           // Check file write operation result
      fbk_err("Error! String file write operation failed");                                                 // Error fbk
      perror("Error during file write operation of string!");                                               // Print perror fbk
    }
  } else {                                                                                                  // If file obj is null
    fbk_err("Error! Null file found during string file write operation");                                   // Error fbk
    perror("Null file found during file write operation of string!");                                       // Print perror fbk
  }
}


void write_sep_on_file(fl file, const char sep){                                                            // Write separator on file function
  /* Body */
  if (file != NULL){                                                                                        // Check file obj not null
    int res = fprintf(file, "%c", sep);                                                                     // Insert separator in file
    if (res < 1){                                                                                           // Check file write operation result
      fbk_err("Error! Separator char file write operation failed");                                         // Error fbk
      perror("Error during file write operation of separator char!");                                       // Print perror fbk
    }
  } else {                                                                                                  // If file obj is null
    fbk_err("Error! Null file found during separator char file write operation");                           // Error fbk
    perror("Null file found during file write operation of separator char!");                               // Print perror fbk
  }
}


void write_nl_on_file(fl file){                                                                             // Write new line on file function
  /* Body */
  if (file != NULL){                                                                                        // Check file obj not null
    int res = fprintf(file, "\n");                                                                          // Insert new line in file
    if (res < 1){                                                                                           // Check file write operation result
      fbk_err("Error! New line file write operation failed");                                               // Error fbk
      perror("Error during file write operation of new line!");                                             // Print perror fbk
    }
  } else {                                                                                                  // If file obj is null
    fbk_err("Error! Null file found during new line file write operation");                                 // Error fbk
    perror("Null file found during file write operation of new line!");                                     // Print perror fbk
  }
}


void write_tab_on_file(fl file){                                                                            // Write tab on file function
  /* Body */
  if (file != NULL){                                                                                        // Check file obj not null
    int res = fprintf(file, "\t");                                                                          // Insert tab in file
    if (res < 1){                                                                                           // Check file write operation result
      fbk_err("Error! Tab file write operation failed");                                                    // Error fbk
      perror("Error during file write operation of tab!");                                                  // Print perror fbk
    }
  } else {                                                                                                  // If file obj is null
    fbk_err("Error! Null file found during tab file write operation");                                      // Error fbk
    perror("Null file found during file write operation of tab!");                                          // Print perror fbk
  }
}


void read_from_file(fl file){                                                                               // Read from file function
  /* Body */
  if (file != NULL){                                                                                        // Check file obj not null
    fbk_nl(1);                                                                                              // New line fbk
    u_int line_num = 0;                                                                                     // Line number counter
    while ( fgets(file_in_buff, FILE_IN_BUFF_SIZE, file) != NULL ){                                         // In case of file found, scan lines 'till null line (last one)
      ++line_num;                                                                                           // Line number val upd
      printf("%s%d)  %s%s", BU, line_num, OG, file_in_buff);                                                // Print line number and val fbk
    }
  } else {                                                                                                  // If file obj is null
    fbk_err("Error! Null file found during file read operation");                                           // Error fbk
    perror("Null file found during file read operation!");                                                  // Print perror fbk
  }
}


void close_file(fl file){                                                                                   // Close file function
  /* Body */
  if (file != NULL){                                                                                        // Check file obj not null
    int res = fclose(file);                                                                                 // Close file
    if (res == EOF){                                                                                        // Check file close operation result
      fbk_err("Error! File close operation failed");                                                        // Error fbk
      perror("Error during file close operation!");                                                         // Print perror fbk
    }
  } else {                                                                                                  // If file obj is null
    fbk_err("Error! Null file found during file close operation");                                          // Error fbk
    perror("Null file found during file close operation!");                                                 // Print perror fbk
  }
}



/* File open modes */
/*
 * "w" = write (clear file)
 * "r" = read only
 * "a" = append (do not clear file, add text in write only, create if file doesn't exist)
 * "r+" = read/write (only if file exists)
 * "w+" = read&write (create file if not exists)
 * "a+" = read&write&append (create file if not exists)
 */
