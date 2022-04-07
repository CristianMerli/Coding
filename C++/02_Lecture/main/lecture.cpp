/*
 * Author: Cristian Merli
 * Code title: Lecture
 * Code version: 3.0
 * Creation date: 24/03/2022
 * Last mod. date: 31/03/2022
 */


/* Dependencies */
#include "../lib/lecture/lib_lecture.h"                                                                     // Import lecture library header file


/* Namespaces */
using namespace std;                                                                                        // Include std namespace


/* Main cycle */
int main(const int argc, char *const argv[]){
  title(10, "Lecture-02", YE, '#', GN);                                                                     // Print responsive-title
  /* Code-start */


  if (false && argv!=0) unused=argc;                                                                        // Avoid unused parameters error

  Integer n=0, div=0;                                                                                       // Number and divisor declaration
  ACQ_CYCLE("Insert a value to check if it's prime", INTEGER, n, n<1, "Error, value must be positive!");    // Number def
  div=is_prime(n);                                                                                          // Chk if num is prime
  if (div!=1) PRINT_VAL("The given number ain't prime and one of its divisors is", div);           	        // If not prime, print div
  else PRINT_VAL("The given number is prime and the only divisor is", div);  			                          // If prime, print div (=1)

  // Real a=0.0, b=0.0, x=0.0;                                                                                 // Eqn vars declaration
  // get_val("Insert 'a' parameter in ax+b=0 equation", REAL, &a);                                             // Eqn 'a' param def
  // get_val("Insert 'b' parameter in ax+b=0 equation", REAL, &b);                                             // Eqn 'b' param def
  // switch (solve_first_deg_eqn(a, b, x)){                                                                    // Solve 1st degree equations (ax+b=0)
  // case -1: PRINT_VAL("The equation has endless solutions, (x) is", x); break;                               // Case -1 code: endless solutions - print equation solution with fbk
  // case -2: PRINT_VAL("The equation has no solution, (x) is", x); break;                                     // Case -2 code: no solution - print equation solution with fbk
  // default: PRINT_VAL("The equation solution (x) is", x);                                                    // Case 0 code: solution found - print equation solution
  // }

  // Real coeff[]={0.0, 0.0, 0.0}, x[]={0.0, 0.0};                                                             // Eqn vect declaration
  // C_string coeff_names[]={"a","b","c"};                                                                     // Eqn coeff names vect declaration
  // for (Short i=0; i<3; ++i)                                                                                 // Eqn param def cycle
  //   get_val("Insert '"+coeff_names[i]+"' parameter in ax^2+bx+c=0 equation", REAL, &coeff[i]);              // Eqn param def
  // switch (solve_second_deg_eqn(coeff, x)){                                                                  // Solve 2nd degree equations (ax^2+bx+c=0)
  // case -1: PRINT_VAL("The equation has endless solutions, (x1-2) is", x[0]); break;                         // Case -1 code: endless solutions - print equation solution with fbk
  // case -2: PRINT_VAL("The equation has no real solutions, (x1-2) is", x[0]); break;                         // Case -2 code: no real solutions - print equation solution with fbk
  // case -3: PRINT_VAL("The equation is undefined, (x1-2) is", x[0]); break;                                  // Case -3 code: undefined equation - print equation solution with fbk
  // default:                                                                                                  // Case 0 code: solutions found
  //   PRINT_VAL("The first equation solution (x1) is", x[0]);                                                 // Print the first equation solution
  //   PRINT_VAL("The second equation solution (x2) is", x[1]);                                                // Print the second equation solution
  // }

  // Real coeff[]={0.0, 0.0, 0.0};                                                                             // Eqn coeff vect declaration
  // Complex x[]={{0.0, 0.0},{0.0, 0.0}};                                                                      // Eqn sol vect declaration
  // C_string coeff_names[]={"a","b","c"};                                                                     // Eqn coeff names vect declaration
  // for (Short i=0; i<3; ++i)                                                                                 // Eqn param def cycle
  //   get_val("Insert '"+coeff_names[i]+"' parameter in ax^2+bx+c=0 equation", REAL, &coeff[i]);              // Eqn param def
  // switch (solve_second_deg_eqn_complex(coeff, x)){                                                          // Solve 2nd degree equations with complex solutions (ax^2+bx+c=0)
  // case -1: PRINT_VAL("The equation has endless solutions, (x1-2) is", x[0]); break;                         // Case -1 code: endless solutions - print equation solution with fbk
  // case -3: PRINT_VAL("The equation is undefined, (x1-2) is", x[0]); break;                                  // Case -3 code: undefined equation - print equation solution with fbk
  // default:                                                                                                  // Case 0 code: solutions found
  //   PRINT_VAL("The first equation solution (x1) is", x[0]);                                                 // Print the first equation solution
  //   PRINT_VAL("The second equation solution (x2) is", x[1]);                                                // Print the second equation solution
  // }

  // Character lang;                                                                                           // Language chr declaration
  // get_val("Insert your language first letter", CHARACTER, &lang);                                           // Language chr def
  // C_integer res=multilang_gm(lang);                                                                         // Say 'good morning' in specified language
  // if (res==0) term_print("Language correctly recognized"); else term_print("Language not recognized");      // Fbk post-call dependin' on funct res val

  // Integer num=0;                                                                                            // Number var declaration
  // C_integer res=num_guesser(num);                                                                           // Guess number (from 0 to 7)
  // if (res==0) PRINT_VAL("The number is", num);                                                              // Print guessed number
  // else term_print("Something went wrong! Sorry...", ERR);                                                   // Print err


  /* Code-end */
  close_bye();                                                                                              // Close SW with bye fbk
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
