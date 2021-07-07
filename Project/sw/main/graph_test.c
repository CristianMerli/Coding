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
 * Check old functions + verbose + source node memo + names
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
  C_real ar_costs_vect[] = {1.165, 2.165, 3.165, 4.165, 5.165, 6.165, 7.165, 8.165, 6.165, 0.165};          // Arches costs vector

  /* Code */
  signal(SIGINT, terminate_keyboard);                                                                       // Manage program exit from keyboard ctrl+c shortcut
  logo(6, "GRAPHS MANAGEMENT LIBRARY TEST SOFTWARE", LBU, '#', OG);                                         // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  press_enter("Hi");                                                                                        // Press enter to start SW fbk
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //                                          LIBRARY TEST SOFTWATRE                                        // --> TEST BEGIN
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Create some archs                                                                                      //
  add_new_arch(ar_costs_vect[0], "1");                                                                      // Create new arch (arch allocated inside heap)
  add_new_arch(ar_costs_vect[1], "2");                                                                      // "
  add_new_arch(ar_costs_vect[2], "3");                                                                      // "
  add_new_arch(ar_costs_vect[3], "4");                                                                      // "
  add_new_arch(ar_costs_vect[4], "5");                                                                      // "
  add_new_arch(ar_costs_vect[5], "6");                                                                      // "
  add_new_arch(ar_costs_vect[6], "7");                                                                      // "
  add_new_arch(ar_costs_vect[7], "8");                                                                      // "
  add_new_arch(ar_costs_vect[8], "9");                                                                      // "
  add_new_arch(ar_costs_vect[9], "10");                                                                     // "
  // Create some nodes                                                                                      //
  add_new_node("1");                                                                                        // Create new node (node allocated inside heap)
  add_new_node("2");                                                                                        // "
  add_new_node("3");                                                                                        // "
  add_new_node("4");                                                                                        // "
  add_new_node("5");                                                                                        // "
  add_new_node("6");                                                                                        // "
  add_new_node("7");                                                                                        // "
  add_new_node("8");                                                                                        // "
  add_new_node("9");                                                                                        // "
  add_new_node("10");                                                                                       // "
  // Connect archs & nodes (excluding node "10")                                                            //
  connect_node_arch(1, 1, ARCH_ND1, LIST_TAIL);                                                             // Connect arch1 to node1, non-zero index (new arch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(1, 2, ARCH_ND2, LIST_TAIL);                                                             // Connect arch1 to node2, non-zero index (new arch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(2, 1, ARCH_ND1, LIST_TAIL);                                                             // Connect arch2 to node1, non-zero index (new arch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(2, 3, ARCH_ND2, LIST_TAIL);                                                             // Connect arch2 to node3, non-zero index (new arch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(3, 1, ARCH_ND1, LIST_TAIL);                                                             // Connect arch3 to node1, non-zero index (new arch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(3, 4, ARCH_ND2, LIST_TAIL);                                                             // Connect arch3 to node4, non-zero index (new arch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(4, 1, ARCH_ND1, LIST_TAIL);                                                             // Connect arch4 to node1, non-zero index (new arch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(4, 5, ARCH_ND2, LIST_TAIL);                                                             // Connect arch4 to node5, non-zero index (new arch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(5, 5, ARCH_ND1, LIST_TAIL);                                                             // Connect arch5 to node5, non-zero index (new arch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(5, 6, ARCH_ND2, LIST_TAIL);                                                             // Connect arch5 to node6, non-zero index (new arch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(6, 6, ARCH_ND1, LIST_TAIL);                                                             // Connect arch6 to node6, non-zero index (new arch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(6, 7, ARCH_ND2, LIST_TAIL);                                                             // Connect arch6 to node7, non-zero index (new arch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(7, 6, ARCH_ND1, LIST_TAIL);                                                             // Connect arch7 to node6, non-zero index (new arch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(7, 8, ARCH_ND2, LIST_TAIL);                                                             // Connect arch7 to node8, non-zero index (new arch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(8, 8, ARCH_ND1, LIST_TAIL);                                                             // Connect arch8 to node8, non-zero index (new arch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(8, 9, ARCH_ND2, LIST_TAIL);                                                             // Connect arch8 to node9, non-zero index (new arch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(9, 1, ARCH_ND1, LIST_TAIL);                                                             // Connect arch9 to node1, non-zero index (new arch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(9, 7, ARCH_ND2, LIST_TAIL);                                                             // Connect arch9 to node7, non-zero index (new arch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(10, 1, ARCH_ND1, LIST_TAIL);                                                            // Connect arch10 to node1, non-zero index (new arch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(10, 6, ARCH_ND2, LIST_TAIL);                                                            // Connect arch10 to node6, non-zero index (new arch list element allocated inside heap, opt param --> arch pos, non-zero index)
  // Apply Dijkstra's algorithm and find some min paths                                                     //
  dijkstra_alg(1);                                                                                          // Apply Dijkstra alg using node "1" as source node
  buid_min_path(6);                                                                                         // -
  buid_min_path(9);                                                                                         // -
  // Apply Dijkstra's algorithm and find some min paths                                                     //
  dijkstra_alg(4);                                                                                          // Apply Dijkstra alg using node "4" as source node
  buid_min_path(8);                                                                                         // -
  buid_min_path(10);                                                                                        // -
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
