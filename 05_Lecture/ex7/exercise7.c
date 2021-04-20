/*
 * Author: Cristian Merli
 * Code title: Exercise 7 (Vectors 1)
 * Code version: 3.0
 * Creation date: 19/04/2021
 * Last mod. date: 19/04/2021
 * 
 * Notes: Run software using the following command: "LD_LIBRARY_PATH=. ./exercise7"
 * the first part has the purpose of definin' env var for shared library path
 * --> To create shared libraries see: https://www.youtube.com/watch?v=Slfwk28vhws
 * 
 * gcc -Wall -c exercise7.c -o exercise7.o                      -->   Create software object file
 * gcc -Wall -fpic -shared libexercise7.c -o libexercise7.so    -->   Create library object file
 * gcc -Wall exercise7.o -o exercise7 -l exercise7 -L.          -->   Link software and library object files to executable
 */


/* Libraries import */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <stdlib.h>                                                                                         // Standard library inclusion (for atof ecc.)
#include "libexercise7.h"                                                                                   // Library for exercise 7 import header file


/* Global vars declaration and definition */
char in_buff[512];                                                                                          // Input buffer char array for fgets func


/* Main cycle */
int main(){
  /* Vars declaration and definition */
  byte n;                                                                                                   // Vector size declaration
  byte n_minval = 1;                                                                                        // Input val n, min val range limit (min u_char value - alias byte)
  byte n_maxval = 255;                                                                                      // Input val n, max val range limit (max u_char value - alias byte)
  shrt tmp_chk = 0;                                                                                         // Tmp var to check n input val from terminal in allowed range

  /* Code */
  logo(4, "VECTORS SUM AND VOWELS COUNTER", ye, '#', gn);                                                   // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  str_init(in_buff, sizeof(in_buff));                                                                       // String initialization (definition) function call for in_buff
  do {                                                                                                      // Expect input val in range while-loop
    printf("\n\n%s>>>%s Specify the number of vector components (val between %hu and %hu): %s",
           gn, pu, n_minval, n_maxval, er);                                                                 // Number of vector elements definition request fbk
    fgets(in_buff, sizeof(in_buff), stdin);                                                                 // Save input val from terminal into buffer char array --> fgets to avoid char-loop problem associated with scanf when detects char expecting numeric val
    tmp_chk = atof(in_buff);                                                                                // Convert to double and copy buffer char array val into tmp var
    if (tmp_chk >= n_minval && tmp_chk <= n_maxval){                                                        // Tmp var check (case in range)
      n = tmp_chk;                                                                                          // Number of vector elements val definition
    } else {                                                                                                // Tmp var check (case out of range)
      printf("%sInput val error! The value must be between %hu and %hu. %sRetry!%s",
             rd, n_minval, n_maxval, cy, er);                                                               // Print error fbk
    }
  } while ((tmp_chk < n_minval || tmp_chk > n_maxval));                                                     // Expect input val in range while-loop exit cond

  real vect[iaddr(V, n, n)];                                                                                // Vector declaration (in execution)

  vect_init(in_buff, sizeof(in_buff), vect, n);                                                             // Vector initialization (definition) function call
  printf("\n%s>>>%s Defined vector:%s", gn, pu, er);                                                        // Defined vector fbk
  vect_print(vect, n);                                                                                      // Vector print function call
  printf("\n\n%s>>>%s Vector components sum: %s%lf%s\n", gn, pu, ye, vect_comp_sum(vect, n), er);           // Vector components sum function call and value print
  printf("\n\n%s>>>%s Specify a string to count vowels: %s", gn, pu, er);                                   // String to count vowels definition request fbk
  fgets(in_buff, sizeof(in_buff), stdin);                                                                   // Reads the input string and save in input buffer char array
  count_vowels(in_buff, sizeof(in_buff));                                                                   // Count vowels in string function call
  printf("\n\n%s>>>%s Vowles count: %s%s%s\n", gn, pu, ye, in_buff, er);                                    // Vowels count in input str print fbk
  printf("\n\n%s>>>%s Done! %s;)%s\n", gn, pu, cy, er);                                                     // Done print fbk

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Scrivere una libreria che continene due funzioni 
 * La prima funzione:
 * dato una vettore di interi o double ritorna la somma di tutti i suoi elementi
 * nel caso sia positiva; se la somma è negativa torna sempre -1.
 * La seconda funzione:
 * prende una stringa e conta le ricorrenze di tutte le vocali
 * e ne stampa in numero scrivendo:
 * "Nella stringa "#STRINGA#" ci sono #N A, #N E, #N I, #N O, #N U
 * esempio:
 * Se passo la stringa "Io mi chiamo Gastone" il risultato è
 * "Nella stringa "Io mi chiamo Gastone" ci sono 2 A, 1 E, 3 I, 3 O
 * Se non vi sono vocali di quel tipo semplicemente non stampa quella vocale
 * come nell'esempio.
 * Compilare successivamente la libreria separatamente e utilizzarla all'interno
 * del programma main.
 */
