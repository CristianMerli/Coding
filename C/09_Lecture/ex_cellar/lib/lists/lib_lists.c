/*
 * Author: Cristian Merli
 * Code title: Linked lists library
 * Code version: 3.0
 * Creation date: 11/05/2021
 * Last mod. date: 20/05/2021
 */


/* Libraries */
#include "lib_lists.h"                                                                                      // Import linked lists library header file
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file


/* Functions */
static void swp_elems(elem **el1, elem **el2){                                                              // Function to swap 2 elements in list
  /* Body */
  elem *tmp_el = *el1;                                                                                      // Save element1 in tmp var to swap element1 and element2 ptrs
  *el1 = *el2;                                                                                              // Save element2 in element1
  *el2 = tmp_el;                                                                                            // Save old element1 val (from tmp var) in element2
}


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


void add_elem_head(elem **objs_list_head, elem *const el_to_add){                                           // Function to add a new element in list (head position)
  /* Body */  
  if (el_to_add != NULL){                                                                                   // Check element to add not null
    elem *tmp_el = *objs_list_head;                                                                         // Copy old list head addr in tmp var
    el_to_add->nxt = NULL;                                                                                  // Set new element as list tail (in case it'the only element in list - head&tail, otherwise connect it to the old head element)
    *objs_list_head = el_to_add;                                                                            // Set list head addr equal to new elment addr
    el_to_add->nxt = tmp_el;                                                                                // Reconnect the new element to the list
  } else {                                                                                                  // If specified position is less (or equal) than one
    fbk_nl(1);  fbk_err("Error, element to add in list must be not null");                                  // Print error fbk
  }
}


void add_elem_pos(elem **objs_list_head, elem *const el_to_add, const int pos){                             // Function to add a new element in a specific position of the list (non-zero index)
  /* Body */
  if (pos >= 1 && el_to_add != NULL){                                                                       // Check specified postion greater (or equal) than one and element to add not null
    if (pos == 1 || *objs_list_head == NULL){                                                               // If specified position is equal to one or list head position addr is null (empty list)
      add_elem_head(objs_list_head, el_to_add);                                                             // Add element in list (head position)
    } else {
      elem *tmp_el = *objs_list_head;                                                                       // Copy old list head addr in tmp var
      for (int idx = 1; idx < pos-1 && tmp_el->nxt != NULL; tmp_el = tmp_el->nxt, ++idx);                   // Scroll list 'till specified position reached, or tail if position > elements in list
      el_to_add->nxt = tmp_el->nxt;                                                                         // Once target position is reached, set new element connection equal to target position element connection
      tmp_el->nxt = el_to_add;                                                                              // Set target position element connection equal to new element
    }
  } else {                                                                                                  // If specified position is less (or equal) than one
    fbk_nl(1);                                                                                              // New line fbk
    fbk_err("Error, position in list must be greater than one (non-zero index), and element not null");     // Print error fbk
  }
}


void add_elem_tail(elem **objs_list_head, elem *const el_to_add){                                           // Function to add a new element in list (tail position)
  /* Body */
  if (el_to_add != NULL){                                                                                   // Check element to add not null
    if (*objs_list_head != NULL){                                                                           // If objects list has been already initialized
      elem *tmp_el = *objs_list_head;                                                                       // Copy old list head addr in tmp var
      for (; tmp_el->nxt != NULL; tmp_el = tmp_el->nxt);                                                    // Scroll the whole list 'till list tail to find the last element
      el_to_add->nxt = NULL;                                                                                // Set new element as list tail 
      tmp_el->nxt = el_to_add;                                                                              // Cotnnect last element to the new element to add
    } else {                                                                                                // Else if objects list hasn' been already initialized
      add_elem_head(objs_list_head, el_to_add);                                                             // Add element in list (head position)
    }
  } else {                                                                                                  // If specified position is less (or equal) than one
    fbk_nl(1);  fbk_err("Error, element to add in list must be not null");                                  // Print error fbk
  }
}


elem *rmv_elem_pos(elem **objs_list_head, const int pos){                                                   // Function to remove element in a specific position of the list (return element(s), non-zero index)
  /* Body */
  elem *tmp_el = *objs_list_head;                                                                           // Copy old list head addr in tmp var
  fbk_nl(1);  fbk_gn_pu("Removing element from objects list");                                              // Removing element fbk
  if ((pos == 1 || tmp_el->nxt == NULL) && tmp_el != NULL){                                                 // If specified position is the first, or there's one only element in list (and list has been initialized)
    *objs_list_head = tmp_el->nxt;                                                                          // Set the following element as new list head (null in case of one only element present)
    return tmp_el;                                                                                          // Return removed element from list (head or the only one element)
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
  } else if (tmp_el == NULL){                                                                               // If list is empty
    fbk_err("Error, nothing to remove, the list is empty");                                                 // Print error fbk
    return NULL;                                                                                            // Return null ptr to element
  } else {                                                                                                  // If specified position is less (or equal) than one
    fbk_err("Error, position in list must be greater than one (non-zero index)");                           // Print error fbk
    return NULL;                                                                                            // Return null ptr to element
  }
}


void free_elems(elem **list_head){                                                                          // Function to free allocated elements in heap from specified list (or sub-list) head, 'till list (or sub-list) tail
  /* Body */
  elem *tmp_el = *list_head;                                                                                // Tmp var to clear allocated memo in heap
  for (; tmp_el != NULL; tmp_el = tmp_el->nxt){                                                             // List (or sub-list) scrollin' FOR cycle to clear heap allocated memo
    fbk_gn_lbu_ye_str("Removing allocated element from dynamic memory, element name", tmp_el->obj.name);    // Print removing element from heap
    fbk_nl(1);                                                                                              // New line fbk
    free(tmp_el);                                                                                           // Clear allocated elements
  }
  *list_head = NULL;                                                                                        // Set elements list (or sub-list) head to null
}


void selection_sort_name(elem **objs_list_head, const order_names ord){                                     // Selection sort algorithm (for linked lists) function - by object name
  /* Body */
  char *el1_propr = NULL, *el2_propr = NULL;                                                                // Element1  and element2 propriety pointers
  elem *el_b1 = *objs_list_head, *el1 = NULL, *el_b2 = NULL, *el2 = NULL;                                   // Local ptr vars to swap list elements --> Element-b4-element1, element1, element-b4-element2, element2
  byte el1_head_flg = 0;                                                                                    // Element1 equal to the elements list head flag
  // Check elements list
  if (el_b1 == NULL || el_b1->nxt == NULL){                                                                 // In case the objects list hasn't been already initialized or it's composed by one only element
    fbk_err("Error! List is empty or it contains only one element, nothing to sort");                       // Print error fbk
  }
  // If elements list is ok, then start selection sort algorithm
  fbk_gn_lbu_ye_str("Sorting list elements by name, order", order_names_str[ord]);                          // Sorting list elements fbk
  for (el1 = el_b1; el1->nxt != NULL; el1 = el1->nxt){                                                      // Cycle 'till the one before the last element of the list has been reached (array scrolling FOR cycle)
    el_b2 = el1->nxt;                                                                                       // Set element-b4-element2 equal to the element after element1 in list
    for (el2 = el_b2; el2 != NULL; el2 = el2->nxt){                                                         // Cycle 'till last element of the list has been reached (unsorted sub-array scrolling FOR cycle)
      int str_idx = 0;                                                                                      // String index (if name chars are exactly the same, compare the following chars)
      while (el2->obj.name[str_idx] == el1->obj.name[str_idx])                                              // Compare chars value in the same position of name strings
        ++str_idx;                                                                                          // Increment string char idx if the same letter has been found in the same pos, and compare next chars
      el1_propr = el1->obj.name;                                                                            // Point to the element1 propriety to sort inside list
      el2_propr = el2->obj.name;                                                                            // Point to the element2 propriety to sort inside list
      // Sortin' order conditions
      if (((el1_propr[str_idx] > el2_propr[str_idx]) && ord == AZ) ||                                       // If elements swapin' operation is needed
          ((el1_propr[str_idx] < el2_propr[str_idx]) && ord == ZA)){                                        // A-Z (or Z-A) order sorting conditions: swap element's positions if the element1 propriety is greater (or less) than the element2 propriety
        // Swap element1 and element2 next elements
        if (el1 == *objs_list_head)                                                                         // Check wheter the element1 is the head of the linked list
          ++el1_head_flg;                                                                                   // Set element1 equal to the elements list head flag
        if (el1->nxt == el2){                                                                               // If element2 is the element immediately after element1 in linked list
          el1->nxt = el2->nxt;                                                                              // Set the element after element1 equal to the element after element2
          el2->nxt = el1;                                                                                   // Set the element after element2 equal to element1
        } else {                                                                                            // Else if element2 isn't the element immediately after element1 in linked list (some other elems in btwn 'em)
          swp_elems(&el1->nxt, &el2->nxt);                                                                  // Swap element after element1 and element after element2
          el_b2->nxt = el1;                                                                                 // Set the element after element-b4-element2 equal to the element1
        }
        // Swap element1 and element2
        if (el1_head_flg){                                                                                  // In case element1 is the head of the linked list
          swp_elems(&el1, &el2);                                                                            // Swap element1 and element2
          *objs_list_head = el1;                                                                            // Redefine the obj elements linked list head equal to element1
        } else {                                                                                            // Else if element1 isn't the head of the linked list (and element2 isn't the element immediately after element1)
          // + complete element1 and element2 next elements swap
          el_b1->nxt = el2;                                                                                 // Set the element after element-b4-element1 equal to the element2
          swp_elems(&el1, &el2);                                                                            // Swap element1 and element2
        }
      }
      el_b2 = el2;                                                                                          // In each unsorted sub-array iteration, save element2 var for next iteration (it'll become element-b4-element2)
      // Flg rst
      if (el1_head_flg)                                                                                     // If element1 equal to the elements list head flag has been set
        --el1_head_flg;                                                                                     // Reset element1 equal to the elements list head flag
    }
    el_b1 = el1;                                                                                            // After each unsorted sub-array iteration, save element1 var for next iteration (it'll become element-b4-element1)
  }
}


void selection_sort_time(elem **objs_list_head, const order ord){                                          // Selection sort algorithm (for linked lists) function - by object date/time
  /* Body */
  elem *el_b1 = *objs_list_head, *el1 = NULL, *el_b2 = NULL, *el2 = NULL;                                   // Local ptr vars to swap list elements --> Element-b4-element1, element1, element-b4-element2, element2
  byte el1_head_flg = 0;                                                                                    // Element1 equal to the elements list head flag
  // Check elements list
  if (el_b1 == NULL || el_b1->nxt == NULL){                                                                 // In case the objects list hasn't been already initialized or it's composed by one only element
    fbk_err("Error! List is empty or it contains only one element, nothing to sort");                       // Print error fbk
  }
  // If elements list is ok, then start selection sort algorithm
  fbk_gn_lbu_ye_str("Sorting list elements by date/time, order", order_str[ord]);                           // Sorting list elements fbk
  for (el1 = el_b1; el1->nxt != NULL; el1 = el1->nxt){                                                      // Cycle 'till the one before the last element of the list has been reached (array scrolling FOR cycle)
    el_b2 = el1->nxt;                                                                                       // Set element-b4-element2 equal to the element after element1 in list
    for (el2 = el_b2; el2 != NULL; el2 = el2->nxt){                                                         // Cycle 'till last element of the list has been reached (unsorted sub-array scrolling FOR cycle)
      cmp_res date_cmp_res = cmp_date_time(&el1->obj.date, NEWER, &el2->obj.date);                          // Compare element1 and element2 assignation date (if element1 is newer than elemnt2)
      // Sortin' order conditions
      if ((date_cmp_res == OK && ord == CREASING) ||                                                        // If elements swapin' operation is needed
          (date_cmp_res == NOT_OK && ord == DECREASING)){                                                   // Creasing (or decreasing) order sorting conditions: swap element's positions if the element1 assignation date is greater (or less) than the element2 assignation date
        // Swap element1 and element2 next elements
        if (el1 == *objs_list_head)                                                                         // Check wheter the element1 is the head of the linked list
          ++el1_head_flg;                                                                                   // Set element1 equal to the elements list head flag
        if (el1->nxt == el2){                                                                               // If element2 is the element immediately after element1 in linked list
          el1->nxt = el2->nxt;                                                                              // Set the element after element1 equal to the element after element2
          el2->nxt = el1;                                                                                   // Set the element after element2 equal to element1
        } else {                                                                                            // Else if element2 isn't the element immediately after element1 in linked list (some other elems in btwn 'em)
          swp_elems(&el1->nxt, &el2->nxt);                                                                  // Swap element after element1 and element after element2
          el_b2->nxt = el1;                                                                                 // Set the element after element-b4-element2 equal to the element1
        }
        // Swap element1 and element2
        if (el1_head_flg){                                                                                  // In case element1 is the head of the linked list
          swp_elems(&el1, &el2);                                                                            // Swap element1 and element2
          *objs_list_head = el1;                                                                            // Redefine the obj elements linked list head equal to element1
        } else {                                                                                            // Else if element1 isn't the head of the linked list (and element2 isn't the element immediately after element1)
          // + complete element1 and element2 next elements swap
          el_b1->nxt = el2;                                                                                 // Set the element after element-b4-element1 equal to the element2
          swp_elems(&el1, &el2);                                                                            // Swap element1 and element2
        }
      }
      el_b2 = el2;                                                                                          // In each unsorted sub-array iteration, save element2 var for next iteration (it'll become element-b4-element2)
      // Flg rst
      if (el1_head_flg)                                                                                     // If element1 equal to the elements list head flag has been set
        --el1_head_flg;                                                                                     // Reset element1 equal to the elements list head flag
    }
    el_b1 = el1;                                                                                            // After each unsorted sub-array iteration, save element1 var for next iteration (it'll become element-b4-element1)
  }
}


int position_by_name(elem *const *objs_list_head, const char *obj_name){                                    // Function to find element position in list by obj name (non-zero index)
  /* Body */
  elem *tmp_el = *objs_list_head;                                                                           // Copy old list head addr in tmp var
  int pos = 0;                                                                                              // Element position
  fbk_nl(1);                                                                                                // New line fbk
  fbk_gn_pu("Scrolling elements list to find matches");                                                     // Scrollin' list fbk

  if (tmp_el != NULL && strlen(obj_name) > 0){                                                              // In case objects list has been already initialized and object name string length is greater than zero
    ++pos;                                                                                                  // Increment position to have non-zero index pos
    for (; tmp_el != NULL; tmp_el = tmp_el->nxt, ++pos){                                                    // Scrollin' elements (in list) FOR cycle
      if (0 == strcmp(tmp_el->obj.name, obj_name)){                                                         // If there's a match
        return pos;                                                                                         // Return match found position
      }
    }
  } else if (tmp_el == NULL){                                                                               // If list is empty
    fbk_err("Error, elements list is empty");                                                               // Print error fbk
  } else {                                                                                                  // If object name string length isn't greater than one
    fbk_err("Error, name length must be greater than zero");                                                // Print error fbk
  }
  return 0;                                                                                                 // Return zero (error or no match found)
}
