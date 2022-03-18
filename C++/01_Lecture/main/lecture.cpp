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
  
  // Real temp=conv_c_k();                                                                                     // Interactively convert temperature from [°C] to [K]
  // print_val("The temperature is", temp, "K");                                                               // Print temperature [K]
  
  // Real temp=conv_c_f_f_c();                                                                                 // Interactively convert temperature from [°C] to [F] or from [F] to [°C]
  // temp=temp;                                                                                                // Avoid unused err
  
  //chk_if_div();                                                                                             // Funct to interactively check division
  
  Real sol=solve_first_deg_eqn();                                                                           // Funct to interactively solve 1st degree equations
  print_val("The equation solution is", sol);                                                               // Print equation solution

  /* Code-end */
  close_bye();                                                                                              // Close SW with bye fbk
}
