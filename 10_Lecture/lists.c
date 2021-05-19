/*
 * Author: Cristian Merli
 * Code title: Linked lists
 * Code version: 3.0
 * Creation date: 11/05/2021
 * Last mod. date: 12/05/2021
 * 
 * 
 * // Compile-commands:
 * gccW99_lib lib/lists/lib_lists.so lib/lists/lib_lists.c    --> Create LISTS dynamic library object file
 * gccW99_lib lib/ui/lib_ui.so lib/ui/lib_ui.c                --> Create UI (TERMINAL I/O) dynamic library object file
 * gccW99_c lists.c                                           --> Create SOFTWARE object file
 * 
 * // Link-command:
 * gccW99_o lists lists.o lib/lists/lib_lists.so lib/ui/lib_ui.so   --> LINK software and dynamic libraries object files to executable
 * 
 * // Aliases:
 * alias gccW99_o="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -o"
 * alias gccW99_c="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -c"
 * alias gccW99_lib="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -fpic -shared -o"
 */


/* Libraries */
#include "lib/lists/lib_lists.h"                                                                            // Import linked lists library header file


/* Global vars */
elem *objs_list_head = NULL;                                                                                // Define objects list head element (pointer to the first elemen of the list)


// Main cycle
int main(){
  logo(10, "LISTS LIBRARY TEST", YE, '#', GN);                                                              // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  press_enter("Hi");                                                                                        // Press enter to start SW fbk

  elem *new_el = allocate_obj(1);                                                                           // Allocate a new element inside heap
  strcpy(new_el->obj.name, "TEST1");                                                                        // Define new obj element name
  new_el->obj.data = 1;                                                                                     // Define new obj element data val
  printf("\n%sAdding element in list head: \"%s=%d\"%s\n", OG, new_el->obj.name, new_el->obj.data, ER);     // Adding element in list head fbk
  add_elem_head(&objs_list_head, new_el);                                                                   // Add new elment in objects list (head position)
  // New_el can be used to assign other elements in list
  new_el = allocate_obj(1);                                                                                 // Allocate a new element inside heap
  strcpy(new_el->obj.name, "TEST2");                                                                        // Define new obj element name
  new_el->obj.data = 2;                                                                                     // Define new obj element data val
  printf("%sAdding element in list head: \"%s=%d\"%s\n", OG, new_el->obj.name, new_el->obj.data, ER);       // Adding element in list head fbk
  add_elem_head(&objs_list_head, new_el);                                                                   // Add new elment in objects list (head position)
  // New_el can be used to assign other elements in list
  new_el = allocate_obj(1);                                                                                 // Allocate a new element inside heap
  strcpy(new_el->obj.name, "TEST3");                                                                        // Define new obj element name
  new_el->obj.data = 3;                                                                                     // Define new obj element data val
  printf("%sAdding element in list tail: \"%s=%d\"%s\n", OG, new_el->obj.name, new_el->obj.data, ER);       // Adding element in list tail fbk
  add_elem_tail(&objs_list_head, new_el);                                                                   // Add new elment in objects list (tail position)
  // New_el can be used to assign other elements in list
  new_el = allocate_obj(1);                                                                                 // Allocate a new element inside heap
  strcpy(new_el->obj.name, "TEST4");                                                                        // Define new obj element name
  new_el->obj.data = 4;                                                                                     // Define new obj element data val
  printf("%sAdding element in list 2nd posit: \"%s=%d\"%s\n", OG, new_el->obj.name, new_el->obj.data, ER);  // Adding element in list 2nd position fbk
  add_elem_pos(&objs_list_head, new_el, 2);                                                                 // Add new elment in objects list (specified position, non-zero index)
  // Print list
  fbk_nl(1);                                                                                                // New line fbk
  fbk_gn_pu("Printin' list...");                                                                            // Print ptintin' list fbk
  print_list(&objs_list_head);                                                                              // Print elemets in list
  // Remove element
  elem *el_to_rmv = rmv_elem_pos(&objs_list_head, 1);                                                       // Remove element in a specific position of the list (return element, non-zero index)
  printf("%sRemoving element: \"%s=%d\"%s\n", OG, el_to_rmv->obj.name, el_to_rmv->obj.data, ER);            // Removing element fbk
  free(el_to_rmv);                                                                                          // Free allocated memo
  // Print list
  fbk_nl(1);                                                                                                // New line fbk
  fbk_gn_pu("Printin' list...");                                                                            // Print ptintin' list fbk
  print_list(&objs_list_head);                                                                              // Print elemets in list

  close_fbk();                                                                                              // Print close fbk
}



/* Task */
/* 
 * Linked lists
 */
