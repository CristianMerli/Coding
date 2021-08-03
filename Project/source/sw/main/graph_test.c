/*
 * Author: Cristian Merli
 * Code title: Graph test
 * Code version: 3.0
 * Creation date: 22/06/2021
 * Last mod. date: 16/07/2021
 */


/*!
 * @page        page1 1 - General notes about software
 * @brief       General notes, informations and warnings about the software.
 * 
 * ---
 * 
 * @section     section1 Software info:
 * 
 * @author      Cristian Merli
 * @date        16/07/2021
 * @version     3.0 - Completed 16/05/2021
 * 
 * @note        Important notes:
 *                * Graphical effects are managed by gnuplot (based on data manipulated by test software main program), so it is highly recommended to have it installed.
 *                * It is possibile to compile, run and execute further actions taking advantege of makefile, <i>for more informations see doxygen <b><a href="page3.html">'Makefile'</a></b> section inside <b>'Related pages'</b> (or main makefile commands in <b><a href="index.html">'Main page'</a></b>).</i>
 * @warning     Important warnings:
 *                * Pay attention, arch/node names must only be max 30 chars long. To modify max names lenght, change relative macros inside 'lib_graph.h' header file: #AR_STR_LEN and #ND_STR_LEN.
 *                * User-interface library is now set to have an input buffer able to take max 63 chars strings + '\0'; to modify terminal-input buffer size see #IN_BUFF_SIZE macro.
 *                * Similarly, files-library is now set to have an input buffer able to take max 1023 chars strings + '\0' (for each file line); to modify file-input buffer size see #FILE_IN_BUFF_SIZE macro.
 *                * If there is need to modify graph-structe, gnuplot archs.dat, costs.dat and costs.dat files needs to be manually updated to have reliable graphical representations.
 * @bug         No known bugs.
 * 
 * ---
 * 
 * @section     section2 Code:
 *              Dijkstra's algorithm (contained in graph-library) test software.
 * @subsection  subsection1 Code details:
 *              Software to test Dijkstra's algorithm function placed inside graph-library.
 *              This function has the purpose of finding the shortest path between source and destination nodes. Through this software, it is possible to run two different types
 *              of test (<i>for more info, see <b><a href="page2.html">'Testing software'</a></b> section inside doxygen <b>'Related pages'</b></i>):
 *              * Prepared test.
 *              * Personalized test.
 * @subsection  subsection2 Manual compiling operations:
 *              Manual compiling and linking operations, alternative to the automated commands in <a href="page3.html">'makefile'</a>:
 *              * <b>Aliases:</b>
 *                * alias gccW99_o="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -o"
 *                * alias gccW99_c="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -c -o"
 *                * alias gccW99_lib="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -fpic -shared -o"
 *              * <b>Compile-commands:</b>
 *                * gccW99_lib lib/graph/lib_graph.so lib/graph/lib_graph.c   &nbsp;&nbsp;--> <i>Create GRAPH dynamic library object file.</i>
 *                * gccW99_lib lib/ui/lib_ui.so lib/ui/lib_ui.c               &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;--> <i>Create UI (TERMINAL I/O) dynamic library object file.</i><br/>
 *                * gccW99_lib lib/files/lib_files.so lib/files/lib_files.c   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;--> <i>Create FILES dynamic library object file.</i>
 *                * gccW99_lib lib/timer/lib_timer.so lib/timer/lib_timer.c   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;--> <i>Create TIMER dynamic library object file.</i>
 *                * gccW99_c main/graph_test.o main/graph_test.c              &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;--> <i>Create MAIN object file.</i>
 *              * <b>Link-command:</b>
 *                * gccW99_o graph_test main/graph_test.o lib/graph/lib_graph.so lib/ui/lib_ui.so lib/files/lib_files.so lib/timer/lib_timer.so  &nbsp;&nbsp;--> <i>LINK main and dynamic libraries object files to test executable.</i>
 * 
 * ---
 * 
 * @section     section3 Copyright &copy;
 *              This project has been realized respecting copyright. Software know-how and documentation have been personally developed. Available pictures are gnuplot exports and terminal-outputs screens, taken during software testing stage and documentation drafting.
 *              Icons are open-source images, coming from free downloading websites (correctly cited as requested from contents developers). Gif animations, have been taken from wikipedia.
 * @subsection  subsection3 Pictures:
 *              Pictures in this software documentation have been personally realized, taking screens of software's terminal-outputs and exporting .png images, from personally-developed gnuplot scripts.
 * @subsection  subsection4 Animations:
 *              Gif animations are from <a href="https://en.wikipedia.org/wiki/Dijkstra's_algorithm">www.wikipedia.org</a>
 * @subsection  subsection5 Logo and other icons:
 *              Logo and other icons, have been downloaded from <a href="https://www.flaticon.com/">flaticon</a> free-images website as free user, respecting indicated <a href="https://support.flaticon.com/hc/en-us/articles/207248209-Attribution-How-when-and-where-">attribution rules</a>.<br/>
 *              @image html logo.png "Documentation logo-icon"
 *              <center>Logo icon made by <a href="https://www.flaticon.com/authors/becris">Berics</a> from <a href="https://www.flaticon.com/free-icon/neural_2103658?related_id=2103633&origin=search#">www.flaticon.com</a></center>
 */


/*!
 * @page        page2 2 - Testing software
 * @brief       Graph-library test software main code file info
 * 
 * ---
 * 
 * @section     section4 Main code description:
 *              Main code has the aim of testing graph-library, in particular Dijkstra's algorithm implementation (file graph_test.c).
 * @subsection  subsection6 Main code details:
 *              The main code consists in a set of functions which are called to test graph-library, in particular Dijkstra's algorithm implementation: #dijkstra_alg() and #buid_shortest_path() functions.
 *              Once test software has been compiled and launched through <b><a href="page3.html">'makefile'</a></b> commands, it will display a logo by means of #logo() function call, and will wait for <b>enter</b>
 *              key to be pressed (with function #press_enter()), in order to start flowing through the main code inside #main() function.
 *              At this point test-software program flow, will be explained below using numbers identifying chapters and sub-chapters, which compose the main function (reported in comments and also printed on terminal):
 *              * <b>(1) Arches and nodes allocation inside heap:</b>
 *                * <b>(1.1) Arches allocation inside heap:</b> #create_archs() routine call to allocate arches defined in #strts_vect[] test vector of #street.
 *                * <b>(1.2) Nodes allocation inside heap:</b> #create_nodes() routine call to allocate nodes defined in #crss_names_vect[] test vector of #C_str.
 *              * <b>(2) Test-graph creation (connecting arches and nodes together) and testing option choice:</b>
 *                * <b>(2.1) Connect arches and nodes (excluding node 'Cross10'):</b> #create_connections() routine call to connect arches and nodes in a certain way.
 *                * <b>(2.2) Testing mode choice:</b> #test_option_choice() routine call to choose which testing mode to adopt.
 *                  * <b>(2.2.1) In case selected #test_choice is not #EXIT, display test-graph:</b> #display_test_graph(#GPLOT_TEST_GRAPH_LAYOUT_CMD) routine call to graphically displaying test-graph allocated structure.
 *              * <b>(3) Dijkstra's algorithm implementation to find shortest path:</b>
 *                * <b>(3.x.1) Prepared test:</b> in case selected #test_choice is #PREPARED, use source and destination nodes defined in #SOURCE_NODE_NAME and #DESTINATION_NODE_NAME macros. Then show two special cases with a debug print.
 *                  * <b>(3.1.1) Apply Dijkstra's algorithm:</b> #apply_dijkstra(#SOURCE_NODE_NAME) routine call to find min-cost paths from #SOURCE_NODE_NAME towards each other node inside #nodes_collect_vect.
 *                  * <b>(3.2.1) Reconstruct test min-path:</b> #reconstruct_min_path(#DESTINATION_NODE_NAME) routine call to reconstruct shortest path towards #DESTINATION_NODE_NAME (from #SOURCE_NODE_NAME); path saved inside #min_path_conn_vect.
 *                  * <b>(3.3.1) Display test-graph layout and shortest path with gnuplot:</b> #display_test_graph(#GPLOT_SHORTEST_PATH_CMD) routine call in case shortest-path is not trivial.
 *                  * <b>(3.4.1) Reconstruct some special-cases paths:</b> #reconstruct_min_path(#DEST_NODE_NAME_SPECIAL_CASE1) and #reconstruct_min_path(#DEST_NODE_NAME_SPECIAL_CASE2) routines call to show how special cases are handled <i>(<b>special-case1:</b> source node = destination node / <b>special-case2:</b> destination node unreachble).
 *                * <b>(3.x.2) Personalized test:</b> in case selected #test_choice is #PERSONALIZED, ask the user to choose personalized source and destination nodes by-name.
 *                  * <b>(3.1.2) Apply Dijkstra's algorithm:</b> #define_src_node_name() and #apply_dijkstra() routines call to find min-cost paths from user-defined source node towards each other node inside #nodes_collect_vect.
 *                  * <b>(3.2.2) Reconstruct personalized min-path:</b> #define_dest_node_name() and #reconstruct_min_path() routines call to reconstruct shortest path towards user-defined destination node (from user-defined source node); path saved inside #min_path_conn_vect.
 *                  * <b>(3.3.2) Display test-graph layout and shortest path with gnuplot:</b> #display_test_graph(#GPLOT_SHORTEST_PATH_CMD) routine call in case shortest-path is not trivial.
 *              * <b>(4) Allocated graph-structure deallocation:</b>
 *                  * <b>(4.1) Deallocate the whole graph structure:</b> #free_graph() routine call to clear allocated memory inside heap.
 *              
 *              Once this point has been reached, the software will be closed with goodbye feedback on terminal by calling #close_fbk() function.<br/><br/><br/>
 *              @image html test.png
 *              <br/><center>Icon made by <a href="https://www.flaticon.com/authors/freepik">Freepik</a> from <a href="https://www.flaticon.com/premium-icon/test_2995522?term=testing&page=1&position=5&page=1&position=5&related_id=2995522&origin=search#">www.flaticon.com</a></center>
 * 
 * @file        graph_test.c <i>More info in <b><a href="page2.html">'Testing software'</a></b> section inside doxygen <b>'Related pages'</b>.</i>
 * @brief       <b>Graph-library test software main code file</b>
 * 
 * @file        graph_test.o <i>Object file generated from graph_test.c during compiling operations.</i>
 * @brief       <b>Graph-library test software main object file</b>
 * 
 * @file        graph_test <i>Executable file generated from graph_test.c during compiling operations.</i>
 * @brief       <b>Graph-library test software main executable file</b>
 */


/*!
 * @page        page3 3 - Makefile
 * @brief       Software makefile info
 * 
 * ---
 * 
 * @section     section5 Makefile description:
 *              Makefile has the main purpose of automating software compiling/linking operations.<br/>
 * @subsection  subsection7 Makefile details:
 *              In this project, makefile purposes has been extended in order to take care of further actions to simplify testing operations and documentation management.
 *              So the makefile can handle different tasks like: compiling/launching the software, to make/view doxygen documentation and displaying LaTeX abstract pdf.
 *              As can be seen inside makefile (<i>accessible in <b><a href="makefile_source.html">'makefile'</a></b> section of doxygen <b>'File list'</b></i>), the file has
 *              been divided in chapters and sub-chapters to be better explained in this page:
 *              * <b>(1) Variables and files:</b>
 *                * <b>(1.1) Variables to compile and run software:</b> compiling flags for libraries and main program, for linking and command to run the software.
 *                * <b>(1.2) Source files:</b> graph-library, user-interface-library, files-library, timer-library and main program code files.
 *                * <b>(1.3) Header files:</b> graph-library, user-interface-library, files-library and timer-library header files.
 *                * <b>(1.4) Output files:</b> software executable, graph-library, user-interface-library, files-library, timer-library and main program object files.
 *                * <b>(1.5) Doxygen documentation:</b> doxygen-configuration file, doxygen-exports folder and doxygen main html page.
 *                * <b>(1.6) Abstract pdf file (from LaTeX):</b> LaTeX abstract exported (.pdf) file, containing theoretical aspects about Dijkstra's algorithm.<br/><br/>
 *              * <b>(2) Make commands</b>
 *                * <b>(2.1) Compile and link all files:</b> command to compile and link all software's files.
 *                * <b>(2.2) Run test software (main program):</b> command to run test software.
 *                * <b>(2.3) Compile-link all files and run test software (main program):</b> chapter <b>(2.1)</b> and chapter <b>(2.2)</b> in one shortcut-command.
 *                * <b>(2.4) Commands to compile and link software step-by-step:</b> commands to compile graph-library, user-interface-library, files-library, timer-library, main program and command to link all the software's files.<br/>
 *                * <b>(2.5) Clear:</b> command to clear all the software's generated files.
 *                * <b>(2.6) Export/view/clear doxygen html documentation:</b> command to view documentation in browser, command to re-generate documentation, shortcut-command to re-generate and view documentation in browser, command to clear documentation, and shortcut-command to clear and re-generate documentation.<br/>
 *                * <b>(2.7) Open abstract pdf file (made with LaTeX):</b> command to open <b>'relazione-finale-CRISTIAN-MERLI.pdf'</b> file using the predefined pdf-viewer software.
 * @subsection  subsection8 Available makefile commands:
 *              <i><b>Note:</b> in order to correctly execute makefile's commands, the user must be inside <b>'Project/sw/'</b> folder (same folder of the makefile).</i><br/>
 *              <i><b>Note:</b> makefile commands-syntax</i> <b>make [command]</b><i>, available commands listed below.</i>
 *              * <b> Software compiling commands:</b>
 *                * <b>make:</b> command to compile and link the whole project to executable (shortcut command of the following one).
 *                * <b>make all:</b> same command as above, full-name command.
 *                * <b>make run:</b> command to launch test-software executable.
 *                * <b>make all_run:</b> shortcut-command to compile/link the whole project to test-software executable and to run it.
 *                * <b>make clr:</b> command to clear all the software's generated files.
 *              * <b> Software step-by-step compiling commands:</b>
 *                * <b>make compile_lib_graph:</b> command to compile only the graph-library.
 *                * <b>make compile_lib_ui:</b> command to compile only the user-interface-library.
 *                * <b>make compile_lib_files:</b> command to compile only the files-library.
 *                * <b>make compile_lib_timer:</b> command to compile only the timer-library.
 *                * <b>make compile_main:</b> command to compile only the main program (test software).
 *                * <b>make link_all:</b> command to link all libraries and main program to test-software executable.
 *              * <b> Doxygen documentation commands:</b>
 *                * <b>make docs:</b> command to open browser in order to display doxygen html documentation.
 *                * <b>make docs_gen:</b> command to re-generate doxygen html (and rtf) documentation.
 *                * <b>make docs_gen_view:</b> shortcut-command to re-generate doxygen html (and rtf) documentation and to open browser displaying doxygen html documentation.
 *                * <b>make docs_clr:</b> command to clear generated doxygen html (and rtf) documentation.
 *                * <b>make docs_clr_gen:</b> shortcut-command to clear and re-generate doxygen html (and rtf) documentation.
 *              * <b> LaTeX abstract (pdf) command:</b>
 *                * <b>make abstract:</b> command to open and view LaTeX exported pdf file through the predefined pdf-viewer software.<br/><br/><br/>
 *              @image html m.png
 *              <br/><center>Icon made by <a href="https://www.flaticon.com/authors/freepik">Freepik</a> from <a href="https://www.flaticon.com/free-icon/m_3600932?term=m&page=1&position=1&page=1&position=1&related_id=3600932&origin=search#">www.flaticon.com</a></center>
 * 
 * @file        makefile <i>More info in <b><a href="page3.html">'Makefile'</a></b> section inside doxygen <b>'Related pages'</b>.</i>
 * @brief       <b>Makefile to compile/run software, make/view doxygen documentation and view LaTeX abstract pdf</b>
 */


/*!
 * @page        page4 4 - Gnuplot
 * @brief       Info about graphical representations through gnuplot
 * 
 * ---
 * 
 * @section     section6 Gnuplot description:
 *              In this software, gnuplot is called to manage graphical representations.
 * @subsection  subsection9 Gnuplot details:
 *              Gnuplot is called via two different plotting scripts, to recreate graphical representations of graph's data and Dijkstra's algorithm function output;
 *              highlighting the shortest path between specified source and destination nodes. These two gnuplot scripts are launched by main testing code,
 *              through #display_test_graph() function. The first plotting script, loads static data inserted by developer in three (.dat) files; while the second one, loads dynamically
 *              manipulated data by the software, from the inside of four other (.dat) files. In particular, data manipulating operations picks information of interest
 *              from the three static gnuplot data files, and inserts them insede the four dynamic gnuplot data files. Dynamic files are modified through #build_shortest_path_graphics_data()
 *              routine call, in main testing code.
 *              * <b>Gnuplot scripts:</b>
 *                * <b>Graph-structure plotting command:</b> graph_plot.cmd file, system command defined using #GPLOT_TEST_GRAPH_LAYOUT_CMD macro.
 *                * <b>Graph-structure and detected shortest path plotting command:</b> shortest_plot.cmd file, system command defined using #GPLOT_SHORTEST_PATH_CMD macro.<br/><br/>
 *              * <b>Gnuplot data-files:</b>
 *                * <b>Static data-files:</b>
 *                  * <b>Archs data file:</b> archs.dat, defined using #ARCHS_DAT_FILE macro. This file contains the arches to be drawn in purple during graph-structure plotting and gray during shortest path plotting.
 *                  * <b>Arch-costs data file:</b> costs.dat, defined using #COSTS_DAT_FILE macro. This file contains the arch-costs to be drawn in blue during graph-structure plotting and gray during shortest path plotting.
 *                  * <b>Nodes data file:</b> nodes.dat, defined using #NODES_DAT_FILE macro. This file contains the nodes to be drawn in black/white during graph-structure plotting and gray/white during shortest path plotting.
 *                * <b>Dynamic data-files:</b>
 *                  * <b>Shortest path archs data file:</b> shortest_archs.dat, defined using #SHORTEST_ARCHS_DAT_FILE macro. This file contains the arches to be drawn in green during shortest path plotting.
 *                  * <b>Shortest path arch-costs data file:</b> shortest_costs.dat, defined using #SHORTEST_COSTS_DAT_FILE macro. This file contains the arch-costs to be drawn in blue during shortest path plotting.
 *                  * <b>Shortest path nodes data file (source-destination nodes excluded):</b> shortest_nodes.dat, defined using #SHORTEST_NODES_DAT_FILE macro. This file contains the nodes to be drawn in green during shortest path plotting.
 *                  * <b>Shortest path source and destination nodes data file:</b> src_dest_nodes.dat, defined using #SRC_DEST_NODES_DAT_FILE macro. This file contains the nodes to be drawn in violet during shortest path plotting.<br/><br/><br/>
 *              @image html plot.png
 *              <br/><center>Icon made by <a href="https://www.flaticon.com/authors/freepik">Freepic</a> from <a href="https://www.flaticon.com/free-icon/pencil_603519?term=drawing&page=1&position=13&page=1&position=13&related_id=603519&origin=search#">www.flaticon.com</a></center>
 * 
 * @file        archs.dat <i>More info in <b><a href="page4.html">'Gnuplot'</a></b> section inside doxygen <b>'Related pages'</b>.</i>
 * @brief       <b>Static file containing data to plot archs inside graph using gnuplot</b>
 * 
 * @file        costs.dat <i>More info in <b><a href="page4.html">'Gnuplot'</a></b> section inside doxygen <b>'Related pages'</b>.</i>
 * @brief       <b>Static file containing data to plot arch-costs inside graph using gnuplot</b>
 * 
 * @file        nodes.dat <i>More info in <b><a href="page4.html">'Gnuplot'</a></b> section inside doxygen <b>'Related pages'</b>.</i>
 * @brief       <b>Static file containing data to plot nodes inside graph using gnuplot</b>
 * 
 * @file        shortest_archs.dat <i>More info in <b><a href="page4.html">'Gnuplot'</a></b> section inside doxygen <b>'Related pages'</b>.</i>
 * @brief       <b>Dynamic file containing data to plot shortest-path archs inside graph using gnuplot (green)</b>
 * 
 * @file        shortest_costs.dat <i>More info in <b><a href="page4.html">'Gnuplot'</a></b> section inside doxygen <b>'Related pages'</b>.</i>
 * @brief       <b>Dynamic file containing data to plot shortest-path arch-costs inside graph using gnuplot (blue)</b>
 * 
 * @file        shortest_nodes.dat <i>More info in <b><a href="page4.html">'Gnuplot'</a></b> section inside doxygen <b>'Related pages'</b>.</i>
 * @brief       <b>Dynamic file containing data to plot shortest-path nodes inside graph using gnuplot (green)</b>
 * 
 * @file        src_dest_nodes.dat <i>More info in <b><a href="page4.html">'Gnuplot'</a></b> section inside doxygen <b>'Related pages'</b>.</i>
 * @brief       <b>Dynamic file containing data to plot shortest-path source and destination nodes inside graph using gnuplot (purple)</b>
 * 
 * @file        graph_plot.cmd <i>More info in <b><a href="page4.html">'Gnuplot'</a></b> section inside doxygen <b>'Related pages'</b>.</i>
 * @brief       <b>Gnuplot sctipt to plot graph structure</b>
 * 
 * @file        shortest_plot.cmd <i>More info in <b><a href="page4.html">'Gnuplot'</a></b> section inside doxygen <b>'Related pages'</b>.</i>
 * @brief       <b>Gnuplot sctipt to plot graph structure with shortest-path</b>
 */


/* Libraries */
#include "../lib/graph/lib_graph.h"                                                                         // Import graph library header file
#include "../lib/files/lib_files.h"                                                                         // Import files library header file


/* Constants */
/// <b>Macro description:</b> Advanced verbose mode </i>(Y/N)</i> for #dijkstra_alg() and #buid_shortest_path() functions.
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
 * @param[in] signal  Keyboard interrupt signal.
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
 * @param[in,out] choice  Option chosen by the user (enum).
 * 
 * @return                None.
 * 
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
 *            * <b>Shortest-path costs data file</b>: shortest_costs.dat data file which contains the coordinates to draw arch-costs in shortest-path graph, with target name as comment in the previous line (defined in #SHORTEST_COSTS_DAT_FILE).
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
        fbk_err("Encountered error durig archs data copy in shortest path file! Check archs .dat file");    // Print error fbk
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
        fbk_err("Encountered error durig costs data copy in shortest path file! Check costs .dat file");    // Print error fbk
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
        fbk_err("Encountered error durig nodes data copy in shortest path file! Check nodes .dat file");    // Print error fbk
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
        fbk_err("Encountered error durig src-dest data copy in shortest path file! Check nodes .dat file"); // Print error fbk
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
 *                * <b>Plot graph</b>: calls gnuplot and loads plotting command in .cmd file (graph_plot.cmd, defined with a macro: #GPLOT_TEST_GRAPH_LAYOUT_CMD), in order to plot: arches, arch-costs and nodes in graph. @image html test_graph.png "Image displayed by gnuplot when calling graph-plotting command"<br/><br/>
 *                * <b>Plot graph with shortest-path</b>: calls gnuplot and loads plotting command in .cmd file (shortest_plot.cmd, defined with a macro: #GPLOT_SHORTEST_PATH_CMD), in order to plot: arches, arch-costs and nodes in graph highlighting the shortest path. @image html personalized_shortest_path.png "Image displayed by gnuplot when calling shortest path graph-plotting command (in this particular case, from predefined testing mode)"<br/><br/>
 * 
 * @param[in] cmd Display test-graph gnuplot system command string.
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
    fbk_err("Ops! Encountered error during gnuplot command exec, make sure to have gnuplot installed");     // Error fbk
}


/*!
 * @brief                 <p><b>Static function description:</b></p> Static routine to apply Dijkstra's algorithm with verbose-mode enabled, from specified source node (selected by-name and checking if contained in nodes collection).
 *                        Find min-cost paths from specified source node, towards each other node inside allocated graph. Find out if a specific possible destination node is unreachble, or if it corresponds to the source node.
 * 
 * @param[in] src_nd_name Source node name, from which to apply Dijkstra's algorithm.
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
 * @param[in] dest_nd_name  Destination node name towards which min-cost path must be reconstructed (backwards).
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
 * @param[in,out] src_nd_nm Source node name terminal-input, for Dijkstra's algorithm.
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
 * @param[in,out] dest_nd_nm  Destination node name terminal-input, to reconstruct min-cost path.
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
    // (2.2.1) Display test-graph layout with gnuplot                                                       // --------------------------------------------------------- (2.2.1)
    fbk_nl(2);  fbk_separator(SEP_CHR, OG);                                                                 // Print separator fbk
    fbk_nl(1);  fbk_gn_pu("(2.2.1) Displayin' test-graph layout with gnuplot...");                          // Print displayin' test-graph layout with gnuplot fbk
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
      // (3.2.1) Reconstruct test min-path (from Cross4 to Cross9)                                          // --------------------------------------------------------- (3.2.1)
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
      // (3.2.2) Reconstruct personalized min-path                                                          // --------------------------------------------------------- (3.2.2)
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
}



/* Task */
/* 
 * Final project (G3 - number 3) --> Dijkstra's algorithm.
 */
