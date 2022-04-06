/*
 * Author: Cristian Merli
 * Code title: Lecture library header file
 * Code version: 3.0
 * Creation date: 31/03/2022
 * Last mod. date: 06/04/2022 
 */


/* Include guards */
#pragma once                                                                                                // Avoid multiple inclusions
#ifndef _LECTURE_H_                                                                                         // Avoid multiple inclusions (old-alternative start)
#define _LECTURE_H_                                                                                         // Avoid multiple inclusions (old-alternative)


/* Dependencies */
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file


/* Libraries */
//


/* Public functions */
void def_vect(Real v[], Integer &sz, C_integer &sz_max, C_string &v_nm);                                    // Funct to define vector
void print_vect(C_real v[], C_integer &sz, C_string &v_nm);                                                 // Funct to print vector
Integer vect_scalar(C_real v1[], C_integer &sz1, C_real v2[], C_integer &sz2, Real &res);                   // Funct to apply vector scalar operation
Integer add_vect_elem(C_real &el, C_integer &i, Real v[], Integer &sz, C_integer &sz_max, C_string &v_nm);  // Funct to add element in vector at spec pos
// ---


#endif                                                                                                      // Avoid multiple inclusions (old-alternative end)
