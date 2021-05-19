/*
 * Author: Cristian Merli
 * Code title: Linked lists library header file
 * Code version: 2.0
 * Creation date: 11/05/2021
 * Last mod. date: 19/05/2021 
 */


/* Libraries */
#include "../timer/lib_timer.h"                                                                             // Import timer library header file


/* Constants */
#define OBJ_NAME_STR_LEN  30                                                                                // Object name string length


/* Enums & data-types */
typedef enum order{ CREASING, DECREASING } order;                                                           // Creasing/decreasing sorting order enum
const char *order_str[] = {"CREASING", "DECREASING"};                                                       // Creasing/decreasing sorting order enum associated strings
typedef enum order_names{ AZ, ZA } order_names;                                                             // A-Z/Z-A names sorting order enum
const char *order_names_str[] = {"A-Z", "Z-A"};                                                             // A-Z/Z-A names sorting order enum associated strings

/* Unions & data-types */
//


/* Structs & data-types */
typedef struct object {                                                                                     // Object struct typedef (name, data)
  char name[OBJ_NAME_STR_LEN];                                                                              // Object name str
  date_time date;                                                                                           // Object assignment date/time
}object;

typedef struct elem {                                                                                       // Element struct typedef for list creation (object, next object in list)
  object obj;                                                                                               // Element, object in this list position
  struct elem *nxt;                                                                                         // Next element, object in next list position
}elem;


/* Library functions */
elem *allocate_obj(const int num_obj);                                                                      // Elements dyn memo alloc (calloc) function

void add_elem_head(elem **objs_list_head, elem *const el_to_add);                                           // Function to add a new element in list (head position)

void add_elem_pos(elem **objs_list_head, elem *const el_to_add, const int pos);                             // Function to add a new element in a specific position of the list (non-zero index)

void add_elem_tail(elem **objs_list_head, elem *const el_to_add);                                           // Function to add a new element in list (tail position)

elem *rmv_elem_pos(elem **objs_list_head, const int pos);                                                   // Function to remove element in a specific position of the list (return element(s), non-zero index)

void selection_sort_name(elem **objs_list_head, const order_names ord);                                     // Selection sort algorithm (for linked lists) function - by name

void selection_sort_time(elem **objs_list_head, const order ord);                                           // Selection sort algorithm (for linked lists) function - by object date/time

int position_by_name(elem *const *objs_list_head, const char *obj_name);                                    // Function to find element position in list by obj name (non-zero index)
