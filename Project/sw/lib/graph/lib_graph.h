/*
 * Author: Cristian Merli
 * Code title: Graph library header file
 * Code version: 1.0
 * Creation date: 22/06/2021
 * Last mod. date: 04/07/2021 
 */


/* Libraries */
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file
#include <limits.h>                                                                                         // Include limits library (for _DBL_MAX_ --> Real max val to simulate +inf)


/* Constants */
const Real _REAL_MAX_ = __DBL_MAX__;                                                                        // Real max val to simulate +inf


/* Structs & data-types */
typedef struct list_elem {                                                                                  // List element struct typedef for list creation (element, next element in list)
  struct arch*      ar;                                                                                     // List element, arch ptr in this list position
  struct list_elem* nxt;                                                                                    // Next list element, arch ptr in next list position
} List_elem;

typedef List_elem* List;                                                                                    // List of elements (list head element ptr) typedef

typedef struct node {                                                                                       // Node struct typedef (list of arches and Dijkstra-dataset ptr)
  List archs_lst;                                                                                           // Arches list
  struct dijkstra_dataset* dd;                                                                              // Dijkstra-dataset pointer
} Node;

typedef Node* Graph_node;                                                                                   // Graph-node (aka Node ptr) typedef

typedef struct arch {                                                                                       // Arch struct typedef (node1 ptr, arch cost, node2 ptr)
  Graph_node  nd1;                                                                                          // Node1 pointer
  Real        cost;                                                                                         // Arch cost
  Graph_node  nd2;                                                                                          // Node2 pointer
} Arch;

typedef Arch* Graph_arch;                                                                                   // Graph-arch (aka Arch ptr) typedef

typedef struct dijkstra_dataset {                                                                           // Dijkstra-dataset struct typedef (prev node ptr, min path cost, node analyzed flag)
  Graph_node  prev_nd;                                                                                      // Previous node pointer
  Real        min_path_cost;                                                                                // Min path cost
  Byte        an_flg;                                                                                       // Node analyzed flag
} Dijkstra_dataset;

typedef struct connection {                                                                                 // Node connection struct typedef (node ptr, connection arch ptr)
  Graph_node  nd;                                                                                           // Node pointer
  Graph_arch  conn_ar;                                                                                      // Connection arch pointer
} Connection;


/* Enums & data-types */
typedef const enum vect_coords {V, V2, V3} Vect_coords;                                                     // Matrix/vectors enum typedef

typedef const enum verbose_mode {Y, N} Verbose_mode;                                                        // Verbose mode enum typedef

typedef const enum node_pos_in_arch {ARCH_ND1, ARCH_ND2} Node_pos_in_arch;                                  // Node position in arch enum typedef
C_str node_pos_in_arch_str[] = {"ARCH NODE1 POSITION", "ARCH NODE2 POSITION"};                              // Node position in arch enum typedef strings array

typedef enum arch_pos_typ {LIST_HEAD, LIST_POS, LIST_TAIL} Arch_pos_typ;                                    // Position type to add arch in node arches connections list enum typedef
C_str arch_pos_typ_str[] = {"LIST HEAD POSITION", "LIST SPECIFIC POSITION", "LIST TAIL POSITION"};          // Position type to add arch in node arches connections list enum typedef strings array


/* Library functions */
void add_new_arch(C_real cost);                                                                             // Function to add new graph arch (arch allocated inside heap)

void add_new_node();                                                                                        // Function to add new graph node (node allocated inside heap)

void connect_node_arch(C_int ar_num, C_int nd_num, Node_pos_in_arch nd_pos, Arch_pos_typ ar_pos, ...);      // Function to connect arch-node in graph, non-zero index (new arch list element allocated inside heap, opt param --> arch pos, non-zero index)

void dijkstra_alg(C_int src_nd_num, C_int dest_nd_num);                                                     // Dijkstra alg 2 find min graph-path btwn source and destination nodes (non-zero index)

void free_graph();                                                                                          // Function to free graph allocated memory
