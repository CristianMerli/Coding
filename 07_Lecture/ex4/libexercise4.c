/*
 * Author: Cristian Merli
 * Code title: Exercise 4 (es_strutture_2) library
 * Code version: 3.0
 * Creation date: 21/04/2021
 * Last mod. date: 22/04/2021
 */


/* Libraries import */
#include "libexercise4.h"                                                                                   // Library for exercise 4 import header file


/* Functions declaration and definition */
void logo(const byte start_sp, const char *txt, const char *txt_col, const char bkg_chr,
          const char *bkg_col){                                                                             // Print responsive-logo function
  /* Function body */
  struct winsize w;                                                                                         // Window-size struct declaration
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);                                                                     // Save the number of terminal's rows/cloumns in window-size struct
  byte vthck = (w.ws_row / 5);                                                                              // Logo bkg vertical thickness calc
  byte lthck = (w.ws_col / 6);                                                                              // Logo bkg lateral thickness calc
  byte lsp = (w.ws_col - 2*lthck - 2*start_sp - strlen(txt)) / 2;                                           // Logo internal lateral spaces calc
  byte len = 2*lthck+2*lsp+strlen(txt);                                                                     // Logo length calc

  printf("\n%s", bkg_col);                                                                                  // New line fbk
  for (byte i = 0; i < (4*vthck+1); ++i){                                                                   // Logo lines print FOR cycle
    for (byte j = 0; j < start_sp; ++j){                                                                    // Initial spaces print FOR cycle
      printf(" ");                                                                                          // Print initial spaces
    }
    if ((i < vthck || i > (3*vthck)) && (i != (4*vthck)/2)){                                                // Full bkg logo lines print cond
      for (byte h = 0; h < len; ++h){                                                                       // Full bkg logo lines print FOR cycle
        printf("%c", bkg_chr);                                                                              // Bkg logo char print
      }
      printf("\n");                                                                                         // New line fbk
    } else if ((i >= vthck && i <= (3*vthck)) && (i != (4*vthck)/2)) {                                      // Partial-empty bkg logo lines print cond
      for (byte l = 0; l < lthck; ++l){                                                                     // Partial-empty bkg logo lines, initial full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Partial-empty bkg logo lines, initial full part print
      }
      for (byte m = 0; m < (len - 2*lthck); ++m){                                                           // Partial-empty bkg logo lines, central empty part print FOR cycle
        printf(" ");                                                                                        // Partial-empty bkg logo lines, central empty part print
      }
      for (byte n = 0; n < lthck; ++n){                                                                     // Partial-empty bkg logo lines, final full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Partial-empty bkg logo lines, final full part print
      }
      printf("\n");                                                                                         // New line fbk
    } else if (i == ((4*vthck)/2)) {                                                                        // Text logo line initial full part print cond
      for (byte o = 0; o < lthck; ++o){                                                                     // Text logo line initial full part print FOR cycle
        printf("%C", bkg_chr);                                                                              // Text logo line initial full part print
      }
      for (byte p = 0; p < lsp; ++p){                                                                       // Text logo line central empty part print FOR cycle
        printf(" ");                                                                                        // Text logo line central empty part print
      }
      printf("%s%s%s", txt_col, txt, bkg_col);                                                              // Text logo line central text part print
      for (byte q = 0; q < lsp; ++q){                                                                       // Text logo line central empty part print FOR cycle
        printf(" ");                                                                                        // Text logo line central empty part print
      }
      for (byte r = 0; r < lthck; ++r){                                                                     // Text logo line final full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Text logo line final full part print
      }
      printf("\n");                                                                                         // New line fbk
    }
  }
  printf("\033[0m\n");                                                                                      // New line fbk and erase logo bkg color
}


u_shrt iaddr(const u_shrt i, const u_shrt j, const u_shrt lda){                                             // Arrays/vectors memo addressing
  /* Function body */
  return (i*lda)+j;                                                                                         // Return index number
}


int vehic_garage_chk(const struct vehicle vehic, const struct garage gar,
                    const struct overdim_space_weight ovrdim_sp_wght){                                      // Vehicle-garage check function (compare vehicle dimensions and weight with garage dimensions and concrecte foundations max strength, considering space overdimensioning to allow vehicle-parking operations and weight factor of safety - sicurity coefficient)
  /* Function body */
  if (((vehic.dimens.x + 2*ovrdim_sp_wght.dimens.x) < gar.dimens.x) &&
      ((vehic.dimens.y + 2*ovrdim_sp_wght.dimens.y) < gar.dimens.y) &&
      ((vehic.dimens.z + ovrdim_sp_wght.dimens.z) < gar.dimens.z) &&
      ((vehic.weight * ovrdim_sp_wght.weight_fos) < gar.found_strngth)){                                    // Vehicle-garage check conditions (considering extra space and weight factor of safety)
    return 1;                                                                                               // Return 1 (Case OK)
  } else {                                                                                                  // Vehicle-garage check conditions not met
    return 0;                                                                                               // Return 0 (Case NOT-OK)
  }
}


static void bubble_sort(struct vehicle *elems, const shrt elems_num, const enum order ord){                 // Bubble sort algorithm (for structs) function
  /* Function body */
  shrt i, j;                                                                                                // FOR cycles idx
  real *elem_propr;                                                                                         // Element propriety to sort pointer
  real *nxt_elem_propr;                                                                                     // Next-element propriety to sort pointer
  struct vehicle tmp;                                                                                       // TMP var to swap elements in vector

  for (i = elems_num-1; i >= 0; --i){                                                                       // Remaning elements to sort FOR cycle
    for (j = 0; j < i; ++j){                                                                                // Sorting swaps FOR cycle
      elem_propr = &elems[j].weight;                                                                        // Point to the jth element propriety to sort elements inside the vector
      nxt_elem_propr = &elems[j+1].weight;                                                                  // Point to the jth+1 element propriety to sort elements inside the vector
      
      if (((*elem_propr < *nxt_elem_propr) && ord == DECREASING) ||
         ((*elem_propr > *nxt_elem_propr) && ord == CREASING)){                                             // Decreasing (or creasing) order conditions: swap element's positions if the following element propriety is greater (or less) than the propriety of the pointed element
        tmp = *(elems+iaddr(V, j, elems_num));                                                              // Save pointed element in TMP var to swap elements (use pointers and get vector position idx through the iaddr() function)
        *(elems+iaddr(V, j, elems_num)) = *(elems+iaddr(V, j+1, elems_num));                                // Move the following element in pointing position (use pointers and get vector position idx through the iaddr() function)
        *(elems+iaddr(V, j+1, elems_num)) = tmp;                                                            // Then copy the old pointed element previously saved in TMP swap variable, into the following element position (use pointers and get vector position idx through the iaddr() function)
      }
    }
  }
}


static void insertion_sort(struct vehicle *elems, const shrt elems_num, const enum order ord){              // Insertion sort algorithm (for structs) function
  /* Function body */
  shrt i, j;                                                                                                // FOR cycles idx
  struct vehicle tmp;                                                                                       // TMP var to swap elements in vector
  real volumes[elems_num];                                                                                  // Volumes vector for vehicles sorting declaration

  for(shrt k = 0; k < elems_num; ++k)                                                                       // Volumes vector population FOR cycle
    volumes[k] = elems[k].dimens.x*elems[k].dimens.y*elems[k].dimens.z*0.000000001;                         // Calculate vehicles volumes and save 'em in vector (conversion from mm^3 to m^3)

  for (i = 1; i < elems_num; ++i){                                                                          // Sorting elements FOR cycle
    tmp = *(elems+iaddr(V, i, elems_num));                                                                  // Save sorting element to swap in tmp var (use pointers and get vector position idx through the iaddr() function)
    for (j = i-1; j >= 0 && (((volumes[j] < volumes[i]) && ord == DECREASING) ||
        ((volumes[j] > volumes[i]) && ord == CREASING)); --j){                                              // Swap elements FOR cycle (cycle 'till zero or 'till already sorted elements reached in vector)
      *(elems+iaddr(V, j+1, elems_num)) = *(elems+iaddr(V, j, elems_num));                                  // Swap elements (use pointers and get vector position idx through the iaddr() function)
    }
    *(elems+iaddr(V, j+1, elems_num)) = tmp;                                                                // Complete elements swappin' (use pointers and get vector position idx through the iaddr() function)
  }
}


struct vehicle heaviest_vehic(struct vehicle *vehics, const shrt vehics_num){                               // Find heaviest vehicle in vehicles vector
  /* Function body */
  bubble_sort(vehics, vehics_num, DECREASING);                                                              // Sort vehicles in vector by weight usin' bubble sortin' algorithm

  return *vehics;                                                                                           // Return the first vehicle in the sorted vector (the heaviest one)
}


struct vehicle biggest_vehic(struct vehicle *vehics, const shrt vehics_num){                                // Find biggest vehicle in vehicles vector (volume)
  /* Function body */
  insertion_sort(vehics, vehics_num, CREASING);                                                             // Sort vehicles in vector by volume usin' insertion sortin' algorithm

  return *vehics;                                                                                           // Return the first vehicle in the sorted vector (the biggest one - volume)
}


void vehic_garage_assign(const struct vehicle vehic, struct garage *gar,
                        struct overdim_space_weight ovrdim_sp_wght){                                        // Vehicle-garage assign function
  /* Function body */
  if(vehic_garage_chk(vehic, *gar, ovrdim_sp_wght)){                                                        // First of all check if the garage is big enough to store the vehicle (case OK)
    printf("%sOK! Vehicle correctly assigned to the grage! :)%s\n", lgn, er);                               // Print vehicle correctly assigned to the grage fbk
    gar->parked_vehicle = vehic;                                                                            // Assign the vehicle to the garage
  } else {                                                                                                  // After vehicle-garage check (case NOT-OK)
    printf("%sERROR! Vehicle not assigned to the grage! :("
            "\n    Too big or too heavy for this box, retry with a different one...%s\n", rd, er);          // Print vehicle not assigned to the grage fbk
  }
}
