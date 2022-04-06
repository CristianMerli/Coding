/*
 * Author: Cristian Merli
 * Code title: Lecture library
 * Code version: 3.0
 * Creation date: 31/03/2022
 * Last mod. date: 06/04/2022
 */


/* Dependencies */
#include "lib_lecture.h"                                                                                    // Import lecture library header file


/* Public functions */
void def_vect(Real v[], Integer &sz, C_string &vect_nm){                                                    // Funct to define vector
  ACQ_CYCLE("Insert "+vect_nm+" size", INTEGER, sz, (sz<1 || sz>MAX_SZ),
            "Error, the array size must be between 1 and 10!");                                             // Array size def
  for (Integer i=0; i<sz; ++i) get_val("Insert "+vect_nm+" element "+std::to_string(i), REAL, &v[i]);       // Array elements def
  term_print("Acquisition completed, recap...");                                                            // Print acq completed fbk
  print_vect(v, sz, vect_nm);                                                                               // Print vect
}


void print_vect(C_real v[], C_integer &sz, C_string &vect_nm){                                              // Funct to print vector
  String vect_str="[";                                                                                      // Vect-str init
  for (Integer i=0; i<sz-1; ++i) vect_str+=(std::to_string(v[i])+", ");                                     // Vect-str upd with elements
  vect_str+=(std::to_string(v[sz-1])+"]");                                                                  // Vect-str completed with last elem
  PRINT_VAL(vect_nm, vect_str);                                                                             // Print vect-str
}


Integer vect_scalar(C_real v1[], C_integer &sz1, C_real v2[], C_integer &sz2, Real &res){                   // Funct to apply vector scalar operation
  res=0;                                                                                                    // Vect scalar oper res val rst
  C_integer min_sz=(sz1<sz2) ? sz1 : sz2;                                                                   // Def min vect size
  for (Integer i=0; i<min_sz; ++i) res+=(v1[i]*v2[i]);                                                      // Apply vect scalar oper 'till min vect size
  return EXIT_SUCCESS;                                                                                      // Return OK code
}


Integer add_vect_elem(C_real &elem, C_integer &idx, Real v[], Integer &sz, C_string &vect_nm){              // Funct to add element in vector at spec pos
  if (sz < MAX_SZ){                                                                                         // In case of space for a new elem inside vect
    for(Integer i=sz-1; i>=idx; --i) v[i+1]=v[i];                                                           // Move old elements
    (idx<=sz) ? ++sz : sz+=(idx-sz+1);                                                                      // Vect size upd
    v[idx]=elem;                                                                                            // Add elem in vect spec pos
    print_vect(v, sz, vect_nm);                                                                             // Print vect
    return EXIT_SUCCESS;                                                                                    // Return OK code
  } else return EXIT_FAILURE;                                                                               // In case of no more space for a new elem inside vect, return ERR code
}


void def_mat(Real m[MAX_SZ][MAX_SZ], Integer sz[], C_string &mat_nm){                                       // Funct to define matrix (array)
  ACQ_CYCLE("Insert "+mat_nm+" rows number", INTEGER, sz[0], (sz[0]<1 || sz[0]>MAX_SZ),
            "Error, the matrix rows number must be between 1 and 10!");                                     // Mat rows def
  ACQ_CYCLE("Insert "+mat_nm+" columns number", INTEGER, sz[1], (sz[1]<1 || sz[1]>MAX_SZ),
            "Error, the matrix columns number must be between 1 and 10!");                                  // Mat rows def
  for (Integer i=0; i<sz[0]; ++i)                                                                           // Mat rows def
    for (Integer j=0; j<sz[1]; ++j)                                                                         // Mat columns def
      get_val("Insert "+mat_nm+"["+std::to_string(i+1)+"]["+std::to_string(j+1)+"]", REAL, &m[i][j]);       // Mat elements def
  term_print("Acquisition completed, recap...");                                                            // Print acq completed fbk
  print_mat(m, sz, mat_nm, 16, 4);                                                                          // Print mat
}


void print_mat(C_real m[MAX_SZ][MAX_SZ], C_integer sz[], C_string &mat_nm, C_integer &lt, C_integer t){     // Funct to print matrix (array)
  std::cout << GN << ">>> " << PU << mat_nm+"["<< sz[0] << "][" << sz[1] << "]: " << std::endl << ER;       // Print mat name and size
  for (Integer i=0; i<sz[0]; ++i){                                                                          // Mat rows printin'
    std::cout << OG << std::setw(lt) << "|" << ER;                                                          // Print left vert-line
    for (Integer j=0; j<sz[1]; ++j)                                                                         // Mat columns printin'
      std::cout << LBU << std::setw(t) << m[i][j] << ER;                                                    // Mat elements printin'
    std::cout << OG << std::setw(t) << "|" << std::endl << ER;                                              // Print right vert-line
  }
}


Integer mat_trasp(C_real m[MAX_SZ][MAX_SZ], C_integer sz[], Real m_t[MAX_SZ][MAX_SZ]){                      // Funct to apply matrix (array) transposition operation
  /*
    Per casa es su matrici:
    In c a[][]=a[0][0] e si muove in row-measure in C/C++, in realtà è un array 1D
    Matrici anche non quadre
    Chiedo matrice def dall'utente con elem e stampo matrice e matrice trasposta (a[i][j]=a[j][i])
  */
}
