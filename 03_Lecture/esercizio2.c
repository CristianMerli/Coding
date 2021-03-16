/*
 * Author: Cristian Merli
 * Code title: Esercizio 2
 * Code version 1.0
 * Creation date: 16/03/2021
 * Last mod. date: 16/03/2021
 */

#include <stdio.h> // Standard I/O library inclusion 

/* Funzione somma */
int somma(int a, int b){ // Definizione tipo di funzione (INT), parametri (int a ed int b)
  /* Corpo funzione */
  return a + b; // Valore di ritorno della funzione
} // Fine funzione

/* Funzione sottrazione */
int sottrazione(int a, int b){ // Definizione tipo di funzione (INT), parametri (int a ed int b)
  /* Corpo funzione */
  return a - b; // Valore di ritorno della funzione
} // Fine funzione

/* Funzione divisione */
double divisione(int a, int b){ // Definizione tipo di funzione (DOUBLE), parametri (int a ed int b)
  /* Corpo funzione */
  return a / b; // Valore di ritorno della funzione
} // Fine funzione

int main(){ // Main cycle
  /* Vars declaration */
  int a = 10, b = 5; // Dichiarazione e inizializzazione variabili
  
  /* Code */
  printf("\n--> Somma: (%d + %d) = %d\n", a, b, somma(a, b));             // Stampa somma numeri
  printf("\n--> Sottrazione: (%d - %d) = %d\n", a, b, sottrazione(a, b)); // Stampa sottrazione numeri
  printf("\n--> Divisione: (%d / %d) = %f\n", a, b, divisione(a, b));     // Stampa divisione numeri
  return 0;  // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
} // End main cycle



/* Consegna */
/*
 * Scrivere un programma inizializza due variabili
 * intere a 10 e 5 ne esegue
 * la somma e la stampa a video
 * la sottrazione e la stampa a video
 * la divisione e la stampa a video
 */
