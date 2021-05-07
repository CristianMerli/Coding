/*
 * Author: Cristian Merli
 * Code title: Navigator
 * Code version: 3.0
 * Creation date: 04/05/2021
 * Last mod. date: 07/05/2021
 * 
 * 
 * // Compile-commands:
 * gccW99_lib lib/nav/lib_nav.so lib/nav/lib_nav.c            --> Create NAVIGATOR dynamic library object file
 * gccW99_lib lib/ui/lib_ui.so lib/ui/lib_ui.c                --> Create UI (TERMINAL I/O) dynamic library object file
 * gccW99_lib lib/timer/lib_timer.so lib/timer/lib_timer.c    --> Create TIMER dynamic library object file
 * gccW99_c navigator.c                                       --> Create SOFTWARE object file
 * 
 * // Link-command:
 * gccW99_o navigator navigator.o lib/nav/lib_nav.so lib/ui/lib_ui.so lib/timer/lib_timer.so  --> LINK software and dynamic libraries object files to executable
 */


/* Libraries */
#include "lib/nav/lib_nav.h"                                                                                // Import navigator library header file


/* Constants */
#define MIN_CHRS  3                                                                                         // Terminal input min chars val
#define EXIT_CHR  '.'                                                                                       // Terminal input exit char


/* Global vars */
street *strts_collec_ptr = NULL;                                                                            // Streets collection pointer var
cross *crss_collec_ptr = NULL;                                                                              // Crosses collection pointer var
u_int strts_num = 1, crss_num = 1;                                                                          // Streets and crosses number


/* Main routines */
static void create_map_streets_collection(){                                                                // Create map streets collection routine
  /* Body */
  char *in_str = NULL;                                                                                      // Terminal input string tmp var
  byte exit_flg = 0;                                                                                        // Terminal input while-loop exit flag

  // Define starting street inside streets collection
  press_enter("Create the virtual map before starting navigation");                                         // Press enter to start map definition fbk
  fbk_nl(1);  fbk_gn_cy("Define streets inside streets collection...");                                     // Print terminal input title fbk
  in_str = read_term_in_min_chrs(MIN_CHRS, "Enter starting street name", "Error! Starting street name");    // Read terminal input (min chars) function call
  strts_collec_ptr = create_strts_collection(strts_num, in_str);                                            // Create street and init streets collection (size 1) function call
  fbk_gn_lbu_ye_int("Ok! Value correctly saved! Number of saved streets", (int)strts_num);                  // Print terminal input OK fbk
  // Define the other streets inside streets collection
  do{
    fbk_nl(1);                                                                                              // New line fbk
    in_str = read_term_in_min_chrs_exit_chr(MIN_CHRS, "Enter other street names",
                                            "Error! Street name", EXIT_CHR);                                // Read terminal input (min chars and exit char) function call
    exit_flg = (in_str[0] == EXIT_CHR);                                                                     // Terminal input while-loop exit flag val upd
    if (!exit_flg){                                                                                         // Exit flag val check
      ++strts_num;                                                                                          // Street index in streets collection update
      strts_collec_ptr = realloc_strts_collection(strts_collec_ptr, strts_num);                             // Reallocate streets collection (change size) function call
      add_strt_in_strts_collection(strts_collec_ptr, in_str, strts_num-1);                                  // Add street in streets collection function
      fbk_gn_lbu_ye_int("Ok! Value correctly saved! Saved streets", (int)strts_num);                        // Print terminal input OK fbk
    } else {                                                                                                // In case of dynamic memory allocation error flag
      fbk_gn_cy("Streets correctly initialized!");                                                          // Print terminal input exit fbk
    }
  } while (!exit_flg);                                                                                      // Check while-loop exit flag
}


static void create_map_crosses_collection(){                                                                // Create map crosses collection routine
  /* Body */
  fbk_nl(2);  fbk_gn_cy("Define crosses inside crosses collection...");                                     // New line + print terminal input title fbk                                                                                                // New line fbk
  crss_num = (u_int)read_term_in_int_inrange(MIN_CRSS, MAX_CRSS, "Enter the number of crosses to create",
                                             "Error! The number of crosses in collection");                 // Read terminal input INT (in-range) function call
  crss_collec_ptr = create_crss_collection(crss_num);                                                       // Create and init crosses collection function call
  fbk_gn_lbu_ye_int("Ok! Cross correctly created! Number of created crosses", (int)crss_num);               // Print terminal input OK fbk
  fbk_nl(1);  fbk_gn_cy("Crosses correctly initialized!");                                                  // New line feedback + print terminal input exit fbk
}


static void build_map_conn(){                                                                               // Build map connections routine
  /* Body */
  char *in_str = NULL;                                                                                      // Terminal input string tmp var
  conn tmp_conn;                                                                                            // Temporary connection var
  
  // Define streets connections
  fbk_nl(2);  fbk_gn_cy("Define streets connections to street/cross/nothing...");                           // Print terminal input title fbk
  for (u_int i = 0; i < strts_num; ++i){                                                                    // Streets connections definition FOR cycle
    do{
      fbk_nl(1);  printf("%s>>> %sDefine the connection of street number %s%d%s --> %s%s: %s",
                          GN, PU, YE, (int)i+1, BU, YE, strts_collec_ptr[i].name, ER);                      // New line + definition info fbk
      printf("\n    %s[1] %sSTREET     %s[2] %sCROSS     %s[3] %sNONE%s",
              RD, OG, RD, OG, RD, OG, ER);                                                                  // Print connection options fbk
      in_str = read_term_in_min_chrs_exit_chr(1, "Define street connection type",
                                        "Error! The number of crosses in collection", EXIT_CHR);            // Read terminal input
      if (strcmp(in_str, "1") == 0){                                                                        // Street-to-street connection case
        print_strts_names_idxs(strts_collec_ptr, strts_num);                                                // Print streets names and indexes funciton call (as a table)
        int sel_strt = read_term_in_int_inrange(1, (int)strts_num, "Select street index",
                                            "Error! Street index");                                         // Select street idx
        if ((sel_strt-1) == (int)i){                                                                        // Infinite-loop detecting condition
          fbk_err("Infinite loop detected! A street can't be connected to itself, retry");                  // Infinite-loop detected fbk
          continue;                                                                                         // Retry
        }
        tmp_conn.strt = &strts_collec_ptr[sel_strt-1];                                                      // Define tmp connection with selected street idx in streets collection
        assign_conn_to_strt(&strts_collec_ptr[i], &tmp_conn, STREET);                                       // Pass tmp connection to street-to-street connection function
        break;                                                                                              // Exit street connections definition
      } else if (strcmp(in_str, "2") == 0){                                                                 // Street-to-cross connection case
        int sel_strt = read_term_in_int_inrange(1, (int)crss_num, "Select cross index",
                                            "Error! cross index");                                          // Select cross idx
        tmp_conn.cross = &crss_collec_ptr[sel_strt-1];                                                      // Define tmp connection with selected cross idx in crosses collection
        assign_conn_to_strt(&strts_collec_ptr[i], &tmp_conn, CROSS);                                        // Pass tmp connection to street-to-cross connection function
        break;                                                                                              // Exit street connections definition
      } else if (strcmp(in_str, "3") == 0 || in_str[0] == EXIT_CHR){                                        // Street-to-nothing connection case
        break;                                                                                              // Exit street connections definition
      } else {                                                                                              // Wrong answ case
        fbk_err("Error! Invalid option selected");                                                          // Error fbk
        continue;                                                                                           // Repeat question
      }
    } while(1);                                                                                             // Acquisition while-loop (exit only with breaks)
  }
  fbk_gn_cy("Streets connections correctly defined!");                                                      // Print terminal input exit fbk

  // Define crosses connections (streets in crosses)
  fbk_nl(2);  fbk_gn_cy("Define streets inside each cross...");                                             // Print terminal input title fbk
  for (u_int i = 0; i < crss_num; ++i){                                                                     // Crosses connections (streets in crosses) definition FOR cycle
    fbk_nl(1);  print_strts_names_idxs(strts_collec_ptr, strts_num);                                        // Print streets names and indexes funciton call (as a table)
    strts_in_crss pos = FIRST;                                                                              // Street position inside cross var
    do{
      fbk_nl(1);  printf("%s>>> %sDefine the street number %s%d%s inside cross number %s%d%s: %s",
                          GN, PU, YE, (int)pos+1, PU, YE, (int)i+1, PU, ER);                                // New lines + definition info fbk
      in_str = read_term_in_min_chrs_exit_chr(1, "Select street index",
                                              "Error! Street index", EXIT_CHR);                             // Read terminal input
      int sel_strt = atoi(in_str);                                                                          // Convert terminal input into int val
      if (in_str[0] == EXIT_CHR){                                                                           // check if terminal is == exit char
        ++pos;                                                                                              // Skip street in cross, increment street position inside cross counter
      } else if (sel_strt >= 1 && sel_strt <= (int)strts_num && sel_strt != 0) {                            // If val is in range
        assign_strt_to_crss(&strts_collec_ptr[sel_strt-1], &crss_collec_ptr[i], pos);                       // Assign street to cross in defined position function call
        ++pos;                                                                                              // Increment street position inside cross counter
      } else {                                                                                              // Wrong answ case
        fbk_err("Error! Invalid street selected");                                                          // Error fbk
      }
    } while(pos < STRTS_NUM);                                                                               // Acquisition while-loop (exit when all streets inside the cross has been corrtectly defined)
    print_crs_strts_names(&crss_collec_ptr[i]);                                                             // Print streets names inside cross
  }
}


static void navigate_in_map(){                                                                              // Navigate in map routine
  /* Body */
  press_enter("Starting navigation from the first defined street");                                         // Press enter to start navigation fbk
  fbk_gn_cy("Ready to navigate in created virtual map, starting navigation...");                            // Print terminal input title fbk
  navigate(strts_collec_ptr);                                                                               // Navigate through streets and crosses function call
  clear_map(strts_collec_ptr, crss_collec_ptr);                                                             // Clear map from heap (free allocated dyn memo) function call
  close_fbk();                                                                                              // Close feedback function call
}


/* Main cycle */
int main(){
  /* Main vars */
  //

  /* Code */
  logo(10, "CROSSES AND STREETS NAVIGATOR", YE, '#', GN);                                                   // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  create_map_streets_collection();                                                                          // Create map streets collection routine call
  create_map_crosses_collection();                                                                          // Create map crosses collection routine call
  build_map_conn();                                                                                         // Build map connections routine call
  navigate_in_map();                                                                                        // Navigate in map routine call

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/* 
 * Scrivere una libreria che gestisce la configurazione di incroci stradali
 * L'incrocio è caratterizzado da connettere 4 strade.
 * Ogni strada ha un nome ed è connessa a un elemento che può essere strada o un incrocio.
 * Scrivere un set di istruzioni che funzioni:
 * 1. Assegnare una strada ad un incrocio in una certa posizione.
 * 2. Assegnare a una strada cosa è connessa.
 * 3. Fare una funzione che partendo da una strada scelta percorre la strada mostrado il
 * nume della via percorsa fino ad incontrare un incrocio e a quel punto chiede all'utente 
 * di scegliere dove andare tra le strade disponibili nell'incrocio, termina quando la strada 
 * non è connessa a niente.
 */
