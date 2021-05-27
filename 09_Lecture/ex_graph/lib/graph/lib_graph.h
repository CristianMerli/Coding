/*
 * Author: Cristian Merli
 * Code title: Graph library header file
 * Code version: 1.0
 * Creation date: 21/05/2021
 * Last mod. date: 21/05/2021 
 */


/* Libraries */
#include "../lists/lib_lists.h"                                                                             // Import linked lists library header file
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file


/* Constants */
//


/* Structs & data-types */
typedef struct node {                                                                                       // Node struct typedef (cost, arches)
  double cost;                                                                                              // Node cost
  elem* arches;                                                                                             // -
} node;

typedef struct arch {                                                                                       // Arch struct typedef (node1 ptr, node2 ptr)
  node* nd1;                                                                                                // Node1 pointer
  node* nd2;                                                                                                // Node2 pointer
} arch;

typedef node* graph;                                                                                        // Graph object (connected list of nodes and arches - starting from a node)


/* Enums & data-types */
typedef union graph_elem {                                                                                  // Graph element typedef (node ptr, arch ptr)
  node* nd;                                                                                                 // Node pointer
  arch* ar;                                                                                                 // Arch pointer
} graph_elem;



/* Library functions */
//



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
