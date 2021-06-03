/*
 * Author: Cristian Merli
 * Code title: Graph library header file
 * Code version: 2.0
 * Creation date: 21/05/2021
 * Last mod. date: 03/06/2021 
 */


/* Libraries */
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file


/* Constants */
//


/* Structs & data-types */
typedef struct list_elem {                                                                                  // List element struct typedef for list creation (element, next element in list)
  struct arch*      ar;                                                                                     // List element, arch ptr in this list position
  struct list_elem* nxt;                                                                                    // Next list element, arch ptr in next list position
} List_elem;

typedef List_elem* List;                                                                                    // List of elements (list head element ptr) typedef

typedef struct node {                                                                                       // Node struct typedef (list of arches)
  List archs_lst;                                                                                           // Arches list
} Node;

typedef Node* Graph_node;                                                                                   // Graph-node (aka Node ptr) typedef

typedef struct arch {                                                                                       // Arch struct typedef (node1 ptr, arch cost, node2 ptr)
  Graph_node  nd1;                                                                                          // Node1 pointer
  Real        cost;                                                                                         // Arch cost
  Graph_node  nd2;                                                                                          // Node2 pointer
} Arch;

typedef Arch* Graph_arch;                                                                                   // Graph-arch (aka Arch ptr) typedef


/* Enums & data-types */
typedef const enum vect_coords {V, V2, V3} Vect_coords;                                                     // Matrix/vectors enum typedef

typedef const enum verbose_mode {Y, N} Verbose_mode;                                                        // Verbose mode enum typedef

typedef const enum node_pos_in_arch {ARCH_ND1, ARCH_ND2} Node_pos_in_arch;                                  // Node position in arch enum typedef
C_str node_pos_in_arch_str[] = {"ARCH NODE1 POSITION", "ARCH NODE2 POSITION"};                              // Node position in arch enum typedef strings array

typedef enum arch_pos_typ {LIST_HEAD, LIST_POS, LIST_TAIL} Arch_pos_typ;                                    // Position type to add arch in node arches connections list enum typedef
C_str arch_pos_typ_str[] = {"LIST HEAD POSITION", "LIST SPECIFIC POSITION", "LIST TAIL POSITION"};          // Position type to add arch in node arches connections list enum typedef strings array


/* Library functions */
Graph_arch add_new_arch(C_real cost);                                                                       // Function to add new graph arch (arch allocated inside heap)

Graph_node add_new_node();                                                                                  // Function to add new graph node (node allocated inside heap)

void connect_node_arch(Graph_node* nd, Graph_arch* ar, Node_pos_in_arch nd_pos, Arch_pos_typ ar_pos, ...);  // Function to connect arch-node in graph (new anch list element allocated inside heap, opt param --> arch pos, non-zero index)

Graph_arch* archs_connected_to_node(const Graph_node* const nd, int* const vect_size, Verbose_mode v_mode); // Function to get a vector of arche ptrs connected to a node (vector allocated inside heap) - Y/N for verbose mode

Graph_node* nodes_connected_to_node(const Graph_node* const nd, int* const vect_size);                      // Function to get a vector of node ptrs connected to a node (vector allocated inside heap)

void print_archs_costs(Graph_node* const start_nd);                                                         // Function to print all the arches costs, starting from a specified node and moving through the whole graph structure

// void free_graph(Graph_arch* archs_collec_vect, int *const ar_num,
//                  Graph_node* nodes_collec_vect, int *const nd_num);                                          // Function to free graph allocated memory

