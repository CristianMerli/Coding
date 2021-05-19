/*
 * Author: Cristian Merli
 * Code title: Cellar
 * Code version: 2.0
 * Creation date: 10/05/2021
 * Last mod. date: 19/05/2021
 * 
 * 
 * // Compile-commands:
 * gccW99_lib lib/cellar/lib_cellar.so lib/cellar/lib_cellar.c    --> Create CELLAR dynamic library object file (interface with linked lists library)
 * gccW99_lib lib/lists/lib_lists.so lib/lists/lib_lists.c        --> Create LISTS dynamic library object file
 * gccW99_lib lib/ui/lib_ui.so lib/ui/lib_ui.c                    --> Create UI (TERMINAL I/O) dynamic library object file
 * gccW99_lib lib/timer/lib_timer.so lib/timer/lib_timer.c        --> Create TIMER dynamic library object file
 * gccW99_lib lib/files/lib_files.so lib/files/lib_files.c        --> Create FILES dynamic library object file
 * gccW99_c cellar.c                                              --> Create SOFTWARE object file
 * 
 * // Link-command:
 * gccW99_o cellar cellar.o lib/cellar/lib_cellar.so lib/lists/lib_lists.so lib/ui/lib_ui.so lib/timer/lib_timer.so && lib/files/lib_files.so   --> LINK software and dynamic libraries object files to executable
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
static elem *objs_list_head = NULL;                                                                         // Define objects list head element (pointer to the first elemen of the list)


/* Main routines */
//


/* Main cycle */
int main(){
  /* Main vars */
  //

  /* Code */
  logo(10, "CELLAR MANAGEMENT SOFTWARE", YE, '#', GN);                                                      // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  press_enter("Hi");                                                                                        // Press enter to start SW fbk

  add_obj_in_cellar(&objs_list_head, "Abddd", HEAD, 0);                                                     // Add object in cellar (add object in list head position)
  delay(1000);                                                                                              // Delay
  add_obj_in_cellar(&objs_list_head, "Aaddd", TAIL, 0);                                                     // Add object in cellar (add object in list tail position)
  delay(1000);                                                                                              // Delay
  add_obj_in_cellar(&objs_list_head, "Acddd", POS, 2);                                                      // Add object in cellar (add object in list specific position)
  delay(1000);                                                                                              // Delay
  add_obj_in_cellar(&objs_list_head, "dcsdscd", HEAD, 0);                                                   // Add object in cellar (add object in list head position)
  delay(1000);                                                                                              // Delay
  add_obj_in_cellar(&objs_list_head, "fdvfsc", HEAD, 0);                                                    // Add object in cellar (add object in list head position)
  delay(1000);                                                                                              // Delay
  add_obj_in_cellar(&objs_list_head, "sdsdvsa", HEAD, 0);                                                   // Add object in cellar (add object in list head position)
  delay(1000);                                                                                              // Delay
  add_obj_in_cellar(&objs_list_head, "sdcdvsbdf", HEAD, 0);                                                 // Add object in cellar (add object in list head position)
  delay(1000);                                                                                              // Delay
  print_objects_in_cellar(&objs_list_head);                                                                 // Print elements in cellar

  selection_sort_name(&objs_list_head, AZ);                                                                 // Sort objects by name (A-Z order)
  print_objects_in_cellar(&objs_list_head);                                                                 // Print elements in cellar
  selection_sort_time(&objs_list_head, DECREASING);                                                         // Sort objects by date/time (DECREASING ORDER)
  print_objects_in_cellar(&objs_list_head);                                                                 // Print elements in cellar

  rmv_obj_name(&objs_list_head, "Acddd");                                                                   // Remove element by name
  print_objects_in_cellar(&objs_list_head);                                                                 // Print elements in cellar

  //date_time tmp_date = objs_list_head->nxt->nxt->nxt->obj.date;                                             // Set tmp date/time var to remove objects added after this date
  //rmv_obj_old_date(&objs_list_head, &tmp_date);                                                             // Remove elements older than defined date/time
  print_objects_in_cellar(&objs_list_head);                                                                 // Print elements in cellar

  save_objs_file(&objs_list_head, "bkps/Objs.bkp");                                                         // Save objects list on backup file
  for (; objs_list_head != NULL; objs_list_head = objs_list_head->nxt)                                      // List scrollin' FOR cycle to clear heap allocated memo
    free(objs_list_head);                                                                                   // Clear allocated elements
  load_objs_file(&objs_list_head, "bkps/Objs.bkp");                                                         // Load objects list from backup file
  print_objects_in_cellar(&objs_list_head);                                                                 // Print elements in cellar

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
