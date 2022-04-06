/*
 * Author: Cristian Merli
 * Code title: Lecture library
 * Code version: 3.0
 * Creation date: 31/03/2022
 * Last mod. date: 06/04/2022
 */


/* Dependencies */
#include "lib_lecture.h"                                                                                    // Import lecture library header file


/* Public functions */
void def_vect(Real v[], Integer &sz, C_integer &sz_max, C_string &v_nm){                                    // Funct to define vector
  ACQ_CYCLE("Insert "+v_nm+" size", INTEGER, sz, (sz<1 || sz>sz_max),
            "Error, the array size must be between 1 and 10!");                                             // Array size def
  for (Integer i=0; i<sz; ++i) get_val("Insert "+v_nm+" element "+std::to_string(i), REAL, &v[i]);          // Array elements def
  term_print("Acquisition completed, recap...");                                                            // Print acq completed fbk
  print_vect(v, sz, v_nm);                                                                                  // Print vect
}


void print_vect(C_real v[], C_integer &sz, C_string &v_nm){                                                 // Funct to print vector
  String vect_str="[";                                                                                      // Vect-str init
  for (Integer i=0; i<sz-1; ++i) vect_str+=(std::to_string(v[i])+", ");                                     // Vect-str upd with elements
  vect_str+=(std::to_string(v[sz-1])+"]");                                                                  // Vect-str completed with last elem
  PRINT_VAL(v_nm, vect_str);                                                                                // Print vect-str
}


Integer vect_scalar(C_real v1[], C_integer &sz1, C_real v2[], C_integer &sz2, Real &res){                   // Funct to apply vector scalar operation
  res=0;                                                                                                    // Vect scalar oper res val rst
  C_integer min_sz=(sz1<sz2) ? sz1 : sz2;                                                                   // Def min vect size
  for (Integer i=0; i<min_sz; ++i) res+=(v1[i]*v2[i]);                                                      // Apply vect scalar oper 'till min vect size
  return EXIT_SUCCESS;                                                                                      // Return OK code
}


Integer add_vect_elem(C_real &el, C_integer &i, Real v[], Integer &sz, C_integer &sz_max, C_string &v_nm){  // Funct to add element in vector at spec pos
  if (sz < sz_max){                                                                                         // In case of space for a new elem inside vect
    for(Integer i=sz-1; i>=i; --i) v[i+1]=v[i];                                                             // Move old elements
    (i<=sz) ? ++sz : sz+=(i-sz+1);                                                                          // Vect size upd
    v[i]=el;                                                                                                // Add elem in vect spec pos
    print_vect(v, sz, v_nm);                                                                                // Print vect
    return EXIT_SUCCESS;                                                                                    // Return OK code
  } else return EXIT_FAILURE;                                                                               // In case of no more space for a new elem inside vect, return ERR code
}


// ---
