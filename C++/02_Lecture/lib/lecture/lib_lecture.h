/*
 * Author: Cristian Merli
 * Code title: Lecture library header file
 * Code version: 3.0
 * Creation date: 24/03/2022
 * Last mod. date: 27/03/2022 
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
Real solve_first_deg_eqn(C_real &a, C_real &b);                                                             // Funct to solve 1st degree equations (ax+b=0)
Real solve_second_deg_eqn();                                                                                // Funct to solve 2nd degree equations
Complex solve_second_deg_eqn_complex();                                                                     // Funct to solve 2nd degree equations with complex solutions
void multilang_gm();                                                                                        // Funct to say 'good morning' in specified language
Integer num_guesser();                                                                                      // Funct to guess number (from 0 to 7)


#endif                                                                                                      // Avoid multiple inclusions (old-alternative end)
