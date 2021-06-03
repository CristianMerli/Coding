/*
 * Author: Cristian Merli
 * Code title: Graph
 * Code version: 2.0
 * Creation date: 21/05/2021
 * Last mod. date: 03/06/2021
 * 
 * 
 * // Compile-commands:
 * gccW99_lib lib/graph/lib_graph.so lib/graph/lib_graph.c          --> Create GRAPH dynamic library object file (interface with linked lists library)
 * gccW99_lib lib/ui/lib_ui.so lib/ui/lib_ui.c                      --> Create UI (TERMINAL I/O) dynamic library object file
 * gccW99_c graph.c                                                 --> Create SOFTWARE object file
 * 
 * // Link-command:
 * gccW99_o graph graph.o lib/graph/lib_graph.so lib/ui/lib_ui.so   --> LINK software and dynamic libraries object files to executable
 * 
 * // Aliases:
 * alias gccW99_o="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -o"
 * alias gccW99_c="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -c"
 * alias gccW99_lib="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -fpic -shared -o"
 */


/* Libraries */
#include "lib/graph/lib_graph.h"                                                                            // Import graph library header file


/* Constants */
//


/* Global vars */
//


/* Main routines */
void terminate_keyboard(int signal){                                                                        // Manage program exit from keyboard ctrl+c shortcut
  /* Body */
  close_keyboard_interrupt(signal);                                                                         // Close SW with fbk due to keyboard interrupt detected (ctrl+c)
}


/* Main cycle */
int main(){                                                                                                 // SW main cycle
  /* Main vars */
  C_real ar1_cost = 1.165, ar2_cost = 2.165, ar3_cost = 3.165, ar4_cost = 4.165, ar5_cost = 5.165;          // Arches cost vars to test graph-management functions
  C_real ar6_cost = 6.165, ar7_cost = 7.165, ar8_cost = 8.165;                                              // Arches cost vars to test graph-management functions
  int arch_ptrs_vect_size = 0, node_ptrs_vect_size = 0;                                                     // Arch and node ptr vectors size vars to test graph-management functions

  /* Code */
  signal(SIGINT, terminate_keyboard);                                                                       // Manage program exit from keyboard ctrl+c shortcut
  logo(6, "GRAPHS MANAGEMENT LIBRARY TEST SOFTWARE", YE, '#', GN);                                          // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  press_enter("Hi");                                                                                        // Press enter to start SW fbk
  
  // Create & connect nodes/arches - test functions number 1, 2 and 3
  Graph_arch ar1 = add_new_arch(ar1_cost);                                                                  // Create new arch (arch allocated inside heap)
  Graph_arch ar2 = add_new_arch(ar2_cost);                                                                  // Create new arch (arch allocated inside heap)
  Graph_arch ar3 = add_new_arch(ar3_cost);                                                                  // Create new arch (arch allocated inside heap)
  Graph_arch ar4 = add_new_arch(ar4_cost);                                                                  // Create new arch (arch allocated inside heap)
  Graph_arch ar5 = add_new_arch(ar5_cost);                                                                  // Create new arch (arch allocated inside heap)
  Graph_arch ar6 = add_new_arch(ar6_cost);                                                                  // Create new arch (arch allocated inside heap)
  Graph_arch ar7 = add_new_arch(ar7_cost);                                                                  // Create new arch (arch allocated inside heap)
  Graph_arch ar8 = add_new_arch(ar8_cost);                                                                  // Create new arch (arch allocated inside heap)
  Graph_node nd1 = add_new_node();                                                                          // Create new node (node allocated inside heap)
  Graph_node nd2 = add_new_node();                                                                          // Create new node (node allocated inside heap)
  Graph_node nd3 = add_new_node();                                                                          // Create new node (node allocated inside heap)
  Graph_node nd4 = add_new_node();                                                                          // Create new node (node allocated inside heap)
  Graph_node nd5 = add_new_node();                                                                          // Create new node (node allocated inside heap)
  Graph_node nd6 = add_new_node();                                                                          // Create new node (node allocated inside heap)
  Graph_node nd7 = add_new_node();                                                                          // Create new node (node allocated inside heap)
  Graph_node nd8 = add_new_node();                                                                          // Create new node (node allocated inside heap)
  Graph_node nd9 = add_new_node();                                                                          // Create new node (node allocated inside heap)
  connect_node_arch(&nd1, &ar1, ARCH_ND1, LIST_POS, 1);                                                     // Connect node1 to arch1 (new anch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(&nd2, &ar1, ARCH_ND2, LIST_POS, 1);                                                     // Connect node2 to arch1 (new anch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(&nd1, &ar2, ARCH_ND1, LIST_HEAD);                                                       // Connect node1 to arch2 (new anch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(&nd3, &ar2, ARCH_ND2, LIST_HEAD);                                                       // Connect node3 to arch2 (new anch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(&nd1, &ar3, ARCH_ND1, LIST_TAIL);                                                       // Connect node1 to arch3 (new anch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(&nd4, &ar3, ARCH_ND2, LIST_TAIL);                                                       // Connect node4 to arch3 (new anch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(&nd1, &ar4, ARCH_ND1, LIST_POS, 2);                                                     // Connect node1 to arch4 (new anch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(&nd5, &ar4, ARCH_ND2, LIST_POS, 2);                                                     // Connect node5 to arch4 (new anch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(&nd5, &ar5, ARCH_ND1, LIST_HEAD);                                                       // Connect node5 to arch5 (new anch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(&nd6, &ar5, ARCH_ND2, LIST_HEAD);                                                       // Connect node6 to arch5 (new anch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(&nd6, &ar6, ARCH_ND1, LIST_HEAD);                                                       // Connect node6 to arch6 (new anch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(&nd7, &ar6, ARCH_ND2, LIST_HEAD);                                                       // Connect node7 to arch6 (new anch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(&nd6, &ar7, ARCH_ND1, LIST_HEAD);                                                       // Connect node6 to arch7 (new anch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(&nd8, &ar7, ARCH_ND2, LIST_HEAD);                                                       // Connect node8 to arch7 (new anch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(&nd8, &ar8, ARCH_ND1, LIST_HEAD);                                                       // Connect node8 to arch8 (new anch list element allocated inside heap, opt param --> arch pos, non-zero index)
  connect_node_arch(&nd9, &ar8, ARCH_ND2, LIST_HEAD);                                                       // Connect node9 to arch8 (new anch list element allocated inside heap, opt param --> arch pos, non-zero index)
  // Find arches connected to a specific node - test function number 4
  Graph_arch* arch_ptrs_vect = archs_connected_to_node(&nd1, &arch_ptrs_vect_size, Y);                      // Define arch ptrs vect (vector allocated inside heap) - YES --> with verbose mode
  for (int i = 0; i < arch_ptrs_vect_size; ++i){                                                            // Random FOR cycle
    fbk_gn_lbu_ye_real("Arch cost", arch_ptrs_vect[i]->cost); fbk_nl(1);                                    // Random print
  }
  free(arch_ptrs_vect);                                                                                     // Free arch ptrs allocated vector inside heap
  // Find nodes connected to a specific node - test function number 5
  Graph_node* node_ptrs_vect = nodes_connected_to_node(&nd1, &node_ptrs_vect_size);                         // Define node ptrs vect (vector allocated inside heap)
  for (int j = 0; j < node_ptrs_vect_size; ++j){                                                            // Random FOR cycle
    fbk_gn_lbu_ye_ptr("Node pointed address", (Ptr)node_ptrs_vect[j]);  fbk_nl(1);                          // Random print
  }
  free(node_ptrs_vect);                                                                                     // Free node ptrs allocated vector inside heap
  // Print arches costs through the whole graph structure startin' from node1 - test function number 6
  print_archs_costs(&nd1);                                                                                  // Print all the arches costs, starting from a specified node and moving through the whole graph structure
  // // Deallocate the whole structure - test function number 7
  // free_graph(archs_collec_vect, &arches_vect_size, nodes_collec_vect, &nodes_vect_size);                    // Clear the whole graph structure from heap

  close_fbk();                                                                                              // Close SW with fbk
  return EXIT_SUCCESS;                                                                                      // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/* 
 * Creare una libreria per gestire un oggetto di tipo grafo
 * il grafo è composto da nodi e archi
 * ogni arco è connesso ad al più due nodi, ogni arco ha un costo (double)
 * ogni nodo è connesso a un numero variabile di archi
 * se un arco è connesso ad un nodo anche il nodo è connesso a quell'arco
 * Scrivere le seguenti funzioni:
 * 1. Dato un nodo ed un arco la funzione connette nodo ed arco
 * 2. Funzione che crea un arco e ne ritorna il puntatore
 * 3. Funzione che crea il nodo e ne rotorna il puntatore
 * 4. Funzione che dato un nodo ritorna tutti gli archi connessi
 * 5. Funzione che dato un nodo ritorna i nodi connessi
 * 6. Funzione che stampa a video per ogni nodo la lista degli archi connessi
 * 7. Funzione che dealloca la struttura
 */
