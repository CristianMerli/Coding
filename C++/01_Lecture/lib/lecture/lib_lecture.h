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
//


/* Public functions */
Real conv_c_k();                                                                                            // Funct to interactively convert temperature from [°C] to [K]
Integer conv_c_f_f_c();                                                                                     // Funct to interactively convert from [°C] to [F] or from [F] to [°C]
void chk_if_div();                                                                                          // Funct to interactively check if a number can be divided
void print_vals();                                                                                          // Funct to interactively print values function
void fibonacci();                                                                                           // Funct to interactively print Fibonacci numbers
Real solve_first_deg_eqn();                                                                                 // Funct to interactively solve 1st degree equations
Real solve_second_deg_eqn();                                                                                // Funct to interactively solve 2nd degree equations
Complex solve_second_deg_eqn_complex();                                                                     // Funct to interactively solve 2nd degree equations with complex solutions
void multilang_gm();                                                                                        // Funct to interactively say 'good morning' in specified language
Integer num_guesser();                                                                                      // Funct to interactively guess number (from 0 to 7)


#endif                                                                                                      // Avoid multiple inclusions (old-alternative end)
