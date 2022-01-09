/*
 * Author: Cristian Merli
 * Code title: Linked lists library
 * Code version: 3.0
 * Creation date: 11/05/2021
 * Last mod. date: 12/05/2021
 */


/* Libraries */
#include "lib_lists.h"                                                                                      // Import linked lists library header file


/* Functions */
elem *allocate_obj(const int num_obj){                                                                      // Elements dyn memo alloc (calloc) function
  /* Body */
  elem *ptr = calloc((size_t)num_obj, sizeof(elem));                                                        // Elements ptr creation to point first obj allocated memo cell inside heap

  if (ptr == NULL || num_obj == 0){                                                                         // Check calloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during objects data management");                                        // Error fbk
    perror("Error in objects dynamic memory allocation with calloc!");                                      // print perror fbk
    close_err();                                                                                            // Close software with error function call
  }
  return ptr;                                                                                               // Return first object allocated memo cell inside heap (pointer)
}


void add_elem_head(elem **objs_list_head, elem *el_to_add){                                                 // Function to add a new element in list (head position)
  /* Body */
  elem *tmp_el = *objs_list_head;                                                                           // Copy old list head addr in tmp var
  el_to_add->nxt = NULL;                                                                                    // Set new element as list tail (in case it'the only element in list - head&tail, otherwise connect it to the old head element)
  *objs_list_head = el_to_add;                                                                              // Set list head addr equal to new elment addr
  el_to_add->nxt = tmp_el;                                                                                  // Reconnect the new element to the list
}


void add_elem_pos(elem **objs_list_head, elem *el_to_add, int pos){                                         // Function to add a new element in a specific position of the list (non-zero index)
  /* Body */
  if (pos >= 0){                                                                                            // Check specified postion greater (or equal) than zero
    if (pos == 0 || objs_list_head == NULL){                                                                // If specified position is equal to zero or list head position addr is null (empty list)
      add_elem_head(objs_list_head, el_to_add);                                                             // Add element in list (head position)
    } else {
      elem *tmp_el = *objs_list_head;                                                                       // Copy old list head addr in tmp var
      for (int idx = 1; idx < pos-1 && tmp_el->nxt != NULL; tmp_el = tmp_el->nxt, ++idx);                   // Scroll list 'till specified position reached, or tail if position > elements in list
      el_to_add->nxt = tmp_el->nxt;                                                                         // Once target position is reached, set new element connection equal to target position element connection
      tmp_el->nxt = el_to_add;                                                                              // Set target position element connection equal to new element
    }
  } else {                                                                                                  // If specified position is less (or equal) than zero
    fbk_err("Error, position in list must be greater than zero");                                           // Print error fbk
  }
}


void add_elem_tail(elem **objs_list_head, elem *el_to_add){                                                 // Function to add a new element in list (tail position)
  /* Body */
  elem *tmp_el = *objs_list_head;                                                                           // Copy old list head addr in tmp var
  for (; tmp_el->nxt != NULL; tmp_el = tmp_el->nxt);                                                        // Scroll the whole list 'till list tail to find the last element
  el_to_add->nxt = NULL;                                                                                    // Set new element as list tail 
  tmp_el->nxt = el_to_add;                                                                                  // Connect last element to the new element to add
}


elem *rmv_elem_pos(elem **objs_list_head, int pos){                                                         // Function to remove element in a specific position of the list (return element, non-zero index)
  /* Body */
  elem *tmp_el = *objs_list_head;                                                                           // Copy old list head addr in tmp var
  if ((pos == 1 || tmp_el->nxt == NULL) && tmp_el != NULL){                                                 // If specified position is the first, or there's one only element in list (and list has been initialized)
    *objs_list_head = tmp_el->nxt;                                                                          // Set the following element as new list head (null in case of one only element present)
    return tmp_el;                                                                                          // Return list removed element (head or the only one element)
  } else if (pos > 1 && tmp_el != NULL && tmp_el->nxt != NULL){                                             // Else if specified position is greater than the first (and list has been initialized)
    for (int idx = 1; idx < pos-1 && tmp_el->nxt != NULL; tmp_el = tmp_el->nxt, ++idx);                     // Scroll list 'till specified position reached, or tail if position > elements in list
    if (tmp_el->nxt == NULL){                                                                               // In case after list scrolling, tail element has been reached
      elem *new_tail_el = *objs_list_head;                                                                  // Create a new element (second to last element, it'll be the new list tail)
      for (; new_tail_el->nxt != tmp_el; new_tail_el = new_tail_el->nxt);                                   // Scroll again the whole list 'till second to last element
      new_tail_el->nxt = NULL;                                                                              // Set the second to last element as list tail
      return tmp_el;                                                                                        // Return the old list tail element
    } else {                                                                                                // In case after list scrolling, tail element hasn't been reached
      elem *tgt_el = tmp_el->nxt;                                                                           // Create an element pointer to the element that has to be removed (target element)
      tmp_el->nxt = tgt_el->nxt;                                                                            // Set target previous element connection to target following element (extract target from the list chain)
      return tgt_el;                                                                                        // Return list removed element (neither the head nor the tail - with more than one element in list)
    }
  }else if (objs_list_head == NULL){                                                                        // If list is empty
    fbk_err("Error, nothing to remove, the list is empty");                                                 // Print error fbk
    return NULL;                                                                                            // Return null ptr to element
  } else {                                                                                                  // If specified position is less (or equal) than zero
    fbk_err("Error, position in list must be greater than zero");                                           // Print error fbk
    return NULL;                                                                                            // Return null ptr to element
  }
}


void print_list(elem **objs_list_head){                                                                     // Function to print elements in list
  /* Body */
  printf("\n    %s[ %s", BU, YE);                                                                           // Print initial char
  for (elem *tmp_el = *objs_list_head; tmp_el != NULL; tmp_el = tmp_el->nxt){                               // Scroll the whole list 'till list tail element
    printf("%s=%d", tmp_el->obj.name, tmp_el->obj.data);                                                    // Print each element name and val
    if (tmp_el->nxt != NULL)                                                                                // If focused element isn't the tail one
      printf("%s, %s", BU, YE);                                                                             // Print comma (elements separator)
  }
  printf(" %s]%s\n\n", BU, ER);                                                                             // Print last char
}
