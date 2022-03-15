/*
 * Author: Cristian Merli
 * Code title: Lecture library header file
 * Code version: 3.0
 * Creation date: 03/02/2022
 * Last mod. date: 09/02/2022 
 */


/* Include guards */
#pragma once                                                                                                // Avoid multiple inclusions
#ifndef _LECTURE_H_                                                                                         // Avoid multiple inclusions (old-alternative start)
#define _LECTURE_H_                                                                                         // Avoid multiple inclusions (old-alternative)


/* Dependencies */
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file


/* Libraries */
#include <complex>                                                                                          // Complex-numbers library inclusion (for real, imag ecc.)


/* Public functions */
Real solve_second_deg_eqn();                                                                                // Funct to interactively solve 2nd degree equations
std::complex<Real> solve_second_deg_eqn_complex();                                                          // Funct to interactively solve 2nd degree equations with complex solutions
void multilang_gm();                                                                                        // Funct to interactively say 'good morning' in specified language
Integer num_guesser();                                                                                      // Funct to interactively guess number (from 0 to 7)


#endif                                                                                                      // Avoid multiple inclusions (old-alternative end)
