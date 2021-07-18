/*
 * Author: Cristian Merli
 * Code title: Graph test
 * Code version: 3.0
 * Creation date: 22/06/2021
 * Last mod. date: 16/07/2021
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
 * gccW99_lib lib/files/lib_files.so lib/files/lib_files.c                                              --> Create FILES dynamic library object file
 * gccW99_lib lib/timer/lib_timer.so lib/timer/lib_timer.c                                              --> Create TIMER dynamic library object file
 * gccW99_c main/graph_test.o main/graph_test.c                                                         --> Create MAIN object file
 * 
 * // Link-command:
 * gccW99_o graph_test main/graph_test.o lib/graph/lib_graph.so lib/ui/lib_ui.so lib/files/lib_files.so lib/timer/lib_timer.so  --> LINK main and dynamic libraries object files to test executable
 */


/*!
 * \page        page1 General notes
 *              Dijkstra's algorithm library test-software.
 * 
 * @author      Cristian Merli
 * @date        15/07/2021
 * @version     3.0 - Completed 15/05/2021
 * 
 * @note        Important notes:
 *                * Graphical effects are managed by gnuplot (based on data manipulated by test software main program), so it is highly recommended to have it installed.
 *                * It is possibile to compile, run and execute further actions tacking advantege of makefile, for more informations see doxygen 'Main page' or README.md file.
 * @warning     Important warnings:
 *                * Pay attention, arch/node names must only be max 30 chars long. To modify max names lenght, change relative macros inside 'lib_graph.h' header file: # and #.
 *                * Change in_buff size also in UI lib and read funct....
 * @bug         No known bugs.
 * 
 * \section     section1 Code title:
 *              Polynomial interpolation with Newton algorithm and divided-differences.
 * 
 * \subsection  subsection1 Code details:
 *              Polynomial interpolation C code --> Newton algorithm with divided-differences to interpolate 'till 170 points,
 *              polynomial evaluation in given points and derivate calculation.
 * 
 * @brief       rfefrerf
 */


/*!
 * \page        page2 Test-page
 *              ---.
 * \section     section1 Title:
 *              ---.
 * 
 * \subsection  subsection1 Code details:
 *              Polynomial interpolation C code --> Newton algorithm with divided-differences to interpolate 'till 170 points,
 *              polynomial evaluation in given points and derivate calculation.
 * 
 * @file        graph_test.c saxxasxsa
 * 
 * @brief       csdcds
 */


/* Libraries */
#include "../lib/graph/lib_graph.h"                                                                         // Import graph library header file
#include "../lib/files/lib_files.h"                                                                         // Import files library header file


/* Constants */
/// <b>Macro description:</b> Advanced verbose mode (Y/N) for #dijkstra_alg() and #buid_shortest_path() functions.
#define VERBOSE                       Y                                                                     // Verbose mode (Y/N)
/// <b>Macro description:</b> Source node name for graph-library prepared testing mode, for #dijkstra_alg() function.
#define SOURCE_NODE_NAME              "Cross4"                                                              // Graph test sorce node name
/// <b>Macro description:</b> Destination node name for graph-library prepared testing mode, for #buid_shortest_path() function.
#define DESTINATION_NODE_NAME         "Cross9"                                                              // Graph test destination node name
/// <b>Macro description:</b> Destination node name for graph-library prepared testing mode special case1 (source = destination), for #buid_shortest_path() function.
#define DEST_NODE_NAME_SPECIAL_CASE1  "Cross4"                                                              // Graph test destination node name (special-case path 1: destinstion=source node)
/// <b>Macro description:</b> Destination node name for graph-library prepared testing mode special case2 (destination node unreachble), for #buid_shortest_path() function.
#define DEST_NODE_NAME_SPECIAL_CASE2  "Cross10"                                                             // Graph test destination node name (special-case path 2: destinstion node unreachble from source node)
/// <b>Macro description:</b> Gnuplot graph plotting system command, for #display_test_graph() function.
#define GPLOT_TEST_GRAPH_LAYOUT_CMD   "gnuplot -e \"load 'gnuplot/graph_plot.cmd'; pause -1\""              // Command to display test-graph layout with gnuplot
/// <b>Macro description:</b> Gnuplot graph and shortest path plotting system command, for #display_test_graph() function.
#define GPLOT_SHORTEST_PATH_CMD       "gnuplot -e \"load 'gnuplot/shortest_plot.cmd'; pause -1\""           // Command to display test-graph layout and shortest path with gnuplot
/// <b>Macro description:</b> Gnuplot archs data file, for #build_shortest_path_graphics_data() function.
#define ARCHS_DAT_FILE                "gnuplot/archs.dat"                                                   // Test-graph gnuplot arch-coords .dat file
/// <b>Macro description:</b> Gnuplot arch-costs data file, for #build_shortest_path_graphics_data() function.
#define COSTS_DAT_FILE                "gnuplot/costs.dat"                                                   // Test-graph gnuplot arches cost-coords .dat file
/// <b>Macro description:</b> Gnuplot nodes data file, for #build_shortest_path_graphics_data() function.
#define NODES_DAT_FILE                "gnuplot/nodes.dat"                                                   // Test-graph gnuplot node-coords .dat file
/// <b>Macro description:</b> Gnuplot shortest-path archs data file, for #build_shortest_path_graphics_data() function.
#define SHORTEST_ARCHS_DAT_FILE       "gnuplot/shortest_archs.dat"                                          // Test-graph shortest path gnuplot arch-coords .dat file
/// <b>Macro description:</b> Gnuplot shortest-path arch-costs data file, for #build_shortest_path_graphics_data() function.
#define SHORTEST_COSTS_DAT_FILE       "gnuplot/shortest_costs.dat"                                          // Test-graph shortest path gnuplot arches cost-coords .dat file
/// <b>Macro description:</b> Gnuplot shortest-path nodes data file (source and destination nodes excluded), for #build_shortest_path_graphics_data() function.
#define SHORTEST_NODES_DAT_FILE       "gnuplot/shortest_nodes.dat"                                          // Test-graph shortest path gnuplot node-coords .dat file
/// <b>Macro description:</b> Gnuplot shortest-path source and destination nodes data file, for #build_shortest_path_graphics_data() function.
#define SRC_DEST_NODES_DAT_FILE       "gnuplot/src_dest_nodes.dat"                                          // Test-graph gnuplot source and destination node-coords .dat file


/* Enums & data-types */
/*!
 * \var PREPARED
 * Prepared-test testing option: pre-defined source and destination nodes in graph to find min-cost path (defined with macros #SOURCE_NODE_NAME and #DESTINATION_NODE_NAME).
 * \var PERSONALIZED
 * Personalized-test testing option: choose source and destination nodes in graph to find min-cost path.
 * \var EXIT
 * Exit option: deallocate graph structure and close software.
 */
/// <b>Enum-typedef description:</b> Test-choice enum typedef to define graph-library testing mode: prepared test, personalized test or exit and close test software.
typedef enum test_choice {PREPARED=1, PERSONALIZED, EXIT} Test_choice;                                      // Test-choice enum typedef


/* Structs & data-types */
/// <b>Struct-typedef description:</b> Street struct typedef for graph-library test (use crosses and streets as example of archs and nodes).
typedef struct street {                                                                                     // Street (arch) struct typedef (street name, street length)
  /// Street name, string length defined through #AR_STR_LEN macro.
  C_char  name[AR_STR_LEN];                                                                                 // Street name
  /// Street length (arch cost).
  C_real  length;                                                                                           // Street length
} Street;


/* Global vars */
/// <b>Global-variable description:</b> Street-structs vector (to dynamically initalize archs).
const Street strts_vect[] = {{"Street1",1.1}, {"Street2",2.2}, {"Street3",3.3}, {"Street4",4.4}, 
   {"Street5",5.5}, {"Street6",6.6}, {"Street7",7.7}, {"Street8",8.8},
   {"Street9",6.3}, {"Street10",0.2}, {"Street11",9.3}, {"Street12",7.1},
   {"Street13",12.8}};                                                                                      // Street-structs vector
/// <b>Global-variable description:</b> Cross-names vector (to dynamically initalize nodes).
C_str crss_names_vect[] = {"Cross1", "Cross2", "Cross3", "Cross4", "Cross5", "Cross6", "Cross7",
   "Cross8", "Cross9", "Cross10"};                                                                          // Cross-names vector


/* Main routines */
/*!
 * @brief             <p><b>Static function description:</b></p> Static routine to manage close keyboard interrupt signal calling #close_keyboard_interrupt() function.
 * 
 * \param[in] signal  Keyboard interrupt signal.
 * 
 * @return            None.
 */
static void terminate_keyboard(int signal){                                                                 // Manage program exit from keyboard ctrl+c shortcut
  /* Body */
  close_keyboard_interrupt(signal);                                                                         // Close SW with fbk due to keyboard interrupt detected (ctrl+c)
}


/*!
 * @brief   <p><b>Static function description:</b></p> Static routine to create test-graph arches, working on graph-library public variables.
 * 
 * @return  None.
 */
static void create_archs(){                                                                                 // Routine to create archs
  /* Body */
  for (int i = 0; i < (int)(sizeof(strts_vect)/sizeof(const Street)); ++i)                                  // Streets allocation FOR cycle
    add_new_arch((C_str)strts_vect[i].name, strts_vect[i].length);                                          // Create new street (arch allocated inside heap)
}


/*!
 * @brief   <p><b>Static function description:</b></p> Static routine to create test-graph nodes, working on graph-library public variables.
 * 
 * @return  None.
 */
static void create_nodes(){                                                                                 // Routine to create nodes
  /* Body */
  for (int j = 0; j < (int)(sizeof(crss_names_vect)/sizeof(C_str)); ++j)                                    // Crosses allocation FOR cycle
    add_new_node(crss_names_vect[j]);                                                                       // Create new cross (node allocated inside heap)
}


/*!
 * @brief   <p><b>Static function description:</b></p> Static routine to create test-graph arch-nodes connections, working on graph-library public variables.
 * 
 * @return  None.
 */
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


/*!
 * @brief                 <p><b>Static function description:</b></p> Static routine to give give to the user the possibility to choose a testing option,
 *                        using pre-defined graph dynamically generated with graph-library functions:
 *                        * <b>Prepared test</b>: find shortest path from 'Cross4' to 'Cross9' nodes (defined with macros #SOURCE_NODE_NAME and #DESTINATION_NODE_NAME), applying Dijkstra's algorithm. In addition, show two special cases: shortest path from 'Cross4' to 'Cross4' (source = destination) and from 'Cross4' to 'Cross10' (unreachble node). In conclusion clear dynamic memory allocated inside heap. This option requires gnuplot to display graphical data.
 *                        * <b>Personalized test</b>: find shortest path from user-defined source and destination nodes, applying Dijkstra's algorithm. In conclusion clear dynamic memory allocated inside heap. This option requires gnuplot to display graphical data.
 *                        * <b>Close test software</b>: clear dynamic memory allocated inside heap and close test software.
 * 
 * \param[in,out] choice  Option chosen by the user (enum).
 * 
 * @return                None.
 */
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


/*!
 * @brief   <p><b>Static function description:</b></p> Static routine to build shortest-path graphical data, working on gnuplt .dat data files (listed below) and defined with macros.
 *          * <b>Test-graph gnuplot data files (gnuplot data source)</b>:
 *            * <b>Archs data file</b>: archs.dat data file which contains the coordinates to draw arches in graph, with target name as comment in the previous line (defined in #ARCHS_DAT_FILE).
 *            * <b>Costs data file</b>: costs.dat data file which contains the coordinates to draw arch-costs in graph, with target name as comment in the previous line (defined in #COSTS_DAT_FILE).
 *            * <b>Nodes data file</b>: nodes.dat data file which contains the coordinates to draw nodes in graph, with target name as comment in the previous line (defined in #NODES_DAT_FILE).
 *          * <b>Test-graph shortest path gnuplot data files (gnuplot data destination of selected elements to graphically recreate the min-cost path)</b>:
 *            * <b>Shortest-path archs data file</b>: shortest_archs.dat data file which contains the coordinates to draw arches in shortest-path graph, with target name as comment in the previous line (defined in #SHORTEST_ARCHS_DAT_FILE).
 *            * <b>Shortest-path costs data file</b>: shortest_costs.dat data file which contains the coordinates to draw arch-costs in shortest-path graph, with target name as comment in the previous line (defined in #SHORTEST_ARCHS_DAT_FILE).
 *            * <b>Shortest-path nodes data file (source-destination nodes excluded)</b>: shortest_nodes.dat data file which contains the coordinates to draw nodes in shortest-path graph (source-destination nodes excluded), with target name as comment in the previous line (defined in #SHORTEST_NODES_DAT_FILE).
 *            * <b>Shortest-path source and destination nodes data file</b>: src_dest_nodes.dat data file which contains the coordinates to draw source and destination nodes in shortest-path graph, with target name as comment in the previous line (defined in #SRC_DEST_NODES_DAT_FILE).
 * 
 * @return  None.
 */
static void build_shortest_path_graphics_data(){                                                            // Routine to build the shortest-path graphics data for gnuplot
  /* Body */
  fbk_nl(1);  fbk_gn_pu("Building shortest-path graphics data (working on .dat files) for gnuplot...");     // Print workin' on gnuplot graphics data files fbk
  // Open .dat files
  Fl archs_dat_file = open_file(ARCHS_DAT_FILE, "r");                                                       // Open test-graph gnuplot arch-coords .dat file in read mode
  Fl costs_dat_file = open_file(COSTS_DAT_FILE, "r");                                                       // Open test-graph gnuplot arches cost-coords .dat file in read mode
  Fl nodes_dat_file = open_file(NODES_DAT_FILE, "r");                                                       // Open test-graph gnuplot node-coords .dat file in read mode
  Fl shortest_archs_dat_file = open_file(SHORTEST_ARCHS_DAT_FILE, "w");                                     // Open test-graph shortest path gnuplot arch-coords .dat file in write mode, clearin' file at open
  Fl shortest_costs_dat_file = open_file(SHORTEST_COSTS_DAT_FILE, "w");                                     // Open test-graph shortest path gnuplot arches cost-coords .dat file in write mode, clearin' file at open
  Fl shortest_nodes_dat_file = open_file(SHORTEST_NODES_DAT_FILE, "w");                                     // Open test-graph shortest path gnuplot node-coords .dat file in write mode, clearin' file at open
  Fl src_dest_nodes_dat_file = open_file(SRC_DEST_NODES_DAT_FILE, "w");                                     // Open test-graph gnuplot source and destination node-coords .dat file in write mode, clearin' file at open
  // Check .dat files correctly opened
  if (archs_dat_file != NULL && costs_dat_file != NULL && nodes_dat_file != NULL &&
      shortest_archs_dat_file != NULL && shortest_costs_dat_file != NULL &&
      shortest_nodes_dat_file != NULL && src_dest_nodes_dat_file != NULL){                                  // If gnuplot .dat files has been correctly opened
    // Vars init to modify gnuplot .dat files
    int tgt_line_num = 0;                                                                                   // Define target-line number var to find path archs/nodes coordinates in test-graph .dat files
    Str tgt_line_str = NULL;                                                                                // Define target-line string var to copy path archs/nodes coordinates from test-graph .dat files to shortest-path and src-dest nodes .dat files
    // Archs
    for (int i = 1; i < min_pth_conn_vect_size; ++i){                                                       // Shortest-path archs scrollin' FOR cycle
      rewind(archs_dat_file);                                                                               // Start/restart scannin' file from line 0
      tgt_line_num = get_substr_line_from_file(archs_dat_file, min_path_conn_vect[i].ar->name);             // Define target line number by shortest-path arch name
      if (tgt_line_num >= 0){                                                                               // If arch name has been found in shortest-path archs
        for (int j = 0; j < 3; ++j, ++tgt_line_num){                                                        // Extract target-line and the two following lines FOR cycle
          rewind(archs_dat_file);                                                                           // Restart scannin' file from line 0
          tgt_line_str = get_line_str_from_file(archs_dat_file, tgt_line_num);                              // Get extracted line content (str)
          if (tgt_line_str != NULL){                                                                        // If target string ain't NULL (no errors and string correctly acquired)
            write_str_on_file(shortest_archs_dat_file, tgt_line_str);                                       // Write extracted string inside dedicated shortest-path gnuplot .dat file
          } else                                                                                            // Else in case of target string null
            fbk_err("Found error durig archs data copy in shortest path file! Check archs .dat file");      // Print error fbk
        }
        write_nl_on_file(shortest_archs_dat_file);                                                          // Write new line inside dedicated shortest-path gnuplot .dat file
      } else                                                                                                // Else in case of no-match found
        fbk_err("Encountred error durig archs data copy in shortest path file! Check archs .dat file");     // Print error fbk
    }
    // Arch-costs
    for (int i = 1; i < min_pth_conn_vect_size; ++i){                                                       // Shortest-path arch-costs scrollin' FOR cycle
      rewind(costs_dat_file);                                                                               // Start/restart scannin' file from line 0
      tgt_line_num = get_substr_line_from_file(costs_dat_file, min_path_conn_vect[i].ar->name);             // Define target line number by shortest-path arch name
      if (tgt_line_num >= 0){                                                                               // If arch name has been found in shortest-path archs
        for (int j = 0; j < 2; ++j, ++tgt_line_num){                                                        // Extract target-line and the following line FOR cycle
          rewind(costs_dat_file);                                                                           // Restart scannin' file from line 0
          tgt_line_str = get_line_str_from_file(costs_dat_file, tgt_line_num);                              // Get extracted line content (str)
          if (tgt_line_str != NULL){                                                                        // If target string ain't NULL (no errors and string correctly acquired)
            write_str_on_file(shortest_costs_dat_file, tgt_line_str);                                       // Write extracted string inside dedicated shortest-path gnuplot .dat file
          } else                                                                                            // Else in case of target string null
            fbk_err("Found error durig costs data copy in shortest path file! Check costs .dat file");      // Print error fbk
        }
        write_nl_on_file(shortest_costs_dat_file);                                                          // Write new line inside dedicated shortest-path gnuplot .dat file
      } else                                                                                                // Else in case of no-match found
        fbk_err("Encountred error durig costs data copy in shortest path file! Check costs .dat file");     // Print error fbk
    }
    // Nodes (source and destination excluded)
    for (int i = 1; i < min_pth_conn_vect_size-1; ++i){                                                     // Shortest-path intermediate-nodes scrollin' FOR cycle
      rewind(nodes_dat_file);                                                                               // Start/restart scannin' file from line 0
      tgt_line_num = get_substr_line_from_file(nodes_dat_file, min_path_conn_vect[i].nd->name);             // Define target line number by shortest-path node name
      if (tgt_line_num >= 0){                                                                               // If node name has been found in shortest-path nodes
        for (int j = 0; j < 2; ++j, ++tgt_line_num){                                                        // Extract target-line and the following line FOR cycle
          rewind(nodes_dat_file);                                                                           // Restart scannin' file from line 0
          tgt_line_str = get_line_str_from_file(nodes_dat_file, tgt_line_num);                              // Get extracted line content (str)
          if (tgt_line_str != NULL){                                                                        // If target string ain't NULL (no errors and string correctly acquired)
            write_str_on_file(shortest_nodes_dat_file, tgt_line_str);                                       // Write extracted string inside dedicated shortest-path gnuplot .dat file
          } else                                                                                            // Else in case of target string null
            fbk_err("Found error durig nodes data copy in shortest path file! Check nodes .dat file");      // Print error fbk
        }
        write_nl_on_file(shortest_nodes_dat_file);                                                          // Write new line inside dedicated shortest-path gnuplot .dat file
      } else                                                                                                // Else in case of no-match found
        fbk_err("Encountred error durig nodes data copy in shortest path file! Check nodes .dat file");     // Print error fbk
    }
    // Source and destination nodes
    for (int i = 0; i < min_pth_conn_vect_size; i += (min_pth_conn_vect_size-1)){                           // Shortest-path source and destination nodes scrollin' FOR cycle
      rewind(nodes_dat_file);                                                                               // Restart scannin' file from line 0
      tgt_line_num = get_substr_line_from_file(nodes_dat_file, min_path_conn_vect[i].nd->name);             // Define target line number by shortest-path node name
      if (tgt_line_num >= 0){                                                                               // If node name has been found in shortest-path nodes
        for (int j = 0; j < 2; ++j, ++tgt_line_num){                                                        // Extract target-line and the following line FOR cycle
          rewind(nodes_dat_file);                                                                           // Restart scannin' file from line 0
          tgt_line_str = get_line_str_from_file(nodes_dat_file, tgt_line_num);                              // Get extracted line content (str)
          if (tgt_line_str != NULL){                                                                        // If target string ain't NULL (no errors and string correctly acquired)
            write_str_on_file(src_dest_nodes_dat_file, tgt_line_str);                                       // Write extracted string inside dedicated shortest-path gnuplot .dat file
          } else                                                                                            // Else in case of target string null
            fbk_err("Found error durig src-dest data copy in shortest path file! Check nodes .dat file");   // Print error fbk
        }
        write_nl_on_file(src_dest_nodes_dat_file);                                                          // Write new line inside dedicated shortest-path gnuplot .dat file
      } else                                                                                                // Else in case of no-match found
        fbk_err("Encountred error durig src-dest data copy in shortest path file! Check nodes .dat file");  // Print error fbk
    }
    // Close .dat files
    close_file(archs_dat_file);                                                                             // Close test-graph gnuplot arch-coords .dat file
    close_file(costs_dat_file);                                                                             // Close test-graph gnuplot arches cost-coords .dat file
    close_file(nodes_dat_file);                                                                             // Close test-graph gnuplot node-coords .dat file
    close_file(shortest_archs_dat_file);                                                                    // Close test-graph shortest path gnuplot arch-coords .dat file
    close_file(shortest_costs_dat_file);                                                                    // Close test-graph shortest path gnuplot arches cost-coords .dat file
    close_file(shortest_nodes_dat_file);                                                                    // Close test-graph shortest path gnuplot node-coords .dat file
    close_file(src_dest_nodes_dat_file);                                                                    // Close test-graph gnuplot source and destination node-coords .dat file
    fbk_nl(1);  fbk_gn_cy("Shortest-path graphics data managenent for gnuplot completed!\n");               // Print Shortest-path graphics data managenent completed fbk
  } else                                                                                                    // Else if gnuplot .dat files ain't been correctly opened
    fbk_err("Ops! Something went wrong during shortest-path graphics data managenent for gnuplot");         // Print err fbk
}


/*!
 * @brief         <p><b>Static function description:</b></p> Static routine to send gnuplot system command string, with the aim of printing graphical data contained inside .dat files.
 *                In case command is the one to print graph and highlight the shortest-path, call a specific function (build_shortest_path_graphics_data()) to manipulate gnuplot data and graphically recreate the min cost path.
 *                Gnuplot system commands listed below:
 *                * <b>Plot graph</b>: calls gnuplot and load plotting command in .cmd file (graph_plot.cmd, defined with a macro: #GPLOT_TEST_GRAPH_LAYOUT_CMD), in order to plot: arches, arch-costs and nodes in graph.
 *                * <b>Plot graph with shortest-path</b>: calls gnuplot and load plotting command in .cmd file (shortest_plot.cmd, defined with a macro: #GPLOT_SHORTEST_PATH_CMD), in order to plot: arches, arch-costs and nodes in graph highlighting the shortest path.
 * 
 * \param[in] cmd Display test-graph gnuplot system command string.
 * 
 * @return        None.
 */
static void display_test_graph(C_str cmd){                                                                  // Routine to display test-graph through gnuplot
  /* Body */
  fbk_gn_pu("Close gnuplot to continue graph-library test..."); fbk_nl(1);                                  // Print close gnuplot to continue fbk
  if (strcmp(cmd, GPLOT_SHORTEST_PATH_CMD) == 0)                                                            // If display command request min path
    build_shortest_path_graphics_data();                                                                    // Routine call to build the shortest-path graphics data for gnuplot
  fflush(stdout);                                                                                           // Force fbk print b4 openin' gnuplot
  int ret_val = system(cmd);                                                                                // Display test-graph layout with gnuplot
  if (ret_val == 0){                                                                                        // Chack command return val, if ok
    fbk_nl(1);  fbk_gn_cy("Test-graph layout correctly displayed with gnuplot!\n");                         // Test-graph layout correctly displayed with gnuplot fbk
  } else                                                                                                    // Else if command return val ain't ok
    fbk_err("Ops! Encountred error during gnuplot command execution, make sure to have gnuplot installed"); // Error fbk
}


/*!
 * @brief                 <p><b>Static function description:</b></p> Static routine to apply Dijkstra's algorithm with verbose-mode enabled, from specified source node (selected by-name and checking if contained in nodes collection).
 *                        Find min-cost paths from specified source node, towards each other node inside allocated graph. Find out if a specific possible destination node is unreachble, or if it corresponds to the source node.
 * 
 * \param[in] src_nd_name Source node name, from which to apply Dijkstra's algorithm.
 * 
 * @return                None.
 */
static void apply_dijkstra(C_str src_nd_name){                                                              // Routine to apply Dijkstra's algorithm
  /* Body */
  dijkstra_alg(src_nd_name, VERBOSE);                                                                       // Apply Dijkstra alg using defined source node (find all min path-costs and prev nodes in shortest paths, Dijkstra-dataset vect allocated/reallocated inside heap) - Y/N for verbose mode
}


/*!
 * @brief                   <p><b>Static function description:</b></p> Static routine to reconstruct min-cost path with verbose-mode enabled, towards specified destination node (from source node defined when calling Dijkstra's algoritm;
 *                          destination node selected by-name, checking if node is contained in nodes collection). Find out if a specific possible destination node is unreachble, or if it corresponds to the source node.
 * 
 * \param[in] dest_nd_name  Destination node name towards which min-cost path must be reconstructed (backwards).
 * 
 * @return                  None.
 */
static void reconstruct_min_path(C_str dest_nd_name){                                                       // Routine to reconstruct min path
  /* Body */
  buid_shortest_path(dest_nd_name, VERBOSE);                                                                // Reconstruct min path to defined destination node startin' from pre-defined source node, (min path connections vect allocated/reallocated inside heap) - Y/N for verbose mode
}


/*!
 * @brief                   <p><b>Static function description:</b></p> Static routine to define source node name for Dijkstra's algorithm function, from user terminal-input. After that, function checks if
 *                          specified node is contained in nodes collection.
 * 
 * \param[in,out] src_nd_nm Source node name terminal-input, for Dijkstra's algorithm.
 * 
 * @return                  None.
 */
static void define_src_node_name(Str* src_nd_nm){                                                           // Routine to define presonalized source-node name
  /* Body */
  for (int i = 0; i < nds_collect_size; ++i){                                                               // Nodes collection vect scrollin' FOR cycle
    fbk_nl(1);  fbk_gn_lbu_ye_str("Node name", nodes_collect_vect[i].name);                                 // Print node name fbk
  }
  do {                                                                                                      // Cycle to define personalized source-node name
    *src_nd_nm = read_term_in_min_chrs(1, "Choose a source node (by name)", "Source node name");            // Read user input str
  } while(idx_by_name(ND, *src_nd_nm) < 0);                                                                 // Check whether node-name specified by the user exists in nodes collection vect, otherwise repeat question
}


/*!
 * @brief                     <p><b>Static function description:</b></p> Static routine to define destination node name from user terminal-input, to be abe to reconstruct min-cost pah from
 *                            source node defined when calling Dijkstra's algorithm. After that, function checks if specified node is contained in nodes collection.
 * 
 * \param[in,out] dest_nd_nm  Destination node name terminal-input, to reconstruct min-cost path.
 * 
 * @return                    None.
 */
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
/*!
 * @brief   <p><b>Function description:</b></p> Main software routine to dynamically allocate a test-graph, asking for graph-library test mode, (eventually) displaying results and graphichs through
 *          gnuplot and finally clearing allocated memory inside heap.
 * 
 * @return  None.
 */
int main(){                                                                                                 // Main SW cycle
  /* Main vars */
  Test_choice choice = 0;                                                                                   // Test choice var

  /* Code */
  signal(SIGINT, terminate_keyboard);                                                                       // Manage program exit from keyboard ctrl+c shortcut
  logo(6, "GRAPHS MANAGEMENT LIBRARY TEST SOFTWARE", LBU, '#', OG);                                         // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  press_enter("Hi");                                                                                        // Press enter to start SW fbk
  unused = read_term_in_int();  ///// ------------------------------ ///// ?????????????????
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
  if (choice == PREPARED || choice == PERSONALIZED){                                                        // If exit mode ain't been selected
    // (2.3) Display test-graph layout with gnuplot                                                         // --------------------------------------------------------- (2.3)
    fbk_nl(2);  fbk_separator(SEP_CHR, OG);                                                                 // Print separator fbk
    fbk_nl(1);  fbk_gn_pu("(2.3) Displayin' test-graph layout with gnuplot...");                            // Print displayin' test-graph layout with gnuplot fbk
    fbk_nl(1);  fbk_separator(SEP_CHR, OG); fbk_nl(2);                                                      // Print separator fbk
    display_test_graph(GPLOT_TEST_GRAPH_LAYOUT_CMD);                                                        // Routine call to display test-graph through gnuplot
  }                                                                                                         //
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
      if (min_pth_conn_vect_size > 1){                                                                      // If min path contains at least src and dest nodes
        fbk_nl(2);  fbk_separator(SEP_CHR, OG);                                                             // Print separator fbk
        fbk_nl(1);  fbk_gn_pu("(3.3.1) Displayin' test-graph and shortest path with gnuplot (Cr4-Cr9)..."); // Print displayin' test-graph layout and shortest path with gnuplot fbk
        fbk_nl(1);  fbk_separator(SEP_CHR, OG); fbk_nl(2);                                                  // Print separator fbk
        display_test_graph(GPLOT_SHORTEST_PATH_CMD);                                                        // Routine call to display test-graph through gnuplot
      }                                                                                                     //
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
      if (min_pth_conn_vect_size > 1){                                                                      // If min path contains at least src and dest nodes
        fbk_nl(2);  fbk_separator(SEP_CHR, OG);                                                             // Print separator fbk
        fbk_nl(1);  fbk_gn_pu("(3.3.2) Displayin' test-graph and shortest path with gnuplot...");           // Print displayin' test-graph layout and shortest path with gnuplot fbk
        fbk_nl(1);  fbk_separator(SEP_CHR, OG); fbk_nl(2);                                                  // Print separator fbk
        display_test_graph(GPLOT_SHORTEST_PATH_CMD);                                                        // Routine call to display test-graph through gnuplot
      }                                                                                                     //
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
