/*
 * Author: Cristian Merli
 * Code title: Graph library
 * Code version: 1.0
 * Creation date: 22/06/2021
 * Last mod. date: 22/06/2021
 */


/* Libraries */
#include "lib_graph.h"                                                                                      // Import graph library header file


/* Lib vars */
static int ars_collect_size = 0, nds_collect_size = 0;                                                      // Arches and nodes collection vectors sizes
static Arch* archs_collect_vect = NULL;                                                                     // Graph arches collection vector
static Node* nodes_collect_vect = NULL;                                                                     // Graph nodes collection vector


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


static void free_list_elems(List* list_head, Verbose_mode v_mode){                                          // Function to free allocated elements inside heap, startin' from specified list (or sub-list) head, 'till list (or sub-list) tail - Y/N for verbose mode
  /* Body */
  List tmp_list_head = *list_head;                                                                          // Tmp var to clear allocated memo inside heap
  for (int i = 0; tmp_list_head != NULL; tmp_list_head = tmp_list_head->nxt, ++i){                          // List (or sub-list) scrollin' FOR cycle to clear heap allocated memo
    if (v_mode == Y){                                                                                       // If verbose mode is enabled, print fbk
    fbk_nl(1);  fbk_gn_lbu_ye_int("Removing allocated list element from heap, element number", i+1);        // Print removing element from heap fbk
    }
    free(tmp_list_head);                                                                                    // Clear allocated elements
  }
  *list_head = NULL;                                                                                        // Set elements list (or sub-list) head to null
}


static int iaddr(C_int i, C_int j, C_int lda){                                                              // Arrays/vectors memo addressing
  /* Body */
  return (i*lda)+j;                                                                                         // Return index number
}


static void allocate_new_archs(){                                                                           // Function to allocate new graph arches (single/vect)
  /* Body */
  ars_collect_size = 0;                                                                                     // Make sure to have arches collection vect size set to zero
  archs_collect_vect = calloc(1, sizeof(Arch));                                                             // Tmp graph arch ptr creation to point at first allocated memo cell inside heap
  if (archs_collect_vect == NULL){                                                                          // Check calloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during graph data management");                                          // Error fbk
    perror("Found error during graph arches dynamic memory allocation with calloc!");                       // print perror fbk
    close_err();                                                                                            // Close software with error function call
  } else                                                                                                    // In case of dyn memo allocation OK
    ++ars_collect_size;                                                                                     // Upd arches collection vect size
}


static void allocate_new_nodes(){                                                                           // Function to allocate new graph nodes (single/vect)
  /* Body */
  nds_collect_size = 0;                                                                                     // Make sure to have nodes collection vect size set to zero
  nodes_collect_vect = calloc(1, sizeof(Node));                                                             // Tmp graph node ptr creation to point at first allocated memo cell inside heap
  if (nodes_collect_vect == NULL){                                                                          // Check calloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during graph data management");                                          // Error fbk
    perror("Found error during graph nodes dynamic memory allocation with calloc!");                        // print perror fbk
    close_err();                                                                                            // Close software with error function call
  } else                                                                                                    // In case of dyn memo allocation OK
    ++nds_collect_size;                                                                                     // Upd nodes collection vect size
}


static void reallocate_new_archs(){                                                                         // Function to reallocate new graph arches (single/vect)
  /* Body */
  archs_collect_vect = realloc(archs_collect_vect, (size_t)(ars_collect_size+1)*sizeof(Arch));              // Tmp graph arch ptr creation to point at first allocated memo cell inside heap
  if (archs_collect_vect == NULL){                                                                          // Check realloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during graph data management");                                          // Error fbk
    perror("Found error during graph arches dynamic memory reallocation with realloc!");                    // print perror fbk
    close_err();                                                                                            // Close software with error function call
  } else                                                                                                    // In case of dyn memo reallocation OK
    ++ars_collect_size;                                                                                     // Upd arches collection vect size
}


static void reallocate_new_nodes(){                                                                         // Function to reallocate new graph nodes (single/vect)
  /* Body */
  nodes_collect_vect = realloc(nodes_collect_vect, (size_t)(nds_collect_size+1)*sizeof(Node));              // Tmp graph node ptr creation to point at first allocated memo cell inside heap
  if (nodes_collect_vect == NULL){                                                                          // Check realloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during graph data management");                                          // Error fbk
    perror("Found error during graph nodes dynamic memory reallocation with realloc!");                     // print perror fbk
    close_err();                                                                                            // Close software with error function call
  } else                                                                                                    // In case of dyn memo reallocation OK
    ++nds_collect_size;                                                                                     // Upd nodes collection vect size
}


static Connection* allocate_new_nd_conn_vect(C_int num){                                                    // Function to allocate new node connections vector
  /* Body */
  Graph_arch* tmp_nd_conn_ptr = calloc((size_t)num, sizeof(Graph_arch));                                    // Tmp graph arch ptr of ptrs creation to point at first allocated memo cell inside heap
  if (tmp_arch_ptr == NULL || num == 0){                                                                    // Check calloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during graph data management");                                          // Error fbk
    perror("Found error during graph arch pointers dynamic memory allocation with calloc!");                // print perror fbk
    close_err();                                                                                            // Close software with error function call
  }
  return tmp_arch_ptr;                                                                                      // Return tmp graph arch ptrs, firtst allocated memo cell inside heap (pointer)
}


static void reallocate_arch_ptrs_vect(Graph_arch** archs_vect, C_int size){                                 // Function to reallocate graph arch pointers vector (resize)
  /* Body */
  *archs_vect = realloc(*archs_vect, (size_t)size*sizeof(Graph_arch));                                      // Graph arch ptrs vect ptr addr upd to make sure it points at first reallocated memo cell inside heap
  if (*archs_vect == NULL || size == 0){                                                                    // Check realloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during graph data management");                                          // Error fbk
    perror("Found error during graph arches vector dynamic memory reallocation with realloc!");             // print perror fbk
    close_err();                                                                                            // Close software with error function call
  }
}


static Connection* node_conn(Node* nd, int* const vect_size, Verbose_mode v_mode){                          // Function to get a vector of connections associated to a specific node (vector allocated inside heap) - Y/N for verbose mode
  /* Body */
  List_elem* tmp_el = nd->archs_lst;                                                                        // Define tmp list elem ptr var (to scroll arches inside node conn. arches list)
  Connection* arch_ptrs_vect = NULL;                                                                        // Vector of arch ptrs connected to node
  *vect_size = 0;                                                                                           // Number of arches connected to node
  if (v_mode == Y){                                                                                         // If verbose mode is enabled, print fbk
    fbk_nl(1);  fbk_gn_pu("Looking for arches connected to specified node...");                             // Looking for arches connected to node fbk
    fbk_nl(1);  fbk_gn_lbu_ye_ptr("Node address", nd);                                                      // Print node address fbk
  }
  for (; tmp_el != NULL; tmp_el = tmp_el->nxt, ++*vect_size){                                               // Scroll node conn. arches list, upd num of arches connected to node, resize arch ptrs vect inside heap and define vector elements
    if (*vect_size == 0)                                                                                    // If it's the first iteration, allocate arch ptrs vector
      arch_ptrs_vect = allocate_new_arch_ptrs(*vect_size+1);                                                // Init arch ptrs vect inside heap
    else                                                                                                    // If it's not the first iteration, reallocate arch ptrs vector (resize)
      reallocate_arch_ptrs_vect(&arch_ptrs_vect, *vect_size+1);                                             // Resize arch ptrs vect inside heap
    *(arch_ptrs_vect+iaddr(V, *vect_size, *vect_size+1)) = tmp_el->ar;                                      // Define elements of arch ptrs vect inside heap
//     if (&nodes_collect_vect[nd_num-1] == tmp_el->ar->nd1)                                                   // If specified node memo addr corresponds to the arch conn. node1, assign arch conn. node2 in newly allocated memo cell inside vect
//       *(node_ptrs_vect+iaddr(V, *vect_size, *vect_size+1)) = tmp_el->ar->nd2;                               // Define elements of node ptrs vect inside heap
//     else                                                                                                    // If specified node memo addr doesn't correspond to the arch conn. node1, assign arch conn. node1 in newly allocated memo cell inside vect
//       *(node_ptrs_vect+iaddr(V, *vect_size, *vect_size+1)) = tmp_el->ar->nd1;                               // Define elements of node ptrs vect inside heap
  }
  if (v_mode == Y){                                                                                         // If verbose mode is enabled, print fbk
    fbk_nl(1);  fbk_gn_cy("Arches connected to specified node correctly acquired!\n");                      // Arches connected to node correctly acquired fbk
  }
  return arch_ptrs_vect;                                                                                    // Return vector of arch ptrs connected to node
}


/* Public functions */
void add_new_arch(C_real cost){                                                                             // Function to add new graph arch (arch allocated inside heap)
  /* Body */
  fbk_nl(1);  fbk_gn_pu("Adding new graph arch...");                                                        // Adding new graph arch fbk
  if (archs_collect_vect == NULL)                                                                           // Check arches collection vector, if null
    allocate_new_archs();                                                                                   // Allocate a new graph arch inside arches collection vector (vect calloc)
  else                                                                                                      // Else if not null
    reallocate_new_archs();                                                                                 // Allocate a new graph arch inside arches collection vector (vect realloc)
  archs_collect_vect[ars_collect_size-1].cost = cost;                                                       // Define arch cost
  fbk_nl(1);  fbk_gn_lbu_ye_real("New arch cost", cost);                                                    // Adding new graph arch fbk
  archs_collect_vect[ars_collect_size-1].nd1 = NULL;                                                        // Set node1 connection to NULL
  archs_collect_vect[ars_collect_size-1].nd2 = NULL;                                                        // Set node2 connection to NULL
  fbk_nl(1);  fbk_gn_cy("New graph arch correctly added!\n");                                               // New graph arch correctly added fbk
}


void add_new_node(){                                                                                        // Function to add new graph node (node allocated inside heap)
  /* Body */
  fbk_nl(1);  fbk_gn_pu("Adding new graph node...");                                                        // Adding new graph node fbk
  if (nodes_collect_vect == NULL)                                                                           // Check nodes collection vector, if null
    allocate_new_nodes();                                                                                   // Allocate a new graph node inside arches collection vector (vect calloc)
  else                                                                                                      // Else if not null
    reallocate_new_nodes();                                                                                 // Allocate a new graph node inside arches collection vector (vect realloc)
  nodes_collect_vect[nds_collect_size-1].archs_lst = NULL;                                                  // Set node arches list to NULL
  fbk_nl(1);  fbk_gn_cy("New graph node correctly added!\n");                                               // New graph node correctly added fbk
}


void connect_node_arch(C_int ar_num, C_int nd_num, Node_pos_in_arch nd_pos, Arch_pos_typ ar_pos, ...){      // Function to connect arch-node in graph, non-zero index (new arch list element allocated inside heap, opt param --> arch pos, non-zero index)
  /* Body */
  int list_pos = 0;                                                                                         // List position in which arch must be placed in node conn. arches list
  fbk_nl(1);  fbk_gn_pu("Creating bidirectional connection between node and arch...");                      // Creatin' bidirectional connection between node and arch
  fbk_nl(1);  fbk_gn_lbu_ye_int("Working on node number", nd_num);                                          // Print node num fbk
  fbk_nl(1);  fbk_gn_lbu_ye_int("Working on arch number", ar_num);                                          // Print arch num fbk
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
      archs_collect_vect[ar_num-1].nd1 = &nodes_collect_vect[nd_num-1];                                     // Assign node to arch node1 pos
      break;
    //////////////
    case ARCH_ND2:                                                                                          // Case: assign node to arch node2 position
      archs_collect_vect[ar_num-1].nd2 = &nodes_collect_vect[nd_num-1];                                     // Assign node to arch node2 pos
      break;
    ////////
    default:                                                                                                // Unknown case
      perror("Wrong \"nd_pos\" parameter value passsed to \"connect_node_arch\" function!");                // print perror fbk
    break;
  }
  // Assign arch to node
  fbk_nl(1);  fbk_gn_lbu_ye_str("Connecting arch to node connection archs", arch_pos_typ_str[ar_pos]);      // Connectin' node to arch fbk
  List_elem* tmp_el = allocate_new_list_elems(1);                                                           // Tmp list element ptr creation
  tmp_el->ar = &archs_collect_vect[ar_num-1];                                                               // Tmp list element ptr def with input arch memo cell addr
  switch (ar_pos){                                                                                          // Arch assignin' position type in node arches list switch-case (where to assign arch in node arches connections list) switch-case
    case LIST_HEAD:                                                                                         // Case: assign arch to node arches connections list (head position)
      add_elem_at_list_head(&nodes_collect_vect[nd_num-1].archs_lst, tmp_el);                               // Assign arch (in tmp list element) to the specified node conn. arches list (head position)
      break;
    //////////////
    case LIST_POS:                                                                                          // Case: assign arch to node arches connections list (specific position, pos from optional funct param)
      add_elem_at_list_pos(&nodes_collect_vect[nd_num-1].archs_lst, tmp_el, list_pos);                      // Assign arch (in tmp list element) to the specified node conn. arches list (specific position, non-zero index)
      break;
    ///////////////
    case LIST_TAIL:                                                                                         // Case: assign arch to node arches connections list (tail position)
      add_elem_at_list_tail(&nodes_collect_vect[nd_num-1].archs_lst, tmp_el);                               // Assign arch (in tmp list element) to the specified node conn. arches list (tail position)
      break;
    ////////
    default:                                                                                                // Unknown case
      perror("Wrong \"ar_pos\" parameter value passsed to \"connect_node_arch\" function!");                // print perror fbk
      break;
  }
  fbk_nl(1);  fbk_gn_cy("Bidirectional node-arch connetion correctly created!\n");                          // Bidirectional node-arch connection correctly created fbk
}


void dijkstra_alg(C_int src_nd_num, C_int dest_nd_num){                                                     // Dijikstra alg 2 find min graph-path btwn source and destination nodes (non-zero index)
  Dijkstra_dataset dataset[nds_collect_size];                                                               // Dijikstra-dataset vect def
  // Inits
  for (int i = 0; i < nds_collect_size; ++i){                                                               // Inits FOR cycle
    if (i != src_nd_num-1)                                                                                  // If node is different from source node (non-zero idx)
      dataset[i].min_path_cost = INF;                                                                       // Init unknown min costs from source node (preset val)
    else                                                                                                    // Else if node ain't different from source node (non-zero idx)
      dataset[i].min_path_cost = 0;                                                                         // Init source-to-source cost (preset val)
    dataset[i].nd = &nodes_collect_vect[i];                                                                 // Dataset nodes init
    dataset[i].prev_nd = NULL;                                                                              // Dataset prev nodes init
    dataset[i].an_flg = 0;                                                                                  // Node analyzed flag val preset (as not analyzed)
  }
  int min_cost_idx = 0;                                                                                     // Min cost node in dataset index val init
  int nd_conn_vect_size = 0;                                                                                // Node connections vector size var to store selected node connections init
  Connection* nd_conn_vect = NULL;                                                                          // Node connections vector ptr var decl
  // Algorithm
  for (int j = 0; j < nds_collect_size-1; ++j){                                                             // Main algo loop
    // Select min-cost path node
    for (int k = 0; k < nds_collect_size; ++k){                                                             // Scroll the entire nodes collection (through Dijikstra-dataset vect) 2 detect min cost path node
      if (dataset[k].an_flg == 0 && dataset[k].min_path_cost < dataset[min_cost_idx].min_path_cost)         // Min cost path node detectin' cond (min val and node not alredy analized)
        min_cost_idx = k;                                                                                   // If detectin' cond is met, upd min cost node idx val
    }
    ++dataset[min_cost_idx].an_flg;                                                                         // Mark selected node as alredy analized b4 processin' it
    // Find archs connected 2 selected node
    nd_conn_vect_size = 0;                                                                                  // Node connections vector size var to store selected node connections (rst)
    nd_conn_vect = node_conn(dataset[min_cost_idx].nd, &nd_conn_vect_size, N);                              // Define selected node connections vect (vector allocated inside heap) - NO --> without verbose mode
    for (int k = 0; k < nd_conn_vect_size; ++k){                                                            // Scroll selected node connections vect
      //
    }
    if (nd_conn_vect != NULL)                                                                               // If node connections vector was correctly defined
      free(nd_conn_vect);                                                                                   // Free node connections vector allocated inside heap
  }
}


void free_graph(){                                                                                          // Function to free graph allocated memory
  /* Body */
  fbk_nl(1);  fbk_gn_pu("Clearing the whole graph structure...");                                           // Clearing the whole graph from heap fbk
  for (int i = 0; i < nds_collect_size; ++i)                                                                // Graph nodes scrollin' FOR cycle
    free_list_elems(&nodes_collect_vect[i].archs_lst, N);                                                   // Free graph arches list elems associated to each graph node - NO --> without verbose mode
  free(archs_collect_vect);                                                                                 // Free arches collection vector allocated memo inside heap
  free(nodes_collect_vect);                                                                                 // Free nodes collection vector allocated memo inside heap
  ars_collect_size = 0;                                                                                     // Set graph arches number back to zero
  nds_collect_size = 0;                                                                                     // Set graph nodes number back to zero
  fbk_nl(1);  fbk_gn_cy("Graph structure correctly erased!\n");                                             // Graph structure correctly created erased from heap fbk
}
