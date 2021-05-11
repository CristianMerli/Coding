/*
 * Author: Cristian Merli
 * Code title: Cellar
 * Code version: 1.0
 * Creation date: 10/05/2021
 * Last mod. date: 10/05/2021
 * 
 * 
 * // Compile-commands:
 * gccW99_lib lib/cellar/lib_cellar.so lib/cellar/lib_cellar.c    --> Create CELLAR dynamic library object file
 * gccW99_lib lib/ui/lib_ui.so lib/ui/lib_ui.c                    --> Create UI (TERMINAL I/O) dynamic library object file
 * gccW99_lib lib/timer/lib_timer.so lib/timer/lib_timer.c        --> Create TIMER dynamic library object file
 * gccW99_c cellar.c                                              --> Create SOFTWARE object file
 * 
 * // Link-command:
 * gccW99_o cellar cellar.o lib/cellar/lib_cellar.so lib/ui/lib_ui.so lib/timer/lib_timer.so    --> LINK software and dynamic libraries object files to executable
 * 
 * // Aliases:
 * alias gccW99_o="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -o"
 * alias gccW99_c="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -c"
 * alias gccW99_lib="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -fpic -shared -o"
 */


/* Libraries */
#include "lib/cellar/lib_cellar.h"                                                                          // Import cellar library header file


/* Constants */
//


/* Global vars */
obj *objects = NULL;                                                                                        // Objects collection pointer
int num_obj = 0;                                                                                            // Objects number


/* Main routines */
//


/* Main cycle */
int main(){
  /* Main vars */
  //

  /* Code */
  logo(10, "CELLAR MANAGEMENT SOFTWARE", YE, '#', GN);                                                      // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  press_enter("Hi");                                                                                        // Press enter to start SW fbk
  fbk_nl(1);                                                                                                // New line fbk

  obj obj1 = { .name={"Abahah"}, .time=clock() };                                                           // Define obj1
  delay(500);                                                                                               // Delay
  obj obj2 = { .name={"Boh"}, .time=clock() };                                                              // Define obj2
  delay(500);                                                                                               // Delay
  obj obj3 = { .name={"Aaah"}, .time=clock() };                                                             // Define obj3
  delay(500);                                                                                               // Delay

  objects = add_obj_in_cellar(objects, &num_obj, obj1);                                                     // Add obj1 to objects collection
  objects = add_obj_in_cellar(objects, &num_obj, obj2);                                                     // Add obj2 to objects collection
  objects = add_obj_in_cellar(objects, &num_obj, obj3);                                                     // Add obj3 to objects collection

  fbk_gn_lbu_ye_str("Name obj1", objects[0].name);                                                          // Print obj1 name
  fbk_nl(1);                                                                                                // New line fbk
  fbk_gn_lbu_ye_str("Name obj2", objects[1].name);                                                          // Print obj2 name
  fbk_nl(1);                                                                                                // New line fbk
  fbk_gn_lbu_ye_str("Name obj3", objects[2].name);                                                          // Print obj3 name
  fbk_nl(2);                                                                                                // New line fbk
  selection_sort_name(objects, num_obj, CREASING);                                                          // Sort by name
  fbk_gn_lbu_ye_str("Name obj1", objects[0].name);                                                          // Print obj1 name
  fbk_nl(1);                                                                                                // New line fbk
  fbk_gn_lbu_ye_str("Name obj2", objects[1].name);                                                          // Print obj2 name
  fbk_nl(1);                                                                                                // New line fbk
  fbk_gn_lbu_ye_str("Name obj3", objects[2].name);                                                          // Print obj3 name
  fbk_nl(2);                                                                                                // New line fbk

  fbk_gn_lbu_ye_int("Time obj1", (int)objects[0].time);                                                     // Print obj1 time
  fbk_nl(1);                                                                                                // New line fbk
  fbk_gn_lbu_ye_int("Time obj2", (int)objects[1].time);                                                     // Print obj2 time
  fbk_nl(1);                                                                                                // New line fbk
  fbk_gn_lbu_ye_int("Time obj3", (int)objects[2].time);                                                     // Print obj3 time
  fbk_nl(2);                                                                                                // New line fbk
  selection_sort_time(objects, num_obj, CREASING);                                                          // Sort by time
  fbk_gn_lbu_ye_int("Time obj1", (int)objects[0].time);                                                     // Print obj1 time
  fbk_nl(1);                                                                                                // New line fbk
  fbk_gn_lbu_ye_int("Time obj2", (int)objects[1].time);                                                     // Print obj2 time
  fbk_nl(1);                                                                                                // New line fbk
  fbk_gn_lbu_ye_int("Time obj3", (int)objects[2].time);                                                     // Print obj3 time
  fbk_nl(2);                                                                                                // New line fbk

  close_fbk();                                                                                              // Print close fbk

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/* 
 * La cantina può contenere un numero imprecisato di oggetti (utilizzare un vettore iniziale e poi modificarne la dimensione)
 * Un oggetto è definito da un nome e da un orario nel quale è stato messo in cantina
 * utilizzare la libreria time.h (https://www.cplusplus.com/reference/ctime/)
 * scrivere le seguenti funzioni:
 * 1. funzione che aggiunge un oggetto in cantina
 * 2. funziona che ordina gli oggetti alfabeticamente
 * 3. funzione che ordina gli oggetti per data di inserimento
 * 4. funzione che elimina un oggetto in base al nome
 * 5. funzione che rimuove tutti gli oggetti più vecchi di una certa data e ne ritorna la lista
 * 6. funzione che salva la lista degli oggetti su file
 * 7. funzione che carica gli oggetti da file
 */
