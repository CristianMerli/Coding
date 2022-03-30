/*
 * Author: Cristian Merli
 * Code title: Lecture library header file
 * Code version: 3.0
 * Creation date: 24/03/2022
 * Last mod. date: 31/03/2022 
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
Integer is_prime(C_integer &num);                                                                           // Function to check whether a number is prime and if not returns one of its divisors
Integer solve_first_deg_eqn(C_real &a, C_real &b, Real &x);                                                 // Funct to solve 1st degree equations (ax+b=0)
Integer solve_second_deg_eqn(C_real coeff[], Real x[]);                                                     // Funct to solve 2nd degree equations (ax^2+bx+c=0)
Integer solve_second_deg_eqn_complex(C_real coeff[], Complex x[]);                                          // Funct to solve 2nd degree equations with complex solutions (ax^2+bx+c=0)
Integer multilang_gm(C_character &lang);                                                                    // Funct to say 'good morning' in specified language
Integer num_guesser(Integer &num);                                                                          // Funct to guess number (from 0 to 7)


#endif                                                                                                      // Avoid multiple inclusions (old-alternative end)
