/*
 * Author: Cristian Merli
 * Code title: Lecture
 * Code version: 3.0
 * Creation date: 03/02/2022
 * Last mod. date: 09/02/2022
 */


/* Dependencies */
#include "../lib/lecture/lib_lecture.h"                                                                     // Import lecture library header file


/* Namespaces */
using namespace std;                                                                                        // Include std namespace


/* Main cycle */
int main(){
  title(10, "Lecture-01", YE, '#', GN);                                                                     // Print responsive-title
  /* Code-start */
  

  // Real temp=conv_c_k();                                                                                     // Funct to interactively convert temperature from [°C] to [K]
  // PRINT_VAL("The temperature is", temp, "K");                                                               // Print temperature [K]
  
  // Real temp=conv_c_f_f_c();                                                                                 // Funct to interactively convert temperature from [°C] to [F] or from [F] to [°C]
  // temp=temp;                                                                                                // Avoid unused err
  
  // chk_if_div();                                                                                             // Funct to interactively check division

  // print_vals();                                                                                             // Funct to interactively print numbers

  fibonacci();                                                                                              // Funct to interactively print Fibonacci numbers

  // Real sol=solve_first_deg_eqn();                                                                           // Funct to interactively solve 1st degree equations
  // PRINT_VAL("The equation solution is", sol, "");                                                           // Print equation solution

  // Real sol=solve_second_deg_eqn();                                                                          // Funct to interactively solve 2nd degree equations
  // PRINT_VAL("The equation solution is", sol, "");                                                           // Print equation solution

  // Complex sol=solve_second_deg_eqn_complex();                                                               // Funct to interactively solve 2nd degree equations with complex solutions
  // PRINT_VAL("The equation solution is", sol, "");                                                           // Print equation solution

  // void multilang_gm();                                                                                      // Funct to interactively say 'good morning' in specified language
  
  // Integer num=num_guesser();                                                                                // Funct to interactively guess number (from 0 to 7)
  // PRINT_VAL("The number is", num, "");                                                                      // Print equation solution


  /* Code-end */
  close_bye();                                                                                              // Close SW with bye fbk
}
