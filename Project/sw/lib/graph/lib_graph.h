/*
 * Author: Cristian Merli
 * Code title: Graph library header file
 * Code version: 3.0
 * Creation date: 22/06/2021
 * Last mod. date: 14/07/2021 
 */


/*!
 * @page        page5 5 - Graph library
 * @brief       Graph-library info
 * 
 * @section     section5 Library description:
 *              vdfdvfvfv.
 * @subsection  subsection5 Library details:
 *              vdfdvfvfv.
 * 
 * @file        lib_graph.h <i>Library header file of lib_graph.c.</i>
 * @brief       <b>Graph-library header file</b>
 * 
 * @file        lib_graph.c <i>More info in <b>'Graph library'</b> section inside doxygen <b>'Related pages'</b>.</i>
 * @brief       <b>Graph-library code file</b>
 * 
 * @file        lib_graph.so <i>Library object file generated from lib_graph.c during compiling operations.</i>
 * @brief       <b>Graph-library object file</b>
 */


/* Libraries */
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file
#include "../timer/lib_timer.h"                                                                             // Import timer library header file


/* Constants */
/// <b>Macro description:</b> Max node-names length in chars <i>(30 + '\0')</i>.
#define ND_STR_LEN        31                                                                                // String length used to define node-names (max 30 chars + '\0')
/// <b>Macro description:</b> Max arch-names length in chars <i>(30 + '\0')</i>.
#define AR_STR_LEN        31                                                                                // String length used to define arch-names (max 30 chars + '\0')
/// <b>Macro description:</b> Char used to create separator lines by library in output feedbacks.
#define SEP_CHR           '-'                                                                               // Separator-char
/// <b>Macro description:</b> Char used to create separator lines by library in shortest-path output feedbacks.
#define SHORT_PTH_SEP_CHR '*'                                                                               // Shortest path separator-char
/// <b>Macro description:</b> Printing delay during shortest-path description in milliseconds.
#define PRINT_DLY_MS      500                                                                               // Print delay [ms]


/* Structs & data-types */
/// <b>Struct-typedef description:</b> List element struct typedef to store connection archs associated to a specific node.
typedef struct list_elem {                                                                                  // List element struct typedef for list creation (element, next element in list)
  /// Node-connection arch pointer.
  struct arch*      ar;                                                                                     // List element, arch ptr in this list position
  /// Next list element pointer (next arch in node archs list).
  struct list_elem* nxt;                                                                                    // Next list element, arch ptr in next list position
} List_elem;

/// <b>Typedef description:</b> List pointer typedef to point at list-head element pointer in node archs list (inside heap).
typedef List_elem* List;                                                                                    // List of elements (list head element ptr) typedef

/// <b>Struct-typedef description:</b> Node struct typedef to store node name, a list of connection archs associated to that node and a Dijkstra-dataset which contains the informations about that specific node to find min-cost path with Dijkstra's algorithm and reconstruct shortest path.
typedef struct node {                                                                                       // Node struct typedef (node name, list of arches and Dijkstra-dataset ptr)
  /// Node-name string, length defined through #ND_STR_LEN macro.
  char                      name[ND_STR_LEN];                                                               // Node name
  /// Node-connection archs list head pointer.
  List                      archs_lst;                                                                      // Arches list
  /// Dijkstra-dataset pointer (set of informations to be able to find and reconstruct min-cost path, allocated inside a dynamic-memory vector: #dijk_dataset_vect).
  struct dijkstra_dataset*  dd;                                                                             // Dijkstra-dataset pointer
} Node;

/// <b>Typedef description:</b> Node pointer typedef to point at a specific graph-node allocated in nodes collection vector (inside heap: #nodes_collect_vect).
typedef Node* Graph_node;                                                                                   // Graph-node (aka Node ptr) typedef

/// <b>Struct-typedef description:</b> Arch struct typedef to store arch name, arch cost and connection nodes associated to that arch (Node1 and Node2).
typedef struct arch {                                                                                       // Arch struct typedef (arch name, node1 ptr, arch cost, node2 ptr)
  /// Arch-name string, length defined through #AR_STR_LEN macro.
  char name[AR_STR_LEN];                                                                                    // Arch name
  /// Arch-connection Node1 pointer to graph-node element allocated in nodes collection vector (inside heap: #nodes_collect_vect).
  Graph_node  nd1;                                                                                          // Node1 pointer
  /// Arch-connection cost (reference value for #dijkstra_alg() function to find min-cost path between specified source and destination nodes).
  Real        cost;                                                                                         // Arch cost
  /// Arch-connection Node2 pointer to graph-node element allocated in nodes collection vector (inside heap: #nodes_collect_vect).
  Graph_node  nd2;                                                                                          // Node2 pointer
} Arch;

/// <b>Typedef description:</b> Arch pointer typedef to point at a specific graph-arch allocated in archs collection vector (inside heap: #archs_collect_vect).
typedef Arch* Graph_arch;                                                                                   // Graph-arch (aka Arch ptr) typedef

/// <b>Struct-typedef description:</b> Dijkstra-dataset struct typedef to store informations about a specific node, in order to be able to find min-cost path with Dijkstra's algorithm and reconstruct shortest path.
typedef struct dijkstra_dataset {                                                                           // Dijkstra-dataset struct typedef (prev node ptr, min path cost, node analyzed flag)
  /// Previous node in shortest path (pointer to a graph-node element allocated in nodes collection vector inside heap: #nodes_collect_vect).
  Graph_node  prev_nd;                                                                                      // Previous node pointer
  /// Shortest-path cost to reach that specific node, from source node specified during #dijkstra_alg() function call (path can be reconstructed backwards using #prev_nd by calling buid_shortest_path() function).
  Real        min_path_cost;                                                                                // Min path cost
  /// Node flag to mark it as already analyzed when processed by #dijkstra_alg() function.
  Byte        an_flg;                                                                                       // Node analyzed flag
} Dijkstra_dataset;

/// <b>Struct-typedef description:</b> Node connection, composed by connection arch and node on the other edge of the arch.
typedef struct connection {                                                                                 // Node connection struct typedef (node ptr, connection arch ptr, arch num in node)
  /// Connection node pointer to graph-node element allocated in nodes collection vector (inside heap: #nodes_collect_vect).
  Graph_node  nd;                                                                                           // Node pointer
  /// Connection arch pointer to graph-arch element allocated in archs collection vector (inside heap: #archs_collect_vect).
  Graph_arch  ar;                                                                                           // Connection arch pointer
} Connection;


/* Enums & data-types */
/*!
 * \var V
 * Vectors addressing.
 * \var V2
 * 2d-matrix addressing (composed by 2 vectors).
 * \var V3
 * 3d-matrix addressing (composed by 3 vectors).
 */
/// <b>Enum-typedef description:</b> Coordinates enum, indexes for #iaddr() function.
typedef const enum vect_coords {V, V2, V3} Vect_coords;                                                     // Matrix/vectors enum typedef

/*!
 * \var Y
 * YES, enable advanced verbose mode.
 * \var N
 * NO, do not enable advanced verbose mode.
 */
/// <b>Enum-typedef description:</b> Advanced verbose mode (Y/N) for #dijkstra_alg() and #buid_shortest_path() functions.
typedef const enum verbose_mode {Y, N} Verbose_mode;                                                        // Verbose mode enum typedef

/*!
 * \var AR
 * Graph-arch object type.
 * \var ND
 * Graph-node object type.
 */
/// <b>Enum-typedef description:</b> Object type (ARCH/NODE) for #idx_by_name() function.
typedef const enum obj_type {AR, ND} Obj_type;                                                              // Object type enum typedef (arch/node)

/*!
 * \var ARCH_ND1
 * Connect node in Node1 position of the arch.
 * \var ARCH_ND2
 * Connect node in Node2 position of the arch.
 */
/// <b>Enum-typedef description:</b> Node position type for #connect_node_arch() function (position in which connecting node to arch).
typedef const enum node_pos_in_arch {ARCH_ND1, ARCH_ND2} Node_pos_in_arch;                                  // Node position in arch enum typedef
/// <b>Global-variable description:</b> Node position in arch strings vector, associated with #node_pos_in_arch enum to print position as string in terminal-output.
C_str node_pos_in_arch_str[] = {"ARCH NODE1 POSITION", "ARCH NODE2 POSITION"};                              // Node position in arch enum typedef strings array

/*!
 * \var LIST_HEAD
 * Connect arch to node, adding it in head position of node connection-archs list.
 * \var LIST_POS
 * Connect arch to node, adding it in specific position of node connection-archs list.
 * \var LIST_TAIL
 * Connect arch to node, adding it in tail position of node connection-archs list.
 */
/// <b>Enum-typedef description:</b> Arch position type for #connect_node_arch() function (position in which connecting arch to node in archs list).
typedef enum arch_pos_typ {LIST_HEAD, LIST_POS, LIST_TAIL} Arch_pos_typ;                                    // Position type to add arch in node arches connections list enum typedef
/// <b>Global-variable description:</b> Arch position in node strings vector, associated with #arch_pos_typ enum to print position as string in terminal-output.
C_str arch_pos_typ_str[] = {"LIST HEAD POSITION", "LIST SPECIFIC POSITION", "LIST TAIL POSITION"};          // Position type to add arch in node arches connections list enum typedef strings array


/* Public vars */
/// <b>Public-variable description:</b> Constant variabile to indicate max real value, simulating +&infin; in #dijkstra_alg() function.
extern const Real _REAL_MAX;                                                                                // Real max val to simulate +inf
extern int ars_collect_size;                                                                                // Archs collection vector size
extern int nds_collect_size;                                                                                // Nodes collection vector size
extern int min_pth_conn_vect_size;                                                                          // Min path connections vector size
extern Arch* archs_collect_vect;                                                                            // Graph arches collection vector ptr
extern Node* nodes_collect_vect;                                                                            // Graph nodes collection vector ptr
extern Connection* min_path_conn_vect;                                                                      // Min path connections vect ptr (from 0 to 'min_pth_conn_vect_size-1' nodes and from 1 to 'min_pth_conn_vect_size-1' archs)


/* Library functions */
int idx_by_name(Obj_type object_type, C_str object_name);                                                   // Function to get object (arch/node) vector index by name (-1 = No match found / -2 = Error)

void add_new_arch(C_str name, C_real cost);                                                                 // Function to add new graph arch (arch allocated inside heap)

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
