/*
 * Author: Cristian Merli
 * Code title: Function pointers
 * Code version: 3.0
 * Creation date: 24/05/2021
 * Last mod. date: 24/05/2021
 */ 


/* Libraries */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <stdlib.h>                                                                                         // Standard library inclusion (EXIT_SUCCESS, EXIT_FAILURE)


/* Functions */
int function(int val1, int val2);                                                                           // Function declaration

int function(int val1, int val2){                                                                           // Function implementation
  /* Body */
  return val1 + val2;                                                                                       // Return vals sum
}

int (*ptr_function)(int, int);                                                                              // Function pointer declaration (parenthesis between 'ptr_function' is essential to distinguish from function with ptr return)

int (*ptr_vect_funtions[3])(int, int);                                                                      // Vector of function pointers

//////////

double sum(double val1, double val2){                                                                       // Sum function
  /* Body */
  return val1 + val2;                                                                                       // Return sum result
}

double sub(double val1, double val2){                                                                       // Subtract function
  /* Body */
  return val1 - val2;                                                                                       // Return subtraction result
}

double mul(double val1, double val2){                                                                       // Multiplicate function
  /* Body */
  return val1 * val2;                                                                                       // Return multiplication result
}

double dvs(double val1, double val2){                                                                       // Divide function
  /* Body */
  return val1 / val2;                                                                                       // Return division result
}

double (*operations[4])(double, double);                                                                    // Operations vector of function pointers

typedef enum oper {SUM, SUB, MUL, DIV} oper;                                                                // Operations enum

char *oper_str[] = {"+", "-", "*", "/"};                                                                    // Operation enum strings vector

//////////

double operation(double (*op[])(double, double), oper operation, double val1, double val2){                 // Functions ptr might be used as function parameter
  /* Body */
  return op[operation](val1, val2);                                                                         // Return the result of the specified operation between val1 and val2
}

//////////

double (*ret_op(char chr))(double, double){                                                                 // Function which takes a char input and returns a function ptr
  switch (chr)                                                                                              // Char switch-case
  {
  case '+':                                                                                                 // Case sum char
    return sum;                                                                                             // Return sum function
  /////////
  case '-':                                                                                                 // Case subtraction char
    return sub;                                                                                             // Return subtraction function
  /////////
  case '*':                                                                                                 // Case multiplication char
    return mul;                                                                                             // Return multiplication function
  /////////
  case '/':                                                                                                 // Case division char
    return dvs;                                                                                             // Return division function
  ////////
  default:                                                                                                  // Case unknown char
    perror("Error in operation function call by char, unknown char!");                                      // Print perror
    exit(1);                                                                                                // Terminate program
  }
}

//////////

typedef double (*fun)(double, double);                                                                      // Function ptr typedef

fun (*ptr_ret_op)(char);                                                                                    // Function ptr declaration which returns function ptr


/* Main cycle */
int main(){
  /* Main vars */
  double vect[] = {2.0, 3.0, 4.0, 5.0}, res = 0;                                                            // Double vars for operations vector of function ptrs test

  /* Code */
  ptr_function = function;                                                                                  // Function pointer direct definition (by val)
  ptr_function = &function;                                                                                 // Function pointer direct definition (by ref)
  printf("%d + %d = %d\n", 4, 5, ptr_function(4,5));                                                        // Function pointer direct implementation example (by val)
  printf("%d + %d = %d\n", 4, 5, (*ptr_function)(4,5));                                                     // Function pointer direct implementation example (by ref)
  ptr_vect_funtions[0] = function;                                                                          // Vector of function pointers definition
  printf("%d + %d = %d\n", 4, 5, ptr_vect_funtions[0](4,5));                                                // Vector of function pointers implementation example
  printf("\n");                                                                                             // New line fbk
  //////////
  operations[0] = sum;                                                                                      // First operation's element vector of function ptrs definition
  operations[1] = sub;                                                                                      // Second operation's element vector of function ptrs definition
  operations[2] = mul;                                                                                      // Third operation's element vector of function ptrs definition
  operations[3] = dvs;                                                                                      // Fourth operation's element vector of function ptrs definition
  for (int i = 0; i < (int)(sizeof(operations)/sizeof(double)); ++i){                                       // Functions call FOR cycle
    printf("%lf %s %lf = ", res, oper_str[i], vect[i]);                                                     // Print calc fbk
    res = operations[i](res, vect[i]);                                                                      // Calc res
    printf("%lf\n", res);                                                                                   // Print calc res fbk
  }
  printf("\n");                                                                                             // New line fbk
  //////////
  printf("%lf\n", operation(operations, SUM, 5, 6));                                                        // Operation function call example
  printf("\n");                                                                                             // New line fbk
  //////////
  double (*ptr_funct)(double, double) = ret_op('+');                                                        // Return operation function call example
  printf("%lf\n", ptr_funct(5, 6));                                                                         // Print return operation function call result
  //////////
  ptr_ret_op = ret_op;                                                                                      // Function pointer indirect definition (by val) --> Points to 'ret_op(char chr)' function
  ptr_ret_op = &ret_op;                                                                                     // Function pointer indirect definition (by ref) --> Points to 'ret_op(char chr)' function

  return EXIT_SUCCESS;                                                                                      // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Function pointers
 */
