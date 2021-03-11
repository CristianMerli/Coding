/*
  Author: Cristian Merli
  Code title: Hello world e compilazione
  Code version 3.0
  Creation date: 02/03/2021
  Last mod. date: 11/03/2021
*/

#include <stdio.h> // Standard I/O library inclusion 

int main(){ // Main cycle
  printf("\nHello world\n"); // Print new line + hello world + new line
  return 0; // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
} // End main cycle



// Struttura di un programma C //
/*
  Un programma C consiste di una funzione dal nome "main".
  La funzione restituisce un intero (int).
  Il corpo del programma e' contenuto
  tra parentesi grafe { }.
  Le parentesi tonde () possono contenere
  gli argomenti passati al programma dal sistema operativo
  (non considerato per il momento)
*/

// Compilazione di un programma C //
/*
  Per compilarlo da linea di comando con nome standard:
  > gcc esempio1.c                  # Su macchine unix con compilatore gcc (compilazione+linking di "esempio1.c" e creazione eseguibile "a.out")

  Per compilarlo da linea di comando con nome personalizzato:
  > gcc esempio1.c -o esempio1      # Su macchine unix con compilatore gcc (compilazione+linking di "esempio1.c" e creazione eseguibile "esempio1")
  > gcc -o esempio1 esempio1.c      # ALTERNATIVA - Cambiando l'ordine non c'è differenza

  In due passi (Compilazione + linking separati)
  > gcc -c esempio1.c               # Compilo e generero il file "esempio1.o" (file oggetto codice eseguibile "incompleto")
  > gcc esempio1.o -o esempio1      # Link del codice eseguibile con librerie standard e del sistema operativo (linking "esempio1.o" e creazione eseguibile "esempio1")

  Esecuzione su unix:
  > ./esempio1                      # Esecuzione del file eseguibile "esempio1"

  Compilazione con Wall flag (all warnings)
  > gcc -Wall -o esempio1 esempio1.c  # Compilazione+linking di "esempio1.c" e creazione eseguibile "esempio1" (compilazione con indicazione anche di AVVISI)
*/