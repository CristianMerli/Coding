/*
 * Author: Cristian Merli
 * Code title: Navigator library
 * Code version: 3.0
 * Creation date: 04/05/2021
 * Last mod. date: 04/05/2021
 */


/* Libraries */
#include "lib_nav.h"                                                                                        // Import navigator library header file


/* Functions */
void assign_strt_to_crss(street *strt, cross *cross, const byte pos){                                       // Assign street to cross function
  /* Body */  
  if (pos < STRTS_NUM){                                                                                     // Check street position in cross val consistency
    cross->cross_strts[pos] = strt;                                                                         // Assign the input street in specified position of the input cross
  } else {
    printf("\n%s    Error in cross street definition! %s\n", RD, ER);                                       // Cross street definition error fbk
    printf("%sThe position of the street must be less than %s%d%s", RD, YE, STRTS_NUM, ER);                 // Cross street definition error specifications fbk
  }
}


void assign_conn_to_strt(street *strt, const union conn *conn, const conn_typ type){                        // Assign connection to street function
  /* Body */
  switch (type)                                                                                             // Connecttion type swith-case
  {
    ////////////
    case STREET:                                                                                            // Case STREET connection type
      strt->conn.strt = conn->strt;                                                                         // Assign to the given street, the given street connection
      strt->conn_typ = type;                                                                                // Assign to the given street, the given street connection type
      break;
    ///////////
    case CROSS:                                                                                             // Case CROSS connection type
      strt->conn.cross = conn->cross;                                                                       // Assign to the given street, the given cross connection
      strt->conn_typ = type;                                                                                // Assign to the given street, the given street connection type
      break;
    //////////
    case NONE:                                                                                              // Case NONE connection type
      fbk_err("Error in street connection definition! Connection type not defined");                        // Connection type not defined error fbk
      close_err();                                                                                          // Close software with error function call
      break;
    ////////
    default:                                                                                                // Default-case connection type
      fbk_err("Error in street connection definition! Unknown connection type");                            // Unknown connection type error fbk
      close_err();                                                                                          // Close software with error function call
      break;
  }
}


void navigate(const street *start_strt){                                                                    // Navigate through streets and crosses function
  /* Body */
  street nav_strt = *start_strt;                                                                            // Assign starting street to navigation street
  int sel_srtr = 0;                                                                                         // Selected street in cross to continue navigation
  byte err_flg = 0;                                                                                         // Error flag
  byte exit_flg = 0;                                                                                        // Exit flag

  fbk_nl(1);                                                                                                // New line fbk
  while (nav_strt.conn_typ != NONE){                                                                        // Streets and crosses navigation while cycle (exit condition --> next street connection empty)
    printf("%s\n    --> %sNow you are in %s%s%s, continuing...%s\n",
            OG, CY, LBU, nav_strt.name, CY, ER);                                                            // Print this street name fbk
    delay(1000);                                                                                            // Delay [ms] function call
    switch (nav_strt.conn_typ)                                                                              // Navigation street connection type swith-case
    {
      ////////////
      case STREET:                                                                                          // Case STREET connection type
        nav_strt = *nav_strt.conn.strt;                                                                     // Go into next street
        break;
      ///////////
      case CROSS:                                                                                           // Case CROSS connection type
        printf("\n%s    --> %sCross with %s%d streets found%s, choose a street to continue... %s\n",
                OG, CY, LBU, STRTS_NUM, CY, ER);                                                            // Print cross found fbk
        printf("\n        %s[1] %s%s,   %s[2] %s%s,   %s[3] %s%s,   %s[4] %s%s%s",
                RD, OG, nav_strt.conn.cross->cross_strts[FIRST]->name,
                RD, OG, nav_strt.conn.cross->cross_strts[SECOND]->name,
                RD, OG, nav_strt.conn.cross->cross_strts[THIRD]->name,
                RD, OG, nav_strt.conn.cross->cross_strts[FOURTH]->name, ER);                                // Print streets in cross options fbk
        printf("\n    ");                                                                                   // New lines fbk
        do{
          sel_srtr = read_term_in_int_inrange(1, STRTS_NUM,
                                              "Choose a street to continue", "The street number");          // String conversion to byte and val save into selected street var
          exit_flg = (nav_strt.conn.cross->cross_strts[sel_srtr-1] != NULL);                                // Exit flag val update
          if (!exit_flg)                                                                                    // Selected NULL street in cross detectin' cond
            fbk_err("Street not existing, retry");                                                          // Error fbk
        } while(!exit_flg);                                                                                 // Check if sel street val is in allowed range
        nav_strt = *nav_strt.conn.cross->cross_strts[sel_srtr-1];                                           // Proceed going into selected street
        break;
      ////////
      default:                                                                                              // Default-case connection type
        ++err_flg;                                                                                          // Set error flag
        fbk_err("Error in street connection definition! Unknown connection type");                          // Unknown connection type error fbk
        close_err();                                                                                        // Close software with error function call
        break;
    }
  }
  
  if (!err_flg){                                                                                            // Check error flag val
    printf("\n%s    --> %sNow you are in %s%s%s, arrived! %s:)%s\n",
            OG, CY, LBU, nav_strt.name, CY, LGN, ER);                                                       // Print last street name fbk
    delay(1000);                                                                                            // Delay [ms] function call
    printf("\n%s    --> %sNavigation completed! %sThe road trip is terminated.%s\n", OG, LGN, OG, ER);      // Navigation completed fbk
  }
}


void print_crs_strts_names(const cross *cross){                                                             // Print street names in cross function
  /* Body */
  printf("%s    Cross streets  %s--> %s", YE, CY, ER);                                                      // Print info fbk
  for (strts_in_crss i = FIRST; i < STRTS_NUM; ++i){                                                        // Street names in cross print FOR cycle
    if (cross->cross_strts[i] != NULL)                                                                      // NOT-NULL street in cross detectin' cond
      printf("%s | %s%s%s | %s", BU, OG, cross->cross_strts[i]->name, BU, ER);                              // Prtint each street name in cross (vector of streets)
    else                                                                                                    // NULL street in cross
      printf("%s | %sEMPTY%s | %s", BU, OG, BU, ER);                                                        // Prtint NULL street in cross (vector of streets)
  }
  fbk_nl(1);                                                                                                // New line fbk
}


street *create_strts_collection(const u_int num_strts, const char *name){                                   // Dyn memo alloc (calloc) function for streets collection init
  /* Body */
  street *ptr = calloc((size_t)num_strts, sizeof(street));                                                  // Street ptr creation to point first streets collection allocated memo cell inside heap
  
  if (ptr != NULL && num_strts > 0){                                                                        // Check calloc funct output to detect dynamic memory allocation errors
    strcpy(ptr->name, name);                                                                                // First street name init inside heap through pointer dereferencing
    ptr->conn_typ = NONE;                                                                                   // First street connection type init inside heap through pointer dereferencing      
  } else {
    perror("Error in streets collection dynamic memory allocation with calloc!");                           // print perror fbk
    close_err();                                                                                            // Close software with error function call
  }
  return ptr;                                                                                               // Return first streets collection allocated memo cell addr inside heap (pointer)
}


street *realloc_strts_collection(street *strts_collec, const u_int num_strts){                              // Dyn memo realloc function for streets collection
  /* Body */
  street *ptr = realloc(strts_collec, (size_t)num_strts*sizeof(street));                                    // Street ptr creation to point first streets collection allocated memo cell inside heap
  
  if (ptr == NULL || num_strts == 0){                                                                       // Check realloc funct output to detect dynamic memory allocation errors
    perror("Error in streets collection dynamic memory reallocation with realloc!");                        // Print perror fbk
    close_err();                                                                                            // Close software with error function call
  }
  return ptr;                                                                                               // Return first streets collection allocated memo cell addr inside heap (pointer)
}


void add_strt_in_strts_collection(street *strts_collec, const char *strt_name, const u_int pos){            // Add street in streets collection function
  /* Body */
  strcpy((*(strts_collec+pos)).name, strt_name);                                                            // Copy name in street
  (*(strts_collec+pos)).conn_typ = NONE;                                                                    // Define street as unconnected
}


cross *create_crss_collection(const u_int num_crss){                                                        // Dyn memo alloc (calloc) function for crosses collection init
  /* Body */
  cross *ptr = calloc((size_t)num_crss, (size_t)sizeof(cross));                                             // Cross ptr creation to point first crosses collection allocated memo cell inside heap
  
  if (ptr == NULL){                                                                                         // Check calloc funct output to detect dynamic memory allocation errors
    perror("Error in crosses collection dynamic memory allocation with calloc!");                           // Print perror fbk
    close_err();                                                                                            // Close software with error function call
  }
  return ptr;                                                                                               // Return first crosses collection allocated memo cell addr inside heap (pointer)
}


cross *realloc_crss_collection(cross *crss_collec, const u_int num_crss){                                   // Dyn memo realloc function for crosses collection
  /* Body */
  cross *ptr = realloc(crss_collec, (size_t)num_crss*sizeof(cross));                                        // Cross ptr creation to point first crosses collection allocated memo cell inside heap
  
  if (ptr == NULL){                                                                                         // Check realloc funct output to detect dynamic memory allocation errors
    perror("Error in crosses collection dynamic memory reallocation with realloc!");                        // Print perror fbk
    close_err();                                                                                            // Close software with error function call
  }
  return ptr;                                                                                               // Return first cross collection allocated memo cell addr inside heap (pointer)
}


void add_crs_in_crss_collection(cross *crss_collec, const int pos){                                         // Add cross in crosses collection function
  /* Body */
  for(strts_in_crss num = FIRST; num <= FOURTH; ++num){                                                     // Streets in cross empty val init FOR cycle
    (*(crss_collec+pos)).cross_strts[num] = NULL;                                                           // Streets in cross empty val init
  }
}


void print_strts_names_idxs(street *strts_collec, const u_int num_strts){                                   // Print streets names and indexes function
  /* Body */
  fbk_gn_pu("Listing index and name for each street in created streets collection:");                       // Print printin' info fbk

  // Table print
  const char *table_body_col = OG;                                                                          // Table body color
  const char *table_databody_col = GN;                                                                      // Table data-body color
  const char *table_titles_col = YE;                                                                        // Table titles text color
  const char *table_idx_col = CY;                                                                           // Table indexes text color
  const char *table_data_col = LBU;                                                                         // Table data text color
  fbk_nl(1);                                                                                                // New lines fbk                                                                                                 // New line feedback function call
  printf("%s    +-------+--------------------------------+%s\n", table_body_col, ER);                       // Top-line of the table
  printf("%s    | %s%4s%s  | %s%15s                %s|%s\n", table_body_col, table_titles_col,
         "Idx", table_body_col, table_titles_col, "Name", table_body_col, ER);                              // First line of the table (column identification)
  printf("%s    +-------+--------------------------------+%s\n", table_body_col, ER);                       // Top-line of the data inside the table
  for (u_int idx = 0; idx < num_strts; ++idx){                                                              // Data print FOR cycle
    printf("%s    | %s%3d%s   | %s%30s%s |%s\n",
           table_body_col, table_idx_col, idx+1,
           table_body_col, table_data_col, strts_collec[idx].name, table_databody_col, ER);                 // Data print
    printf("%s    +-------+%s--------------------------------+%s\n",
            table_body_col, table_databody_col, ER);                                                        // Bottom-line of the data inside the table
  }
}


void clear_map(street *strts_collec, cross *crss_collec){                                                   // Clear map from heap (free allocated dyn memo) function
  /* Body */
  free(strts_collec);                                                                                       // Clear streets collection
  free(crss_collec);                                                                                        // Clear crosses collection
}
