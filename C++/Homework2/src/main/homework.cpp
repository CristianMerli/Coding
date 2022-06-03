/*
 * Author: Cristian Merli
 * Code title: Homework2
 * Code version: 3.0
 * Creation date: 31/05/2022
 * Last mod. date: 03/06/2022
 * 
 * NOTES:
 * - This is a building management software.
 * - Comments marked with '---' pattern are incomplete!
 */


/* Dependencies */
#include "../lib/ui/lib_ui.hpp"                                                                             // Import UI (terminal I/O) library header file
#include "../lib/building/lib_building.hpp"                                                                 // Import building library header file


/* Namespaces */
using namespace std;                                                                                        // Include std namespace


/* Main routine to load command-line parameters [ADJUST TO DEFINE EXPECTED PARAM TYP] */
static void load_param(C_integer argc, char *const argv[], Real p[], C_integer &p_sz, C_string p_str[]) {
  if (read_cl_param(argc, argv, p, p_sz))                                                                   // Command-line parameters management callin' dedicated function
    term_close_err("Try to insert "+S(p_sz)+" real value(s) as main command-line parameter(s)!");           // In case of ERR: close terminal UI with err fbk [ADJUST FOR DETAILED INFO]
  else for (Byte i=0; i<p_sz; ++i) term_print("Param1 "+p_str[i], p[i]);                                    // In case of NO-ERR: print command-line parameters [ADJUST FOR DETAILED INFO]
  term_print_nl(1);                                                                                         // Print new-line
}


/* Main code-cycle start */
int main(const int argc, char *const argv[]) {

  // Print SW responsive-title on terminal
  term_print_title("Homework-2 Cristian Merli", YE, '#', GN);                                               // Print responsive-title on terminal (title-txt, title-col, bkg-char, bkg-col)

  // Load command-line parameters [UNUSED]
  Real param[]={0}; C_string param_str[]={"[UNUSED]"};                                                      // Param vect declaration [ADJUST TO DEFINE EXPECTED PARAM TYP AND NUM]
  load_param(argc, argv, param, array_sz(param), param_str);                                                // Load command-line parameters


  // *** BUILDING-LIB TEST *** //
  // Test-step-0: Random seed init and test fbk print
  random_init();                                                                                            // Initialize time-based seed to create random-values sequence
  term_print("*** BUILDING-LIB TEST ***");                                                                  // Print-test-fbk
  
  // Test-step-1: Init building
  term_print_nl();                                                                                          // Print new-line
  term_print("Test-step-1 -> Building details definition:");                                                // Print Test-step-fbk
  Building building={def_building_rooms_from_terminal()};                                                   // Define building object using building rooms collection from terminal
  
  // Test-step-2: Print building info
  term_print_nl();                                                                                          // Print new-line
  term_print("Test-step-2 -> Defined building:");                                                           // Print Test-step-fbk
  building.show_info();                                                                                     // Show building info
  
  // Test-step-3: Add random number of people 'till saturation
  Integer ppl;                                                                                              // Declare people-num var to add people into the building
  term_print_nl();                                                                                          // Print new-line
  term_print("Test-step-3 -> Addin' people into the building:");                                            // Print Test-step-fbk
  do {ppl=random_val<Integer>(1,4); term_print("Adding",ppl,"people");} while (!building.add_people(ppl));  // Add random number of people in the building 'till saturation
  
  // Test-step-4: Print building status
  term_print_nl();                                                                                          // Print new-line
  term_print("Test-step-4 -> Building status:");                                                            // Print Test-step-fbk
  building.show_info();                                                                                     // Show building info
  
  // Test-step-5: Empty building and print building status
  building.rm_all_people();                                                                                 // Empty building
  term_print_nl();                                                                                          // Print new-line
  term_print("Test-step-5 -> Fire alarm ringing, people evacuation completed, building status:");           // Print Test-step-fbk
  building.show_info();                                                                                     // Show building info
  
  // Test-step-6: Creating two rooms to test rooms 'add' operator
  Room room1=Room{6.2, 4.8, 2.75}, room2=Room{4.95, 4.8};                                                   // Create two rooms
  term_print_nl();                                                                                          // Print new-line
  term_print("Test-step-6 -> Creating two rooms to test rooms 'add' operator:");                            // Print Test-step-fbk
  term_print("Room1:");                                                                                     // Print room1 fbk
  room1.show_info();                                                                                        // Print room1 info
  term_print("Room2:");                                                                                     // Print room2 fbk
  room2.show_info();                                                                                        // Print room2 info
  
  // Test-step-7: Apply rooms 'add' operator
  Room room3=room1+room2;                                                                                   // Apply rooms add operator
  term_print_nl();                                                                                          // Print new-line
  term_print("Test-step-7 -> Apply 'add' operator:");                                                       // Print Test-step-fbk
  term_print("Room3=Room1+Room2:");                                                                         // Print room3 fbk
  room3.show_info();                                                                                        // Print room3 info


  /* Main code-cycle end */
  term_close_bye("Test successfully completed!");                                                           // Close terminal UI with bye fbk
}
