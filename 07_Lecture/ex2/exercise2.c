/*
 * Author: Cristian Merli
 * Code title: Exercise 2 (Pointers 2)
 * Code version: 3.0
 * Creation date: 20/04/2021
 * Last mod. date: 20/04/2021
 *  
 * Notes: Run software using the following command: "LD_LIBRARY_PATH=. ./exercise7"
 * the first part has the purpose of definin' env var for shared library path
 * --> To create shared libraries see: https://www.youtube.com/watch?v=Slfwk28vhws
 * 
 * gcc -Wall -c exercise2.c -o exercise2.o                      -->   Create software object file
 * gcc -Wall -fpic -shared libexercise2.c -o libexercise2.so    -->   Create library object file
 * gcc -Wall exercise2.o -o exercise2 -l exercise2 -L.          -->   Link software and library object files to executable
 */


/* Libraries import */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <string.h>                                                                                         // String library inclusion (for strlen ecc.)
#include <stdlib.h>                                                                                         // Standard library inclusion (for atof ecc.)
#include <sys/ioctl.h>                                                                                      // System I/O control library inclusion (for ioctl ecc.)
#include <unistd.h>                                                                                         // UniStd library inclusion (for stdout ecc.)
#include "libexercise2.h"                                                                                   // Library for exercise 2 import header file


/* Global vars declaration and definition */
char in_buff[20];                                                                                           // Input buffer char array for fgets func


/* Main cycle */
int main(){
  /* Vars declaration and definition */
  char chr;                                                                                                 // Char var declaration
  char *ptr;                                                                                                // Ptr var declaration

  /* Code */
  logo(4, "FIND CHAR ADDRESS", ye, '#', gn);                                                                // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  printf("\n\n%s>>>%s Insert the string %s(max %lu chars)%s: %s", gn, pu, bl, sizeof(in_buff)-1, pu, er);   // String definition request fbk
  scanf("%19[^\n]", in_buff);                                                                               // Reads the string 'till '\n' char, avoidin' scanf stop at space char and saving '\n' chr (str var definition) --> avoid buffer overflow assigning max input str size to 20-1 for '\0' char
  while ((getchar()) != '\n');                                                                              // Instruction to clear input buffer when buffer overflow occurs, avoiding to save next char as new input
  printf("\n\n%s>>>%s Insert the char: %s", gn, pu, er);                                                    // Char definition request fbk
  scanf(" %c", &chr);                                                                                       // Reads the char 'till '\n' char, to avoid reading '\n' of the previous scanf, insert a space b4 %c in scanf --> ' %c' (char var definition)
  printf("\n\n%s>>>%s The inserted string is: %s%s%s", gn, pu, ye, in_buff, er);                            // Inserted string print fbk
  printf("\n\n\n%s>>>%s The inserted char is: %s%c%s", gn, pu, ye, chr, er);                                // Inserted char print fbk
  printf("\n\n\n%s>>>%s The first defined string memory address is: %s%p%s", gn, pu, ye, in_buff, er);      // Print first defined string memory address fbk

  if (findchr_addr(in_buff, chr, &ptr) == 0){                                                               // Find char address function call and return val check (case OK = 0)
    printf("\n\n\n%s>>>%s The first defined char memory address is: %s%p%s", gn, pu, ye, ptr, er);          // Print first detected char memory address in string fbk
    printf("\n\n\n%s>>>%s The char is the number %s%lu%s inside the string.\n%s",
            gn, pu, ye, ptr-in_buff+1, pu, er);                                                             // Print the first detected char number inside the string fbk
  } else {                                                                                                  // Find char address function return val check (case NOT-OK = 1)
    printf("\n\n\n%s>>>%s Error! %sThe defined char has not been fond inside the given string.\n%s",
            gn, rd, pu, er);    // Print char not found fbk
  }

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Scrivere una libreria che continene una funzione che prende in ingresso
 * una stringa, un carattere, e un puntatore a carattere e ritorna un intero
 * La funzione deve cercare all'interno della stringa il carattere indicato ed assegnare
 * al puntatore (terzo parametro della funzione) l'indirizzo del carattere trovato.
 * La funzione torna zero se il carattere è contenuto nella stringa e 1 se il carattere
 * non è contenuto nella stringa.
 * Il main dovrà utilizzare la funzione scanf chiedendo di inserire una stringa e successivamente
 * il carattere da cercare.
 * Ed in fine stampare l'indirizzo del carattere trovato e la differenza tra l'indirizzo del vettore
 * e l'indirizzo del carattere (che corrisponde alla posizione del carattere nella stringa).
 */
