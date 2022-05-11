/*
 * Author: Cristian Merli
 * Code title: Lecture
 * Code version: 3.0
 * Creation date: 11/05/2022
 * Last mod. date: 11/05/2022
 */


/* Dependencies */
#include "../lib/ui/lib_ui.h"                                                                               // Import UI (terminal I/O) library header file
#include "../lib/lecture/lib_lecture.h"                                                                     // Import lecture library header file


/* Namespaces */
using namespace std;                                                                                        // Include std namespace


/* Main routines */
static Integer read_cl_param(C_integer &argc, char *const argv[], Real param[], C_integer &param_sz){       // Routine to read command-line parameters (return err flg)
  Boolean err_flg=false;                                                                                    // Err flag declaration
  term_print("Loading main command-line parameter(s)... [l, w, h]");                                        // Print oper fbk
  if (argc-1==param_sz){                                                                                    // Chk for expected num of main param
    ALLOC(String, p, argc-1);                                                                               // Allocate commands str dyn vect inside heap
    for (Integer i=1; i<argc; ++i){                                                                         // Param scrollin' cycle (skip prg name)
      p[i-1]=argv[i];                                                                                       // Def commands str vect
      err_flg=chk_num_str(p[i-1], "Expecting real value, not char! [Param"+S(i)+": "+p[i-1]+"]");           // Chk each param str chr to make sure it's numeric
      if (!err_flg) param[i-1]=atof(argv[i]); else break;                                                   // If everything is ok conv param into out var, while in case of err flg set xit param scrollin' cycle
    }
    DEALLOC(p);                                                                                             // Deallocate commands str dyn vect from heap
  } else {                                                                                                  // Case wrong num of param
    term_print("Wrong param num in main funct-call: expecting "+S(param_sz)+", got "+S(argc-1)+"!", ERR);   // Print err fbk
    err_flg=true;                                                                                           // Set err flg
  }
  return (!err_flg) ? EXIT_SUCCESS : EXIT_FAILURE;                                                          // If err flg ain't set: return OK code else if err flg is set: return ERR code
}


/* Main cycle */
int main(const int argc, char *const argv[]){
  term_title(10, "Lecture-06", YE, '#', GN);                                                                // Print responsive-title on terminal
  /* Code-start */


  // Load main parameters
  Real param[]={0,0,0}; C_integer param_sz=ARRAY_SZ(param);                                                 // Param vect declaration and calc num of expected param [adjust to define expected param num]
  if (read_cl_param(argc,argv,param,param_sz))                                                              // Command-line parameters management
    close_err("Try to insert "+S(param_sz)+" real value(s) as main command-line parameter(s)!");            // In case of ERR: close SW with err fbk
  else for (size_t i=0; i<param_sz; ++i) TERM_PRINT_VAL("param["+S(i)+"]", param[i], "m");                  // In case of NO-ERR: print main param
  TERM_NL(1);                                                                                               // New-line fbk

  // Test classes
  Room A202(param[0], param[1], param[2]);                                                                  // Define room class obj usin' main command-line parameters
  TERM_PRINT_VAL("Room area", A202.calc_area(), "m^2");                                                     // Print room area callin' dedicated room class method
  TERM_PRINT_VAL("Room volume", A202.calc_volume(), "m^3");                                                 // Print room volume callin' dedicated room class method
  A202.add_person();                                                                                        // Add person in room callin' dedicated room class method
  A202.add_person(3);                                                                                       // Add people in room callin' dedicated room class method
  A202.rm_person();                                                                                         // Remove person from room callin' dedicated room class method
  A202.rm_person(2);                                                                                        // Remove people from room callin' dedicated room class method
  TERM_PRINT_VAL("People in room", A202.get_people());                                                      // Print number of people in room callin' dedicated room class method
  A202.rm_all_people();                                                                                     // Remove all people from room callin' dedicated room class method
  TERM_PRINT_VAL("Room is empty", (A202.is_empty() ? "YES" : "NO"));                                        // Print empty room fbk callin' dedicated room class method
  A202.add_person(26);                                                                                      // Add people in room callin' dedicated room class method
  TERM_PRINT_VAL("People in room", A202.get_people());                                                      // Print number of people in room callin' dedicated room class method
  TERM_PRINT_VAL("Room is full", (A202.is_full() ? "YES" : "NO"));                                          // Print full room fbk callin' dedicated room class method
  A202.add_person();                                                                                        // Add person in room callin' dedicated room class method
  TERM_PRINT_VAL("People in room", A202.get_people());                                                      // Print number of people in room callin' dedicated room class method
  TERM_PRINT_VAL("Room is full", (A202.is_full() ? "YES" : "NO"));                                          // Print full room fbk callin' dedicated room class method


  /* Code-end */
  close_bye();                                                                                              // Print software closing fbk
}

/*
 * Classe che rappresenti stanza
 * Attributi: dimensioni (l, w, h)
 * Metodi: costruttore, calcolo area, calcolo volume, distruttore
 */