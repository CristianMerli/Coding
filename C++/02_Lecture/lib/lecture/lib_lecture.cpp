/*
 * Author: Cristian Merli
 * Code title: Lecture library
 * Code version: 3.0
 * Creation date: 24/03/2022
 * Last mod. date: 31/03/2022
 */


/* Dependencies */
#include "lib_lecture.h"                                                                                    // Import lecture library header file


/* Public functions */
Integer is_prime(C_integer &num){                                                                           // Function to check whether a number is prime and if not returns one of its divisors
  Integer div=1;											                                                                      // Div var declaration and init
  for (Integer i=num-1; i>1; --i) if(num%i==0) div=i;                                                       // Chk for div and upd var if found
  return div;                                                                                               // Return div
}


Integer solve_first_deg_eqn(C_real &a, C_real &b, Real &x){                                                 // Funct to solve 1st degree equations (ax+b=0)
  if(REAL_DF_Z(a)){                                                                                         // Case a!=0
    x=-b/a;                                                                                                 // Def sol val
    return 0;                                                                                               // Return 0 code (solution found)
  } else if (REAL_EQ_Z(a) && REAL_EQ_Z(b)){                                                                 // Case a=0 and b=0
    x=INFINITY;                                                                                             // Def sol val
    return -1;                                                                                              // Return -1 code (endless solutions)
  } else {                                                                                                  // Case a=0 and b!=0
    x=NAN;                                                                                                  // Def sol val
    return -2;                                                                                              // Return -2 code (no solutions)
  }
}


Integer solve_second_deg_eqn(C_real coeff[], Real x[]){                                                     // Funct to solve 2nd degree equations (ax^2+bx+c=0)
  if (REAL_EQ_Z(coeff[0]) && REAL_EQ_Z(coeff[1]) && REAL_EQ_Z(coeff[2])){                                   // Case a=0, b=0 and c=0
    x[0]=x[1]=INFINITY;                                                                                     // Def sol val
    return -1;                                                                                              // Return -1 code (endless solutions)
  } else if (REAL_EQ_Z(coeff[0]) && (REAL_DF_Z(coeff[1]) || REAL_DF_Z(coeff[2]))){                          // Case a=0 and (b!=0 or c!=0)
      x[0]=x[1]=NAN;                                                                                        // Def sol val
      return -3;                                                                                            // Return -3 code (undefined equation)
  } else {                                                                                                  // In case of limited num of sol
    C_real delta=pow(coeff[1], 2.0)-4*coeff[0]*coeff[2];                                                    // Eqn delta def
    if (delta>0.0){                                                                                         // Case of two solutions
      C_real den=(2*coeff[0]);                                                                              // Formula denominator
      x[0]=(-coeff[1]+sqrt(delta))/den;                                                                     // Calc 1st sol
      x[1]=(-coeff[1]-sqrt(delta))/den;                                                                     // Calc 2nd sol
      return 0;                                                                                             // Return 0 code (solutions found)
    } else if (REAL_EQ_Z(delta)){                                                                           // Case of one solutions
      x[0]=x[1]=(-coeff[1]+sqrt(delta))/(2*coeff[0]);                                                       // Calc and cpy sol
      return 0;                                                                                             // Return 0 code (solutions found)
    } else {                                                                                                // Case of no real solutions
      x[0]=x[1]=NAN;                                                                                        // Def sol val
      return -2;                                                                                            // Return -2 code (no real solutions)
    }
  }
}


Integer solve_second_deg_eqn_complex(C_real coeff[], Complex x[]){                                          // Funct to solve 2nd degree equations with complex solutions (ax^2+bx+c=0)
  if (REAL_EQ_Z(coeff[0]) && REAL_EQ_Z(coeff[1]) && REAL_EQ_Z(coeff[2])){                                   // Case a=0, b=0 and c=0
    x[0].real(INFINITY); x[0].imag(INFINITY);                                                               // Def 1st sol val
    x[1].real(INFINITY); x[1].imag(INFINITY);                                                               // Def 2nd sol val
    return -1;                                                                                              // Return -1 code (endless solutions)
  } else if (REAL_EQ_Z(coeff[0]) && (REAL_DF_Z(coeff[1]) || REAL_DF_Z(coeff[2]))){                          // Case a=0 and (b!=0 or c!=0)
      x[0].real(NAN); x[0].imag(NAN);                                                                       // Def 1st sol val
      x[1].real(NAN); x[1].imag(NAN);                                                                       // Def 2nd sol val
      return -3;                                                                                            // Return -3 code (undefined equation)
  } else {                                                                                                  // In case of limited num of sol
    C_real delta=pow(coeff[1], 2.0)-4*coeff[0]*coeff[2];                                                    // Eqn delta def
    C_real den=(2*coeff[0]);                                                                                // Formula denominator
    if (delta>0.0){                                                                                         // Case of two solutions
      x[0].real((-coeff[1]+sqrt(delta))/den); x[0].imag(0);                                                 // Calc 1st sol
      x[1].real((-coeff[1]-sqrt(delta))/den); x[1].imag(0);                                                 // Calc 2nd sol
    } else if (REAL_EQ_Z(delta)){                                                                           // Case of one solutions
      C_real sol=(-coeff[1]+sqrt(delta))/den;                                                               // Calc sol
      x[0].real(sol); x[0].imag(0);                                                                         // Cpy in 1st sol
      x[1].real(sol); x[1].imag(0);                                                                         // Cpy in 2nd sol
    } else {                                                                                                // Case of imaginary solutions
      C_real re=-coeff[1]/den;                                                                              // Sol real part
      C_real im=sqrt(-delta)/den;                                                                           // Sol imaginary part
      x[0].real(re); x[0].imag(+im);                                                                        // Calc 1st sol
      x[1].real(re); x[1].imag(-im);                                                                        // Calc 2nd sol
    }
    return 0;                                                                                               // Return 0 code (solutions found)
  }
}


Integer multilang_gm(C_character &lang){                                                                    // Funct to say 'good morning' in specified language
  switch (tolower(lang)){                                                                                   // Chk non-case sensitive language key chr
  case 'i': term_print("Buon giorno!"); break;                                                              // Italian: print gm phrase
  case 'e': term_print("Good morining!"); break;                                                            // English: print gm phrase
  case 'd': term_print("Guten tag!"); break;                                                                // German: print gm phrase
  case 'f': term_print("Bonjour!"); break;                                                                  // French: print gm phrase
  case 'p': term_print("Доброе утро!"); break;                                                              // Russian: print gm phrase
  default: term_print("Error, unknown language! Try with are: 'i', 'e', 'd', 'f' or 'p'!", ERR); return -1; // Unknown: print err fbk and return -1 code (unknown language error)
  }
  return 0;                                                                                                 // Return 0 code (ok)
}


Integer num_guesser(Integer &num){                                                                          // Funct to guess number (from 0 to 7)
  Character answ;                                                                                           // Answer chr (y/n)
  Short i=0;                                                                                                // Answ idx
  ACQ_CYCLE("Is the number negative? [y/n]", CHARACTER, answ,
            (tolower(answ)!='y' && tolower(answ)!='n'), "The answer must be [y/n]");                        // Ask if num is negative
  if (tolower(answ)=='y'){                                                                                  // If negative
    term_print("Error, the value can't be negative!", ERR);                                                 // Print err fbk
    return -2;                                                                                              // Return -2 code (number out of range: too small)
  } else {                                                                                                  // Else if num ain't negative
    ACQ_CYCLE("Is the number greater than 7? [y/n]", CHARACTER, answ,
              (tolower(answ)!='y' && tolower(answ)!='n'), "The answer must be [y/n]");                      // Ask if num is greater than 7
    if (tolower(answ)=='y'){                                                                                // If greater than 7
      term_print("Error, the value can't be greater than 7!", ERR);                                         // Print err fbk
      return -3;                                                                                            // Return -3 code (number out of range: too big)
    } else {                                                                                                // Else if num ain't greater than 7
      do {                                                                                                  // Start questions cycle to 'guess' the num
        ACQ_CYCLE("Is the number "+std::to_string(i)+"? [y/n]", CHARACTER, answ,
                  (tolower(answ)!='y' && tolower(answ)!='n'), "The answer must be [y/n]");                  // Question
        if (tolower(answ)=='y'){                                                                            // Anw chk, if affermative
          num=i;                                                                                            // Num def
          break;                                                                                            // Xit questions cycle
        }
        ++i;                                                                                                // Upd answ idx
      } while(i<=7);                                                                                        // Chk answ idx
    }
  }
  return (i>7) ? -1 : 0;                                                                                    // In case of num defined, return 0 code (ok), else return -1 code (undefined number)
}
