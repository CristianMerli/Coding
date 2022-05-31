/*
 * Author: Cristian Merli
 * Code title: Lecture
 * Code version: 3.0
 * Creation date: 11/05/2022
 * Last mod. date: 31/05/2022
 * 
 * NOTES:
 * - This is a random class testing code (Room class).
 * - Comments marked with '---' pattern are incomplete!
 */


/* Dependencies */
#include "../lib/ui/lib_ui.hpp"                                                                             // Import UI (terminal I/O) library header file
#include "../lib/lecture/lib_lecture.hpp"                                                                   // Import lecture library header file


/* Namespaces */
using namespace std;                                                                                        // Include std namespace


/* Main routine to load command-line parameters [ADJUST TO DEFINE EXPECTED PARAM TYP] */
void load_param(C_integer argc, char *const argv[], Real p[], C_integer &p_sz, C_string p_str[]) {
  if (read_cl_param(argc, argv, p, p_sz))                                                                   // Command-line parameters management callin' dedicated function
    term_close_err("Try to insert "+S(p_sz)+" real value(s) as main command-line parameter(s)!");           // In case of ERR: close terminal UI with err fbk [ADJUST FOR DETAILED INFO]
  else for (Integer i=0; i<p_sz; ++i) term_print("Room "+p_str[i], p[i], "m");                              // In case of NO-ERR: print command-line parameters [ADJUST FOR DETAILED INFO]
  term_print_nl(1);                                                                                         // Print new-line
}


/* Main code-cycle start */
int main(const int argc, char *const argv[]) {


  // Print SW responsive-title on terminal
  term_print_title("Lecture-06", YE, '#', GN);                                                              // Print responsive-title on terminal (title-txt, title-col, bkg-char, bkg-col)

  // Load command-line parameters
  Real param[]={0, 0, 0}; C_string param_str[]={"length", "width", "height"};                               // Param vect declaration [ADJUST TO DEFINE EXPECTED PARAM TYP AND NUM]
  load_param(argc, argv, param, array_sz(param), param_str);                                                // Load command-line parameters

  // Test Room class
  Room A202={param[0], param[1], param[2]};                                                                 // Define room class obj usin' main command-line parameters
  term_print("Room area", A202.calc_area(), "m^2");                                                         // Print room area callin' dedicated room class method
  term_print("Room volume", A202.calc_volume(), "m^3");                                                     // Print room volume callin' dedicated room class method
  A202.add_people();                                                                                        // Add person in room callin' dedicated room class method
  A202.add_people(3);                                                                                       // Add people in room callin' dedicated room class method
  A202.rm_people();                                                                                         // Remove person from room callin' dedicated room class method
  A202.rm_people(2);                                                                                        // Remove people from room callin' dedicated room class method
  term_print("People in room", A202.get_people());                                                          // Print number of people in room callin' dedicated room class method
  A202.rm_all_people();                                                                                     // Remove all people from room callin' dedicated room class method
  term_print("Room is empty", (A202.is_empty() ? "YES" : "NO"));                                            // Print empty room fbk callin' dedicated room class method
  A202.add_people(26);                                                                                      // Add people in room callin' dedicated room class method
  term_print("People in room", A202.get_people());                                                          // Print number of people in room callin' dedicated room class method
  term_print("Room is full", (A202.is_full() ? "YES" : "NO"));                                              // Print full room fbk callin' dedicated room class method
  A202.add_people();                                                                                        // Add person in room callin' dedicated room class method
  term_print("People in room", A202.get_people());                                                          // Print number of people in room callin' dedicated room class method
  term_print("Room is full", (A202.is_full() ? "YES" : "NO"));                                              // Print full room fbk callin' dedicated room class method


  /* Main code-cycle end */
  term_close_bye();                                                                                         // Close terminal UI with bye fbk
}
