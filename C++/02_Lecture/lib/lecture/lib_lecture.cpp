/*
 * Author: Cristian Merli
 * Code title: Lecture library
 * Code version: 3.0
 * Creation date: 24/03/2022
 * Last mod. date: 27/03/2022
 */


/* Dependencies */
#include "lib_lecture.h"                                                                                    // Import lecture library header file


/* Public functions */
Integer is_prime(C_integer &num){                                                                           // Function to check whether a number is prime and if not returns one of its divisors
  for (Integer i=num-1; i>1; --i) if(num%i==0) return i;                                                    // Chk for div and return it if found
  term_print("The given number is prime");                                                                  // Else if the num is prime
  return 1;                                                                                                 // Return the only div: 1
}


Real solve_first_deg_eqn(C_real &a, C_real &b){                                                             // Funct to solve 1st degree equations (ax+b=0)
  // mx+q=0 --> x=-q/m, controllo m!=0. se m=0 e q=0 --> inf, se m=0 e q!=0 -> zero
  Real x=0.0;                                                                                               // -
  if (fabs(a)>REAL_EPSILON) x=-b/a;                                                                         // -
  else if (fabs(a)<REAL_EPSILON && fabs(b)<REAL_EPSILON) x=INFINITY;                                        // -
  else x=NAN;                                                                                               // -
  return x;                                                                                                 // -
}


Real solve_second_deg_eqn(){                                                                                // Funct to solve 2nd degree equations
  // Real coeff[3]={0,0,0};                                                                                    // Coeff declaration
  // for (Byte i=0; i<3; ++i) get_val("Inserisci il coefficiente "+i, REAL, &coeff[i]);                        // Define coeff
  // for (Byte i=0; i<3; ++i) print_val("Inserisci il coefficiente "+i, &coeff[i]);                            // Check coeff
  return 0;
}


Complex solve_second_deg_eqn_complex(){                                                                     // Funct to solve 2nd degree equations with complex solutions
  // https://www.geeksforgeeks.org/complex-numbers-c-set-1/
  return 0;
}


void multilang_gm(){                                                                                        // Funct to say 'good morning' in specified language
  //
}


Integer num_guesser(){                                                                                      // Funct to guess number (from 0 to 7)
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
