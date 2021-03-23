/*
 * Author: Cristian Merli
 * Code title: Esercizio 1
 * Code version 3.0
 * Creation date: 23/03/2021
 * Last mod. date: 23/03/2021
 */

/* Libraries import */
#include <stdio.h> // Standard I/O library inclusion 

/* Funzione 1 */
void stampa(int val){                                                         // Definizione tipo di funzione (VOID), parametri (int val)
  /* Corpo funzione */
  for(int i = 0; i <= val; i++){                                              // Ciclo FOR per print calore
    printf("%d\n", i);                                                        // Print valore
  }
} // Fine funzione

int main(){ // Main cycle
  /* Vars declaration */
  int a = 5, b = 10, c = 25;                                                  // Definizione a=5, b=10, c=25

  /* Code */
  printf("\n");                                                               // New line
  stampa(a);                                                                  // Stampa con a=5
  printf("\n");                                                               // New line
  stampa(b);                                                                  // Stampa con b=10
  printf("\n");                                                               // New line
  stampa(c);                                                                  // Stampa con c=25
  return 0;  // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
} // End main cycle



/* Consegna */
/*
 * Scrivere una funzione che prende in ingresso un intero e stampa a video
 * tutti i numeri in sequenza:
 * numero 5
 * 1,2,3,4,5
 * Successivamente chiamare la funzione con 10 e 25
 */

