/*
 * Author: Cristian Merli
 * Code title: Lecture library
 * Code version: 3.0
 * Creation date: 03/03/2022
 * Last mod. date: 24/03/2022
 */


/* Dependencies */
#include "lib_lecture.h"                                                                                    // Import lecture library header file


/* Public functions */
Real conv_c_k(){                                                                                            // Funct to interactively convert temperature from [°C] to [K]
  Real temp_c=0.0;                                                                                          // Temp [°C] val declaration
  C_real conv_const=273.15;                                                                                 // [°C] to [K] conv const
  get_val("Insert temperature value [°C]", REAL, &temp_c);                                                  // Temp [°C] def
  if (temp_c<-conv_const){                                                                                  // Chk temp val
    term_print("Error, temperature value in [K] cannot be lower than absolute zero!", ERR);                 // Err fbk
    return -1;                                                                                              // Return err val
  }
  return temp_c+conv_const;                                                                                 // Return converted temp [K]
}


Integer conv_c_f_f_c(){                                                                                     // Funct to interactively convert from [°C] to [F] or from [F] to [°C]
  Character conv_mode;                                                                                      // Conv mode declaration
  Real in_temp=0.0, out_temp=0.0;                                                                           // In-temp and out-temp vals declaration
  do {                                                                                                      // Acq cycle
    get_val("Insert conversion mode ( c=[°C]->[F] / f=[F]->[°C] )", CHARACTER, &conv_mode);                 // Conv mode def
    switch (conv_mode){                                                                                     // Options switch-case
    case 'c':                                                                                               // [°C]->[F] temp conv
      get_val("Insert temperature value in [°C]", REAL, &in_temp);                                          // In-temp val def
      out_temp=in_temp*(9.0/5.0)+32.0;                                                                      // Out-temp val def
      PRINT_VAL("The converted temperature is", out_temp, "F");                                             // Print temp in [F]
      break;                                                                                                // End-case
    case 'f':                                                                                               // [F]->[°C] temp conv
      get_val("Insert temperature value in [F]", REAL, &in_temp);                                           // In-temp val def
      out_temp=(in_temp-32.0)*(5.0/9.0);                                                                    // Out-temp val def
      PRINT_VAL("The converted temperature is", out_temp, "°C");                                            // Print temp in [°C]
      break;                                                                                                // End-case
    default:                                                                                                // Unknown opt selected
      term_print("Error, unknown conversion option selected!", ERR);                                        // Print err fbk
    }
  } while (conv_mode=='c' || conv_mode=='f');                                                               // Acq cycle xit cond
  return -1;                                                                                                // Return err val
}


void chk_if_div(){                                                                                          // Funct to interactively check if a number can be divided
  Integer num=0, den=0;                                                                                     // Numerator and denominator vals declaration
  get_val("Insert numerator", INTEGER, &num);                                                               // Numerator val def
  ACQ_CYCLE("Insert denominator", INTEGER, den, den==0, "The denominator can't be zero");                   // Denominator val def
  if (num%den==0) PRINT_VAL("It can be divided, and the division result is", num/den);                      // Dividable fbk
  else term_print("Can't be divided!", ERR);                                                                // Not-dividable fbk
}


void consecutive_num(){                                                                                     // Funct to interactively plot consecutive numbers
  Integer n=0, m=0;                                                                                         // Limiting vals declaration  
  ACQ_CYCLE("Insert positive starting value", INTEGER, n, n<0, "Inserted value must be positive, retry");   // Starting val def
  ACQ_CYCLE("Insert positive ending value", INTEGER, m, m<0, "Inserted value must be positive, retry");     // Ending val def
  if (n<=m) while (n<=m) PRINT_VAL("Numero", n++);                                                          // Print and increment
  else while (n>=m) PRINT_VAL("Numero", n--);                                                               // Print and decrement
}


void fibonacci(){                                                                                           // Funct to interactively print Fibonacci numbers
  Integer n=0, fn2=0, fn1=1, fn=0;                                                                          // N, Fn-2, Fn-1 and Fn vals declaration
  ACQ_CYCLE("Define N value", INTEGER, n, n<0, "N value must be greater than zero, please retry");          // N val def
  switch (n){                                                                                               // N vals cases
  case 0: PRINT_VAL("Fn", n); break;                                                                        // N=0 case management
  case 1: PRINT_VAL("Fn", n); break;                                                                        // N=1 case management
  default:                                                                                                  // Std cases management (from N=1 on)
    for (Integer i=2; i<=n; ++i){                                                                           // Iteration cycle from 2 to N
      if (fn1>INTEGER_MAX-fn2) close_err("Error, overflow detected in Fibonacci sequence evaluation!");     // Overflow detection
      fn=fn1+fn2; fn2=fn1; fn1=fn;                                                                          // Fn, Fn-1 and Fn-2 vals upd
    }
    PRINT_VAL("Fn", fn);                                                                                    // Print Fn value if overflow ain't been detected
  }
}
