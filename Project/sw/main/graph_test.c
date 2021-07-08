/*
 * Author: Cristian Merli
 * Code title: Graph test
 * Code version: 1.0
 * Creation date: 22/06/2021
 * Last mod. date: 04/07/2021
 * 
 * 
 * // Compile-commands:
 * gccW99_lib lib/graph/lib_graph.so lib/graph/lib_graph.c                          --> Create GRAPH dynamic library object file
 * gccW99_lib lib/ui/lib_ui.so lib/ui/lib_ui.c                                      --> Create UI (TERMINAL I/O) dynamic library object file
 * gccW99_c main/graph_test.o main/graph_test.c                                     --> Create MAIN object file
 * 
 * // Link-command:
 * gccW99_o graph_test main/graph_test.o lib/graph/lib_graph.so lib/ui/lib_ui.so    --> LINK main and dynamic libraries object files to test executable
 * 
 * // Aliases:
 * alias gccW99_o="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -o"
 * alias gccW99_c="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -c -o"
 * alias gccW99_lib="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -fpic -shared -o"
 */


/* NOTES */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * Check old functions + verbose
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */


/* Libraries */
#include "../lib/graph/lib_graph.h"                                                                         // Import graph library header file


/* Constants */
//


/* Global vars */
//


/* Main routines */
static void terminate_keyboard(int signal){                                                                 // Manage program exit from keyboard ctrl+c shortcut
  /* Body */
  close_keyboard_interrupt(signal);                                                                         // Close SW with fbk due to keyboard interrupt detected (ctrl+c)
}


/* Main cycle */
int main(){                                                                                                 // SW main cycle
  /* Main vars */
  C_real strts_len_vect[] = {1.165, 2.165, 3.165, 4.165, 5.165, 6.165, 7.165, 8.165, 6.165, 0.165};         // Street-lenghts vector

  /* Code */
  signal(SIGINT, terminate_keyboard);                                                                       // Manage program exit from keyboard ctrl+c shortcut
  logo(6, "GRAPHS MANAGEMENT LIBRARY TEST SOFTWARE", LBU, '#', OG);                                         // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  press_enter("Hi");                                                                                        // Press enter to start SW fbk
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //                                          LIBRARY TEST SOFTWATRE                                        // --> TEST BEGIN
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Create some archs                                                                                      //
  add_new_arch(strts_len_vect[0], "Street1");                                                               // Create new street (arch allocated inside heap)
  add_new_arch(strts_len_vect[1], "Street2");                                                               // "
  add_new_arch(strts_len_vect[2], "Street3");                                                               // "
  add_new_arch(strts_len_vect[3], "Street4");                                                               // "
  add_new_arch(strts_len_vect[4], "Street5");                                                               // "
  add_new_arch(strts_len_vect[5], "Street6");                                                               // "
  add_new_arch(strts_len_vect[6], "Street7");                                                               // "
  add_new_arch(strts_len_vect[7], "Street8");                                                               // "
  add_new_arch(strts_len_vect[8], "Street9");                                                               // "
  add_new_arch(strts_len_vect[9], "Street10");                                                              // "
  // Create some nodes                                                                                      //
  add_new_node("Cross1");                                                                                   // Create new cross (node allocated inside heap)
  add_new_node("Cross2");                                                                                   // "
  add_new_node("Cross3");                                                                                   // "
  add_new_node("Cross4");                                                                                   // "
  add_new_node("Cross5");                                                                                   // "
  add_new_node("Cross6");                                                                                   // "
  add_new_node("Cross7");                                                                                   // "
  add_new_node("Cross8");                                                                                   // "
  add_new_node("Cross9");                                                                                   // "
  add_new_node("Cross10");                                                                                  // "
  // Connect archs & nodes (excluding node "10")                                                            //
  connect_node_arch("Street1", "Cross1", ARCH_ND1, LIST_TAIL);                                              // Connect "Street1" to "Cross1", (opt param --> arch pos, non-zero index)
  connect_node_arch("Street1", "Cross2", ARCH_ND2, LIST_TAIL);                                              // Connect "Street1" to "Cross2", (opt param --> arch pos, non-zero index)
  connect_node_arch("Street2", "Cross1", ARCH_ND1, LIST_TAIL);                                              // Connect "Street2" to "Cross1", (opt param --> arch pos, non-zero index)
  connect_node_arch("Street2", "Cross3", ARCH_ND2, LIST_TAIL);                                              // Connect "Street2" to "Cross3", (opt param --> arch pos, non-zero index)
  connect_node_arch("Street3", "Cross1", ARCH_ND1, LIST_TAIL);                                              // Connect "Street3" to "Cross1", (opt param --> arch pos, non-zero index)
  connect_node_arch("Street3", "Cross4", ARCH_ND2, LIST_TAIL);                                              // Connect "Street3" to "Cross4", (opt param --> arch pos, non-zero index)
  connect_node_arch("Street4", "Cross1", ARCH_ND1, LIST_TAIL);                                              // Connect "Street4" to "Cross1", (opt param --> arch pos, non-zero index)
  connect_node_arch("Street4", "Cross5", ARCH_ND2, LIST_TAIL);                                              // Connect "Street4" to "Cross5", (opt param --> arch pos, non-zero index)
  connect_node_arch("Street5", "Cross5", ARCH_ND1, LIST_TAIL);                                              // Connect "Street5" to "Cross5", (opt param --> arch pos, non-zero index)
  connect_node_arch("Street5", "Cross6", ARCH_ND2, LIST_TAIL);                                              // Connect "Street5" to "Cross6", (opt param --> arch pos, non-zero index)
  connect_node_arch("Street6", "Cross6", ARCH_ND1, LIST_TAIL);                                              // Connect "Street6" to "Cross6", (opt param --> arch pos, non-zero index)
  connect_node_arch("Street6", "Cross7", ARCH_ND2, LIST_TAIL);                                              // Connect "Street6" to "Cross7", (opt param --> arch pos, non-zero index)
  connect_node_arch("Street7", "Cross6", ARCH_ND1, LIST_TAIL);                                              // Connect "Street7" to "Cross6", (opt param --> arch pos, non-zero index)
  connect_node_arch("Street7", "Cross8", ARCH_ND2, LIST_TAIL);                                              // Connect "Street7" to "Cross8", (opt param --> arch pos, non-zero index)
  connect_node_arch("Street8", "Cross8", ARCH_ND1, LIST_TAIL);                                              // Connect "Street8" to "Cross8", (opt param --> arch pos, non-zero index)
  connect_node_arch("Street8", "Cross9", ARCH_ND2, LIST_TAIL);                                              // Connect "Street8" to "Cross9", (opt param --> arch pos, non-zero index)
  connect_node_arch("Street9", "Cross1", ARCH_ND1, LIST_TAIL);                                              // Connect "Street9" to "Cross1", (opt param --> arch pos, non-zero index)
  connect_node_arch("Street9", "Cross7", ARCH_ND2, LIST_TAIL);                                              // Connect "Street9" to "Cross7", (opt param --> arch pos, non-zero index)
  connect_node_arch("Street10", "Cross1", ARCH_ND1, LIST_TAIL);                                             // Connect "Street10" to "Cross1", (opt param --> arch pos, non-zero index)
  connect_node_arch("Street10", "Cross6", ARCH_ND2, LIST_TAIL);                                             // Connect "Street10" to "Cross6", (opt param --> arch pos, non-zero index)
  // Apply Dijkstra's algorithm and find some min paths (includin' some special cases)                      //
  dijkstra_alg("Cross4");                                                                                   // Apply Dijkstra alg using "Cross4" as source node (find all min path-costs and prev nodes in shortest paths)
  buid_shortest_path("Cross9");                                                                             // Reconstruct min path to "Cross9" startin' from "Cross4"
  dbg_print("Some special-cases examples:");                                                                // Print special-cases examples debug fbk
  buid_shortest_path("Cross4");                                                                             // Reconstruct min path to "Cross4" (src=dest) startin' from "Cross4"
  buid_shortest_path("Cross10");                                                                            // Reconstruct min path to "Cross10" (unreachble node) startin' from "Cross4"
  // Deallocate the whole graph structure                                                                   //
  free_graph();                                                                                             // Clear graph structure from heap and reset some flags to be able to use again lib functions
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //                                          LIBRARY TEST SOFTWATRE                                        // --> TEST END
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  close_fbk();                                                                                              // Close SW with fbk
  return EXIT_SUCCESS;                                                                                      // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/* 
 * Final project (G3 - number 3) --> Dijkstra.
 */
