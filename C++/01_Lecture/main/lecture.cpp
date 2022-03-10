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
  title(30, "Lecture-01", YE, '#', GN);                                                                     // Print responsive-title
  
  unused=int_usr_in("Insert your age");                                                                     // Test req

  close_bye();                                                                                              // Close SW with bye fbk
}
