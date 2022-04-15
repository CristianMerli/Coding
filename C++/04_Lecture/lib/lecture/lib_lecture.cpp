/*
 * Author: Cristian Merli
 * Code title: Lecture library
 * Code version: 3.0
 * Creation date: 07/04/2022
 * Last mod. date: 15/04/2022
 */


/* Dependencies */
#include "lib_lecture.h"                                                                                    // Import lecture library header file


/* Public functions */
void def_mat(Real m[MAX_SZ][MAX_SZ], Integer sz[], C_string &mat_nm){                                       // Funct to define matrix (array)
  ACQ_CYCLE("Insert "+mat_nm+" rows number", INTEGER, sz[0], (sz[0]<1 || sz[0]>MAX_SZ),
            "Error, the matrix rows number must be between 1 and 10!");                                     // Mat rows def
  ACQ_CYCLE("Insert "+mat_nm+" columns number", INTEGER, sz[1], (sz[1]<1 || sz[1]>MAX_SZ),
            "Error, the matrix columns number must be between 1 and 10!");                                  // Mat rows def
  for (Integer i=0; i<sz[0]; ++i)                                                                           // Mat rows def
    for (Integer j=0; j<sz[1]; ++j)                                                                         // Mat columns def
      get_val("Insert "+mat_nm+"["+std::S(i+1)+"]["+std::S(j+1)+"]", REAL, &m[i][j]);                       // Mat elements def
  term_print("Acquisition completed, recap...");                                                            // Print acq completed fbk
  print_mat(m, sz, mat_nm, 16, 4);                                                                          // Print mat
}


void print_mat(C_real m[MAX_SZ][MAX_SZ], C_integer sz[], C_string &mat_nm, C_integer &lt, C_integer t){     // Funct to print matrix (array)
  std::cout << GN << ">>> " << PU << mat_nm+"["<< sz[0] << "][" << sz[1] << "]: " << std::endl << ER;       // Print mat name and size
  for (Integer i=0; i<sz[0]; ++i){                                                                          // Mat rows printin'
    std::cout << LBU << std::setw(lt) << "|" << ER;                                                         // Print left vert-line
    for (Integer j=0; j<sz[1]; ++j)                                                                         // Mat columns printin'
      std::cout << LBU << std::setw(t) << m[i][j] << ER;                                                    // Mat elements printin'
    std::cout << LBU << std::setw(t) << "|" << std::endl << ER;                                             // Print right vert-line
  }
}


Integer mat_trasp(Real m[MAX_SZ][MAX_SZ], Integer sz[], C_string &mat_nm){                                  // Funct to apply matrix (array) transposition operation
  PRINT_VAL("Executing matrix transposition operation", "T("+mat_nm+")");                                   // Oper fbk
  for (Integer i=0; i<MIN(sz[0],sz[1]); ++i)                                                                // Max size idx scrollin'
    for (Integer j=i+1; j<MAX(sz[0],sz[1]); ++j){                                                           // Min size idx scrollin'
      SWAP(m[i][j], m[j][i], Real);                                                                         // Elem swappin'
    }
  SWAP(sz[0], sz[1], Integer);                                                                              // Sizes swappin'
  print_mat(m, sz, mat_nm, 16, 4);                                                                          // Print transp mat
  return EXIT_SUCCESS;                                                                                      // Return OK code
}


Integer mat_multipl(C_real m1[MAX_SZ][MAX_SZ], C_integer sz1[], C_string &mat1_nm,
                    C_real m2[MAX_SZ][MAX_SZ], C_integer sz2[], C_string &mat2_nm,
                    Real m3[MAX_SZ][MAX_SZ], Integer sz3[], C_string &mat3_nm){                             // Funct to apply matrix (array) multiplication oper
  if (sz1[1]==sz2[0]){                                                                                      // Chk if mat are compatible: col-mat1=row-mat2
    Real elem=0;                                                                                            // Declare res-mat elem var
    sz3[0]=sz1[0]; sz3[1]=sz2[1];                                                                           // Def res-mat size
    PRINT_VAL("Executing matrix multiplication operation, calculating", mat3_nm+"="+mat1_nm+"*"+mat2_nm);   // Oper fbk
    for (Integer i=0; i<sz1[0]; ++i)                                                                        // Scroll mat1 rows
      for (Integer j=0; j<sz2[1]; ++j){                                                                     // Scroll mat2 col
        elem=0;                                                                                             // Set res-mat elem var to zero
        for (Integer k=0; k<sz1[1]; ++k)                                                                    // Incremental add cycle
          elem+=m1[i][k]*m2[k][j];                                                                          // Update res-mat elem var usin' increm add
        m3[i][j]=elem;                                                                                      // Def i-j elem in res-mat
      }
    print_mat(m3, sz3, mat3_nm, 16, 4);                                                                     // Print res mat
    return EXIT_SUCCESS;                                                                                    // Return OK code
  } else {                                                                                                  // Else in case of incompatible mat
    term_print("Incompatible matrix!", ERR);                                                                // Print err fbk
    return EXIT_FAILURE;                                                                                    // Return ERR code
  }
}
