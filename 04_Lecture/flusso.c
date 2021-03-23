/*
 * Author: Cristian Merli
 * Code title: Gestione flusso
 * Code version 3.0
 * Creation date: 23/03/2021
 * Last mod. date: 23/03/2021
 */

/* Libraries import */
#include <stdio.h> // Standard I/O library inclusion 

int main(){ // Main cycle
  /* Vars declaration */
  int r = 1;                                                      // Dichiarazione e definizione variabili
  
  /* Code */
  printf("\n");                                                   // New line fbk

  // Ciclo WHILE --> while(1) --> While infinito
  while(r < 4){                                                   // Condizione WHILE (prima controlla la condizione e poi esegue il codice)
    printf("While r=%d\n", r);                                    // Print fbk
    r++;                                                          // Cambio variabile condizione
  }                                                               // End while cycle
  printf("\n");                                                   // New line fbk
  // Ciclo DO-WHILE
  do{
    printf("Do-while r=%d\n", r);                                 // Print fbk
    r--;                                                          // Cambio variabile condizione
  }while(r >= 4);                                                 // Condizione WHILE (prima esegue il codice e poi controlla la condizione)
  printf("\n");                                                   // New line fbk

  // Ciclo FOR --> for(;;) --> For infinito
  for (int i = 0, r = 0; i < 4; i++, r++){                        // Gestione ciclo FOR (inizializzazione; condizione; update) --> Più variavili separate dal carattere ','
    printf("For r=%d, i=%d\n", r, i);                             // Print fbk
    if ( r == 2 ){                                                // Condizione di uscita anticipata dal ciclo FOR
      break;                                                      // Esci in anticipo dal ciclo FOR (utilizzabile anche in WHILE e DO-WHILE)
    } else {                                                      // Condizione di ritorno al controllo della condizione del ciclo FOR
      continue;                                                   // Torna al controllo della condizione del ciclo FOR (utilizzabile anche in WHILE e DO-WHILE)
    }                                                             // End condizione di ritorno al controllo della condizione del ciclo FOR
  }                                                               // End for cycle (Ordine operazioni: inizializzazione var., codice ciclo for, update var., controllo condizione)
  printf("\n");                                                   // New line fbk

  // Switch-case
  switch(r){                                                      // Variabile da controllare suddividendo in casi
    case 0:                                                       // Caso r=0
      printf("Case r=0\n");                                       // Print fbk
      break;                                                      // End case

    case 1:                                                       // Caso r=1
      printf("Case r=1\n");                                       // Print fbk
      break;                                                      // End case
    
    case 2:                                                       // Caso r=2
      printf("Case r=2\n");                                       // Print fbk
      break;                                                      // End case

    case 3:                                                       // Caso r=3
      printf("Case r=3\n");                                       // Print fbk
      break;                                                      // End case

    case 4:                                                       // Caso r=4
      printf("Case r=4\n");                                       // Print fbk
      break;                                                      // End case

    default:                                                      // Caso nessuna delle precedenti
      printf("Default\n");                                        // Print fbk
  } // End Swith-case

  // Labels and GOTO
  label1:                                                         // Label 1 definition
    if (r == 3){                                                  // Condizione per goto
      printf("Label r=%d\n", r);                                  // Print fbk
      r++;                                                        // Cambio variabile condizione
      goto label2;                                                // Label 2 call
    }                                                             // End condizione per goto
  label2:                                                         // Label 2 definition
    if (r == 3){                                                  // Condizione per goto
      goto label1;                                                // Label 1 call
    }                                                             // End condizione per goto

  return 0;  // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
} // End main cycle
