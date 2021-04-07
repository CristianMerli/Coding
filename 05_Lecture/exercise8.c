/*
 * Author: Cristian Merli
 * Code title: Exercise 8 (Vectors 2)
 * Code version: 3.0
 * Creation date: 30/03/2021
 * Last mod. date: 07/04/2021
 */


/* Libraries import */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <string.h>                                                                                         // String library inclusion (for strlen ecc.)
#include <stdlib.h>                                                                                         // Standard libray inclusion (for abs ecc.)


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
const unsigned char n = 3;                                                                                  // Number of vector a rows constant val declaration and definition
const unsigned char m = 3;                                                                                  // Number of vector b rows constant val declaration and definition


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

void vect_init(double a[], double b[], const unsigned char n, const unsigned char m){                       // Vectors initialization (definition) function
  /* Function body */
  for (unsigned char i = 0; i < n; i++){                                                                    // Vector a lines definition FOR cycle
    printf("%s-->%s Define the a vector element %s[%d]%s: %s", O, C, B, i+1, C, E);                         // Vector a elements definition request
    scanf("%lf", &a[i]);                                                                                    // Vector a elements value init
  }
  printf("\n");                                                                                             // New line
  for (unsigned char i = 0; i < m; i++){                                                                    // Vector b lines definition FOR cycle
    printf("%s-->%s Define the b vector element %s[%d]%s: %s", O, C, B, i+1, C, E);                         // Vector b elements definition request
    scanf("%lf", &b[i]);                                                                                    // Vector b elements value init
  }
}

void print_vect(double a[], double b[], const unsigned char n, const unsigned char m){                      // Vectors print function
  /* Function body */
  printf("\n\n%s--> %s%dx1%s a vector: %s\n", O, B, n, C, E);                                               // Print vect a info
  for (unsigned char i = 0; i < n; i++){                                                                    // Vect a lines print FOR cycle
    printf("   %s%lf%s\n", LB, a[i], E);                                                                    // Vect a print
  }
  printf("\n%s--> %s%dx1%s b vector: %s\n", O, B, m, C, E);                                                 // Print vect b info
  for (unsigned char i = 0; i < m; i++){                                                                    // Vect b lines print FOR cycle
    printf("   %s%lf%s\n", LB, b[i], E);                                                                    // Vect b print
  }
}

int vect_add(double a[], double b[], const unsigned char n, const unsigned char m){                         // Vector add function
  /* Function body */
  if (n == m){                                                                                              // In case of vectors a and b equally-sized
    for (unsigned char i = 0; i < n; i++){                                                                  // Vectors components add, lines FOR cycle
      a[i] += b[i];                                                                                         // Save each a+b component in a vector
    }
    return 0;                                                                                               // Return 0 code (OK)
  } else {                                                                                                  // While in case of vectors a and b not equally-sized
    return abs(n-m);                                                                                        // Return X code (NOT-OK)
  }
}


/* Main cycle */
int main(){
  /* Vars declaration and definition */
  double a[n];                                                                                              // Vector a declaration
  double b[m];                                                                                              // Vector b declaration

  /* Code */
  logo(5, 3, 6, 22, "VECTOR ADD", Y, 'X', G);                                                               // Print logo function call (vert_thick, lat_thick_vert_thick_ratio, start_spaces, lat_spaces, text, txt_color, background_char, bkgchr_color)
  vect_init(a, b, n, m);                                                                                    // Vectors initialization (definition) function call
  printf("\n\n%s>>>%s Defined vectors:%s", G, P, E);                                                        // Defined vectors fbk
  print_vect(a, b, n, m);                                                                                   // Vectors print function call

  printf("\n\n%s>>>%s Vector add:%s", G, P, E);                                                             // Defined vectors fbk
  int ret_code = vect_add(a, b, n, m);                                                                      // Vectors a and b rows number difference
  if (ret_code == 0){                                                                                       // In case of equal vectors a and b rows number - 0 code (OK)
    printf("\n\n%s--> %s%dx1%s a+b vector: %s\n", O, B, n, C, E);                                           // Print vect a info
    for (unsigned char i = 0; i < n; i++){                                                                  // Vect a lines print FOR cycle
      printf("   %s%lf%s\n", LB, a[i], E);                                                                  // Vect a print
    }
  } else {                                                                                                  // While in case of vectors a and b rows number difference - X code (NOT-OK)
    printf("\n\n%s--> %s%d row(s) difference%s in a+b vector add, ERROR!%s\n", O, B, ret_code, C, E);       // Print vect add error code, rows number mismatch
  }

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Scrivere una funzione che prende due vettori e ne esegue la somma elemento
 * per elemento se i vettori sono lunghi uguale, mette il risultato
 * nel primo vettore e ritorna 0.
 * Se i due vettori sono lunghi diversamente azzera il contenuto dei due vettori.
 * Il valore del ritorno in quel caso sarà la differenza di lunghezza tra i due vettori a-b.
 */
