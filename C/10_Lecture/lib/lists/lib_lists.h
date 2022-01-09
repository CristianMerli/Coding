/*
 * Author: Cristian Merli
 * Code title: Linked lists library header file
 * Code version: 3.0
 * Creation date: 11/05/2021
 * Last mod. date: 12/05/2021 
 */


/* Libraries */
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file


/* Constants */
#define OBJ_NAME_STR_LEN  30                                                                                // Object name string length


/* Enums & data-types */
//


/* Unions & data-types */
//


/* Structs & data-types */
typedef struct object {                                                                                     // Object struct typedef (name, data)
  char name[OBJ_NAME_STR_LEN];                                                                              // Object name str
  int data;                                                                                                 // Object data val
}object;

typedef struct elem {                                                                                       // Element struct typedef for list creation (object, next object in list)
  object obj;                                                                                               // Element, object in this list position
  struct elem *nxt;                                                                                         // Next element, object in next list position
}elem;


/* Library functions */
elem *allocate_obj(const int num_obj);                                                                      // Elements dyn memo alloc (calloc) function

void add_elem_head(elem **objs_list_head, elem *el_to_add);                                                 // Function to add a new element in list (head position)

void add_elem_pos(elem **objs_list_head, elem *el_to_add, int pos);                                         // Function to add a new element in a specific position of the list (non-zero index)

void add_elem_tail(elem **objs_list_head, elem *el_to_add);                                                 // Function to add a new element in list (tail position)

elem *rmv_elem_pos(elem **objs_list_head, int pos);                                                         // Function to remove element in a specific position of the list (return element, non-zero index)

void print_list(elem **objs_list_head);                                                                     // Function to print elements in list
