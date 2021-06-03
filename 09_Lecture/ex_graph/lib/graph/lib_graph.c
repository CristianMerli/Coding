/*
 * Author: Cristian Merli
 * Code title: Graph library
 * Code version: 2.0
 * Creation date: 21/05/2021
 * Last mod. date: 03/06/2021
 */


/* Libraries */
#include "lib_graph.h"                                                                                      // Import graph library header file


/* Functions */
static List_elem* allocate_new_list_elems(C_int num){                                                       // Function to allocate new list elements (single/vect)
  /* Body */
  List_elem* tmp_list_elems = calloc((size_t)num, sizeof(List_elem));                                       // Tmp list element ptr creation to point at first allocated memo cell inside heap
  if (tmp_list_elems == NULL || num == 0){                                                                  // Check calloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during lists data management");                                          // Error fbk
    perror("Found error during list elements dynamic memory allocation with calloc!");                      // print perror fbk
    close_err();                                                                                            // Close software with error function call
  }
  return tmp_list_elems;                                                                                    // Return tmp list elements, firtst allocated memo cell inside heap (pointer)
}


static void add_elem_at_list_head(List* list, List_elem* const el_to_add){                                  // Function to add a new element in list (head position)
  /* Body */  
  if (el_to_add != NULL){                                                                                   // Check element to add not null
    List tmp_el_head = *list;                                                                               // Copy the old list head addr in tmp var
    el_to_add->nxt = NULL;                                                                                  // Set new element as list tail (in case it's the only element in list - head&tail, otherwise connect it to the old head element)
    *list = el_to_add;                                                                                      // Set list head addr equal to new elment addr
    el_to_add->nxt = tmp_el_head;                                                                           // Reconnect the new element to the list
  } else {                                                                                                  // If specified position is less (or equal) than one
    fbk_nl(1);  fbk_err("Error, element to add in list must be not null");                                  // Print error fbk
  }
}


static void add_elem_at_list_pos(List* list, List_elem* const el_to_add, C_int pos){                        // Function to add a new element at a specific position of the list (non-zero index)
  /* Body */
  if (pos >= 1 && el_to_add != NULL){                                                                       // Check specified postion greater (or equal) than one and element to add not null
    if (pos == 1 || *list == NULL)                                                                          // If specified position is equal to one or list is null (empty list)
      add_elem_at_list_head(list, el_to_add);                                                               // Add element in list (head position)
    else {                                                                                                  // Else if specified position is greater than one or list ain't null (list not empty)
      List tmp_list = *list;                                                                                // Copy old list in tmp var
      for (int idx = 1; idx < pos-1 && tmp_list->nxt != NULL; tmp_list = tmp_list->nxt, ++idx);             // Scroll list 'till specified position reached, or tail if position > elements in list
      el_to_add->nxt = tmp_list->nxt;                                                                       // Once target position is reached, set new element connection equal to target position element connection
      tmp_list->nxt = el_to_add;                                                                            // Set target position element connection equal to new element
    }
  } else {                                                                                                  // If specified position is less (or equal) than one
    fbk_nl(1);                                                                                              // New line fbk
    fbk_err("Error, position in list must be greater than one (non-zero index), and element not null");     // Print error fbk
  }
}


static void add_elem_at_list_tail(List* list, List_elem* const el_to_add){                                  // Function to add a new element in list (tail position)
  /* Body */ 
  if (el_to_add != NULL){                                                                                   // Check element to add not null
    if (*list != NULL){                                                                                     // If objects list has been already initialized
      List tmp_list = *list;                                                                                // Copy old list in tmp var
      for (; tmp_list->nxt != NULL; tmp_list = tmp_list->nxt);                                              // Scroll the whole list 'till list tail, to find last element
      el_to_add->nxt = NULL;                                                                                // Set new element as list tail 
      tmp_list->nxt = el_to_add;                                                                            // Cotnnect last element to the new element to add
    } else                                                                                                  // Else if objects list ain't been already initialized
      add_elem_at_list_head(list, el_to_add);                                                               // Add element in list (head position)
  } else {                                                                                                  // If specified position is less (or equal) than one
    fbk_nl(1);  fbk_err("Error, element to add in list must be not null");                                  // Print error fbk
  }
}


// static void swp_elems(List_elem** el1, List_elem** el2){                                                    // Function to swap 2 elements in list
//   /* Body */
//   List_elem* tmp_el = *el1;                                                                                 // Save element1 in tmp var to swap element1 and element2 ptrs
//   *el1 = *el2;                                                                                              // Save element2 in element1
//   *el2 = tmp_el;                                                                                            // Save old element1 val (from tmp var) in element2
// }


// static List rmv_elem_pos(List* list_head, C_int pos){                                                       // Function to remove element in a specific position of the list (return element(s), non-zero index)
//   /* Body */
//   List_elem* tmp_el = *list_head;                                                                           // Copy old list head addr in tmp var
//   if ((pos == 1 || tmp_el->nxt == NULL) && tmp_el != NULL){                                                 // If specified position is the first, or there's one only element in list (and list has been initialized)
//     *list_head = tmp_el->nxt;                                                                               // Set the following element as new list head (null in case of one only element present)
//     return tmp_el;                                                                                          // Return list removed element (head or the only one element)
//   } else if (pos > 1 && tmp_el != NULL && tmp_el->nxt != NULL){                                             // Else if specified position is greater than the first (and list has been initialized)
//     for (int idx = 1; idx < pos-1 && tmp_el->nxt != NULL; tmp_el = tmp_el->nxt, ++idx);                     // Scroll list 'till specified position reached, or tail if position > elements in list
//     if (tmp_el->nxt == NULL){                                                                               // In case after list scrolling, tail element has been reached
//       List_elem* new_tail_el = *list_head;                                                                  // Create a new element (second to last element, it'll be the new list tail)
//       for (; new_tail_el->nxt != tmp_el; new_tail_el = new_tail_el->nxt);                                   // Scroll again the whole list 'till second to last element
//       new_tail_el->nxt = NULL;                                                                              // Set the second to last element as list tail
//       return tmp_el;                                                                                        // Return the old list tail element
//     } else {                                                                                                // In case after list scrolling, tail element hasn't been reached
//       List_elem* tgt_el = tmp_el->nxt;                                                                      // Create an element pointer to the element that has to be removed (target element)
//       tmp_el->nxt = tgt_el->nxt;                                                                            // Set target previous element connection to target following element (extract target from the list chain)
//       return tgt_el;                                                                                        // Return list removed element (neither the head nor the tail - with more than one element in list)
//     }
//   } else if (list_head == NULL){                                                                            // If list is empty
//     fbk_err("Error, nothing to remove, the list is empty");                                                 // Print error fbk
//     return NULL;                                                                                            // Return null ptr to element
//   } else {                                                                                                  // If specified position is less (or equal) than zero
//     fbk_err("Error, position in list must be greater than zero");                                           // Print error fbk
//     return NULL;                                                                                            // Return null ptr to element
//   }
// }


// static void free_elems(List* list_head){                                                                    // Function to free allocated elements inside heap, startin' from specified list (or sub-list) head, 'till list (or sub-list) tail
//   /* Body */
//   List tmp_list_head = *list_head;                                                                          // Tmp var to clear allocated memo inside heap
//   for (int i = 0; tmp_list_head != NULL; tmp_list_head = tmp_list_head->nxt, ++i){                          // List (or sub-list) scrollin' FOR cycle to clear heap allocated memo
//     fbk_gn_lbu_ye_int("Removing allocated list element from dynamic memory, element number", i);            // Print removing element from heap fbk
//     fbk_nl(1);                                                                                              // New line fbk
//     free(tmp_list_head);                                                                                    // Clear allocated elements
//   }
//   *list_head = NULL;                                                                                        // Set elements list (or sub-list) head to null
// }


static List_elem** allocate_new_elem_ptrs(C_int num){                                                       // Function to allocate new list element pointers (single/vect)
  /* Body */
  List_elem** tmp_el_ptr = calloc((size_t)num, sizeof(List_elem*));                                         // Tmp list element ptr of ptrs creation to point at first allocated memo cell inside heap
  if (tmp_el_ptr == NULL || num == 0){                                                                      // Check calloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during lists data management");                                          // Error fbk
    perror("Found error during list element pointers dynamic memory allocation with calloc!");              // print perror fbk
    close_err();                                                                                            // Close software with error function call
  }
  return tmp_el_ptr;                                                                                        // Return tmp list element ptrs, firtst allocated memo cell inside heap (pointer)
}


static void reallocate_elem_ptrs_vect(List_elem** elems_vect, C_int size){                                  // Function to reallocate list element pointers vector (resize)
  /* Body */
  elems_vect = realloc(elems_vect, (size_t)size*sizeof(List_elem*));                                        // List element ptrs vect ptr addr upd to make sure it points at first reallocated memo cell inside heap
  if (elems_vect == NULL || size == 0){                                                                     // Check realloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during lists data management");                                          // Error fbk
    perror("Found error during list element vector dynamic memory reallocation with realloc!");             // print perror fbk
    close_err();                                                                                            // Close software with error function call
  }
}


static int iaddr(C_int i, C_int j, C_int lda){                                                              // Arrays/vectors memo addressing
  /* Body */
  return (i*lda)+j;                                                                                         // Return index number
}


static Graph_arch allocate_new_archs(C_int num){                                                            // Function to allocate new graph arches (single/vect)
  /* Body */
  Graph_arch tmp_archs = calloc((size_t)num, sizeof(Arch));                                                 // Tmp graph arch ptr creation to point at first allocated memo cell inside heap
  if (tmp_archs == NULL || num == 0){                                                                       // Check calloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during graph data management");                                          // Error fbk
    perror("Found error during graph arches dynamic memory allocation with calloc!");                       // print perror fbk
    close_err();                                                                                            // Close software with error function call
  }
  return tmp_archs;                                                                                         // Return tmp graph arches, firtst allocated memo cell inside heap (pointer)
}


static Graph_node allocate_new_nodes(C_int num){                                                            // Function to allocate new graph nodes (single/vect)
  /* Body */
  Graph_node tmp_nodes = calloc((size_t)num, sizeof(Node));                                                 // Tmp graph node ptr creation to point at first allocated memo cell inside heap
  if (tmp_nodes == NULL || num == 0){                                                                       // Check calloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during graph data management");                                          // Error fbk
    perror("Found error during graph nodes dynamic memory allocation with calloc!");                        // print perror fbk
    close_err();                                                                                            // Close software with error function call
  }
  return tmp_nodes;                                                                                         // Return tmp graph nodes, firtst allocated memo cell inside heap (pointer)
}


static Graph_arch* allocate_new_arch_ptrs(C_int num){                                                       // Function to allocate new graph arch pointers (single/vect)
  /* Body */
  Graph_arch* tmp_arch_ptr = calloc((size_t)num, sizeof(Graph_arch));                                       // Tmp graph arch ptr of ptrs creation to point at first allocated memo cell inside heap
  if (tmp_arch_ptr == NULL || num == 0){                                                                    // Check calloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during graph data management");                                          // Error fbk
    perror("Found error during graph arch pointers dynamic memory allocation with calloc!");                // print perror fbk
    close_err();                                                                                            // Close software with error function call
  }
  return tmp_arch_ptr;                                                                                      // Return tmp graph arch ptrs, firtst allocated memo cell inside heap (pointer)
}


static Graph_node* allocate_new_node_ptrs(C_int num){                                                       // Function to allocate new graph node pointers (single/vect)
  /* Body */
  Graph_node* tmp_node_ptr = calloc((size_t)num, sizeof(Graph_node));                                       // Tmp graph arch ptr of ptrs creation to point at first allocated memo cell inside heap
  if (tmp_node_ptr == NULL || num == 0){                                                                    // Check calloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during graph data management");                                          // Error fbk
    perror("Found error during graph node pointers dynamic memory allocation with calloc!");                // print perror fbk
    close_err();                                                                                            // Close software with error function call
  }
  return tmp_node_ptr;                                                                                      // Return tmp graph arch ptrs, firtst allocated memo cell inside heap (pointer)
}


static void reallocate_arch_ptrs_vect(Graph_arch* archs_vect, C_int size){                                  // Function to reallocate graph arch pointers vector (resize)
  /* Body */
  archs_vect = realloc(archs_vect, (size_t)size*sizeof(Graph_arch));                                        // Graph arch ptrs vect ptr addr upd to make sure it points at first reallocated memo cell inside heap
  if (archs_vect == NULL || size == 0){                                                                     // Check realloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during graph data management");                                          // Error fbk
    perror("Found error during graph arches vector dynamic memory reallocation with realloc!");             // print perror fbk
    close_err();                                                                                            // Close software with error function call
  }
}


static void reallocate_node_ptrs_vect(Graph_node* nodes_vect, C_int size){                                  // Function to reallocate graph node pointers vector (resize)
  /* Body */
  nodes_vect = realloc(nodes_vect, (size_t)size*sizeof(Graph_node));                                        // Graph node ptrs vect ptr addr upd to make sure it points at first reallocated memo cell inside heap
  if (nodes_vect == NULL || size == 0){                                                                     // Check realloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during graph data management");                                          // Error fbk
    perror("Found error during graph nodes vector dynamic memory reallocation with realloc!");              // print perror fbk
    close_err();                                                                                            // Close software with error function call
  }
}


/* Public functions */
Graph_arch add_new_arch(C_real cost){                                                                       // Function to add new graph arch (arch allocated inside heap)
  /* Body */
  fbk_nl(1);  fbk_gn_pu("Adding new graph arch...");                                                        // Adding new graph arch fbk
  Graph_arch ar_ptr = allocate_new_archs(1);                                                                // Allocate a new graph arch inside heap
  ar_ptr->cost = cost;                                                                                      // Define arch cost
  fbk_nl(1);  fbk_gn_lbu_ye_real("New arch cost", cost);                                                    // Adding new graph arch fbk
  ar_ptr->nd1 = NULL;                                                                                       // Set node1 connection to NULL
  ar_ptr->nd2 = NULL;                                                                                       // Set node2 connection to NULL
  fbk_nl(1);  fbk_gn_cy("New graph arch correctly added!\n");                                               // New graph arch correctly added fbk
  return ar_ptr;                                                                                            // Retun new allocated arch addr
}


Graph_node add_new_node(){                                                                                  // Function to add new graph node (node allocated inside heap)
  /* Body */
  fbk_nl(1);  fbk_gn_pu("Adding new graph node...");                                                        // Adding new graph node fbk
  Graph_node nd_ptr = allocate_new_nodes(1);                                                                // Allocate a new graph node inside heap
  nd_ptr->archs_lst = NULL;                                                                                 // Set node arches list to NULL
  fbk_nl(1);  fbk_gn_cy("New graph node correctly added!\n");                                               // New graph node correctly added fbk
  return nd_ptr;                                                                                            // Retun new allocated node addr
}


void connect_node_arch(Graph_node* nd, Graph_arch* ar, Node_pos_in_arch nd_pos, Arch_pos_typ ar_pos, ...){  // Function to connect arch-node in graph (new anch list element allocated inside heap, opt param --> arch pos, non-zero index)
  /* Body */
  Graph_node nd_ptr = *nd;                                                                                  // Node ptr var to access given node data
  Graph_arch ar_ptr = *ar;                                                                                  // Arch ptr var to access given arch data
  int list_pos = 0;                                                                                         // List position in which arch must be placed in node conn. arches list
  fbk_nl(1);  fbk_gn_pu("Creating bidirectional connection between node and arch...");                      // Creatin' bidirectional connection between node and arch
  // Function optional parameters management
  if (ar_pos == LIST_POS){                                                                                  // If selected arch position type in list is specific position, read list position optional parameter
    va_list args_lst;                                                                                       // Function optional parameters list int
    va_start(args_lst, ar_pos);                                                                             // Define optional params list startin' point
    list_pos = va_arg(args_lst, int);                                                                       // Read the first optional parameter in funct opt params list (= define list position)
  }
  // Assign node to arch
  fbk_nl(1);  fbk_gn_lbu_ye_str("Connecting node to", node_pos_in_arch_str[nd_pos]);                        // Connectin' node to arch fbk
  switch (nd_pos){                                                                                          // Node assignin' position in arch switch-case (where to assign node in arch)
    case ARCH_ND1:                                                                                          // Case: assign node to arch node1 position
      ar_ptr->nd1 = nd_ptr;                                                                                 // Assign node to arch node1 pos
      break;
    //////////////
    case ARCH_ND2:                                                                                          // Case: assign node to arch node2 position
      ar_ptr->nd2 = nd_ptr;                                                                                 // Assign node to arch node2 pos
      break;
    ////////
    default:                                                                                                // Unknown case
      perror("Wrong \"nd_pos\" parameter value passsed to \"connect_node_arch\" function!");                // print perror fbk
    break;
  }
  // Assign arch to node
  fbk_nl(1);  fbk_gn_lbu_ye_str("Connecting arch to node connection archs", arch_pos_typ_str[ar_pos]);      // Connectin' node to arch fbk
  List_elem* tmp_el = allocate_new_list_elems(1);                                                           // Tmp list element ptr creation
  tmp_el->ar = ar_ptr;                                                                                      // Tmp list element ptr def with input arch memo cell addr
  switch (ar_pos){                                                                                          // Arch assignin' position type in node arches list switch-case (where to assign arch in node arches connections list) switch-case
    case LIST_HEAD:                                                                                         // Case: assign arch to node arches connections list (head position)
      add_elem_at_list_head(&nd_ptr->archs_lst, tmp_el);                                                    // Assign arch (in tmp list element) to the given node conn. arches list (head position)
      break;
    //////////////
    case LIST_POS:                                                                                          // Case: assign arch to node arches connections list (specific position, pos from optional funct param)
      add_elem_at_list_pos(&nd_ptr->archs_lst, tmp_el, list_pos);                                           // Assign arch (in tmp list element) to the given node conn. arches list (specific position, non-zero index)
      break;
    ///////////////
    case LIST_TAIL:                                                                                         // Case: assign arch to node arches connections list (tail position)
      add_elem_at_list_tail(&nd_ptr->archs_lst, tmp_el);                                                    // Assign arch (in tmp list element) to the given node conn. arches list (tail position)
      break;
    ////////
    default:                                                                                                // Unknown case
      perror("Wrong \"ar_pos\" parameter value passsed to \"connect_node_arch\" function!");                // print perror fbk
      break;
  }
  fbk_nl(1);  fbk_gn_cy("Bidirectional node-arch connetion correctly created!\n");                          // Bidirectional node-arch connection correctly created fbk
}


Graph_arch* archs_connected_to_node(const Graph_node* const nd, int* const vect_size, Verbose_mode v_mode){ // Function to get a vector of arch ptrs connected to a node (vector allocated inside heap) - Y/N for verbose mode
  /* Body */
  Graph_node nd_ptr = *nd;                                                                                  // Node ptr var to access given node data
  List_elem* tmp_el = nd_ptr->archs_lst;                                                                    // Define tmp list elem ptr var (to scroll arches inside node conn. arches list)
  Graph_arch* arch_ptrs_vect = NULL;                                                                        // Vector of arch ptrs connected to node
  *vect_size = 0;                                                                                           // Number of arches connected to node
  if (v_mode == Y){                                                                                         // If verbose mode is enabled, print fbk
    fbk_nl(1);  fbk_gn_pu("Looking for arches connected to specified node...");                             // Looking for arches connected to node fbk
  }
  for (; tmp_el != NULL; tmp_el = tmp_el->nxt, ++*vect_size){                                               // Scroll node conn. arches list, upd num of arches connected to node, resize arch ptrs vect inside heap and define vector elements
    if (*vect_size == 0)                                                                                    // If it's the first iteration, allocate arch ptrs vector
      arch_ptrs_vect = allocate_new_arch_ptrs(*vect_size+1);                                                // Init arch ptrs vect inside heap
    else                                                                                                    // If it's not the first iteration, reallocate arch ptrs vector (resize)
      reallocate_arch_ptrs_vect(arch_ptrs_vect, *vect_size+1);                                              // Resize arch ptrs vect inside heap
    *(arch_ptrs_vect+iaddr(V, *vect_size, *vect_size+1)) = tmp_el->ar;                                      // Define elements of arch ptrs vect inside heap
  }
  if (v_mode == Y){                                                                                         // If verbose mode is enabled, print fbk
    fbk_nl(1);  fbk_gn_cy("Arches connected to specified node correctly acquired!\n");                      // Arches connected to node correctly acquired fbk
  }
  return arch_ptrs_vect;                                                                                    // Return vector of arch ptrs connected to node
}


Graph_node* nodes_connected_to_node(const Graph_node* const nd, int* const vect_size){                      // Function to get a vector of node ptrs connected to a node (vector allocated inside heap)
  /* Body */
  Graph_node nd_ptr = *nd;                                                                                  // Node ptr var to access given node data
  List_elem* tmp_el = nd_ptr->archs_lst;                                                                    // Define tmp list elem ptr var (to scroll arches inside node conn. arches list)
  Graph_node* node_ptrs_vect = NULL;                                                                        // Vector of node ptrs connected to node
  *vect_size = 0;                                                                                           // Number of nodes connected to node
  fbk_nl(1);  fbk_gn_pu("Looking for nodes connected to specified node...");                                // Looking for nodes connected to node fbk
  for (; tmp_el != NULL; tmp_el = tmp_el->nxt, ++*vect_size){                                               // Scroll node conn. arches list, upd num of arches connected to node, resize node ptrs vect inside heap and define vector elements
    if (*vect_size == 0)                                                                                    // If it's the first iteration, allocate node ptrs vector
      node_ptrs_vect = allocate_new_node_ptrs(*vect_size+1);                                                // Init node ptrs vect inside heap
    else                                                                                                    // If it's not the first iteration, reallocate node ptrs vector (resize)
      reallocate_node_ptrs_vect(node_ptrs_vect, *vect_size+1);                                              // Resize node ptrs vect inside heap
    if (*nd == tmp_el->ar->nd1)                                                                             // If specified node memo addr corresponds to the arch conn. node1, assign arch conn. node2 in newly allocated memo cell inside vect
      *(node_ptrs_vect+iaddr(V, *vect_size, *vect_size+1)) = tmp_el->ar->nd2;                               // Define elements of node ptrs vect inside heap
    else                                                                                                    // If specified node memo addr doesn't correspond to the arch conn. node1, assign arch conn. node1 in newly allocated memo cell inside vect
      *(node_ptrs_vect+iaddr(V, *vect_size, *vect_size+1)) = tmp_el->ar->nd1;                               // Define elements of node ptrs vect inside heap
  }
  fbk_nl(1);  fbk_gn_cy("Nodes connected to specified node correctly acquired!\n");                         // Nodes connected to node correctly acquired fbk
  return node_ptrs_vect;                                                                                    // Return vector of node ptrs connected to node
}


void print_archs_costs(Graph_node* const start_nd){                                                         // Function to print all the arches costs, starting from a specified node and moving through the whole graph structure
  /* Body */
  Graph_node nd_ptr = *start_nd;                                                                            // Node ptr var to access given node data
  List_elem** tmp_el_vect = allocate_new_elem_ptrs(1);                                                      // Define and allocate tmp list elem ptrs vect inside heap (to scroll arches inside nodes conn. arches lists)
  int tmp_elems_vect_size = 1;                                                                              // Tmp list elements vector size
  tmp_el_vect[tmp_elems_vect_size-1] = nd_ptr->archs_lst;                                                   // -
  List_elem* tmp_el = *tmp_el_vect;                                                                         // Define tmp list elem ptr as the first elem in tmp list elem ptrs vect
  int tmp_el_idx = 0;                                                                                       // Tmp list element index (graph lvl startin' from given node)
  fbk_nl(1);  fbk_gn_pu("Scanning the whole graph structure to print arches costs...");                     // Scanning the whole graph to print arches costs fbk
  for (; tmp_el != NULL && tmp_el_idx == 0; tmp_el = tmp_el->nxt){                                          // Scroll node conn. arches list ---
    fbk_nl(1);  fbk_gn_lbu_ye_real("Arch cost", tmp_el->ar->cost);                                          // Print arch cost fbk
    if (nd_ptr == tmp_el->ar->nd1 && tmp_el->ar->nd2->archs_lst != NULL){                                   // If focused node memo addr corresponds to the arch conn. node1 (and node 2 has other connections), select node2 and look for other arches to print
      reallocate_elem_ptrs_vect(tmp_el_vect, ++tmp_elems_vect_size);                                        // -
      tmp_el_vect[tmp_elems_vect_size-1] = tmp_el->ar->nd2->archs_lst;                                      // -
      tmp_el = tmp_el_vect[++tmp_el_idx];                                                                   // -
      continue;                                                                                             // -
    } else if (nd_ptr == tmp_el->ar->nd2 && tmp_el->ar->nd1->archs_lst != NULL){                            // Else if focused node memo addr doesn't correspond with the arch conn. node1 (and node 1 has other connections), select node1 and look for other arches to print
      reallocate_elem_ptrs_vect(tmp_el_vect, ++tmp_elems_vect_size);                                        // -
      tmp_el_vect[tmp_elems_vect_size-1] = tmp_el->ar->nd1->archs_lst;                                      
      tmp_el = tmp_el_vect[++tmp_el_idx];                                                                   // -
      continue;                                                                                             // -
    } else if ((tmp_el->ar->nd1->archs_lst != NULL || tmp_el->ar->nd2->archs_lst != NULL) && tmp_el_idx > 0){ // -
      reallocate_elem_ptrs_vect(tmp_el_vect, --tmp_elems_vect_size);                                        // -
      tmp_el_vect[tmp_elems_vect_size-1] = tmp_el->nxt;                                                     // -
      tmp_el = tmp_el_vect[--tmp_el_idx];                                                                   // -
      continue;                                                                                             // -
    }
  }
  fbk_nl(1);  fbk_gn_cy("---!\n");                                                                          // ---
}


// void free_graph(Graph_arch* archs_collec_vect, int *const ar_num,
//                 Graph_node* nodes_collec_vect, int *const nd_num){                                          // Function to free graph allocated memory
//   /* Body */
//   fbk_nl(1);  fbk_gn_pu("Clearing the whole graph structure...");                                           // Clearing the whole graph from heap fbk
//   free(archs_collec_vect);                                                                                  // Free arches collection vector allocated memo inside heap
//   free(nodes_collec_vect);                                                                                  // Free nodes collection vector allocated memo inside heap
//   *ar_num = 0;                                                                                              // Set graph arches number back to zero
//   *nd_num = 0;                                                                                              // Set graph nodes number back to zero
//   fbk_nl(1);  fbk_gn_cy("Graph structure correctly erased!\n");                                             // Graph structure correctly created erased from heap fbk
// }



/// MOD on rmv_elm_pos funct
