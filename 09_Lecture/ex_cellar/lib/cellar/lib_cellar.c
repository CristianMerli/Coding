/*
 * Author: Cristian Merli
 * Code title: Cellar library
 * Code version: 1.0
 * Creation date: 10/05/2021
 * Last mod. date: 10/05/2021
 */


/* Libraries */
#include "lib_cellar.h"                                                                                     // Import cellar library header file


/* Functions */
static obj *allocate_obj(const int num_obj){                                                                // Objects dyn memo alloc (calloc) function
  /* Body */
  obj *ptr = calloc((size_t)num_obj, sizeof(obj));                                                          // Objects ptr creation to point first obj allocated memo cell inside heap

  if (ptr == NULL){                                                                                         // Check calloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during objects data management");                                        // Error fbk
    perror("Error in objects dynamic memory allocation with calloc!");                                      // print perror fbk
    close_err();                                                                                            // Close software with error function call
  }
  return ptr;                                                                                               // Return first object allocated memo cell inside heap (pointer)
}


static obj *reallocate_obj(obj *objects, const int num_obj){                                                // Objects dyn memo realloc function
  /* Body */
  obj *ptr = realloc(objects, (size_t)num_obj*sizeof(obj));                                                 // Objects creation to point first obj reallocated memo cell inside heap
  
  if (ptr == NULL){                                                                                         // Check realloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during objects data management");                                        // Error fbk
    perror("Error in objects dynamic memory reallocation with realloc!");                                   // Print perror fbk
    close_err();                                                                                            // Close software with error function call
  }
  return ptr;                                                                                               // Return first object reallocated memo cell inside heap (pointer)
}


static int iaddr(const int i, const int j, const int lda){                                                  // Arrays/vectors memo addressing
  /* Body */
  return (i*lda)+j;                                                                                         // Return index number
}


obj *add_obj_in_cellar(obj *objects, int *num_obj, obj object){                                             // Add object in cellar function
  /* Body */
  if (*num_obj == 0){                                                                                       // If object collection hasn't been already initialized
    objects = allocate_obj(++*num_obj);                                                                     // Allocate memo 1 object
    objects[*num_obj-1] = object;                                                                           // Add obj in created memo
  } else {                                                                                                  // If object collection has been already initialized
    objects = reallocate_obj(objects, ++*num_obj);                                                          // Reallocate memo to add 1 object
    objects[*num_obj-1] = object;                                                                           // Add obj in last created memo
  }
  return objects;                                                                                           // Return objects collection
}


void selection_sort_name(struct obj *objects, const int num_obj, const enum order ord){                     // Selection sort algorithm (for structs) function - by name
  /* Body */
  int i, j, min_idx, str_idx;                                                                               // FOR cycles, min value propriety in unsorted part of the array and string idx
  char *elem_propr, *swp_elem_propr;                                                                        // Element propriety to sort pointer and swap-element propriety to sort pointer
  obj tmp;                                                                                                  // TMP var to swap elements in vector

  for (i = 0; i < (int)(num_obj-1); ++i){                                                                   // Sorting elements FOR cycle
    min_idx = i;                                                                                            // Min value propriety index
    for (j = i+1, str_idx = 0; j < (int)num_obj; ++j){                                                      // Unsorted part of the vector FOR cycle
      while (objects[j].name[str_idx] == objects[min_idx].name[str_idx])                                    // Check chars value in string
        ++str_idx;                                                                                          // Increment idx if same letter has been found (check next)
      elem_propr = objects[j].name;                                                                         // Point to the jth element propriety to sort elements inside the vector
      swp_elem_propr = objects[min_idx].name;                                                               // Point to the propriety min val element to sort elements inside the vector
      
      if (((elem_propr[str_idx] > swp_elem_propr[str_idx]) && ord == DECREASING) ||
         ((elem_propr[str_idx] < swp_elem_propr[str_idx]) && ord == CREASING)){                             // Decreasing (or creasing) order conditions: swap element's positions if the min val element propriety is greater (or less) than the propriety of the pointed element
        min_idx = j;                                                                                        // Update min val propriety index
      }
    }
    tmp = objects[i];                                                                                       // Save pointed element in TMP var to swap elements (use pointers and get vector position idx through the iaddr() function)
    *(objects+iaddr(V, i, num_obj)) = *(objects+iaddr(V, min_idx, num_obj));                                // Move the min val propriety element in pointing position (use pointers and get vector position idx through the iaddr() function)
    *(objects+iaddr(V, min_idx, num_obj)) = tmp;                                                            // Then copy the old pointed element previously saved in TMP swap variable, into the min val propriety element position (use pointers and get vector position idx through the iaddr() function)
  }
}


void selection_sort_time(struct obj *objects, const int num_obj, const enum order ord){                     // Selection sort algorithm (for structs) function - by time
  /* Body */
  int i, j, min_idx;                                                                                        // FOR cycles and min value propriety in unsorted part of the array idx
  time_t *elem_propr, *swp_elem_propr;                                                                      // Element propriety to sort pointer and swap-element propriety to sort pointer
  obj tmp;                                                                                                  // TMP var to swap elements in vector

  for (i = 0; i < (int)(num_obj-1); ++i){                                                                   // Sorting elements FOR cycle
    min_idx = i;                                                                                            // Min value propriety index
    for (j = i+1; j < (int)num_obj; ++j){                                                                   // Unsorted part of the vector FOR cycle
      elem_propr = &objects[j].time;                                                                        // Point to the jth element propriety to sort elements inside the vector
      swp_elem_propr = &objects[min_idx].time;                                                              // Point to the propriety min val element to sort elements inside the vector
      
      if (((*elem_propr > *swp_elem_propr) && ord == DECREASING) ||
         ((*elem_propr < *swp_elem_propr) && ord == CREASING)){                                             // Decreasing (or creasing) order conditions: swap element's positions if the min val element propriety is greater (or less) than the propriety of the pointed element
        min_idx = j;                                                                                        // Update min val propriety index
      }
    }
    tmp = objects[i];                                                                                       // Save pointed element in TMP var to swap elements (use pointers and get vector position idx through the iaddr() function)
    *(objects+iaddr(V, i, num_obj)) = *(objects+iaddr(V, min_idx, num_obj));                                // Move the min val propriety element in pointing position (use pointers and get vector position idx through the iaddr() function)
    *(objects+iaddr(V, min_idx, num_obj)) = tmp;                                                            // Then copy the old pointed element previously saved in TMP swap variable, into the min val propriety element position (use pointers and get vector position idx through the iaddr() function)
  }
}


obj *rmv_obj_by_name(obj *objects, int *num_obj, const char *name){                                         // Remove obj by name function
  /* Body */
  int idx;                                                                                                  // Match index
  byte match_flg = 0;                                                                                       // Match flag

  for (idx = 0; idx < *num_obj; ++idx){                                                                     // Scan objects collection FOR cycle
    if (0 == strcmp(objects[idx].name, name)){                                                              // Match detecting condition
      ++match_flg;                                                                                          // Set match found flag
      break;                                                                                                // Exit FOR cycle
    }
  }
  return NULL;
}
