/*
 * Author: Cristian Merli
 * Code title: Cellar library header file
 * Code version: 1.0
 * Creation date: 10/05/2021
 * Last mod. date: 10/05/2021 
 */


/* Libraries */
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file
#include "../timer/lib_timer.h"                                                                             // Import timer library header file


/* Constants */
#define OBJ_NAME_STR_LEN  30                                                                                // Object name string length


/* Enums & data-types */
enum order{ CREASING, DECREASING };                                                                         // Creasing/decreasing sorting order enum
enum coords{ V };                                                                                           // Matrix/vectors enum


/* Unions & data-types */
//

/* Structs & data-types */
typedef struct obj                                                                                          // Object (name and time when placed in cellar) typedef
{
  char name[OBJ_NAME_STR_LEN];                                                                              // Object name
  time_t time;                                                                                              // Time when placed in cellar
} obj;


/* Library functions */
obj *add_obj_in_cellar(obj *objects, int *num_obj, obj object);                                             // Add object in cellar function

void selection_sort_name(struct obj *objects, const int num_obj, const enum order ord);                     // Selection sort algorithm (for structs) function - by name

void selection_sort_time(struct obj *objects, const int num_obj, const enum order ord);                     // Selection sort algorithm (for structs) function - by time

obj *rmv_obj_by_name(obj *objects, int *num_obj, const char *name);                                         // Remove obj by name function
