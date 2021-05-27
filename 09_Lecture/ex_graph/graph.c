/*
 * Author: Cristian Merli
 * Code title: Graph
 * Code version: 1.0
 * Creation date: 21/05/2021
 * Last mod. date: 21/05/2021
 * 
 * 
 * // Compile-commands:
 * gccW99_lib lib/graph/lib_graph.so lib/graph/lib_graph.c    --> Create GRAPH dynamic library object file (interface with linked lists library)
 * gccW99_lib lib/lists/lib_lists.so lib/lists/lib_lists.c    --> Create LISTS dynamic library object file
 * gccW99_lib lib/ui/lib_ui.so lib/ui/lib_ui.c                --> Create UI (TERMINAL I/O) dynamic library object file
 * gccW99_lib lib/timer/lib_timer.so lib/timer/lib_timer.c    --> Create TIMER dynamic library object file
 * gccW99_c graph.c                                           --> Create SOFTWARE object file
 * 
 * // Link-command:
 * gccW99_o graph graph.o lib/graph/lib_graph.so lib/lists/lib_lists.so lib/ui/lib_ui.so lib/timer/lib_timer.so   --> LINK software and dynamic libraries object files to executable
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
//


/* Main cycle */
int main(){
  /* Main vars */
  //

  /* Code */
  logo(6, "GRAPHS MANAGEMENT LIBRARY TEST SOFTWARE", YE, '#', GN);                                          // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  press_enter("Hi");                                                                                        // Press enter to start SW fbk
  //

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
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
