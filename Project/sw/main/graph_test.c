/*
 * Author: Cristian Merli
 * Code title: Graph test
 * Code version: 1.0
 * Creation date: 22/06/2021
 * Last mod. date: 09/07/2021
 */
 
 
/* Compile-notes */
/* 
 * USE MAKEFILE OR THE FOLLOWING COMMANDS:
 * 
 * // Aliases:
 * alias gccW99_o="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -o"
 * alias gccW99_c="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -c -o"
 * alias gccW99_lib="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -fpic -shared -o"
 * 
 * // Compile-commands:
 * gccW99_lib lib/graph/lib_graph.so lib/graph/lib_graph.c                                              --> Create GRAPH dynamic library object file
 * gccW99_lib lib/ui/lib_ui.so lib/ui/lib_ui.c                                                          --> Create UI (TERMINAL I/O) dynamic library object file
 * gccW99_lib lib/timer/lib_timer.so lib/timer/lib_timer.c                                              --> Create TIMER dynamic library object file
 * gccW99_c main/graph_test.o main/graph_test.c                                                         --> Create MAIN object file
 * 
 * // Link-command:
 * gccW99_o graph_test main/graph_test.o lib/graph/lib_graph.so lib/ui/lib_ui.so lib/timer/lib_timer.so --> LINK main and dynamic libraries object files to test executable
 */


/* NOTES */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * Check old functions + verbose + https://stackoverflow.com/questions/20406346/how-to-plot-tree-graph-web-data-on-gnuplot
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */


/* Libraries */
#include "../lib/graph/lib_graph.h"                                                                         // Import graph library header file


/* Constants */
#define SOURCE_NODE_NAME              "Cross4"                                                              // Graph test sorce node name
#define DESTINATION_NODE_NAME         "Cross9"                                                              // Graph test destination node name
#define DEST_NODE_NAME_SPECIAL_CASE1  "Cross4"                                                              // Graph test destination node name (special case 1: destinstion=source node)
#define DEST_NODE_NAME_SPECIAL_CASE2  "Cross10"                                                             // Graph test destination node name (special case 2: destinstion node unreachble from source node)
#define SEP_CHRS  88                                                                                        // Number of separator-chars


/* Structs & data-types */
typedef struct street {                                                                                     // Street (arch) struct typedef (street name, street length)
  C_char  name[AR_STR_LEN];                                                                                 // Street name
  C_real  length;                                                                                           // Street length
} Street;


/* Main routines */
static void terminate_keyboard(int signal){                                                                 // Manage program exit from keyboard ctrl+c shortcut
  /* Body */
  close_keyboard_interrupt(signal);                                                                         // Close SW with fbk due to keyboard interrupt detected (ctrl+c)
}


/* Main cycle */
int main(){                                                                                                 // SW main cycle
  /* Main vars */
  const Street strts_vect[] = {{"Street1",1.165}, {"Street2",2.165}, {"Street3",3.165}, {"Street4",4.165}, 
                               {"Street5",5.165}, {"Street6",6.165}, {"Street7",7.165}, {"Street8",8.165},
                               {"Street9",6.165}, {"Street10",0.165}};                                      // Street-structs vector
  C_str crss_names_vect[] =   {"Cross1", "Cross2", "Cross3", "Cross4", "Cross5", "Cross6", "Cross7",
                               "Cross8", "Cross9", "Cross10"};                                              // Cross-names vector

  /* Code */
  signal(SIGINT, terminate_keyboard);                                                                       // Manage program exit from keyboard ctrl+c shortcut
  logo(6, "GRAPHS MANAGEMENT LIBRARY TEST SOFTWARE", LBU, '#', OG);                                         // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  press_enter("Hi");                                                                                        // Press enter to start SW fbk
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //                                          LIBRARY TEST SOFTWATRE                                        // --> TEST BEGIN
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Create some archs                                                                                      // ----------------------------------------------- (1.1)
  fbk_nl(2);  fbk_separator(SEP_CHR, OG, SEP_CHRS);                                                         // Print separator fbk
  fbk_nl(1);  fbk_gn_pu("(1.1) Creatin' some archs...");                                                    // Print creatin' archs fbk
  fbk_nl(1);  fbk_separator(SEP_CHR, OG, SEP_CHRS);  fbk_nl(2);                                             // Print separator fbk
  for (int i = 0; i < (int)(sizeof(strts_vect)/sizeof(const Street)); ++i)                                  // Streets allocation FOR cycle
    add_new_arch((C_str)strts_vect[i].name, strts_vect[i].length);                                          // Create new street (arch allocated inside heap)
  // Create some nodes                                                                                      // ----------------------------------------------- (1.2)
  fbk_nl(2);  fbk_separator(SEP_CHR, OG, SEP_CHRS);                                                         // Print separator fbk
  fbk_nl(1);  fbk_gn_pu("(1.2) Creatin' some nodes...");                                                    // Print creatin' nodes fbk
  fbk_nl(1);  fbk_separator(SEP_CHR, OG, SEP_CHRS);  fbk_nl(2);                                             // Print separator fbk
  for (int j = 0; j < (int)(sizeof(crss_names_vect)/sizeof(C_str)); ++j)                                    // Crosses allocation FOR cycle
    add_new_node(crss_names_vect[j]);                                                                       // Create new cross (node allocated inside heap)
  // Connect archs & nodes (excluding node "Cross10")                                                       // ----------------------------------------------- (2.1)
  fbk_nl(2);  fbk_separator(SEP_CHR, OG, SEP_CHRS);                                                         // Print separator fbk
  fbk_nl(1);  fbk_gn_pu("(2.1) Connectin' archs & nodes...");                                               // Print connectin' archs and nodes fbk
  fbk_nl(1);  fbk_separator(SEP_CHR, OG, SEP_CHRS);  fbk_nl(2);                                             // Print separator fbk
  connect_node_arch((C_str)strts_vect[0].name, crss_names_vect[0], ARCH_ND1, LIST_TAIL);                    // Connect "Street1" to "Cross1"
  connect_node_arch((C_str)strts_vect[0].name, crss_names_vect[1], ARCH_ND2, LIST_TAIL);                    // Connect "Street1" to "Cross2"
  connect_node_arch((C_str)strts_vect[1].name, crss_names_vect[0], ARCH_ND1, LIST_TAIL);                    // Connect "Street2" to "Cross1"
  connect_node_arch((C_str)strts_vect[1].name, crss_names_vect[2], ARCH_ND2, LIST_TAIL);                    // Connect "Street2" to "Cross3"
  connect_node_arch((C_str)strts_vect[2].name, crss_names_vect[0], ARCH_ND1, LIST_HEAD);                    // Connect "Street3" to "Cross1", add at list head position instead of list tail pos
  connect_node_arch((C_str)strts_vect[2].name, crss_names_vect[3], ARCH_ND2, LIST_TAIL);                    // Connect "Street3" to "Cross4"
  connect_node_arch((C_str)strts_vect[3].name, crss_names_vect[0], ARCH_ND1, LIST_POS, 2);                  // Connect "Street4" to "Cross1", opt param --> arch pos, non-zero index
  connect_node_arch((C_str)strts_vect[3].name, crss_names_vect[4], ARCH_ND2, LIST_TAIL);                    // Connect "Street4" to "Cross5"
  connect_node_arch((C_str)strts_vect[4].name, crss_names_vect[4], ARCH_ND1, LIST_TAIL);                    // Connect "Street5" to "Cross5"
  connect_node_arch((C_str)strts_vect[4].name, crss_names_vect[5], ARCH_ND2, LIST_TAIL);                    // Connect "Street5" to "Cross6"
  connect_node_arch((C_str)strts_vect[5].name, crss_names_vect[5], ARCH_ND1, LIST_TAIL);                    // Connect "Street6" to "Cross6"
  connect_node_arch((C_str)strts_vect[5].name, crss_names_vect[6], ARCH_ND2, LIST_TAIL);                    // Connect "Street6" to "Cross7"
  connect_node_arch((C_str)strts_vect[6].name, crss_names_vect[5], ARCH_ND1, LIST_TAIL);                    // Connect "Street7" to "Cross6"
  connect_node_arch((C_str)strts_vect[6].name, crss_names_vect[7], ARCH_ND2, LIST_TAIL);                    // Connect "Street7" to "Cross8"
  connect_node_arch((C_str)strts_vect[7].name, crss_names_vect[7], ARCH_ND1, LIST_TAIL);                    // Connect "Street8" to "Cross8"
  connect_node_arch((C_str)strts_vect[7].name, crss_names_vect[8], ARCH_ND2, LIST_TAIL);                    // Connect "Street8" to "Cross9"
  connect_node_arch((C_str)strts_vect[8].name, crss_names_vect[0], ARCH_ND1, LIST_TAIL);                    // Connect "Street9" to "Cross1"
  connect_node_arch((C_str)strts_vect[8].name, crss_names_vect[6], ARCH_ND2, LIST_TAIL);                    // Connect "Street9" to "Cross7"
  connect_node_arch((C_str)strts_vect[9].name, crss_names_vect[0], ARCH_ND1, LIST_TAIL);                    // Connect "Street10" to "Cross1"
  connect_node_arch((C_str)strts_vect[9].name, crss_names_vect[5], ARCH_ND2, LIST_TAIL);                    // Connect "Street10" to "Cross6"
  // Apply Dijkstra's algorithm                                                                             // ----------------------------------------------- (3.1)
  fbk_nl(2);  fbk_separator(SEP_CHR, OG, SEP_CHRS); fbk_nl(1);                                              // Print separator fbk
  fbk_gn_pu("(3.1) Applyin' Dijkstra's algorithm to find min paths from specified source node...");         // Print applyin' Dijkstra's algorithm to find min paths fbk
  fbk_nl(1);  fbk_separator(SEP_CHR, OG, SEP_CHRS);  fbk_nl(2);                                             // Print separator fbk
  dijkstra_alg(SOURCE_NODE_NAME);                                                                           // Apply Dijkstra alg using "Cross4" as source node (find all min path-costs and prev nodes in shortest paths, Dijkstra-dataset vect allocated/reallocated inside heap)
  // Reconstruct some min paths (includin' some special cases)                                              // ----------------------------------------------- (3.2)
  fbk_nl(2);  fbk_separator(SEP_CHR, OG, SEP_CHRS);                                                         // Print separator fbk
  fbk_nl(1);  fbk_gn_pu("(3.2) Reconstructin' some min paths (includin' special cases)...");                // Print reconstructin' some min paths fbk
  fbk_nl(1);  fbk_separator(SEP_CHR, OG, SEP_CHRS);  fbk_nl(2);                                             // Print separator fbk
  buid_shortest_path(DESTINATION_NODE_NAME);                                                                // Reconstruct min path to "Cross9" startin' from "Cross4", (min path connections vect allocated/reallocated inside heap)
  dbg_print("Some special-cases examples:");                                                                // Print special-cases examples debug fbk
  buid_shortest_path(DEST_NODE_NAME_SPECIAL_CASE1);                                                         // Reconstruct min path to "Cross4" (src=dest) startin' from "Cross4", (min path connections vect allocated/reallocated inside heap)
  buid_shortest_path(DEST_NODE_NAME_SPECIAL_CASE2);                                                         // Reconstruct min path to "Cross10" (unreachble node) startin' from "Cross4", (min path connections vect allocated/reallocated inside heap)
  // Deallocate the whole graph structure                                                                   // ----------------------------------------------- (4.1)
  fbk_nl(2);  fbk_separator(SEP_CHR, OG, SEP_CHRS);                                                         // Print separator fbk
  fbk_nl(1);  fbk_gn_pu("(4.1) Deallocatin' the whole graph structure...");                                 // Print clearin' the whole graph structre fbk
  fbk_nl(1);  fbk_separator(SEP_CHR, OG, SEP_CHRS);  fbk_nl(2);                                             // Print separator fbk
  free_graph();                                                                                             // Clear graph structure from heap and reset some flags to be able to use again lib functions
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //                                          LIBRARY TEST SOFTWATRE                                        // --> TEST END
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  close_fbk();                                                                                              // Close SW with fbk
  return EXIT_SUCCESS;                                                                                      // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/* 
 * Final project (G3 - number 3) --> Dijkstra's algorithm.
 */
