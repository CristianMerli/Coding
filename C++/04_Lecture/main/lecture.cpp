/*
 * Author: Cristian Merli
 * Code title: Lecture
 * Code version: 3.0
 * Creation date: 07/04/2022
 * Last mod. date: 07/04/2022
 */


/* Dependencies */
#include "../lib/lecture/lib_lecture.h"                                                                     // Import lecture library header file


/* Namespaces */
using namespace std;                                                                                        // Include std namespace


/* Main routines */
static Integer read_cl_param(C_integer &argc, char *const argv[], Real param[]){                            // Routine to read command-line parameters
  String *p=new String[argc];                                                                               // Allocate commands str dyn vect inside heap
  for (Integer i=0; i<argc; ++i) p[i]=argv[i];                                                              // Def commands str vect
  switch (argc-1){                                                                                          // Param num cases management
    case 1:                                                                                                 // Case 1 param
      PRINT_VAL("Command-line parameter 1 string", p[1]);                                                   // Print cli-pram str fbk
      for (size_t i=0; i<p[1].length(); ++i)                                                                // Chk each param str chr
        if (isdigit(p[1][i])==0){                                                                           // If a param string char ain't a digit
          FBK_NL(1); term_print("Expecting a real value, not a char!", ERR); return EXIT_FAILURE;           // Print err fbk and return ERR code
        }
      param[0]=atof(argv[1]); break;                                                                        // Param conv into out var
    default:                                                                                                // Case wrong num of param
      term_print("Wrong number of param in main funct-call, can't continue...", ERR); return EXIT_FAILURE;  // Print err fbk and return ERR code
  }
  return EXIT_SUCCESS;                                                                                      // Return OK code
}


/* Main cycle */
int main(const int argc, char *const argv[]){
  title(10, "Lecture-04", YE, '#', GN);                                                                     // Print responsive-title
  /* Code-start */


  Real param[]={0};                                                                                         // Real param vect
  if (read_cl_param(argc,argv,param)==EXIT_FAILURE) close_err("Insert 1 real value as main parameter!");    // Command-line parameters management
  PRINT_VAL("param[0]", param[0]);                                                                          // Print param real val
  // Funct to chk if there's a chr in number (see routine and create funct in UI lib) dyn memo delete??

  /* Code-end */
  close_bye();                                                                                              // Close SW with bye fbk
}
