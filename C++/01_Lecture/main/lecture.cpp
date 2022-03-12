/*
 * Author: Cristian Merli
 * Code title: Lecture
 * Code version: 3.0
 * Creation date: 03/02/2022
 * Last mod. date: 09/02/2022
 */


/* Libraries */
#include "../lib/lecture/lib_lecture.h"                                                                     // Import lecture library header file


/* Namespaces */
using namespace std;                                                                                        // Include std namespace


/* Main cycle */
int main(){
  title(10, "Lecture-01", YE, '#', GN);                                                                     // Print responsive-title
  /* Code-start */
  int age=get_val("Insert your age", REAL);                                                                 // Test req
  print_val("Your age is", age);                                                                            // Test answ chk
  /* Code-end */
  close_bye();                                                                                              // Close SW with bye fbk
}
