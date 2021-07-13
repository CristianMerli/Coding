/*
 * Author: Cristian Merli
 * Code title: Graph test
 * Code version: 2.0
 * Creation date: 22/06/2021
 * Last mod. date: 13/07/2021
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


/* Libraries */
#include "../lib/graph/lib_graph.h"                                                                         // Import graph library header file


/* Constants */
#define VERBOSE                       Y                                                                     // Verbose mode (Y/N)
#define SOURCE_NODE_NAME              "Cross4"                                                              // Graph test sorce node name
#define DESTINATION_NODE_NAME         "Cross9"                                                              // Graph test destination node name
#define DEST_NODE_NAME_SPECIAL_CASE1  "Cross4"                                                              // Graph test destination node name (special-case path 1: destinstion=source node)
#define DEST_NODE_NAME_SPECIAL_CASE2  "Cross10"                                                             // Graph test destination node name (special-case path 2: destinstion node unreachble from source node)
#define GPLOT_TEST_GRAPH_LAYOUT_CMD   "gnuplot -e \"load 'gnuplot/graph_plot.cmd'; pause -1\""              // Command to display test-graph layout with gnuplot
#define GPLOT_SHORTEST_PATH_CMD       "gnuplot -e \"load 'gnuplot/shortest_plot.cmd'; pause -1\""           // Command to display test-graph layout and shortest path with gnuplot


/* Enums & data-types */
typedef enum test_choice {PREPARED=1, PERSONALIZED, EXIT} Test_choice;                                      // Test-choice enum typedef


/* Structs & data-types */
typedef struct street {                                                                                     // Street (arch) struct typedef (street name, street length)
  C_char  name[AR_STR_LEN];                                                                                 // Street name
  C_real  length;                                                                                           // Street length
} Street;


/* Global vars */
const Street strts_vect[] = {{"Street1",1.1}, {"Street2",2.2}, {"Street3",3.3}, {"Street4",4.4}, 
                              {"Street5",5.5}, {"Street6",6.6}, {"Street7",7.7}, {"Street8",8.8},
                              {"Street9",6.3}, {"Street10",0.2}, {"Street11",9.3}, {"Street12",7.1},
                              {"Street13",12.8}};                                                           // Street-structs vector

C_str crss_names_vect[] =   {"Cross1", "Cross2", "Cross3", "Cross4", "Cross5", "Cross6", "Cross7",
                              "Cross8", "Cross9", "Cross10"};                                               // Cross-names vector


/* Main routines */
static void terminate_keyboard(int signal){                                                                 // Manage program exit from keyboard ctrl+c shortcut
  /* Body */
  close_keyboard_interrupt(signal);                                                                         // Close SW with fbk due to keyboard interrupt detected (ctrl+c)
}


static void create_archs(){                                                                                 // Routine to create archs
  /* Body */
  for (int i = 0; i < (int)(sizeof(strts_vect)/sizeof(const Street)); ++i)                                  // Streets allocation FOR cycle
    add_new_arch((C_str)strts_vect[i].name, strts_vect[i].length);                                          // Create new street (arch allocated inside heap)
}


static void create_nodes(){                                                                                 // Routine to create nodes
  /* Body */
  for (int j = 0; j < (int)(sizeof(crss_names_vect)/sizeof(C_str)); ++j)                                    // Crosses allocation FOR cycle
    add_new_node(crss_names_vect[j]);                                                                       // Create new cross (node allocated inside heap)
}


static void create_connections(){                                                                           // Routine to create connections btwn archs & nodes
  /* Body */
  connect_node_arch((C_str)strts_vect[0].name, crss_names_vect[0], ARCH_ND1, LIST_TAIL);                    // Connect "Street1" to "Cross1"
  connect_node_arch((C_str)strts_vect[0].name, crss_names_vect[1], ARCH_ND2, LIST_TAIL);                    // Connect "Street1" to "Cross2"
  connect_node_arch((C_str)strts_vect[1].name, crss_names_vect[0], ARCH_ND1, LIST_TAIL);                    // Connect "Street2" to "Cross1"
  connect_node_arch((C_str)strts_vect[1].name, crss_names_vect[2], ARCH_ND2, LIST_TAIL);                    // Connect "Street2" to "Cross3"
  connect_node_arch((C_str)strts_vect[2].name, crss_names_vect[0], ARCH_ND1, LIST_HEAD);                    // Connect "Street3" to "Cross1", add at list head position instead of list tail pos
  connect_node_arch((C_str)strts_vect[2].name, crss_names_vect[3], ARCH_ND2, LIST_TAIL);                    // Connect "Street3" to "Cross4"
  connect_node_arch((C_str)strts_vect[3].name, crss_names_vect[0], ARCH_ND1, LIST_POS, 2);                  // Connect "Street4" to "Cross1", opt param --> add arch at specific pos in archs list, non-zero index
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
  connect_node_arch((C_str)strts_vect[10].name, crss_names_vect[3], ARCH_ND1, LIST_TAIL);                   // Connect "Street11" to "Cross4"
  connect_node_arch((C_str)strts_vect[10].name, crss_names_vect[4], ARCH_ND2, LIST_TAIL);                   // Connect "Street11" to "Cross5"
  connect_node_arch((C_str)strts_vect[11].name, crss_names_vect[4], ARCH_ND1, LIST_TAIL);                   // Connect "Street12" to "Cross5"
  connect_node_arch((C_str)strts_vect[11].name, crss_names_vect[7], ARCH_ND2, LIST_TAIL);                   // Connect "Street12" to "Cross8"
  connect_node_arch((C_str)strts_vect[12].name, crss_names_vect[4], ARCH_ND1, LIST_TAIL);                   // Connect "Street13" to "Cross5"
  connect_node_arch((C_str)strts_vect[12].name, crss_names_vect[8], ARCH_ND2, LIST_TAIL);                   // Connect "Street13" to "Cross9"
}


static void test_option_choice(Test_choice *const choice){                                                  // Routine to choose testing option
  /* Body */
  fbk_nl(1);  fbk_gn_lbu_ye_str("[1]", "Prepared test (requires gnuplot)");                                 // Print opt 1 fbk
  fbk_nl(1);  fbk_gn_lbu_ye_str("[2]", "Personalized test (requires gnuplot)");                             // Print opt 2 fbk
  fbk_nl(1);  fbk_gn_lbu_ye_str("[3]", "Exit"); fbk_nl(1);                                                  // Print opt 3 fbk
  *choice = (Byte)read_term_in_int_inrange(1, 3, "Choose a testing option", "Error! Option");               // Print opt choice fbk
  switch (*choice){                                                                                         // Testin' option switch-case
    case PREPARED:                                                                                          // Option [1] -> Prepared test (requires gnuplot)
      fbk_nl(1);  fbk_gn_lbu_ye_str("Choosen option", "[1] -> Prepared test (requires gnuplot)");           // Print choosen opt fbk
      break;
    //////////////////
    case PERSONALIZED:                                                                                      // Option [2] -> Personalized test (requires gnuplot)
      fbk_nl(1);  fbk_gn_lbu_ye_str("Choosen option", "[2] -> Personalized test (requires gnuplot)");       // Print choosen opt fbk
      break;
    //////////
    case EXIT:                                                                                              // Option [3] -> Exit
      fbk_nl(1);  fbk_gn_lbu_ye_str("Choosen option", "[3] -> Exit"); fbk_nl(1);                            // Print choosen opt fbk
      Confirm answ = read_term_in_confirm("Are you sure you want to close test software");                  // Ask confirm
      switch (answ){                                                                                        // Confirm answ switch-case
        case YES:                                                                                           // YES answer
          close_fbk();                                                                                      // Close SW with fbk
          break;
        ////////
        case NO:                                                                                            // NO answer
          test_option_choice(choice);                                                                       // Go back
          break;
        ////////////
        case CANCEL:                                                                                        // CANCEL answer
          test_option_choice(choice);                                                                       // Go back
          break;
        ////////
        default:                                                                                            // Unknown answer
          fbk_err("Error, bad confirmation answer");                                                        // Print error fbk
          perror("Bad confirmation answer, 'read_term_in_confirm()' requires 'Confirm' data-type!");        // Print perror fbk
          close_err();                                                                                      // Close with error fbk
      }
      break;
    ////////
    default:                                                                                                // Unknown option
      fbk_err("Error, bad testing option value");                                                           // Print error fbk
      perror("Testing option value out of range, check 'read_term_in_int_inrange()' parameter-values!");    // Print perror fbk
      close_err();                                                                                          // Close with error fbk
  }
}


static void display_test_graph(C_str cmd){                                                                  // Routine to display test-graph through gnuplot
  /* Body */
  fbk_gn_pu("Close gnuplot to continue graph-library test..."); fbk_nl(1);                                  // Print close gnuplot to continue fbk
  fflush(stdout);                                                                                           // Force fbk print b4 openin' gnuplot
  int ret_val = system(cmd);                                                                                // Display test-graph layout with gnuplot
  if (ret_val == 0){                                                                                        // Chack command return val, if ok
    fbk_nl(1);  fbk_gn_cy("Test-graph layout correctly displayed with gnuplot!\n");                         // Test-graph layout correctly displayed with gnuplot fbk
  } else                                                                                                    // Else if command return val ain't ok
    fbk_err("Ops! Encountred error during gnuplot command execution!");                                     // Error fbk
}


static void apply_dijkstra(C_str src_nd_name){                                                              // Routine to apply Dijkstra's algorithm
  /* Body */
  dijkstra_alg(src_nd_name, VERBOSE);                                                                       // Apply Dijkstra alg using defined source node (find all min path-costs and prev nodes in shortest paths, Dijkstra-dataset vect allocated/reallocated inside heap) - Y/N for verbose mode
}


static void reconstruct_min_path(C_str dest_nd_name){                                                       // Routine to reconstruct min path
  /* Body */
  buid_shortest_path(dest_nd_name, VERBOSE);                                                                // Reconstruct min path to defined destination node startin' from pre-defined source node, (min path connections vect allocated/reallocated inside heap) - Y/N for verbose mode
}


static void define_src_node_name(Str* src_nd_nm){                                                           // Routine to define presonalized source-node name
  /* Body */
  for (int i = 0; i < nds_collect_size; ++i){                                                               // Nodes collection vect scrollin' FOR cycle
    fbk_nl(1);  fbk_gn_lbu_ye_str("Node name", nodes_collect_vect[i].name);                                 // Print node name fbk
  }
  do {                                                                                                      // Cycle to define personalized source-node name
    *src_nd_nm = read_term_in_min_chrs(1, "Choose a source node (by name)", "Source node name");            // Read user input str
  } while(idx_by_name(ND, *src_nd_nm) < 0);                                                                 // Check whether node-name specified by the user exists in nodes collection vect, otherwise repeat question
}


static void define_dest_node_name(Str* dest_nd_nm){                                                         // Routine to define presonalized destination-node name
  /* Body */
  for (int i = 0; i < nds_collect_size; ++i){                                                               // Nodes collection vect scrollin' FOR cycle
    fbk_nl(1);  fbk_gn_lbu_ye_str("Node name", nodes_collect_vect[i].name);                                 // Print node name fbk
  }
  do {                                                                                                      // Cycle to define personalized destination-node name
    *dest_nd_nm = read_term_in_min_chrs(1, "Choose a destination node (by name)", "Destination node name"); // Read user input str
  } while(idx_by_name(ND, *dest_nd_nm) < 0);                                                                // Check whether node-name specified by the user exists in nodes collection vect, otherwise repeat question
}


/* Main cycle */
int main(){                                                                                                 // Main SW cycle
  /* Main vars */
  Test_choice choice = 0;                                                                                   // Test choice var

  /* Code */
  signal(SIGINT, terminate_keyboard);                                                                       // Manage program exit from keyboard ctrl+c shortcut
  logo(6, "GRAPHS MANAGEMENT LIBRARY TEST SOFTWARE", LBU, '#', OG);                                         // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  press_enter("Hi");                                                                                        // Press enter to start SW fbk

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //                                          LIBRARY TEST SOFTWATRE                                        // --> TEST BEGIN
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // (1.1) Create some archs                                                                                // --------------------------------------------------------- (1.1)
  fbk_nl(2);  fbk_separator(SEP_CHR, OG);                                                                   // Print separator fbk
  fbk_nl(1);  fbk_gn_pu("(1.1) Creatin' some archs...");                                                    // Print creatin' archs fbk
  fbk_nl(1);  fbk_separator(SEP_CHR, OG); fbk_nl(2);                                                        // Print separator fbk
  create_archs();                                                                                           // Routine call to create archs
  // (1.2) Create some nodes                                                                                // --------------------------------------------------------- (1.2)
  fbk_nl(2);  fbk_separator(SEP_CHR, OG);                                                                   // Print separator fbk
  fbk_nl(1);  fbk_gn_pu("(1.2) Creatin' some nodes...");                                                    // Print creatin' nodes fbk
  fbk_nl(1);  fbk_separator(SEP_CHR, OG); fbk_nl(2);                                                        // Print separator fbk
  create_nodes();                                                                                           // Routine call to create nodes
  // (2.1) Connect archs & nodes (excluding node "Cross10")                                                 // --------------------------------------------------------- (2.1)
  fbk_nl(2);  fbk_separator(SEP_CHR, OG);                                                                   // Print separator fbk
  fbk_nl(1);  fbk_gn_pu("(2.1) Connectin' archs & nodes...");                                               // Print connectin' archs and nodes fbk
  fbk_nl(1);  fbk_separator(SEP_CHR, OG); fbk_nl(2);                                                        // Print separator fbk
  create_connections();                                                                                     // Routine call to create connections btwn archs & nodes
  // (2.2) Test mode choice                                                                                 // --------------------------------------------------------- (2.2)
  fbk_nl(2);  fbk_separator(SEP_CHR, OG);                                                                   // Print separator fbk
  fbk_nl(1);  fbk_gn_pu("(2.2) Testin' mode choice...");                                                    // Print testin' mode choice fbk
  fbk_nl(1);  fbk_separator(SEP_CHR, OG); fbk_nl(2);                                                        // Print separator fbk
  test_option_choice(&choice);                                                                              // Routine call to choose testing option
  // (2.3) Display test-graph layout with gnuplot                                                           // --------------------------------------------------------- (2.3)
  fbk_nl(2);  fbk_separator(SEP_CHR, OG);                                                                   // Print separator fbk
  fbk_nl(1);  fbk_gn_pu("(2.3) Displayin' test-graph layout with gnuplot...");                              // Print displayin' test-graph layout with gnuplot fbk
  fbk_nl(1);  fbk_separator(SEP_CHR, OG); fbk_nl(2);                                                        // Print separator fbk
  display_test_graph(GPLOT_TEST_GRAPH_LAYOUT_CMD);                                                          // Routine call to display test-graph through gnuplot
  // (3.1) Apply Dijkstra's algorithm and find min parh                                                     //
  switch (choice){                                                                                          // Testin' option switch-case
    case PREPARED:                                                                                          // Option [1] -> Prepared test (requires gnuplot)
      // (3.1.1) Apply Dijkstra's algorithm (from Cross4)                                                   // --------------------------------------------------------- (3.1.1)
      fbk_nl(2);  fbk_separator(SEP_CHR, OG); fbk_nl(1);                                                    // Print separator fbk
      fbk_gn_pu("(3.1.1) Applyin' Dijkstra's algorithm to find min paths from \"Cross4\" source node...");  // Print applyin' Dijkstra's algorithm to find min paths fbk
      fbk_nl(1);  fbk_separator(SEP_CHR, OG); fbk_nl(2);                                                    // Print separator fbk
      apply_dijkstra(SOURCE_NODE_NAME);                                                                     // Routine call to apply Dijkstra's algorithm
      // (3.2.1) Reconstruct test min path (from Cross4 to Cross9)                                          // --------------------------------------------------------- (3.2.1)
      fbk_nl(2);  fbk_separator(SEP_CHR, OG);                                                               // Print separator fbk
      fbk_nl(1);  fbk_gn_pu("(3.2.1) Reconstructin' test min path (Cross4-Cross9) with delays...");         // Print reconstructin' test min path fbk
      fbk_nl(1);  fbk_separator(SEP_CHR, OG); fbk_nl(2);                                                    // Print separator fbk
      reconstruct_min_path(DESTINATION_NODE_NAME);                                                          // Routine call to reconstruct min path
      // (3.3.1) Display test-graph layout and shortest path with gnuplot (from Cr4 to Cr9)                 // --------------------------------------------------------- (3.3.1)
      fbk_nl(2);  fbk_separator(SEP_CHR, OG);                                                               // Print separator fbk
      fbk_nl(1);  fbk_gn_pu("(3.3.1) Displayin' test-graph and shortest path with gnuplot (Cr4-Cr9)...");   // Print displayin' test-graph layout and shortest path with gnuplot fbk
      fbk_nl(1);  fbk_separator(SEP_CHR, OG); fbk_nl(2);                                                    // Print separator fbk
      display_test_graph(GPLOT_SHORTEST_PATH_CMD);                                                          // Routine call to display test-graph through gnuplot
      // (3.4.1) Reconstruct some special-cases paths (Cr4-Cr4 and Cr4-Cr10)                                // --------------------------------------------------------- (3.4.1)
      fbk_nl(2);  fbk_separator(SEP_CHR, OG);                                                               // Print separator fbk
      fbk_nl(1);  fbk_gn_pu("(3.4.1) Reconstructin' some special-cases paths (Cr4-Cr4 and Cr4-Cr10)...");   // Print reconstructin' some special-cases paths fbk
      fbk_nl(1);  fbk_separator(SEP_CHR, OG); fbk_nl(2);                                                    // Print separator fbk
      reconstruct_min_path(DEST_NODE_NAME_SPECIAL_CASE1);                                                   // Routine call to reconstruct min path
      reconstruct_min_path(DEST_NODE_NAME_SPECIAL_CASE2);                                                   // Routine call to reconstruct min path
      break;                                                                                                //
    //////////////////                                                                                      //
    case PERSONALIZED:                                                                                      // Option [2] -> Personalized test (requires gnuplot)
      // (3.1.2) Apply Dijkstra's algorithm                                                                 // --------------------------------------------------------- (3.1.2)
      fbk_nl(2);  fbk_separator(SEP_CHR, OG); fbk_nl(1);                                                    // Print separator fbk
      fbk_gn_pu("(3.1.2) Applyin' Dijkstra's algorithm to find min paths from specified source node...");   // Print applyin' Dijkstra's algorithm to find min paths fbk
      fbk_nl(1);  fbk_separator(SEP_CHR, OG); fbk_nl(2);                                                    // Print separator fbk
      char* src_nd_nm = NULL;                                                                               // Personalized source-node name str init
      define_src_node_name(&src_nd_nm);                                                                     // Routine call to define presonalized source-node name
      apply_dijkstra(src_nd_nm);                                                                            // Routine call to apply Dijkstra's algorithm
      // (3.2.2) Reconstruct test min path                                                                  // --------------------------------------------------------- (3.2.2)
      fbk_nl(2);  fbk_separator(SEP_CHR, OG);                                                               // Print separator fbk
      fbk_nl(1);  fbk_gn_pu("(3.2.2) Reconstructin' requested min path with delays...");                    // Print reconstructin' requested min path fbk
      fbk_nl(1);  fbk_separator(SEP_CHR, OG); fbk_nl(2);                                                    // Print separator fbk
      char* dest_nd_nm = NULL;                                                                              // Personalized destination-node name str init
      define_dest_node_name(&dest_nd_nm);                                                                   // Routine call to define presonalized destination-node name
      reconstruct_min_path(dest_nd_nm);                                                                     // Routine call to reconstruct min path
      // (3.3.2) Display test-graph layout and shortest path with gnuplot                                   // --------------------------------------------------------- (3.3.2)
      fbk_nl(2);  fbk_separator(SEP_CHR, OG);                                                               // Print separator fbk
      fbk_nl(1);  fbk_gn_pu("(3.3.2) Displayin' test-graph and shortest path with gnuplot...");             // Print displayin' test-graph layout and shortest path with gnuplot fbk
      fbk_nl(1);  fbk_separator(SEP_CHR, OG); fbk_nl(2);                                                    // Print separator fbk
      display_test_graph(GPLOT_TEST_GRAPH_LAYOUT_CMD);                                                      // Routine call to display test-graph through gnuplot
      break;                                                                                                //
    ////////                                                                                                //
    default:                                                                                                // Unknown option (avoid compile errors)
      break;                                                                                                //
  }                                                                                                         //
  // (4.1) Deallocate the whole graph structure                                                             // --------------------------------------------------------- (4.1)
  fbk_nl(2);  fbk_separator(SEP_CHR, OG);                                                                   // Print separator fbk
  fbk_nl(1);  fbk_gn_pu("(4.1) Deallocatin' the whole graph structure...");                                 // Print clearin' the whole graph structre fbk
  fbk_nl(1);  fbk_separator(SEP_CHR, OG); fbk_nl(2);                                                        // Print separator fbk
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
