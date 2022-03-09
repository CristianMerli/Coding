/*
 * Author: Cristian Merli
 * Code title: Lecture
 * Code version: 3.0
 * Creation date: 03/02/2022
 * Last mod. date: 09/02/2022
 */


/* Libraries */
#include "../lib/lecture/lib_lecture.h"                                                                     // Import lecture library header file
#include <limits> // ---

/* Namespaces */
using namespace std;                                                                                        // Include std namespace


/* Main cycle */
int main(){
  logo(30, "Lecture-01", YE, '#', GN);                                                                      // Print responsive-logo
  fbk_gn_cy("Ciao");                                                                                        // Print fbk
  /*---*/

  // Vars
  int age=0;
  bool x_flg=false;
  // User input
  while (!x_flg){
    std::cout << ">> Hi, enter your age and press ENTER..." << std::endl;
    std::cout << " -> Età: ";
    if(cin >> age){
      // Cout
      std::cout << std::endl << ">> You are: " << age << " years old." << std::endl;
      x_flg=true;
      break;
    } else {
      std::cout << std::endl << "PLEASE INSERT AN INTEGER NUMBER!" << std::endl << std::endl;
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  /*---*/
  close_bye();                                                                                              // Close SW with bye fbk
}
