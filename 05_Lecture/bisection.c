/*
 * Author: Cristian Merli
 * Code title: Exercise 1 (For-Break)
 * Code version: 3.0
 * Creation date: 30/03/2021
 * Last mod. date: 08/04/2021
 */


/* Libraries import */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <string.h>                                                                                         // String library inclusion (for strlen ecc.)


/* Constants declaration and definition */
const char R[] = "\033[0;31m";                                                                              // Red color
const char B[] = "\033[0;34m";                                                                              // Blue color
const char LB[] = "\033[1;34m";                                                                             // Light blue color
const char P[] = "\033[0;35m";                                                                              // Purple color
const char C[] = "\033[0;36m";                                                                              // Cyan color
const char Y[] = "\033[1;33m";                                                                              // Yellow color
const char O[] = "\033[0;33m";                                                                              // Orange color
const char G[] = "\033[0;32m";                                                                              // Green color
const char LGN[] = "\033[1;32m";                                                                            // Light green color
const char LGY[] = "\033[0;37m";                                                                            // Light gray color
const char E[] = "\033[0m";                                                                                 // End color


/* Functions declaration and definition */
void logo(unsigned char vthck, unsigned char lthck_vthik_r, unsigned char start_sp, unsigned char lsp,
          char txt[], const char txt_col[], char bkg_chr, const char bkg_col[]){                            // Print logo function
  /* Function body */
  printf("\n%s", bkg_col);                                                                                  // New line
  unsigned char len = 2*lthck_vthik_r*vthck+2*lsp+strlen(txt);                                              // Logo length calc
  for (unsigned char i = 0; i < (4*vthck+1); i++){                                                          // Logo lines print FOR cycle
    for (unsigned char j = 0; j < start_sp; j++){                                                           // Initial spaces print FOR cycle
      printf(" ");                                                                                          // Print initial spaces
    }
    if ((i < vthck || i > (3*vthck)) && (i != (4*vthck)/2)){                                                // Full bkg logo lines print cond
      for (unsigned char h = 0; h < len; h++){                                                              // Full bkg logo lines print FOR cycle
        printf("%c", bkg_chr);                                                                              // Bkg logo char print
      }
      printf("\n");                                                                                         // New line
    } else if ((i >= vthck && i <= (3*vthck)) && (i != (4*vthck)/2)) {                                      // Partial-empty bkg logo lines print cond
      for (unsigned char l = 0; l < lthck_vthik_r*vthck; l++){                                              // Partial-empty bkg logo lines, initial full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Partial-empty bkg logo lines, initial full part print
      }
      for (unsigned char m = 0; m < (len - 2*lthck_vthik_r*vthck); m++){                                    // Partial-empty bkg logo lines, central empty part print FOR cycle
        printf(" ");                                                                                        // Partial-empty bkg logo lines, central empty part print
      }
      for (unsigned char n = 0; n < lthck_vthik_r*vthck; n++){                                              // Partial-empty bkg logo lines, final full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Partial-empty bkg logo lines, final full part print
      }
      printf("\n");                                                                                         // New line
    } else if (i == ((4*vthck)/2)) {                                                                        // Text logo line initial full part print cond
      for (unsigned char o = 0; o < lthck_vthik_r*vthck; o++){                                              // Text logo line initial full part print FOR cycle
        printf("%C", bkg_chr);                                                                              // Text logo line initial full part print
      }
      for (unsigned char p = 0; p < lsp; p++){                                                              // Text logo line central empty part print FOR cycle
        printf(" ");                                                                                        // Text logo line central empty part print
      }
      printf("%s%s%s", txt_col, txt, bkg_col);                                                              // Text logo line central text part print
      for (unsigned char q = 0; q < lsp; q++){                                                              // Text logo line central empty part print FOR cycle
        printf(" ");                                                                                        // Text logo line central empty part print
      }
      for (unsigned char r = 0; r < lthck_vthik_r*vthck; r++){                                              // Text logo line final full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Text logo line final full part print
      }
      printf("\n");                                                                                         // New line
    }
  }
  printf("\033[0m\n");                                                                                      // New line and erase logo bkg color
}

double bisection(double a, double b, double k, int n, double si, double fi){                                // Bisection function
  /* Function body */
  if ((a*si+b)*(a*fi+b) < 0){                                                                               // Check interval choice consistency (case OK) --> zero in interval
    printf("\n\n%s--> %sINTERVAL OK! %sStartin' bisection algorithm to aprox. solution%s", O, LGN, B, E);   // Interval OK fbk
    int idx = 0;                                                                                            // Algorithm iterations index
    double mean = (si + fi) / 2;                                                                            // Interval central point calc
    while (((fi - mean) > k) && (idx < n)){                                                                 // Error dimension while loop (cycle 'till err is lower than k spec val or 'till iterations specified n limit val reached)
      if ((a*si+b)*(a*mean+b) < 0){                                                                         // Zero in left-half interval case
        fi = mean;
      } else if ((a*si+b)*(a*mean+b) > 0){                                                                  // Zero in right-half interval case
        si = mean;
      } else {                                                                                              // Zero exactly in the middle of the interval (mean val)
        printf("\n\n%s--> %sOK! %sExact solution (double precision) found after %s%d%s iterations!%s",
              O, LGN, B, O, idx, B, E);                                                                     // Exact solution found fbk
        return mean;                                                                                        // Return exact solution val
      }
      mean = (si + fi) / 2;                                                                                 // Interval central point upd
      idx++;                                                                                                // Algorithm iterations index upd
    }
    printf("\n\n%s--> %sOK! %sApproximate solution found after %s%d%s iterations!%s",
          O, LGN, B, O, idx, B, E);                                                                         // Approximate solution found fbk
    return mean;                                                                                            // Return approximate solution val
  } else {                                                                                                  // Check interval choice (case NOT-OK) --> zero out of interval
    printf("\n\n%s--> %sINTERVAL NOT OK! %sQuittin' bisection algorithm, change interval!%s", O, R, B, E);  // Interval NOT-OK fbk
    return 18446744073709551616.0;                                                                          // Return solution val (max val to highlight error in case of interval NOT-OK)
  }
}


/* Main cycle */
int main(){
  /* Vars declaration and definition */
  double a = -1.5, b = -2.35, k = 0.00001, si = -50.0, fi = +50.0;                                             // Double vars declaration and definition
  int n = 100;                                                                                              // Int vars declaration and definition

  /* Code */
  logo(5, 3, 7, 22, "BISECTION", Y, 'X', G);                                                                // Print logo function call (vert_thick, lat_thick_vert_thick_ratio, start_spaces, lat_spaces, text, txt_color, background_char, bkgchr_color)
  printf("\n\n%s>>>%s Approximate solution of %s(%lf*x+%lf) = 0 %s--> (a*x+b) = 0%s", G, P, O, a, b, B, E); // Approximate solution fbk
  printf("\n%s>>>%s Bisection interval %s[%lf, %lf]        %s--> [si, fi]%s", G, P, O, si, fi, B, E);       // Bisection interval solution fbk
  printf("\n%s>>>%s Max error %s%lf                                %s--> k%s", G, P, O, k, B, E);           // Max error fbk
  printf("\n%s>>>%s Max steps (iterations) %s%d                        %s--> n%s\n", G, P, O, n, B, E);     // Max steps (iterations) fbk
  printf("\n\n%s--> %sCOMPLETED! %sBisection approximate solution: %s%lf%s\n",
        O, C, B, Y, bisection(a, b, k, n, si, fi), E);                                                      // Bisection function call and approximate solution fbk

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Scrivere una funzione che prende in ingresso tre numeri reali e un intero e altri due numeri reali.
 * Interpreta i primi due come coefficente angolare (a) e intercetta dell'ordinata (b) 
 * di una retta y = a*x+b ed eseguendo il metodo di bisezione ritorna il valore y = 0.  
 * fermandosi se l'errore commesso è inferiore a k (trezo parametro) e non eseguendo più
 * di n passi di bisezione (quarto parametro).
 * L'intervallo di bisezione è indicato dagli ultimi due parametri.
 */
