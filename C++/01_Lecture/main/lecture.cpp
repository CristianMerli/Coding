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
  // Integer age=0;                                                                                            // Test val
  // get_val("Insert your age", INTEGER, &age);                                                                // Test req
  // print_val("Your age is", age, "years old");                                                               // Test answ chk
  /* Code-end */
  close_bye();                                                                                              // Close SW with bye fbk
}
