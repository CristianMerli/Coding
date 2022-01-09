/*
 * Author: Cristian Merli
 * Code title: Variable number of function parameters
 * Code version: 3.0
 * Creation date: 24/05/2021
 * Last mod. date: 24/05/2021
 */ 


/* Libraries */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <stdlib.h>                                                                                         // Standard library inclusion (EXIT_SUCCESS, EXIT_FAILURE)
#include <stdarg.h>                                                                                         // Standard drag library inclusion (for variable number of function parameters)


/* Functions */
double funct(int a, int b, double c, ... ){                                                                 // The '...' notation, indicates that the function accepts a variable number of parameters, but at least 3 (a, b and c)
  /* Body */
  va_list args;                                                                                             // Var to scroll the optinal function parameters
  va_start(args, c);                                                                                        // Function to define where the variable number of function parameters starts (after the last known param --> in this case, c)
  char* str = va_arg(args, char*);                                                                          // Read one optional parameter (each time it's called) --> Pay attention, the number of parameters must be managed by the programmer, the complier won't help
  char chr = (char)va_arg(args, int);                                                                       // Read one optional parameter (each time it's called) --> char MUST be passed as int and then casted into char
  float num = (float)va_arg(args, double);                                                                  // Read one optional parameter (each time it's called) --> float MUST be passed as double and then casted into float
  va_end(args);                                                                                             // Reset params list

  printf("\n- The first optional parameter is: \"%s\"\n", str);                                             // Print first optional param fbk
  printf("\n- The second optional parameter is: '%c'\n", chr);                                              // Print second optional param fbk
  printf("\n- The third optional parameter is: %f\n", num);                                                 // Print third optional param fbk

  return a+b+c;                                                                                             // Random function return
}

//////////

double sum(int argc, ...){                                                                                  // Function to sum a variable number of parameters vals
  /* Body */
  va_list args_lst;                                                                                         // Params list
  va_start(args_lst, argc);                                                                                 // Define params list start
  double tot_sum = 0.0;                                                                                     // Tot sum of params vals

  while(argc--)                                                                                             // Scroll the params list
    tot_sum += va_arg(args_lst, double);                                                                    // Sum params vals
  va_end(args_lst);                                                                                         // Reset params list

  return tot_sum;                                                                                           // Return the tot sum of params vals
}


/* Main cycle */
int main(){
  /* Main vars */
  //

  /* Code */
  funct(1, 2, 3, "Hi", 'k', 7.2);                                                                           // Call to a function with a variable number of parameters
  //////////
  printf("\n- The sum of the defined variable number of parameters vals is: %lf\n", sum(2, 2.5, 3.2));      // Sum a variable number of parameters vals function call

  return EXIT_SUCCESS;                                                                                      // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Variable number of function parameters
 */
