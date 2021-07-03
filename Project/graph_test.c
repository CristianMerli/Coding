/*
 * Author: Cristian Merli
 * Code title: Graph test
 * Code version: 1.0
 * Creation date: 22/06/2021
 * Last mod. date: 03/07/2021
 * 
 * 
 * // Compile-commands:
 * gccW99_lib lib/graph/lib_graph.so lib/graph/lib_graph.c                    --> Create GRAPH dynamic library object file
 * gccW99_lib lib/ui/lib_ui.so lib/ui/lib_ui.c                                --> Create UI (TERMINAL I/O) dynamic library object file
 * gccW99_c graph_test.c                                                      --> Create MAIN object file
 * 
 * // Link-command:
 * gccW99_o graph_test graph_test.o lib/graph/lib_graph.so lib/ui/lib_ui.so   --> LINK main and dynamic libraries object files to executable
 * 
 * // Aliases:
 * alias gccW99_o="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -o"
 * alias gccW99_c="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -c"
 * alias gccW99_lib="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -fpic -shared -o"
 */


/* NOTES */
/*
 * Check old functions
 * Manage path in Dijkstra dataset 
 */


/* Libraries */
#include "lib/graph/lib_graph.h"                                                                            // Import graph library header file


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
  C_real ar_costs_vect[] = {1.165, 2.165, 3.165, 4.165, 5.165, 6.165, 7.165, 8.165};                        // Arches costs vector

  /* Code */
  signal(SIGINT, terminate_keyboard);                                                                       // Manage program exit from keyboard ctrl+c shortcut
  logo(6, "GRAPHS MANAGEMENT LIBRARY TEST SOFTWARE", YE, '#', GN);                                          // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  press_enter("Hi");                                                                                        // Press enter to start SW fbk
  
  // Create & connect nodes/arches - test functions number 1, 2 and 3
  add_new_arch(ar_costs_vect[0]);                                                                           // Create new arch (arch allocated inside heap)
  add_new_arch(ar_costs_vect[1]);                                                                           // Create new arch (arch allocated inside heap)
  add_new_arch(ar_costs_vect[2]);                                                                           // Create new arch (arch allocated inside heap)
  add_new_arch(ar_costs_vect[3]);                                                                           // Create new arch (arch allocated inside heap)
  add_new_arch(ar_costs_vect[4]);                                                                           // Create new arch (arch allocated inside heap)
  add_new_arch(ar_costs_vect[5]);                                                                           // Create new arch (arch allocated inside heap)
  add_new_arch(ar_costs_vect[6]);                                                                           // Create new arch (arch allocated inside heap)
  add_new_arch(ar_costs_vect[7]);                                                                           // Create new arch (arch allocated inside heap)
  for (int i = 0; i < 9; ++i)                                                                               // Nodes creation FOR cycle
    add_new_node();                                                                                         // Create new node (node allocated inside heap)
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
  // Apply Dijikstra alg between graph node number 1 and 6 - test project function (function number 7)
  dijkstra_alg(1, 6);                                                                                       // Dijikstra alg 2 find min graph-path btwn source (Node 1) and destination (Node 6), non-zero index
  // Deallocate the whole structure - test function number 8
  free_graph();                                                                                             // Clear the whole graph structure from heap

  close_fbk();                                                                                              // Close SW with fbk
  return EXIT_SUCCESS;                                                                                      // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/* 
 * Final project (G3 - number 3) --> Dijkstra.
 */
