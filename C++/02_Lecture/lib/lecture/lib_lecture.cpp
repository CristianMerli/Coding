/*
 * Author: Cristian Merli
 * Code title: Lecture library
 * Code version: 3.0
 * Creation date: 24/03/2022
 * Last mod. date: 24/03/2022
 */


/* Dependencies */
#include "lib_lecture.h"                                                                                    // Import lecture library header file


/* Public functions */


// ES. verifico se un numero è primo, ed in caso non lo sia, stampo almeno uno dei suoi divisori


Real solve_first_deg_eqn(){                                                                                 // Funct to interactively solve 1st degree equations
  // mx+q=0 --> x=-q/m, controllo m!=0. se m=0 e q=0 --> inf, se m=0 e q!=0 -> zero
  Real m=0.0, q=0.0, res=0.0;                                                                               // Eqn params and result declaration
  get_val("Define angular coefficient", REAL, &m);                                                          // Param val def (m)
  get_val("Define y=0 value", REAL, &q);                                                                    // Param val def (q)
  if (fabs(m)>REAL_EPSILON) res=-q/m;                                                                       // -
  else if (fabs(m)<REAL_EPSILON && fabs(q)<REAL_EPSILON) res=INFINITY;                                      // -
  else res=NAN;                                                                                             // -
  return res;                                                                                               // -
}


Real solve_second_deg_eqn(){                                                                                // Funct to interactively solve 2nd degree equations
  // Real coeff[3]={0,0,0};                                                                                    // Coeff declaration
  // for (Byte i=0; i<3; ++i) get_val("Inserisci il coefficiente "+i, REAL, &coeff[i]);                        // Define coeff
  // for (Byte i=0; i<3; ++i) print_val("Inserisci il coefficiente "+i, &coeff[i]);                            // Check coeff
  return 0;
}


Complex solve_second_deg_eqn_complex(){                                                                     // Funct to interactively solve 2nd degree equations with complex solutions
  // https://www.geeksforgeeks.org/complex-numbers-c-set-1/
  return 0;
}


void multilang_gm(){                                                                                        // Funct to interactively say 'good morning' in specified language
  //
}


Integer num_guesser(){                                                                                      // Funct to interactively guess number (from 0 to 7)
  return 0;
}


/* REQUESTS:

1) Scrivere un programma che risolva un'equazione di 2 grado
nei reali

2) Scrivere un programma che risolva un'equazione di 2 grado,
dando anche le soluzioni complesse

3) Scriver un programmino che chieda una carattere descrivente una lingua 
(es: 'i'= italiano, 'e'=inglese, ecc.) e scriva "buon giorno" 
nella lingua prescelta. Usare l'istruzione switch. 

4) Scrivere un programma che "indovini" un numero tra 0 e 7
facendo una serie di domande del tipo "s/n" all'utente. 

*/
