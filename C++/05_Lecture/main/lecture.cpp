/*
 * Author: Cristian Merli
 * Code title: Lecture
 * Code version: 3.0
 * Creation date: 07/04/2022
 * Last mod. date: 27/04/2022
 */


/* Dependencies */
#include "../lib/lecture/lib_lecture.h"                                                                     // Import lecture library header file


/* Namespaces */
using namespace std;                                                                                        // Include std namespace


/* Main routines */
static Integer read_cl_param(C_integer &argc, char *const argv[], Real param[], C_integer &param_sz){       // Routine to read command-line parameters (return err flg)
  Boolean err_flg=false;                                                                                    // Err flag declaration
  term_print("Loading main command-line parameter(s)...");                                                  // Print oper fbk
  if (argc-1==param_sz){                                                                                    // Chk for expected num of main param
    ALLOC(String, p, argc-1);                                                                               // Allocate commands str dyn vect inside heap
    for (Integer i=1; i<argc; ++i){                                                                         // Param scrollin' cycle (skip prg name)
      p[i-1]=argv[i];                                                                                       // Def commands str vect
      err_flg=chk_num_str(p[i-1], "Expecting real value, not char! [Param"+S(i)+": "+p[i-1]+"]");           // Chk each param str chr to make sure it's numeric
      if (!err_flg) param[i-1]=atof(argv[i]); else break;                                                   // If everything is ok conv param into out var, while in case of err flg set xit param scrollin' cycle
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
  title(10, "Lecture-05", YE, '#', GN);                                                                     // Print responsive-title
  /* Code-start */


  Real param[]={0}; C_integer param_sz=ARRAY_SZ(param);                                                     // Param vect declaration and calc num of expected param [adjust to define expected param num]
  if (read_cl_param(argc,argv,param,param_sz))                                                              // Command-line parameters management
    close_err("Try to insert "+S(param_sz)+" real value(s) as main command-line parameter(s)!");            // In case of ERR: close SW with err fbk
  else for (size_t i=0; i<param_sz; ++i) PRINT_VAL("-- UNUSED IN THIS CODE -- param["+S(i)+"]", param[i]);  // In case of NO-ERR: print main param
  FBK_NL(1);                                                                                                // New-line fbk


  Integer sz_a=0, sz_b=0, sz_c=0;                                                                           // Vect size-vars declaration
  C_string name_a="Vector-a", name_b="Vector-b", name_c="Vector-c";                                         // Vect name-vars def
  Real *a=def_vect(sz_a, name_a);                                                                           // Def vect-a (dyn-memo)
  Real *b=def_vect(sz_b, name_b);                                                                           // Def vect-b (dyn-memo)
  Real *c=vect_concat(a, sz_a, name_a, b, sz_b, name_b, sz_c, name_c);                                      // Def vec-c (dyn-memo) and delete old vectors
  DEALLOC(c);                                                                                               // Dealloc concat vector

  /* Code-end */
  close_bye();                                                                                              // Close SW with bye fbk
}
