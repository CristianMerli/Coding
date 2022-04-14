/*
 * Author: Cristian Merli
 * Code title: Lecture
 * Code version: 3.0
 * Creation date: 07/04/2022
 * Last mod. date: 14/04/2022
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
  // Define in that way two matrix A and B and calculate C: AxB for squared mat and non squared mat

  // Integer sz[]={0,0};                                                                                       // Declare mat (arr) sizes vect (rows, columns)
  // Real mat[MAX_SZ][MAX_SZ];                                                                                 // Declare mat (arr) with max size
  // def_mat(mat, sz, "Mat");                                                                                  // Def mat (arr)
  // C_integer oper_res=mat_trasp(mat, sz, "Mat");                                                             // Apply mat (arr) transp oper
  // if (oper_res==EXIT_SUCCESS) term_print("Matrix transposition correctly executed!");                       // Chk oper res, if OK print fbk
  // else term_print("Error occurred while applying matrix transposition!", ERR);                              // In case of ERR, print fbk

  Integer sz1[]={0,0}, sz2[]={0,0}, sz3[]={0,0};                                                            // Declare mat (arr) sizes vect (rows, columns)
  Real mat1[MAX_SZ][MAX_SZ], mat2[MAX_SZ][MAX_SZ], mat3[MAX_SZ][MAX_SZ];                                    // Declare mat (arr) with max size
  def_mat(mat1, sz1, "Mat1");                                                                               // Def mat1 (arr)
  def_mat(mat2, sz2, "Mat2");                                                                               // Def mat2 (arr)
  C_integer oper_res=mat_multipl(mat1, sz1, "Mat1", mat2, sz2, "Mat2", mat3, sz3, "Mat3");                  // Apply mat (arr) multipl oper
  if (oper_res==EXIT_SUCCESS) term_print("Matrix multiplication correctly executed!");                      // Chk oper res, if OK print fbk
  else term_print("Error occurred while applying matrix multiplication!", ERR);                             // In case of ERR, print fbk


  /* Code-end */
  close_bye();                                                                                              // Close SW with bye fbk
}
