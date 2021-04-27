/*
 * Author: Cristian Merli
 * Code title: Exercise 3 (es_sol_strutture)
 * Code version: 3.0
 * Creation date: 21/04/2021
 * Last mod. date: 21/04/2021
 *  
 * Notes: To create shared libraries see: https://www.youtube.com/watch?v=Slfwk28vhws
 * 
 * gcc -Wall -c exercise3.c -o exercise3.o                        -->   Create software object file
 * gcc -Wall -fpic -shared libexercise3.c -o libexercise3.so      -->   Create library object file
 * gcc -Wall exercise3.o -o exercise3 "$(pwd)/libexercise3.so"    -->   Link software and library object files to executable
 */


/* Libraries import */
#include "libexercise3.h"                                                                                   // Library for exercise 3 import header file


/* Global vars declaration and definition */
//


/* Main cycle */
int main(){
  /* Vars declaration and definition */
  struct train italo1 = {15, ELECTIC};                                                                      // Train 1 obj init and definition
  struct train trenitalia1 = {10, DIESEL};                                                                  // Train 2 obj init and definition

  /* Code */
  logo(4, "TRAINS MANAGEMENT", ye, '#', gn);                                                                // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  
  printf("\n\n%s>>>%s The first train has %s%d%s wagons and it is powered by %s%s%s motor.%s\n",
          gn, pu, bl, italo1.wag_num, pu, bl, *(traction_str+italo1.tr_tract), pu, er);                     // Print first train fbk
  printf("\n\n%s>>>%s The second train has %s%d%s wagons and it is powered by %s%s%s motor.%s\n",
          gn, pu, bl, trenitalia1.wag_num, pu, bl, *(traction_str+trenitalia1.tr_tract), pu, er);           // Print second train fbk

  printf("\n\n%s>>>%s Adding a wagon to the first train.%s\n", gn, pu, er);                                 // Adding a wagon to the first train fbk
  wag_add(&italo1);                                                                                         // Wagon add (in train struct) function call, passin' first train struct pointer
  printf("\n\n%s>>>%s Removing a wagon of the second train.%s\n", gn, pu, er);                              // Adding a wagon from the second train fbk
  wag_rmv(&trenitalia1);                                                                                    // Wagon remove (in train struct) function call, passin' second train struct pointer
  printf("\n\n%s>>>%s Changing the second train traction type to electic.%s\n", gn, pu, er);                // Changing the second train traction type to electic fbk
  train_trac_typ(&trenitalia1, ELECTIC);                                                                    // Train traction type definition (in train struct) funtion call, passin' second train struct pointer

  printf("\n\n%s>>>%s The first train has %s%d%s wagons and it is powered by %s%s%s motor.%s\n",
          gn, pu, bl, italo1.wag_num, pu, bl, *(traction_str+italo1.tr_tract), pu, er);                     // Print first train fbk
  printf("\n\n%s>>>%s The second train has %s%d%s wagons and it is powered by %s%s%s motor.%s\n",
          gn, pu, bl, trenitalia1.wag_num, pu, bl, *(traction_str+trenitalia1.tr_tract), pu, er);           // Print second train fbk

  printf("\n\n%s>>>%s Adding the second train's wagons to the first train.%s\n", gn, pu, er);               // Adding the second train's wagons to the first train fbk
  trains_join(&italo1, &trenitalia1);                                                                       // Trains join (add the second train's wagons to the first train struct) function call, passin' first and second trains struct pointers and reset second train wagons number

  printf("\n\n%s>>>%s The first train has %s%d%s wagons and it is powered by %s%s%s motor.%s\n",
          gn, pu, bl, italo1.wag_num, pu, bl, *(traction_str+italo1.tr_tract), pu, er);                     // Print first train fbk

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Scrivere un gruppo di funzioni che opera sulla struttura treno
 * Il treno è identificato dal numero di carrozze, dal tipo di trazione (elettrica o a gasolio).
 * La funzione aggiungi carrozza che aumenta le carrozze del treno
 * La funzione rimuovi carrozza che diminuisce le carrozze del treno
 * ed un ultima funzione che prende un treno e un tipo di trazione ed assegna la trazione al treno.
 * Fare una funzione che connette due treni modificando il primo.
 */
