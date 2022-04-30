/*
 * Author: Cristian Merli
 * Code title: Homework1
 * Code version: 0.0
 * Creation date: 30/04/2022
 * Last mod. date: 30/04/2022
 */


/* Dependencies */
#include "../lib/ui/lib_ui.h"                                                                               // Import UI (terminal I/O) library header file
#include "../lib/files/lib_files.h"                                                                         // Import files I/O library header file
#include "../lib/matrices/lib_matrices.h"                                                                   // Import matrices library header file
#include "../lib/cnn/lib_cnn.h"                                                                             // Import ConvNet library header file


/* Namespaces */
using namespace std;                                                                                        // Include std namespace


/* Main routines */
static Integer read_cl_param(C_integer &argc, char *const argv[], String param[], C_integer &param_sz){     // Routine to read command-line parameters (return oper fbk)
  term_print("Loading main command-line parameter(s)...");                                                  // Print oper fbk
  if (argc-1==param_sz) for (Integer i=1; i<argc; ++i) param[i-1]=argv[i];                                  // Chk for expected num of main param and def commands str vect (skip prg name)
  else {                                                                                                    // Case wrong num of param
    term_print("Wrong param num in main funct-call: expecting "+S(param_sz)+", got "+S(argc-1)+"!", ERR);   // Print err fbk
    return EXIT_FAILURE;                                                                                    // Return ERR code
  }
  return EXIT_SUCCESS;                                                                                      // Return OK code
}


/* Main cycle */
int main(const int argc, char *const argv[]){
  title(10, "Homework-1 Cristian Merli", YE, '#', GN);                                                      // Print responsive-title
  /* Code-start */


  String param[]={"",""}; C_integer param_sz=ARRAY_SZ(param);                                               // Param vect declaration and calc num of expected param [adjust to define expected param num]
  if (read_cl_param(argc,argv,param,param_sz))                                                              // Command-line parameters management
    close_err("Try to insert "+S(param_sz)+" real value(s) as main command-line parameter(s)!");            // In case of ERR: close SW with err fbk
  else {                                                                                                    // Else in case of NO-ERR
    PRINT_VAL("In-file name", param[0]);                                                                    // Print ---
    PRINT_VAL("Out-file name", param[1]);                                                                   // Print ---
    FBK_NL(1);                                                                                              // New-line fbk
  }


  //


  /* Code-end */
  close_bye("");                                                                                            // Close SW with bye fbk
}
