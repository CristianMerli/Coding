/*
 * Author: Cristian Merli
 * Code title: Lecture library header file
 * Code version: 3.0
 * Creation date: 03/03/2022
 * Last mod. date: 24/03/2022 
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
void consecutive_num();                                                                                     // Funct to interactively plot consecutive numbers
void fibonacci();                                                                                           // Funct to interactively print Fibonacci numbers


#endif                                                                                                      // Avoid multiple inclusions (old-alternative end)
