/*
 * Author: Cristian Merli
 * Code title: Esercizio 1
 * Code version 3.0
 * Creation date: 16/03/2021
 * Last mod. date: 16/03/2021
 */

#include <stdio.h> // Standard I/O library inclusion 

/* Funzione */
double piccolo(double a, double b){ // Definizione tipo di funzione (DOUBLE), parametri (double a ed double b)
  /* Corpo funzione */
  double c; // Variabile valore di ritorno funzione

  if (a < b) { // Inizio IF e condizioni
    c = a; // Assegnazione valore piu piccolo
  } else { // Condizione ELSE
    c = b; // Assegnazione valore piu piccolo
  }
  return c; // Valore di ritorno della funzione
} // Fine funzione

int main(){ // Main cycle
  /* Vars declaration */
  double a = 0.5, b = 0.6, c = 0.12, d = 0.2; // Dichiarazione e inizializzazione variabili
  
  /* Code */
  printf("\n--> Valore piu piccolo tra (%f, %f, %f, %f) ==> %f\n", a, b, c, d, piccolo(piccolo(a, b), piccolo(c, d))); // Stampa valore piu piccolo con call della funzione piccolo
  return 0;  // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
} // End main cycle



/* Consegna */
/*
 * Scrivere una funzione che prende due numeri double
 * e ritorna il più piccolo
 * Successivamente chiamare la funzione con 0.5 0.6 e 0.12 0.2
 * e stampare a video il numero più piccolo
 */
