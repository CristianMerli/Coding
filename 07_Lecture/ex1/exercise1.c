/*
 * Author: Cristian Merli
 * Code title: Exercise 1 (Pointers 1)
 * Code version: 3.0
 * Creation date: 20/04/2021
 * Last mod. date: 20/04/2021
 *  
 * Notes: Run software using the following command: "LD_LIBRARY_PATH=. ./exercise1"
 * the first part has the purpose of definin' env var for shared library path
 * --> To create shared libraries see: https://www.youtube.com/watch?v=Slfwk28vhws
 * 
 * gcc -Wall -c exercise1.c -o exercise1.o                      -->   Create software object file
 * gcc -Wall -fpic -shared libexercise1.c -o libexercise1.so    -->   Create library object file
 * gcc -Wall exercise1.o -o exercise1 -l exercise1 -L.          -->   Link software and library object files to executable
 */


/* Libraries import */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <stdlib.h>                                                                                         // Standard library inclusion (for atof ecc.)
#include "libexercise1.h"                                                                                   // Library for exercise 1 import header file


/* Global vars declaration and definition */
char in_buff[10];                                                                                           // Input buffer char array for fgets func


/* Main cycle */
int main(){
  /* Vars declaration and definition */
  double val1, val2;                                                                                        // Doble var declaration
  
  /* Code */
  logo(4, "ADD LIBRARY AND PARAMETERS BY VAL/REF", ye, '#', gn);                                            // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)

  printf("\n\n%s>>>%s Insert the first value to add %s(max %lu chars)%s: %s",
          gn, pu, bl, sizeof(in_buff)-1, pu, er);                                                           // Val1 definition request fbk
  scanf("%9[^\n]", in_buff);                                                                                // Reads the string 'till '\n' char, avoidin' scanf stop at space char and saving '\n' chr (str var definition) --> avoid buffer overflow assigning max input str size to 20-1 for '\0' char
  while ((getchar()) != '\n');                                                                              // Instruction to clear input buffer when buffer overflow occurs, avoiding to save next char as new input
  val1 = atof(in_buff);                                                                                     // String conversion to double and val save into val1 var
  
  printf("\n\n%s>>>%s Insert the second value to add %s(max %lu chars)%s: %s",
          gn, pu, bl, sizeof(in_buff)-1, pu, er);                                                           // Val2 definition request fbk
  scanf("%9[^\n]", in_buff);                                                                                // Reads the string 'till '\n' char, avoidin' scanf stop at space char and saving '\n' chr (str var definition) --> avoid buffer overflow assigning max input str size to 20-1 for '\0' char
  while ((getchar()) != '\n');                                                                              // Instruction to clear input buffer when buffer overflow occurs, avoiding to save next char as new input
  val2 = atof(in_buff);                                                                                     // String conversion to double and val save into val2 var
  
  printf("\n\n%s>>>%s First inserted value: %s%lf%s\n", gn, pu, ye, val1, er);                              // First inserted value print fbk
  printf("\n\n%s>>>%s Second inserted value: %s%lf%s\n", gn, pu, ye, val2, er);                             // Second inserted value print fbk
  printf("\n\n%s>>> %sThe add vale is: %s%lf + %lf = %s", gn, pu, ye, val1, val2, er);                      // Print add result fbk
  
  add(&val1, val2);                                                                                         // Call add function from library
  printf("%s%lf%s\n", ye, val1, er);                                                                        // Print add result fbk

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Scrivere una libreria che continene una funzione che torna void e che prende due numeri 
 * uno per indirizzo ed uno per valore e somma al primo il secondo.
 * Scrivere successivamente un main che predere questi due numeri da tastiera utilizzando
 * la funzione scanf e stampa il risultato.
 */
