/*
 * Author: Cristian Merli
 * Code title: Lecture
 * Code version: 3.0
 * Creation date: 03/03/2022
 * Last mod. date: 24/03/2022
 */


/* Dependencies */
#include "../lib/lecture/lib_lecture.h"                                                                     // Import lecture library header file


/* Namespaces */
using namespace std;                                                                                        // Include std namespace


/* Main cycle */
int main(const int argc, char *const argv[]){
  title(10, "Lecture-01", YE, '#', GN);                                                                     // Print responsive-title
  /* Code-start */


  if (false && argv!=0) unused=argc;                                                                        // Avoid unused parameters error

  // Real temp=conv_c_k();                                                                                     // Funct to interactively convert temperature from [°C] to [K]
  // PRINT_VAL("The temperature is", temp, "K");                                                               // Print temperature [K]
  
  // Real temp=conv_c_f_f_c();                                                                                 // Funct to interactively convert temperature from [°C] to [F] or from [F] to [°C]
  // unused=(int)temp;                                                                                         // Avoid unused err
  
  // chk_if_div();                                                                                             // Funct to interactively check division

  // consecutive_num();                                                                                        // Funct to interactively plot consecutive numbers

  // fibonacci();                                                                                              // Funct to interactively print Fibonacci numbers


  /* Code-end */
  close_bye();                                                                                              // Close SW with bye fbk
}
