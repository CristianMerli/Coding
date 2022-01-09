/*
 * Author: Cristian Merli
 * Code title: Advanced preprocessing operations (simple macro functions definition)
 * Code version: 3.0
 * Creation date: 24/05/2021
 * Last mod. date: 24/05/2021
 *
 * --> To compile&run:                    gccW99_o preprocessor preprocessor.c -DLINE && ./preprocessor
 * --> In alternative:                    gccW99_o preprocessor preprocessor.c -DLINE=7 && ./preprocessor
 * --> To generate preprocessor output:   gcc -Wall -E preprocessor.c -o preprocessor.c.out
 * 
 * - the file *.c.out might be compiled and executed, used as intermediate step
 */ 


/* Libraries */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <stdlib.h>                                                                                         // Standard library inclusion (EXIT_SUCCESS, EXIT_FAILURE)


/* Constants */
// Classic macro
#define MACRO 4.0                                                                                           // Classic macro definition

#define CIRCLE_AREA(r)  r*r*3.14                                                                            // Area calc macro function (defined macro)

#define SWAP(type, x, y)  \
{                         \
  type t;                 \
  t = (x);                \
  (x) = (y);              \
  (y) = t;                \
}                                                                                                           // Multiple-lines macro function definition (using '/'), to swap var vals after specifying data type

#define JOIN(x,y) x##y                                                                                      // Join variable name macro function (concat using '##', which is deleted by the preprocessor)

// #undef MACRO                                                                                                // Remove macro definition

#ifdef LINE                                                                                                 // Check if a macro has been defined (gccW99_o preprocessor preprocessor.c -DLINE && ./preprocessor)
  #define MACRO2  "Hi"                                                                                      // Define a new macro
#else                                                                                                       // Else if condition is not met
  #define MACRO2  "Hello"                                                                                   // Define a new macro
#endif                                                                                                      // End if

#if LINE                                                                                                    // If the int MACRO is different from zero, the following operation 'll be executed
  #define MACRO3 = 6                                                                                        // Define a new macro
#else                                                                                                       // Else if condition is not met
  #define MACRO4 = 8                                                                                        // Define a new macro
#endif                                                                                                      // End if


/* Main cycle */
int main(){
  /* Main vars */
  double radius = MACRO, area = 0.0;                                                                        // Double vars to calc circle area
  int a = 5, b = 8;                                                                                         // Int vars to swap values 

  /* Code */
  area = CIRCLE_AREA(radius);                                                                               // Call area calc function (defined macro)
  printf("\n- The circle radius is %lf and the area is %lf\n", radius, area);                               // Print circle parameters
  
  printf("\n- a=%d, b=%d, swapping...\n", a, b);                                                            // Print a and b var vals
  SWAP(int, a, b);                                                                                          // Call swap values function (defined macro)
  printf("\n- a=%d, b=%d\n", a, b);                                                                         // Print a and b var vals

  int JOIN(a,1);                                                                                            // Call join variable name (defined macro)
  a1 = 9; printf("\n- a1=%d\n", a1);                                                                        // Define function val and print fbk

  printf("\n- %s, %d\n", MACRO2, LINE);                                                                     // Defined macro during compilin' step as command-line parameter --> gcc -DMACRONAME or gcc -DMACRONAME=val --> (gccW99_o preprocessor preprocessor.c -DLINE && ./preprocessor or gccW99_o preprocessor preprocessor.c -DLINE=7 && ./preprocessor)
  
  return EXIT_SUCCESS;                                                                                      // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Advanced preprocessing operations (simple macro functions definition)
 */
