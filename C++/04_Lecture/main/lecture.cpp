/*
 * Author: Cristian Merli
 * Code title: Lecture
 * Code version: 3.0
 * Creation date: 07/04/2022
 * Last mod. date: 15/04/2022
 */


/* Dependencies */
#include "../lib/lecture/lib_lecture.h"                                                                     // Import lecture library header file


/* Namespaces */
using namespace std;                                                                                        // Include std namespace


/* Main routines */
static Integer read_cl_param(C_integer &argc, char *const argv[], Real param[], C_integer &param_sz){       // Routine to read command-line parameters
  bool err_flg=false;                                                                                       // Err flag declaration
  if (argc-1==param_sz){                                                                                    // Chk for expected num of main param
    ALLOC(String, p, argc-1);                                                                               // Allocate commands str dyn vect inside heap
    for (Integer i=1; i<argc; ++i){                                                                         // Param scrollin' cycle (skip prg name)
      p[i-1]=argv[i]; PRINT_VAL("Command-line parameter "+S(i), p[i-1]);                                    // Def commands str vect and print cli-pram str fbk
      for (size_t j=0; j<p[i-1].length(); ++j)                                                              // Chk each param str chr
        if (isdigit(p[i-1][j])==0 && p[i-1][j]!='.'){                                                       // If a param string char ain't a digit and it's different from '.' chr (used as fpt-comma)
          term_print("Expecting real value, not char!", ERR); err_flg=true; break; }                        // Print err fbk, set err flg and xit str chr chking cycle
      if (!err_flg) param[i-1]=atof(argv[i]); else break;                                                   // If everything is ok, conv param into out var, while in case of err flg set xit param scrollin' cycle
    }
    DEALLOC(p);                                                                                             // Deallocate commands str dyn vect from heap
  } else {                                                                                                  // Case wrong num of param
    term_print("Wrong param num in main funct-call: expecting "+S(param_sz)+", got "+S(argc-1)+"!", ERR);   // Print err fbk
    err_flg=true;                                                                                           // Set err flg
  }
  return (!err_flg) ? EXIT_SUCCESS : EXIT_FAILURE;                                                          // If err flg ain't set: return OK code else if err flg is set: return ERR code
}


/* Main cycle */
int main(const int argc, char *const argv[]){
  title(10, "Lecture-04", YE, '#', GN);                                                                     // Print responsive-title
  /* Code-start */


  Real param[]={0}; C_integer param_sz=ARRAY_SZ(param);                                                     // Param vect declaration and calc num of expected param
  if (read_cl_param(argc,argv,param,param_sz)==EXIT_FAILURE)                                                // Command-line parameters management
    close_err("Try to insert "+S(param_sz)+" real value(s) as parameter(s)!");                              // In case of ERR: close SW with err fbk

/* 
  Integer sz[]={0,0};                                                                                       // Declare mat (arr) sizes vect (rows, columns)
  Real mat[MAX_SZ][MAX_SZ];                                                                                 // Declare mat (arr) with max size
  def_mat(mat, sz, "Mat");                                                                                  // Def mat (arr)
  C_integer oper_res=mat_trasp(mat, sz, "Mat");                                                             // Apply mat (arr) transp oper
  if (oper_res==EXIT_SUCCESS) term_print("Matrix transposition correctly executed!");                       // Chk oper res, if OK print fbk
  else term_print("Error occurred while applying matrix transposition!", ERR);                              // In case of ERR, print fbk
 */
/* 
  Integer sz1[]={0,0}, sz2[]={0,0}, sz3[]={0,0};                                                            // Declare mat (arr) sizes vect (rows, columns)
  Real mat1[MAX_SZ][MAX_SZ], mat2[MAX_SZ][MAX_SZ], mat3[MAX_SZ][MAX_SZ];                                    // Declare mat (arr) with max size
  def_mat(mat1, sz1, "Mat1");                                                                               // Def mat1 (arr)
  def_mat(mat2, sz2, "Mat2");                                                                               // Def mat2 (arr)
  C_integer oper_res=mat_multipl(mat1, sz1, "Mat1", mat2, sz2, "Mat2", mat3, sz3, "Mat3");                  // Apply mat (arr) multipl oper
  if (oper_res==EXIT_SUCCESS) term_print("Matrix multiplication correctly executed!");                      // Chk oper res, if OK print fbk
  else term_print("Error occurred while applying matrix multiplication!", ERR);                             // In case of ERR, print fbk
 */

  /* Code-end */
  close_bye();                                                                                              // Close SW with bye fbk
}
