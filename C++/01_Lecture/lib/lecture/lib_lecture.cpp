/*
 * Author: Cristian Merli
 * Code title: Lecture library
 * Code version: 3.0
 * Creation date: 03/02/2022
 * Last mod. date: 09/02/2022
 */


/* Dependencies */
#include "lib_lecture.h"                                                                                    // Import lecture library header file


/* Public functions */
Real conv_c_k(){                                                                                            // Funct to interactively convert temperature from [°C] to [K]
  Real temp_c=0.0;                                                                                          // Temp [°C] val declaration
  C_real conv_const=273.15;                                                                                 // [°C] to [K] conv const
  get_val("Insert temperature [°C]", REAL, &temp_c);                                                        // Temp [°C] def
  if (temp_c<-conv_const){                                                                                  // Chk temp val
    term_print("Errore, valore della temperatura in [K] sotto lo zero assoluto!",ERR);                      // Err fbk
    return -1;                                                                                              // Return err val
  }
  return temp_c+conv_const;                                                                                 // Return converted temp [K]
}


// Add enum
Real conv_c_f_f_c(){                                                                                        // Funct to interactively convert from [°C] to [F] or from [F] to [°C]
  Integer conv_mode=0;                                                                                      // Conv mode declaration
  Real in_temp=0.0, out_temp=0.0;                                                                           // In-temp and out-temp vals declaration
  while (conv_mode==0 || conv_mode==1){                                                                     // Options acq cycle
    get_val("Insert conversion mode ( 0=[°C]->[F] / 1=[F]->[°C] )", INTEGER, &conv_mode);                   // Conv mode def
    switch (conv_mode){                                                                                     // Options switch-case
    case 0:                                                                                                 // [°C]->[F] temp conv
      get_val("Inserisci la temperatura in [°C]", REAL, &in_temp);                                          // In-temp val def
      out_temp=in_temp*(9.0/5.0)+32.0;                                                                      // Out-temp val def
      print_val("The converted temperature is", out_temp, "F");                                             // Print temp in [F]
      break;                                                                                                // End-case
    case 1:                                                                                                 // [F]->[°C] temp conv
      get_val("Inserisci la temperatura in [F]", REAL, &in_temp);                                           // In-temp val def
      out_temp=(in_temp-32.0)*(5.0/9.0);                                                                    // Out-temp val def
      print_val("The converted temperature is", out_temp, "°C");                                            // Print temp in [°C]
      break;                                                                                                // End-case
    default:                                                                                                // Unknown opt selected
      term_print("Error, unknown conversion option selected, please retry", ERR);                           // Print err fbk
    }
  }
  return -1;                                                                                                // Return err val
}


void chk_if_div(){                                                                                          // Funct to interactively check if a number can be divided
  Integer num=0, den=0;                                                                                     // Numerator and denominator vals declaration
  get_val("Insert numerator", INTEGER, &num);                                                               // Numerator val def
  while (den==0){                                                                                           // Check denominator different from zero
    get_val("Insert denominator", INTEGER, &den);                                                           // Denominator val def
    if (den==0) term_print("The denominator can't be zero", ERR);                                           // Check denominator val different from zero
  }
  if (num%den==0) print_val("It can be divided, and the division result is", num/den);                      // Dividable
  else term_print("Can't be divided", ERR);                                                                 // Not-dividable
}


Real solve_first_deg_eqn(){                                                                                 // Funct to interactively solve 1st degree equations
  // mx+q=0 --> x=-q/m, controllo m!=0. se m=0 e q=0 --> inf, se m=0 e q!=0 -> zero
  Real m=0.0, q=0.0, res=0.0;                                                                               // Eqn params and result declaration
  get_val("Define angular coefficient", REAL, &m);                                                          // Param val def (m)
  get_val("Define y=0 value", REAL, &q);                                                                    // Param val def (q)
  if (fabs(m)>__DBL_EPSILON__) res=-q/m;                                                                    // -
  else if (fabs(m)<__DBL_EPSILON__ && fabs(q)<__DBL_EPSILON__) res=INFINITY;                                // -
  else res=NAN;                                                                                             // -
  return res;                                                                                               // -
}


Real solve_second_deg_eqn(){                                                                                // Funct to interactively solve 2nd degree equations
  // Real coeff[3]={0,0,0};                                                                                    // Coeff declaration
  // for (Byte i=0; i<3; ++i) get_val("Inserisci il coefficiente "+i, REAL, &coeff[i]);                        // Define coeff
  // for (Byte i=0; i<3; ++i) print_val("Inserisci il coefficiente "+i, &coeff[i]);                            // Check coeff
  return 0;
}


std::complex<Real> solve_second_deg_eqn_complex(){                                                          // Funct to interactively solve 2nd degree equations with complex solutions
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
