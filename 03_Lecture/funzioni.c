/*
 * Author: Cristian Merli
 * Code title: Funzioni e gestione flusso
 * Code version 1.0
 * Creation date: 16/03/2021
 * Last mod. date: 16/03/2021
 */

#include <stdio.h> // Standard I/O library inclusion 

/* Funzione 1 */
int somma(int a, int b){ // Definizione tipo di funzione (INT), parametri (int a ed int b)
  /* Corpo funzione */
  return a + b; // Valore di ritorno della funzione
} // Fine funzione

/* Funzione 2 */
double somma_double(double a, double b){ // Definizione tipo di funzione (DOUBLE), parametri (double a ed double b)
  /* Corpo funzione */
  return a + b; // Valore di ritorno della funzione
} // Fine funzione

/* Funzione 3 */
void print(int a){ // Definizione tipo di funzione (VOID - no return), parametri (int a)
  /* Corpo funzione */
  printf("\nCiao, valore = %i\n", a); // Stampa valore in ingresso alla funzione
} // Fine funzione

int main(){ // Main cycle
  /* Vars declaration */
  int a = 1, b = 2;
  
  /* Code */
  if (b == a) { // Inizio IF e condizioni
    printf("\nCaso a == b"); // Debug print
    printf("\nFunzione somma --> 2 + 4 = %i\n", somma(2, 4)); // Call funzione 1 somma e print risultato
  } else { // Condizione ELSE
    printf("\nCaso a != b"); // Debug print
    print(20); // Call funzione 3 void senza ritorno per stampare il valore dato in ingresso
  }
  return 0;  // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
} // End main cycle



/* Note */
/*
 * Funzioni: Vanno dichiarate prima di essere usate (sopra il main).
 */
