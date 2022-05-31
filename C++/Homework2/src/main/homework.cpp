/*
 * Author: Cristian Merli
 * Code title: Homework2
 * Code version: 0.0
 * Creation date: 31/05/2022
 * Last mod. date: 31/05/2022
 * 
 * NOTES:
 * - This is ---.
 * - Lines marked with '---' pattern are incomplete!
 */


/* Dependencies */
#include "../lib/ui/lib_ui.hpp"                                                                             // Import UI (terminal I/O) library header file
#include "../lib/lecture/lib_lecture.hpp"                                                                   // --- Import lecture library header file


/* Namespaces */
using namespace std;                                                                                        // Include std namespace


/* Main routine to load command-line parameters [ADJUST TO DEFINE EXPECTED PARAM TYP] */
void load_param(C_integer argc, char *const argv[], Real p[], C_integer &p_sz, C_string p_str[]) {
  if (read_cl_param(argc, argv, p, p_sz))                                                                   // Command-line parameters management callin' dedicated function
    term_close_err("Try to insert "+S(p_sz)+" real value(s) as main command-line parameter(s)!");           // --- In case of ERR: close terminal UI with err fbk [ADJUST FOR DETAILED INFO]
  else for (Integer i=0; i<p_sz; ++i) term_print("Room "+p_str[i], p[i], "m");                              // --- In case of NO-ERR: print command-line parameters [ADJUST FOR DETAILED INFO]
  term_print_nl(1);                                                                                         // Print new-line
}


/* Main code-cycle start */
int main(const int argc, char *const argv[]) {


  // Print SW responsive-title on terminal
  term_print_title("Homework-2 Cristian Merli", YE, '#', GN);                                               // Print responsive-title on terminal (title-txt, title-col, bkg-char, bkg-col)

  // Load command-line parameters
  Real param[]={0, 0, 0}; C_string param_str[]={"length", "width", "height"};                               // --- Param vect declaration [ADJUST TO DEFINE EXPECTED PARAM TYP AND NUM]
  load_param(argc, argv, param, array_sz(param), param_str);                                                // Load command-line parameters

  // Test ---
  // ---


  /* Main code-cycle end */
  term_close_bye();                                                                                         // Close terminal UI with bye fbk
}
