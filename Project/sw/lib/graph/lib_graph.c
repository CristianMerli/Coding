/*
 * Author: Cristian Merli
 * Code title: Graph library
 * Code version: 1.0
 * Creation date: 22/06/2021
 * Last mod. date: 04/07/2021
 */


/* Libraries */
#include "lib_graph.h"                                                                                      // Import graph library header file


/* Global vars */
const Real _REAL_MAX_ = __DBL_MAX__;                                                                        // Real max val to simulate +inf


/* Lib vars */
static int src_node_idx = 0, dest_node_idx = 0;                                                             // Source and destination node idxs (lib-vars)
static int ars_collect_size = 0, nds_collect_size = 0, min_pth_conn_vect_size = 0;                          // Arches and nodes collection vectors sizes + min path connections vect size
static Arch* archs_collect_vect = NULL;                                                                     // Graph arches collection vector ptr init
static Node* nodes_collect_vect = NULL;                                                                     // Graph nodes collection vector ptr init
static Dijkstra_dataset* dijk_dataset_vect = NULL;                                                          // Dijkstra-dataset vector ptr init
static Connection* min_path_conn_vect = NULL;                                                               // Min path connections vect ptr init
static Byte realloc_flg = 0;                                                                                // Realloc flag init (0=Dijk_algo-not-called / 1=Dijk_algo-called / 2=Dijk_algo-called+bld_shortest_pth-called)


/* Functions */
static int iaddr(C_int i, C_int j, C_int lda){                                                              // Arrays/vectors memo addressing
  /* Body */
  return (i*lda)+j;                                                                                         // Return index number
}


static List_elem* allocate_new_list_elems(C_int num){                                                       // Function to allocate new list elements (single/vect)
  /* Body */
  List_elem* tmp_list_elems = calloc((size_t)num, sizeof(List_elem));                                       // Tmp list element ptr creation to point at first allocated memo cell inside heap
  if (tmp_list_elems == NULL || num == 0){                                                                  // Check calloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during lists data management");                                          // Error fbk
    perror("Found error during list elements dynamic memory allocation with calloc!");                      // Print perror fbk
    free_graph();                                                                                           // Free graph structure b4 closin' sw
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
  List tmp_list_head = *list_head;                                                                          // Tmp var to clear allocated memo inside heap (list element)
  List tmp_nxt_el = *list_head;                                                                             // Tmp var to store next element in list memo inside heap
  for (int i = 0; tmp_list_head != NULL; tmp_list_head = tmp_nxt_el, ++i){                                  // List (or sub-list) scrollin' FOR cycle to clear heap allocated memo
    if (tmp_list_head != NULL){                                                                             // If allocated element ain't null
      if (v_mode == Y){                                                                                     // If verbose mode is enabled, print fbk
        fbk_nl(1);  fbk_gn_lbu_ye_int("Removing allocated list element from heap, element number", i+1);    // Print removing element from heap fbk
      }
      tmp_nxt_el = tmp_list_head->nxt;                                                                      // Updn ext element in list var
      free(tmp_list_head);                                                                                  // Clear allocated elements
    }
  }
  *list_head = NULL;                                                                                        // Set elements list (or sub-list) head to null
}


static void allocate_new_archs(){                                                                           // Function to allocate new graph arches (single/vect)
  /* Body */
  ars_collect_size = 0;                                                                                     // Make sure to have arches collection vect size set to zero
  archs_collect_vect = calloc(1, sizeof(Arch));                                                             // Tmp graph arch ptr creation to point at first allocated memo cell inside heap
  if (archs_collect_vect == NULL){                                                                          // Check calloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during graph data management");                                          // Error fbk
    perror("Found error during graph arches dynamic memory allocation with calloc!");                       // Print perror fbk
    free_graph();                                                                                           // Free graph structure b4 closin' sw
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
    perror("Found error during graph nodes dynamic memory allocation with calloc!");                        // Print perror fbk
    free_graph();                                                                                           // Free graph structure b4 closin' sw
    close_err();                                                                                            // Close software with error function call
  } else                                                                                                    // In case of dyn memo allocation OK
    ++nds_collect_size;                                                                                     // Upd nodes collection vect size
}


static void reallocate_new_archs(){                                                                         // Function to reallocate new graph arches (single/vect)
  /* Body */
  archs_collect_vect = realloc(archs_collect_vect, (size_t)(ars_collect_size+1)*sizeof(Arch));              // Tmp graph arch ptr creation to point at first allocated memo cell inside heap
  if (archs_collect_vect == NULL){                                                                          // Check realloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during graph data management");                                          // Error fbk
    perror("Found error during graph arches dynamic memory reallocation with realloc!");                    // Print perror fbk
    free_graph();                                                                                           // Free graph structure b4 closin' sw
    close_err();                                                                                            // Close software with error function call
  } else                                                                                                    // In case of dyn memo reallocation OK
    ++ars_collect_size;                                                                                     // Upd arches collection vect size
}


static void reallocate_new_nodes(){                                                                         // Function to reallocate new graph nodes (single/vect)
  /* Body */
  nodes_collect_vect = realloc(nodes_collect_vect, (size_t)(nds_collect_size+1)*sizeof(Node));              // Tmp graph node ptr creation to point at first allocated memo cell inside heap
  if (nodes_collect_vect == NULL){                                                                          // Check realloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during graph data management");                                          // Error fbk
    perror("Found error during graph nodes dynamic memory reallocation with realloc!");                     // print Perror fbk
    free_graph();                                                                                           // Free graph structure b4 closin' sw
    close_err();                                                                                            // Close software with error function call
  } else                                                                                                    // In case of dyn memo reallocation OK
    ++nds_collect_size;                                                                                     // Upd nodes collection vect size
}


static void allocate_new_dijk_dataset_vect(){                                                               // Function to allocate new Dijkstra-dataset vector
  /* Body */
  dijk_dataset_vect = calloc((size_t)nds_collect_size, sizeof(Dijkstra_dataset));                           // Dijkstra-dataset vect ptr creation to point at first allocated memo cell inside heap
  if (dijk_dataset_vect == NULL || nds_collect_size == 0){                                                  // Check calloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during graph data management");                                          // Error fbk
    perror("Found error during Dijkstra-dataset vector dynamic memory allocation with calloc!");            // Print perror fbk
    free_graph();                                                                                           // Free graph structure b4 closin' sw
    close_err();                                                                                            // Close software with error function call
  }
}


static void reallocate_dijk_dataset_vect(){                                                                 // Function to reallocate Dijkstra-dataset vector (resize)
  /* Body */
  dijk_dataset_vect = realloc(dijk_dataset_vect, (size_t)nds_collect_size*sizeof(Dijkstra_dataset));        // Dijkstra-dataset vect ptr addr upd to make sure it points at first reallocated memo cell inside heap
  if (dijk_dataset_vect == NULL || nds_collect_size == 0){                                                  // Check realloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during graph data management");                                          // Error fbk
    perror("Found error during Dijkstra-dataset vector dynamic memory reallocation with realloc!");         // Print perror fbk
    free_graph();                                                                                           // Free graph structure b4 closin' sw
    close_err();                                                                                            // Close software with error function call
  }
}


static Connection* allocate_new_nd_conn_vect(C_int num){                                                    // Function to allocate new node connections vector
  /* Body */
  Connection* tmp_nd_conn_ptr = calloc((size_t)num, sizeof(Connection));                                    // Tmp node connection ptr creation to point at first allocated memo cell inside heap
  if (tmp_nd_conn_ptr == NULL || num == 0){                                                                 // Check calloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during graph data management");                                          // Error fbk
    perror("Found error during node connections vector dynamic memory allocation with calloc!");            // Print perror fbk
    free_graph();                                                                                           // Free graph structure b4 closin' sw
    close_err();                                                                                            // Close software with error function call
  }
  return tmp_nd_conn_ptr;                                                                                   // Return tmp node connection ptr, firtst allocated memo cell inside heap (pointer)
}


static void reallocate_nd_conn_vect(Connection** nd_conn_vect, C_int size){                                 // Function to reallocate node connections vector (resize)
  /* Body */
  *nd_conn_vect = realloc(*nd_conn_vect, (size_t)size*sizeof(Connection));                                  // Node connections vect ptr addr upd to make sure it points at first reallocated memo cell inside heap
  if (*nd_conn_vect == NULL || size == 0){                                                                  // Check realloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during graph data management");                                          // Error fbk
    perror("Found error during node connections vector dynamic memory reallocation with realloc!");         // Print perror fbk
    free_graph();                                                                                           // Free graph structure b4 closin' sw
    close_err();                                                                                            // Close software with error function call
  }
}


static Connection* not_an_node_conn(Node* nd, int* const vect_size, Verbose_mode v_mode){                   // Function to get a vector of non-analyzed connections associated to a specific node (vector allocated inside heap) - Y/N for verbose mode
  /* Body */
  List_elem* tmp_el = nd->archs_lst;                                                                        // Define tmp list elem ptr var (to scroll arches inside node conn. arches list)
  Connection* nan_nd_conn_vect = NULL;                                                                      // Vector of non-analyzed connections associated to a specific node
  *vect_size = 0;                                                                                           // Number of non-analyzed connections associated to a specific node (rst)
  if (v_mode == Y){                                                                                         // If verbose mode is enabled, print fbk
    fbk_nl(1);  fbk_gn_pu("Looking for non-analyzed connections associated to a specific node...");         // Looking for non-analyzed connections associated to a specific node fbk
    fbk_nl(1);  fbk_gn_lbu_ye_ptr("Node address", nd);                                                      // Print node address fbk
  }
  for (; tmp_el != NULL; tmp_el = tmp_el->nxt){                                                             // Scroll node conn. arches list, upd num of non-analyzed connections associated to a specific node, resize node connections vect inside heap and define vector elements
    if ((nd == tmp_el->ar->nd1 && tmp_el->ar->nd2->dd->an_flg == 0) ||
        (nd == tmp_el->ar->nd2 && tmp_el->ar->nd1->dd->an_flg == 0)){                                       // Add node non-analyzed connection only if the destination node ain't been already analyzed
      if (*vect_size == 0)                                                                                  // If it's the first iteration, allocate vector of non-analyzed connections associated to a specific node
        nan_nd_conn_vect = allocate_new_nd_conn_vect(*vect_size+1);                                         // Init node non-analyzed connections vect inside heap
      else                                                                                                  // If it's not the first iteration, reallocate vector of non-analyzed connections associated to a specific node (resize)
        reallocate_nd_conn_vect(&nan_nd_conn_vect, *vect_size+1);                                           // Resize node non-analyzed connections vect inside heap
      if (nd == tmp_el->ar->nd1)                                                                            // If specified node memo addr corresponds to the arch conn. node1, assign arch conn. node2 in newly allocated element inside vect
        (nan_nd_conn_vect+iaddr(V, *vect_size, *vect_size+1))->nd = tmp_el->ar->nd2;                        // Define elements of node (non-analyzed) connections vect inside heap (connection node)
      else                                                                                                  // If specified node memo addr doesn't correspond to the arch conn. node1, assign arch conn. node1 in newly allocated element inside vect
        (nan_nd_conn_vect+iaddr(V, *vect_size, *vect_size+1))->nd = tmp_el->ar->nd1;                        // Define elements of node (non-analyzed) connections vect inside heap (connection node)
      (nan_nd_conn_vect+iaddr(V, *vect_size, *vect_size+1))->conn_ar = tmp_el->ar;                          // Define elements of node (non-analyzed) connections vect inside heap (connection arch)
      ++*vect_size;                                                                                         // Vector of non-analyzed connections associated to a specific node size val upd
    }
  }
  if (v_mode == Y){                                                                                         // If verbose mode is enabled, print fbk
    fbk_nl(1);  fbk_gn_cy("Non-analyzed connections associated to a specific node correctly acquired!\n");  // Non-analyzed connections associated to a specific node correctly acquired fbk
  }
  return nan_nd_conn_vect;                                                                                  // Return vector of non-analyzed connections associated to a specific node
}


static int idx_by_name(Obj_type object_type, Cstr object_name){                                             // Function to get object (arch/node) vector index by name
  /* Body */
  int match_found = -1;                                                                                     // Match found idx (-1 = No match found / -2 = Error)
  switch (object_type){                                                                                     // Object type switch-case
    case AR:                                                                                                // Object type = arch
      for (int i = 0; i < ars_collect_size; ++i)                                                            // Search match by-name in arches collection vector
        if (strcmp(object_name, archs_collect_vect[i].name) == 0)                                           // Match detecting condition
          match_found = i;                                                                                  // Retun match idx in vect
      break;
    ////////
    case ND:                                                                                                // Object type = node
      for (int j = 0; j < nds_collect_size; ++j)                                                            // Search match by-name in nodes collection vector
        if (strcmp(object_name, nodes_collect_vect[j].name) == 0)                                           // Match detecting condition
          match_found = j;                                                                                  // Retun match idx in vect
      break;
    ////////
    default:                                                                                                // Unknown object type
      fbk_err("Error, bad parameter value! A function got an unexpected patameter value");                  // Print error fbk
      perror("Wrong \"object_type\" parameter value passsed to \"idx_by_name\" function!");                 // Print perror fbk
      --match_found;                                                                                        // Decrease match found val to indicate error
      break;
  }
  if (match_found == -1)                                                                                    // No march found cond
    fbk_err("Error, no match found! Specified name probably wrong or not present in collection");           // Print err fbk
  return match_found;                                                                                       // Return val
}


static void print_min_paths(){                                                                              // Function to print each min path cost to reach every single accessible node from specified source-node
  /* Body */
  for (int m = 0; m < nds_collect_size; ++m){                                                               // Min path costs printin' FOR cycle
    fbk_nl(1);  fbk_gn_lbu_ye_str(":--------------------------------------------------------------", "");   // Print separator fbk
    fbk_nl(1);  fbk_gn_lbu_ye_str("--> Node name", nodes_collect_vect[m].name);                             // Print node name fbk
    if (nodes_collect_vect[m].dd->min_path_cost < _REAL_MAX_ &&
        &nodes_collect_vect[m] != &nodes_collect_vect[src_node_idx]){                                       // If node is reachble from specified source node
      fbk_nl(1); fbk_gn_lbu_ye_real("Min path cost to node", nodes_collect_vect[m].dd->min_path_cost);      // Print min path cost to reach that node from specified source-node fbk
    } else {                                                                                                // Else if node is unreachble from specified source node
      if (&nodes_collect_vect[m] == &nodes_collect_vect[src_node_idx]){                                     // Else if node memo addr corresponds to the source node memo addr
        fbk_nl(1);                                                                                          // Print new-line fbk
        fbk_gn_lbu_ye_str("Min path cost to node", "This node is the specified source node!");              // Print node correspondin' to the specified source node fbk
      } else {                                                                                              // Else if node is unreachble from specified source node
        fbk_nl(1);                                                                                          // Print new-line fbk
        fbk_gn_lbu_ye_str("Min path cost to node", "Node unreachble from specified source node!");          // Print node unreachble fbk
      }
    }
  }
  fbk_nl(1);  fbk_gn_lbu_ye_str(":--------------------------------------------------------------", "");     // Print separator fbk
}


static void print_shortest_path(){                                                                          // Print shortest path from pre-defined source node to specified destination node
  /* Body */
  fbk_nl(1);                                                                                                // New line fbk
  if (min_pth_conn_vect_size >= 2){                                                                         // If destination node is reachble and it's different from -
    fbk_gn_lbu_ye_int("Number of nodes between source and destination node", min_pth_conn_vect_size-2);     // Print num of nodes btwn source and destination node fbk
    for (int i = min_pth_conn_vect_size-1; i >= 0; --i){                                                    // -
      fbk_nl(1);  fbk_gn_lbu_ye_str("Path-node name", min_path_conn_vect[i].nd->name);                      // -
    }
  } else {                                                                                                  // -
    fbk_gn_lbu_ye_str("Number of nodes between source and destination node", "-");                          // -
    fbk_nl(1);  fbk_gn_lbu_ye_str("Path-node name", "-");                                                   // -
  }
}


/* Public functions */
void add_new_arch(C_real cost, Cstr name){                                                                  // Function to add new graph arch (arch allocated inside heap)
  /* Body */
  fbk_nl(1);  fbk_gn_pu("Adding new graph arch...");                                                        // Adding new graph arch fbk
  if (cost > 0.0){                                                                                          // If cost is positive
    if (archs_collect_vect == NULL)                                                                         // Check arches collection vector, if null
      allocate_new_archs();                                                                                 // Allocate a new graph arch inside arches collection vector (vect calloc)
    else                                                                                                    // Else if not null
      reallocate_new_archs();                                                                               // Allocate a new graph arch inside arches collection vector (vect realloc)
    if (strlen(name) > 0 && strlen(name) < AR_STR_LEN){                                                     // Check arch name length consistency, if ok
      strcpy(archs_collect_vect[ars_collect_size-1].name, name);  fbk_nl(1);                                // Copy name inside arch name var
    } else {                                                                                                // Else if arch name length consistency ain't ok
      fbk_err("Error, invalid arch name size! Overriding arch name with arch number in collection");        // Print error fbk
      char name_ovrd[AR_STR_LEN];                                                                           // Define new name to override input name
      sprintf(name_ovrd, "%d", ars_collect_size);                                                           // Define override-name as arch number in arches collection vect
      strcpy(archs_collect_vect[ars_collect_size-1].name, name_ovrd);                                       // Copy override-name inside arch name var
    }
    archs_collect_vect[ars_collect_size-1].cost = cost;                                                     // Define arch cost
    archs_collect_vect[ars_collect_size-1].nd1 = NULL;                                                      // Set node1 connection to NULL
    archs_collect_vect[ars_collect_size-1].nd2 = NULL;                                                      // Set node2 connection to NULL
    fbk_gn_lbu_ye_str("New arch name", archs_collect_vect[ars_collect_size-1].name);                        // New graph arch name fbk
    fbk_nl(1);  fbk_gn_lbu_ye_real("New arch cost", archs_collect_vect[ars_collect_size-1].cost);           // New graph arch cost fbk
    fbk_nl(1);  fbk_gn_cy("New graph arch correctly added!\n");                                             // New graph arch correctly added fbk
  } else {                                                                                                  // Else if cost ain't positive
    fbk_err("Ops! Encountred error during graph data management");                                          // Error fbk
    perror("Found error during arch object creation, its cost must be strictly positive!");                 // Print perror fbk
    free_graph();                                                                                           // Free graph structure b4 closin' sw
    close_err();                                                                                            // Close software with error function call
  }
}


void add_new_node(Cstr name){                                                                               // Function to add new graph node (node allocated inside heap)
  /* Body */
  fbk_nl(1);  fbk_gn_pu("Adding new graph node...");                                                        // Adding new graph node fbk
  if (nodes_collect_vect == NULL)                                                                           // Check nodes collection vector, if null
    allocate_new_nodes();                                                                                   // Allocate a new graph node inside nodes collection vector (vect calloc)
  else                                                                                                      // Else if not null
    reallocate_new_nodes();                                                                                 // Allocate a new graph node inside nodes collection vector (vect realloc)
  if (strlen(name) > 0 && strlen(name) < ND_STR_LEN){                                                       // Check node name length consistency, if ok
    strcpy(nodes_collect_vect[nds_collect_size-1].name, name);  fbk_nl(1);                                  // Copy name inside node name var
  } else {                                                                                                  // Else if node name length consistency ain't ok
    fbk_err("Error, invalid node name size! Overriding arch name with node number in collection");          // Print error fbk
    char name_ovrd[ND_STR_LEN];                                                                             // Define new name to override input name
    sprintf(name_ovrd, "%d", nds_collect_size);                                                             // Define override-name as node number in arches collection vect
    strcpy(nodes_collect_vect[nds_collect_size-1].name, name_ovrd);                                         // Copy override-name inside node name var
  }
  nodes_collect_vect[nds_collect_size-1].archs_lst = NULL;                                                  // Set node arches list to NULL
  nodes_collect_vect[nds_collect_size-1].dd = NULL;                                                         // Set node Dijkstra-dataset to NULL
  fbk_gn_lbu_ye_str("New node name", nodes_collect_vect[nds_collect_size-1].name);                          // New graph arch name fbk
  fbk_nl(1);  fbk_gn_cy("New graph node correctly added!\n");                                               // New graph node correctly added fbk
}


void connect_node_arch(Cstr ar_name, Cstr nd_name, Node_pos_in_arch nd_pos, Arch_pos_typ ar_pos, ...){      // Function to connect arch-node in graph (new arch list element allocated inside heap, opt param --> arch pos in arches list, non-zero index)
  /* Body */
  fbk_nl(1);  fbk_gn_pu("Creating bidirectional connection between node and arch...");                      // Creatin' bidirectional connection between node and arch
  int ar_num = idx_by_name(AR, ar_name);                                                                    // Get arch idx by-name
  int nd_num = idx_by_name(ND, nd_name);                                                                    // Get node idx by-name
  fbk_nl(1);  fbk_gn_lbu_ye_str("Working on node", nd_name);                                                // Print node name fbk
  fbk_nl(1);  fbk_gn_lbu_ye_str("Working on arch", ar_name);                                                // Print arch name fbk
  int lst_pos = 0;                                                                                          // List position in which arch must be placed in node conn. arches list
  // Function optional parameters management
  if (ar_pos == LIST_POS){                                                                                  // If selected arch position type in list is specific position, read list position optional parameter
    va_list args_lst;                                                                                       // Function optional parameters list int
    va_start(args_lst, ar_pos);                                                                             // Define optional params list startin' point
    lst_pos = va_arg(args_lst, int);                                                                        // Read the first optional parameter in funct opt params list (= define list position)
  }
  if (nd_num >= 0 && ar_num >= 0 && ((ar_pos == LIST_POS && lst_pos >= 1) || ar_pos != LIST_POS)){          // Check error conditions ok
    // Assign node to arch
    fbk_nl(1);  fbk_gn_lbu_ye_str("Connecting node to", node_pos_in_arch_str[nd_pos]);                      // Connectin' node to arch fbk
    switch (nd_pos){                                                                                        // Node assignin' position in arch switch-case (where to assign node in arch)
      case ARCH_ND1:                                                                                        // Case: assign node to arch node1 position
        archs_collect_vect[ar_num].nd1 = &nodes_collect_vect[nd_num];                                       // Assign node to arch node1 pos
        break;
      //////////////
      case ARCH_ND2:                                                                                        // Case: assign node to arch node2 position
        archs_collect_vect[ar_num].nd2 = &nodes_collect_vect[nd_num];                                       // Assign node to arch node2 pos
        break;
      ////////
      default:                                                                                              // Unknown case
        fbk_err("Error, bad parameter value! A function got an unexpected patameter value");                // Print error fbk
        perror("Wrong \"nd_pos\" parameter value passsed to \"connect_node_arch\" function!");              // Print perror fbk
        break;
    }
    // Assign arch to node
    fbk_nl(1);  fbk_gn_lbu_ye_str("Connecting arch to node connection archs", arch_pos_typ_str[ar_pos]);    // Connectin' node to arch fbk
    List_elem* tmp_el = allocate_new_list_elems(1);                                                         // Tmp list element ptr creation
    tmp_el->ar = &archs_collect_vect[ar_num];                                                               // Tmp list element ptr def with input arch memo cell addr
    switch (ar_pos){                                                                                        // Arch assignin' position type in node arches list switch-case (where to assign arch in node arches connections list) switch-case
      case LIST_HEAD:                                                                                       // Case: assign arch to node arches connections list (head position)
        add_elem_at_list_head(&nodes_collect_vect[nd_num].archs_lst, tmp_el);                               // Assign arch (in tmp list element) to the specified node conn. arches list (head position)
        break;
      //////////////
      case LIST_POS:                                                                                        // Case: assign arch to node arches connections list (specific position, pos from optional funct param)
        add_elem_at_list_pos(&nodes_collect_vect[nd_num].archs_lst, tmp_el, lst_pos);                       // Assign arch (in tmp list element) to the specified node conn. arches list (specific position, non-zero index)
        break;
      ///////////////
      case LIST_TAIL:                                                                                       // Case: assign arch to node arches connections list (tail position)
        add_elem_at_list_tail(&nodes_collect_vect[nd_num].archs_lst, tmp_el);                               // Assign arch (in tmp list element) to the specified node conn. arches list (tail position)
        break;
      ////////
      default:                                                                                              // Unknown case
        fbk_err("Error, bad parameter value! A function got an unexpected patameter value");                // Print error fbk
        perror("Wrong \"ar_pos\" parameter value passsed to \"connect_node_arch\" function!");              // Print perror fbk
        break;
    }
    fbk_nl(1);  fbk_gn_cy("Bidirectional node-arch connetion correctly created!\n");                        // Bidirectional node-arch connection correctly created fbk
  } else {                                                                                                  // If error conditions ain't ok
    fbk_err("Error, not able to create arch-node connection! Connection not created");                      // Print error fbk
    if (ar_pos == LIST_POS && lst_pos < 1)                                                                  // List pos err detect cond
      fbk_err("Error casued by specific list position flag enabled and invalid position value");            // Print error fbk
  }
}


void dijkstra_alg(Cstr src_nd_name){                                                                        // Dijkstra's alg to find min graph-path btwn source and each destination node
  /* Body */
  fbk_nl(1);  fbk_gn_pu("Looking for min path costs from specified source with Dijkstra's algorithm...");   // Print lookin' 4 shortest path btwn spec src and each dest nd fbk
  int src_nd_num = idx_by_name(ND, src_nd_name);                                                            // Get source node idx by-name
  fbk_nl(1);  fbk_gn_lbu_ye_str("Source node name", src_nd_name);                                           // Print source node name
  if (src_nd_num >= 0){                                                                                     // Check error conditions ok
    // Algorithm inits
    int min_cost_idx = 0;                                                                                   // Min cost node idx in dataset var init
    Real min_cost_val = 0.0;                                                                                // Min cost node val in dataset var init
    int nan_nd_conn_vect_size = 0;                                                                          // Node (non-analyzed) connections vector size var to store selected node non-analyzed connections init
    Real new_cost = 0.0;                                                                                    // New cost var init
    Connection* nan_nd_conn_vect = NULL;                                                                    // Node (non-analyzed) connections vector ptr var decl
    if (realloc_flg == 0){                                                                                  // If realloc flag ain't set
      allocate_new_dijk_dataset_vect();                                                                     // Dijkstra-dataset vect init (vector allocated inside heap)
      ++realloc_flg;                                                                                        // Set realloc flg
    } else                                                                                                  // Else if realloc flag has been set
      reallocate_dijk_dataset_vect();                                                                       // Dijkstra-dataset vect realloc (vector reallocated inside heap)
    for (int i = 0; i < nds_collect_size; ++i){                                                             // Inits FOR cycle
      nodes_collect_vect[i].dd = &dijk_dataset_vect[i];                                                     // Define and init nodes Dijkstra-datasets
      nodes_collect_vect[i].dd->prev_nd = NULL;                                                             // Node dataset prev node init
      nodes_collect_vect[i].dd->an_flg = 0;                                                                 // Node dataset analyzed flag val preset (as not analyzed)
      if (i != src_nd_num)                                                                                  // If node is different from source node
        nodes_collect_vect[i].dd->min_path_cost = _REAL_MAX_;                                               // Init unknown min costs from source node (preset val --> +inf)
      else                                                                                                  // Else if node ain't different from source node
        nodes_collect_vect[i].dd->min_path_cost = 0;                                                        // Init source-to-source cost (preset val --> zero)
    }
    src_node_idx = src_nd_num;                                                                              // Set/upd source node idx lib-var val
    // Algorithm loop
    for (int j = 0; j < nds_collect_size-1; ++j){                                                           // Main algo loop
      // Select node with min-cost path
      min_cost_val = _REAL_MAX_;                                                                            // Min cost node val in dataset upd
      for (int k = 0; k < nds_collect_size; ++k){                                                           // Scroll the entire nodes collection 2 detect min cost path node
        if (nodes_collect_vect[k].dd->an_flg == 0 &&
            nodes_collect_vect[k].dd->min_path_cost < min_cost_val){                                        // Min cost path node detectin' cond (min val and node not alredy analized)
          min_cost_val = nodes_collect_vect[k].dd->min_path_cost;                                           // If detectin' cond is met, upd min cost node val
          min_cost_idx = k;                                                                                 // And upd min cost node idx
        }
      }
      ++nodes_collect_vect[min_cost_idx].dd->an_flg;                                                        // Mark selected node as alredy analized b4 processin' it
      // Find non-analyzed connections of selected node
      nan_nd_conn_vect_size = 0;                                                                            // Node (non-analyzed) connections vector size var to store selected node non-analyzed connections (rst)
      nan_nd_conn_vect = not_an_node_conn(&nodes_collect_vect[min_cost_idx], &nan_nd_conn_vect_size, N);    // Define selected node non-analyzed connections vect (vector allocated inside heap) - NO --> without verbose mode
      for (int l = 0; l < nan_nd_conn_vect_size; ++l){                                                      // Scroll selected node non-analyzed connections vect
        new_cost = nodes_collect_vect[min_cost_idx].dd->min_path_cost+nan_nd_conn_vect[l].conn_ar->cost;    // New cost val upd
        // Upd min path cost and previous node in shortest path
        if (new_cost < nan_nd_conn_vect[l].nd->dd->min_path_cost){                                          // In case new cost val is less than min cost val
          nan_nd_conn_vect[l].nd->dd->min_path_cost = new_cost;                                             // Upd min cost val
          nan_nd_conn_vect[l].nd->dd->prev_nd = &nodes_collect_vect[min_cost_idx];                          // Upd previous min path node
        }
      }
      if (nan_nd_conn_vect != NULL)                                                                         // If node non-analyzed connections vector was correctly defined
        free(nan_nd_conn_vect);                                                                             // Free node non-analyzed connections vector allocated inside heap
    }
    // Print each min path cost to reach every single accessible node from specified source-node
    print_min_paths();                                                                                      // Print min paths funct call
    fbk_nl(1);  fbk_gn_cy("Min path costs correctly found!\n");                                             // Print min path costs correctly found fbk
  } else                                                                                                    // If error conditions ain't ok
    fbk_err("Error, not able to find min path costs with Dijkstra's algorithm");                            // Print error fbk
}


void buid_shortest_path(Cstr dest_nd_name){                                                                 // Reconstruct shortest path to specified destination node from source node (pre-defined in Dijkstra's algorithm)
  /* Body */
  fbk_nl(1);  fbk_gn_pu("Building min cost path from pre-defined source to specified destination...");      // Print reconstructin' shortest path from pre-defined source to specified destination fbk
  if (realloc_flg != 0){                                                                                    // If Dijkstra's algorithm has already been called at least once
    fbk_nl(1);  fbk_gn_lbu_ye_str("--> Source node name", nodes_collect_vect[src_node_idx].name);           // Print src-nd name fbk
    int dest_nd_num = idx_by_name(ND, dest_nd_name);                                                        // Get destination node idx by-name
    fbk_nl(1);  fbk_gn_lbu_ye_str("--> Destination node name", dest_nd_name);                               // Print dest-nd name fbk
    if (dest_nd_num >= 0){                                                                                  // Check error conditions ok
      dest_node_idx = dest_nd_num;                                                                          // Set/upd destination node idx lib-var val
      if (nodes_collect_vect[dest_nd_num].dd->min_path_cost < _REAL_MAX_ && dest_nd_num != src_node_idx){   // If destination node is reachble from pre-defined source node
        fbk_nl(1);                                                                                          // Print new-line fbk
        fbk_gn_lbu_ye_real("Min path cost to node", nodes_collect_vect[dest_nd_num].dd->min_path_cost);     // Print min path cost to reach destination node from pre-defined source node fbk
      } else if (dest_nd_num == src_node_idx){                                                              // Else if destination node memo addr corresponds to the source node memo addr
        fbk_nl(1);                                                                                          // Print new-line fbk
        fbk_gn_lbu_ye_str("Min path cost to node", "Destination corresponds to pre-defined source node!");  // Print destination node correspondin' to the pre-defined source node fbk
      } else {                                                                                              // Else if destination node is unreachble from pre-defined source node
        fbk_nl(1);                                                                                          // Print new-line fbk
        fbk_gn_lbu_ye_str("Min path cost to node", "Destination unreachble from pre-defined source node!"); // Print destination node unreachble fbk
      }
      Graph_node tmp_nd = &nodes_collect_vect[dest_nd_num];                                                 // -
      //List_elem* tmp_el = nd->archs_lst;                                                                        // Define tmp list elem ptr var (to scroll arches inside node conn. arches list)
      if (min_pth_conn_vect_size != 0)                                                                      // -
        min_pth_conn_vect_size = 0;                                                                         // -
      while (tmp_nd != NULL){                                                                               // -
        if (realloc_flg == 1){                                                                              // If realloc flag has been set
          min_path_conn_vect = allocate_new_nd_conn_vect(++min_pth_conn_vect_size);                         // -
          ++realloc_flg;                                                                                    // And then upd realloc flag val to use reallocs instead of callocs 'till "free_graph()" funct call
        } else                                                                                              // Else if realloc flag has been set
          reallocate_nd_conn_vect(&min_path_conn_vect, ++min_pth_conn_vect_size);                           // -
        (min_path_conn_vect+iaddr(V, min_pth_conn_vect_size-1, min_pth_conn_vect_size))->nd = tmp_nd;       // Define elements of -- MISSING --- connections vect inside heap (connection node)
        tmp_nd = tmp_nd->dd->prev_nd;                                                                       // -
        // Find arch and arch number in node -- MISSING ---
      }
      // Print shortest path from pre-defined source node to specified destination node
      print_shortest_path();                                                                                // Print shortest path funct call
      fbk_nl(1);  fbk_gn_cy("Destination node min cost path correctly identified!\n");                      // Print destination node min cost path correctly identified fbk
    } else                                                                                                  // If error conditions ain't ok
      fbk_err("Error, not able to find destination node min cost path with Dijkstra's algorithm");          // Print error fbk
  } else                                                                                                    // Else if Dijkstra's algorithm ain't been called
    fbk_err("Error, min path can be reconstructed only after having called Dijkstra's algorithm!");         // Print error fbk
}


void free_graph(){                                                                                          // Function to free graph allocated memory
  /* Body */
  fbk_nl(1);  fbk_gn_pu("Clearing the whole graph structure...");                                           // Clearing the whole graph from heap fbk
  for (int i = 0; i < nds_collect_size; ++i)                                                                // Graph nodes scrollin' FOR cycle
    if (nodes_collect_vect[i].archs_lst != NULL){                                                           // If node arches list ain't null
      free_list_elems(&nodes_collect_vect[i].archs_lst, N);                                                 // Free graph arches list elems associated to each graph node - NO --> without verbose mode
      nodes_collect_vect[i].archs_lst = NULL;                                                               // Set node arches list to null
    }
  if (archs_collect_vect != NULL){                                                                          // If arches collection vector needs to be cleared from heap
    free(archs_collect_vect);                                                                               // Free arches collection vector allocated memo inside heap
    archs_collect_vect = NULL;                                                                              // Set arches collection vector to null
  }
  if (nodes_collect_vect != NULL){                                                                          // If nodes collection vector needs to be cleared from heap
    free(nodes_collect_vect);                                                                               // Free nodes collection vector allocated memo inside heap
    nodes_collect_vect = NULL;                                                                              // Set nodes collection vector to null
  }
  if (dijk_dataset_vect != NULL){                                                                           // If Dijkstra-dataset vector needs to be cleared from heap
    free(dijk_dataset_vect);                                                                                // Free Dijkstra-dataset vector allocated memo inside heap
    dijk_dataset_vect = NULL;                                                                               // Set Dijkstra-dataset vector to null
  }
  if (min_path_conn_vect != NULL){                                                                          // If min path connections vector needs to be cleared from heap
    free(min_path_conn_vect);                                                                               // Free min path connections vector allocated memo inside heap
    min_path_conn_vect = NULL;                                                                              // Set min path connections vector to null
  }
  ars_collect_size = 0;                                                                                     // Set graph arches number back to zero
  nds_collect_size = 0;                                                                                     // Set graph nodes number back to zero
  min_pth_conn_vect_size = 0;                                                                               // Set min path connections vector size back to zero
  realloc_flg = 0;                                                                                          // Realloc flag rst
  fbk_nl(1);  fbk_gn_cy("Graph structure correctly erased!\n");                                             // Graph structure correctly created erased from heap fbk
}
