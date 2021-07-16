/*
 * Author: Cristian Merli
 * Code title: Graph library header file
 * Code version: 3.0
 * Creation date: 22/06/2021
 * Last mod. date: 14/07/2021 
 */


/* Libraries */
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file
#include "../timer/lib_timer.h"                                                                             // Import timer library header file
#include <limits.h>                                                                                         // Include limits library (for _DBL_MAX_ --> Real max val to simulate +inf)


/* Constants */
#define ND_STR_LEN        31                                                                                // String length used to define node-names (max 30 chars + '\0')
#define AR_STR_LEN        31                                                                                // String length used to define arch-names (max 30 chars + '\0')
#define SEP_CHR           '-'                                                                               // Separator-char
#define SHORT_PTH_SEP_CHR '*'                                                                               // Shortest path separator-char
#define PRINT_DLY_MS      500                                                                               // Print delay [ms]


/* Structs & data-types */
typedef struct list_elem {                                                                                  // List element struct typedef for list creation (element, next element in list)
  struct arch*      ar;                                                                                     // List element, arch ptr in this list position
  struct list_elem* nxt;                                                                                    // Next list element, arch ptr in next list position
} List_elem;

typedef List_elem* List;                                                                                    // List of elements (list head element ptr) typedef

typedef struct node {                                                                                       // Node struct typedef (node name, list of arches and Dijkstra-dataset ptr)
  char                      name[ND_STR_LEN];                                                               // Node name
  List                      archs_lst;                                                                      // Arches list
  struct dijkstra_dataset*  dd;                                                                             // Dijkstra-dataset pointer
} Node;

typedef Node* Graph_node;                                                                                   // Graph-node (aka Node ptr) typedef

typedef struct arch {                                                                                       // Arch struct typedef (arch name, node1 ptr, arch cost, node2 ptr)
  char name[AR_STR_LEN];                                                                                    // Arch name
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

typedef struct connection {                                                                                 // Node connection struct typedef (node ptr, connection arch ptr, arch num in node)
  Graph_node  nd;                                                                                           // Node pointer
  Graph_arch  ar;                                                                                           // Connection arch pointer
} Connection;


/* Enums & data-types */
typedef const enum vect_coords {V, V2, V3} Vect_coords;                                                     // Matrix/vectors enum typedef

typedef const enum verbose_mode {Y, N} Verbose_mode;                                                        // Verbose mode enum typedef

typedef const enum obj_type {AR, ND} Obj_type;                                                              // Object type enum typedef (arch/node)

typedef const enum node_pos_in_arch {ARCH_ND1, ARCH_ND2} Node_pos_in_arch;                                  // Node position in arch enum typedef
C_str node_pos_in_arch_str[] = {"ARCH NODE1 POSITION", "ARCH NODE2 POSITION"};                              // Node position in arch enum typedef strings array

typedef enum arch_pos_typ {LIST_HEAD, LIST_POS, LIST_TAIL} Arch_pos_typ;                                    // Position type to add arch in node arches connections list enum typedef
C_str arch_pos_typ_str[] = {"LIST HEAD POSITION", "LIST SPECIFIC POSITION", "LIST TAIL POSITION"};          // Position type to add arch in node arches connections list enum typedef strings array


/* Global vars */
extern const Real _REAL_MAX;                                                                                // Real max val to simulate +inf
extern int ars_collect_size, nds_collect_size, min_pth_conn_vect_size;                                      // Arches and nodes collection vectors sizes + min path connections vect size
extern Arch* archs_collect_vect;                                                                            // Graph arches collection vector ptr
extern Node* nodes_collect_vect;                                                                            // Graph nodes collection vector ptr
extern Connection* min_path_conn_vect;                                                                      // Min path connections vect ptr (from 0 to 'min_pth_conn_vect_size-1' nodes and from 1 to 'min_pth_conn_vect_size-1' archs)


/* Library functions */
int idx_by_name(Obj_type object_type, C_str object_name);                                                   // Function to get object (arch/node) vector index by name (-1 = No match found / -2 = Error)

void add_new_arch(C_str, C_real cost);                                                                      // Function to add new graph arch (arch allocated inside heap)

void add_new_node(C_str name);                                                                              // Function to add new graph node (node allocated inside heap)

void connect_node_arch(C_str ar_name, C_str nd_name, Node_pos_in_arch nd_pos, Arch_pos_typ ar_pos, ...);    // Function to connect arch-node in graph (new arch list element allocated inside heap, opt param --> arch pos in arches list, non-zero index)

void dijkstra_alg(C_str src_nd_name, Verbose_mode v_mode);                                                  // Dijkstra's alg to find min graph-path btwn source and each destination node (Dijkstra-dataset vect allocated/reallocated inside heap) - Y/N for verbose mode

void buid_shortest_path(C_str dest_nd_name, Verbose_mode v_mode);                                           // Find shortest path to specified destination node from source node (pre-defined in Dijkstra's algorithm, min path connections vect allocated/reallocated inside heap) - Y/N for verbose mode

void free_graph();                                                                                          // Function to free graph allocated memory



/* Library-notes */
/* 
 * -> Use lib public-vars (global vars) to access data managed by library
 * -> Call 'free_graph()' funct to clear allocated memory inside heap
 */
