/*
 * Author: Cristian Merli
 * Code title: Lecture
 * Code version: 3.0
 * Creation date: 24/03/2022
 * Last mod. date: 27/03/2022
 */


/* Dependencies */
#include "../lib/lecture/lib_lecture.h"                                                                     // Import lecture library header file


/* Namespaces */
using namespace std;                                                                                        // Include std namespace


/* Main cycle */
int main(int argc, char *const argv[]){
  title(10, "Lecture-02", YE, '#', GN);                                                                     // Print responsive-title
  /* Code-start */


  if(false && argv!=0) unused=argc;                                                                         // Avoid unused parameters error

  // Integer n=0, div=0;                                                                                       // Number and divisor declaration
  // ACQ_CYCLE("Insert a value to check if it's prime", INTEGER, n, n<1, "Error, value must be positive!");    // Number def
  // div=is_prime(n);                                                                                          // Chk if num is prime
  // if(div!=1) PRINT_VAL("The given number ain't prime and one of its divisors is", div);                     // If not prime, print div

  Real a=0.0, b=0.0, x=0.0;                                                                                 // Eqn vars declaration
  ACQ_CYCLE("Insert 'a' parameter in ax+b=0 equation", REAL, a, false, "");                                 // Eqn 'a' param def
  ACQ_CYCLE("Insert 'b' parameter in ax+b=0 equation", REAL, b, false, "");                                 // Eqn 'b' param def
  x=solve_first_deg_eqn(a, b);                                                                              // Funct to solve 1st degree equations (ax+b=0)
  PRINT_VAL("The equation solution (x) is", x);                                                             // Print equation solution

  // Real sol=solve_second_deg_eqn();                                                                          // Funct to solve 2nd degree equations
  // PRINT_VAL("The equation solution is", sol);                                                               // Print equation solution

  // Complex sol=solve_second_deg_eqn_complex();                                                               // Funct to solve 2nd degree equations with complex solutions
  // PRINT_VAL("The equation solution is", sol);                                                               // Print equation solution

  // void multilang_gm();                                                                                      // Funct to say 'good morning' in specified language
  
  // Integer num=num_guesser();                                                                                // Funct to guess number (from 0 to 7)
  // PRINT_VAL("The number is", num);                                                                          // Print equation solution


  /* Code-end */
  close_bye();                                                                                              // Close SW with bye fbk
}
