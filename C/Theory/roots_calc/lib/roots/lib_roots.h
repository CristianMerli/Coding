/*
 * Author: Cristian Merli
 * Code title: Roots library header file
 * Code version: 3.0
 * Creation date: 12/06/2021
 * Last mod. date: 13/06/2021 
 */


/* Avoid multiple inclusions */
#ifndef LIB_ROOTS                                                                                           // Avoid multiple inclusion
#define LIB_ROOTS                                                                                           // Avoid multiple inclusion


/* Libraries */
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file


/* Constants */
//


/* Lib vars */
//


/* Structs & data-types */
//


/* Enums & data-types */
//


/* Library functions */
Real root_calc(C_real a, C_int n);                                                                          // Funct to calc the 'a' val 'n-th' root with newton algorithm, startin' from 'a' pt


#endif /* !LIB_ROOTS */                                                                                     // Avoid multiple inclusion
