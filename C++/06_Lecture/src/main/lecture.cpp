/*
 * Author: Cristian Merli
 * Code title: Lecture
 * Code version: 3.0
 * Creation date: 11/05/2022
 * Last mod. date: 21/05/2022
 * 
 * NOTES:
 * - Random class test (rooms).
 * - Lines containing '---' pattern in comment must be adjusted!
 */


/* Dependencies */
#include "../lib/ui/lib_ui.h"                                                                               // Import UI (terminal I/O) library header file
#include "../lib/lecture/lib_lecture.h"                                                                     // Import lecture library header file


/* Namespaces */
using namespace std;                                                                                        // Include std namespace


/* Global objects and object-ptrs */
static const Term t={"Lecture-06", YE, '#', GN}; C_terminal term=&t;                                        // Initialize terminal UI obj and obj-ptr, printin' responsive-title [TITLE-TXT, TITLE-COL, BKG-CHAR, BKG-COL]


/* Main routine to read command-line parameters (returns err flg) */
static Boolean read_cl_param(C_integer &argc, char *const argv[], Real param[], C_integer &param_sz) {
  Boolean err_flg=false;                                                                                    // Err flag declaration
  term->print("Loading main command-line parameter(s)... [l, w, h]");                                       // Print oper fbk [EDIT INFO]
  if (argc-1==param_sz) {                                                                                   // Chk for expected num of main param
    ALLOC(String, p, argc-1);                                                                               // Allocate commands str dyn vect inside heap
    for (Integer i=1; i<argc; ++i) {                                                                        // Param scrollin' cycle (skip prg name)
      p[i-1]=argv[i];                                                                                       // Def commands str vect
      err_flg=term->chk_numeric_str(p[i-1], "Expecting real value, not char! [Param"+S(i)+": "+p[i-1]+"]"); // Chk each param str character to make sure it's numeric
      if (!err_flg) param[i-1]=atof(argv[i]); else break;                                                   // If everything is ok conv param into out var, while in case of err flg set xit param scrollin' cycle
    } DEALLOC(p);                                                                                           // Deallocate commands str dyn vect from heap
  } else {                                                                                                  // Case wrong num of param
    term->print("Wrong param num in main funct-call: expecting "+S(param_sz)+", got "+S(argc-1)+"!", ERR);  // Print err fbk
    err_flg=true;                                                                                           // Set err flg
  }
  return (!err_flg) ? EXIT_SUCCESS : EXIT_FAILURE;                                                          // If err flg ain't set: return OK code else if err flg is set: return ERR code
}


/* Main code-cycle start */
int main(const int argc, char *const argv[]) {


  // Load main parameters
  Real param[]={0, 0, 0}; C_integer param_sz=ARRAY_SZ(param);                                               // Param vect declaration and num of expected param calc [ADJUST TO DEFINE EXPECTED PARAM NUM]
  if (read_cl_param(argc, argv, param, param_sz))                                                           // Command-line parameters management
    term->close_err("Try to insert "+S(param_sz)+" real value(s) as main command-line parameter(s)!");      // In case of ERR: close terminal UI with err fbk
  else for (size_t i=0; i<param_sz; ++i) term->print("param["+S(i)+"]", param[i], "m");                     // In case of NO-ERR: print main param
  term->print_nl(1);                                                                                        // Print new-line

  // Test Room class
  Room A202={param[0], param[1], param[2], term};                                                           // Define room class obj usin' main command-line parameters
  term->print("Room area", A202.calc_area(), "m^2");                                                        // Print room area callin' dedicated room class method
  term->print("Room volume", A202.calc_volume(), "m^3");                                                    // Print room volume callin' dedicated room class method
  A202.add_people();                                                                                        // Add person in room callin' dedicated room class method
  A202.add_people(3);                                                                                       // Add people in room callin' dedicated room class method
  A202.rm_people();                                                                                         // Remove person from room callin' dedicated room class method
  A202.rm_people(2);                                                                                        // Remove people from room callin' dedicated room class method
  term->print("People in room", A202.get_people());                                                         // Print number of people in room callin' dedicated room class method
  A202.rm_all_people();                                                                                     // Remove all people from room callin' dedicated room class method
  term->print("Room is empty", (A202.is_empty() ? "YES" : "NO"));                                           // Print empty room fbk callin' dedicated room class method
  A202.add_people(26);                                                                                      // Add people in room callin' dedicated room class method
  term->print("People in room", A202.get_people());                                                         // Print number of people in room callin' dedicated room class method
  term->print("Room is full", (A202.is_full() ? "YES" : "NO"));                                             // Print full room fbk callin' dedicated room class method
  A202.add_people();                                                                                        // Add person in room callin' dedicated room class method
  term->print("People in room", A202.get_people());                                                         // Print number of people in room callin' dedicated room class method
  term->print("Room is full", (A202.is_full() ? "YES" : "NO"));                                             // Print full room fbk callin' dedicated room class method

  TERM_ACQ_CYCLE(Integer a, get_integer("Insert a"), a<0, "The value of a must be positive!");              // ---

  /* Main code-cycle end */
  term->close_bye();                                                                                        // Close terminal UI with bye fbk
}
