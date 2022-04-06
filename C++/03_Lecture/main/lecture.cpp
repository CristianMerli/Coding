/*
 * Author: Cristian Merli
 * Code title: Lecture
 * Code version: 3.0
 * Creation date: 31/03/2022
 * Last mod. date: 06/04/2022
 */


/* Dependencies */
#include "../lib/lecture/lib_lecture.h"                                                                     // Import lecture library header file


/* Namespaces */
using namespace std;                                                                                        // Include std namespace


/* Main cycle */
int main(int argc, char *const argv[]){
  title(10, "Lecture-03", YE, '#', GN);                                                                     // Print responsive-title
  /* Code-start */


  if(false && argv!=0) unused=argc;                                                                         // Avoid unused parameters error

  // C_integer sz_max=10;                                                                                      // Define vect max size
  // Integer sz1=0, sz2=0;                                                                                     // Declare vect sizes
  // Real vect1[sz_max], vect2[sz_max], scalar=0;                                                              // Declare vect with max size and def scalar oper res var
  // def_vect(vect1, sz1, sz_max, "Vect1");                                                                    // Def vect1
  // def_vect(vect2, sz2, sz_max, "Vect2");                                                                    // Def vect2
  // C_integer oper_res=vect_scalar(vect1, sz1, vect2, sz2, scalar);                                           // Apply vect scalar oper
  // if (oper_res==EXIT_SUCCESS) PRINT_VAL("The scalar product is", scalar);                                   // Chk oper res, if OK print obtained value
  // else term_print("Error occurred in vect_scalar calculation!", ERR);                                       // In case of ERR, print fbk

  // C_integer sz_max=10;                                                                                      // Define vect max size
  // Integer sz=0, elem_idx=0;                                                                                 // Declare vect size and new elem idx var
  // Real vect[sz_max], elem=0.0;                                                                              // Declare vect with max size and new elem val var
  // def_vect(vect, sz, sz_max, "Vect");                                                                       // Def vect
  // ACQ_CYCLE("Insert new vector element index (zero-idx)", INTEGER, elem_idx,
  //           (elem_idx<0 || elem_idx>sz_max-1),
  //           "Error, new vector element index must be between 0 and 9!");                                    // Def new elem idx in vect
  // get_val("Insert new vector element value", REAL, &elem);                                                  // Def new elem val
  // C_integer oper_res=add_vect_elem(elem, elem_idx, vect, sz, sz_max, "Vect");                               // Add new elem in vect
  // if (oper_res==EXIT_SUCCESS) term_print("New element correctly added inside vector!");                     // Chk oper res, if OK print fbk
  // else term_print("Error occurred while adding new element inside vector, no space!", ERR);                 // In case of ERR, print fbk

  // ---

  /*
    Per casa es su matrici:
    In c a[][]=a[0][0] e si muove in row-measure in C/C++, in realtà è un array 1D
    Matrici anche non quadre
    Chiedo matrice def dall'utente con elem e stampo matrice e matrice trasposta (a[i][j]=a[j][i])
  */


  /* Code-end */
  close_bye();                                                                                              // Close SW with bye fbk
}
