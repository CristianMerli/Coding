/*
 * Author: Cristian Merli
 * Code title: Lecture library
 * Code version: 3.0
 * Creation date: 07/04/2022
 * Last mod. date: 27/04/2022
 */


/* Dependencies */
#include "lib_lecture.h"                                                                                    // Import lecture library header file


/* Public functions */
Real *def_vect(Integer &sz, C_string &vect_nm){                                                             // Funct to define vector
  ACQ_CYCLE("Insert "+vect_nm+" size", INTEGER, sz, (sz<1),
            "Error, vector size must be greater than zero!");                                               // Vect size def
  ALLOC(Real, v, sz);                                                                                       // Vect dyn-alloc
  for (Integer i=0; i<sz; ++i)                                                                              // Vect elements scrollin' cycle
    get_val("Insert "+vect_nm+"["+std::S(i+1)+"]", REAL, &v[i]);                                            // Vect elements def
  term_print("Acquisition completed, recap...");                                                            // Print acq completed fbk
  print_vect(v, sz, vect_nm, 18, 4);                                                                        // Print vect
  return v;                                                                                                 // Return vect ptr
}


void print_vect(C_real *const v, C_integer &sz, C_string &vect_nm, C_integer &lt, C_integer &t){            // Funct to print vector
  std::cout << GN << ">>> " << PU << vect_nm+"["<< sz << "]:" << std::endl << ER;                           // Print vect name and size
  std::cout << LBU << std::setw(lt) << "|" << ER;                                                           // Print left vert-line
  for (Integer i=0; i<sz; ++i)                                                                              // Vect elements printin' cycle
    std::cout << LBU << std::setw(t) << *(v+i) << ER;                                                       // Vect elements printin'
  std::cout << LBU << std::setw(t) << "|" << std::endl << ER;                                               // Print right vert-line
}


Real *vect_concat(C_real *const v1, C_integer &sz1, C_string &vect1_nm,
                  C_real *const v2, C_integer &sz2, C_string &vect2_nm,
                  Integer sz3, C_string &vect3_nm){                                                         // Funct to apply vector concatenation oper (delete old vectors)
  PRINT_VAL("Executing vect-concat operation between", vect3_nm+" = "+vect1_nm+" + "+vect2_nm);             // Oper fbk
  sz3=sz1+sz2;                                                                                              // Concat vect size def
  ALLOC(Real, v3, sz3);                                                                                     // Concat vect dyn-alloc
  for (Integer i=0; i<sz3; ++i) *(v3+i)=(i<sz1) ? (*(v1+i)) : (*(v2+i-sz1));                                // Populate concat vect
  DEALLOC(v1); DEALLOC(v2);                                                                                 // Dealloc old vectors
  term_print("Vect-concat completed, recap...");                                                            // Print oper completed fbk
  print_vect(v3, sz3, vect3_nm, 18, 4);                                                                     // Print vect
  return v3;                                                                                                // Return concat vect ptr
}
