/*
 * Author: Cristian Merli
 * Code title: Keywords (define, const, static, extern)
 * Code version: 3.0
 * Creation date: 18/05/2021
 * Last mod. date: 18/05/2021
 */ 


/* Libraries */
#include <stdio.h>                                                                                          // Standard I/O library inclusion


/* Constants */
//// DEFINE ////
#define DIM 5                                                                                               // Value will be replaced durin' compilin' process


/* Functions */
void funct(int *p){                                                                                         // Random function
  /* Body */
  //// STATIC IN FUNCTIONS ////
  static int count = 0;                                                                                     // Allocated int after instructions and literals (b4 heap and stack) --> allocated during program call and not during function call
  ++count;                                                                                                  // Val saved in static memo data (example used to count the number of times function has been called, but it's not a globar var)
}


//// STATIC IN LIBRARIES ////
static int a = 0;                                                                                           // Var accessible only in this file (if used in lib, not accessible in main)
static void funct2(){                                                                                       // Function accessible only in this file (if used in lib, not accessible in main)
  printf("Ciao");                                                                                           // Random command
}
//// EXTERN IN LIBRARIES ////
extern int g;                                                                                               // Variable decleared as non-local in lib file, make it accessible from main (this in .h file, while normal var declaration and definition in lib .c file)


/* Main cycle */
int main(){
  /* Main vars */
  //

  /* Code */
  //// CONST ////
  int c;                                                                                                    // Random int var
  const int r = 3;                                                                                          // Random const int var (different from define, this allocates memo) --> 'const int' and 'int const' are equivalent
  const int *a = &c;                                                                                        // Can't modify c contennt through 'a' ptr (dereferencing operation not allowed for const int ptrs)
                                                                                                            // --> sometimes used in function parameters (to pass ptrs in read only mode), but pointed addr can be changed
  int *const d = &c;                                                                                        // Const ptr, this don't allow ptr addr modification
  const int *const p = &c;                                                                                  // Constant ptr address and constant value (dereferencing operation and address value modification not allowed)
}



/* Task */
/* 
 * Keywords (define, const, static, extern)
 */
