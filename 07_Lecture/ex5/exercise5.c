/*
 * Author: Cristian Merli
 * Code title: Exercise 5 (es_generico)
 * Code version: 1.0
 * Creation date: 22/04/2021
 * Last mod. date: 22/04/2021
 *  
 * Notes: To create shared libraries see: https://www.youtube.com/watch?v=Slfwk28vhws
 * 
 * gcc -Wall -c exercise5.c -o exercise5.o                        -->   Create software object file
 * gcc -Wall -fpic -shared libexercise5.c -o libexercise5.so      -->   Create library object file
 * gcc -Wall exercise5.o -o exercise5 "$(pwd)/libexercise5.so"    -->   Link software and library object files to executable
 */


/* Libraries import */
#include "libexercise5.h"                                                                                   // Library for exercise 5 import header file


/* Global vars declaration and definition */
connection tmp_connection;                                                                                  // Temporary connection type var to assign connection type into streets
const byte strts_in_cross = 4;                                                                              // Number of streets for each cross


/* Main cycle */
int main(){
  /* Vars declaration and definition */
  street cross1[strts_in_cross];                                                                            // Cross1 vector of streets init
  street cross2[strts_in_cross];                                                                            // Cross2 vector of streets init
  street street1 = { .name="High street" };                                                                 // Street1 struct init
  street street2 = { .name="Wall street" };                                                                 // Street2 struct init
  street street3 = { .name="London street" };                                                               // Street3 struct init
  street street4 = { .name="Oxford street" };                                                               // Street4 struct init
  street street5 = { .name="Cambridge street" };                                                            // Street5 struct init
  street street6 = { .name="Victoria's street" };                                                           // Street6 struct init
  street street7 = { .name="Freedom street" };                                                              // Street7 struct init
  street street8 = { .name="Somethingelse street" };                                                        // Street8 struct init
  street street9 = { .name="9th street" };                                                                  // Street9 struct init
  street street10 = { .name="10th street" };                                                                // Street10 struct init
  street street11 = { .name="11th street" };                                                                // Street11 struct init

  /* Code */
  logo(4, "CROSSES AND STREETS", ye, '#', gn);                                                              // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)

  printf("\n\n%s>>>%s Assigning streets 1-2-3-4 to cross1 in 1st-2nd-3rd-4th position...%s\n", gn, pu, er); // Assigning street1, street2, street3 and street4 to cross1 fbk
  assign_strt_to_crss(street1, cross1, 0);                                                                  // Assign street1 to cross1 in 1st position functio call
  assign_strt_to_crss(street2, cross1, 1);                                                                  // Assign street2 to cross1 in 2nd position functio call
  assign_strt_to_crss(street3, cross1, 2);                                                                  // Assign street3 to cross1 in 3rd position functio call
  assign_strt_to_crss(street4, cross1, 3);                                                                  // Assign street4 to cross1 in 4th position functio call
  printf("\n\n%s>>>%s Street names of cross1's streets:%s\n   ", gn, pu, er);                               // Street names in cross1 fbk
  print_crs_strt_nanes(cross1, strts_in_cross);                                                             // Print street names in cross function call

  printf("\n\n%s>>>%s Assigning streets 5-6-7-8 to cross2 in 1st-2nd-3rd-4th position...%s\n", gn, pu, er); // Assigning street5, street6, street7 and street8 to cross2 fbk
  assign_strt_to_crss(street5, cross2, 0);                                                                  // Assign street5 to cross2 in 1st position functio call
  assign_strt_to_crss(street6, cross2, 1);                                                                  // Assign street6 to cross2 in 2nd position functio call
  assign_strt_to_crss(street7, cross2, 2);                                                                  // Assign street7 to cross2 in 3rd position functio call
  assign_strt_to_crss(street8, cross2, 3);                                                                  // Assign street8 to cross2 in 4th position functio call
  printf("\n\n%s>>>%s Street names of cross2's streets:%s\n   ", gn, pu, er);                               // Street names in cross2 fbk
  print_crs_strt_nanes(cross2, strts_in_cross);                                                             // Print street names in cross function call

  tmp_connection.strt = street5;  assign_conn_to_strt(&street1, &tmp_connection);                           // Assign street1 connection function call (connect street1 to street5)
  printf("\n\n%s>>>%s Assigned street1 connection (other street): %s%s%s\n",
          gn, pu, ye, street1.con->strt.name, er);                                                          // Assigning street1 connection fbk

  tmp_connection.cross = cross2;  assign_conn_to_strt(&street2, &tmp_connection);                           // Assign street2 connection function call (connect street2 to cross2)
  printf("\n\n%s>>>%s Assigned street2 connection (cross), streets names in cross:\n    %s|%s |  | %s |  | %s |  | %s |%s\n",
          gn, pu, ye, street2.con->cross[0].name, street2.con->cross[1].name,
          street2.con->cross[2].name, street2.con->cross[3].name, er);                                      // Assigning street2 connection fbk
  
  tmp_connection.strt = street9;  assign_conn_to_strt(&street5, &tmp_connection);                           // Assign street5 connection function call (connect street5 to street9)
  tmp_connection.strt = street10;  assign_conn_to_strt(&street9, &tmp_connection);                          // Assign street9 connection function call (connect street9 to street10)
  tmp_connection.strt = street11;  assign_conn_to_strt(&street10, &tmp_connection);                         // Assign street10 connection function call (connect street11 to street10)
  printf("\n\n%s>>>%s Navigation through streets and crosses starting from %s%s%s:%s\n   ",
          gn, pu, ye, street1.name, pu, er);                                                                // Navigation through streets and crosses starting from street1 fbk
  navigate(&street5);                                                                                       // Navigate through streets and crosses function call

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/* 
 * Scrivere una libreria che gestisce la configurazione di incroci stradali
 * L'incrocio è caratterizzado da connettere 4 strade.
 * Ogni strada ha un nome ed è connessa a un elemento che può essere strada o un incrocio.
 * Scrivere un set di istruzioni che funzioni:
 * 1. Assegnare una strada ad un incrocio in una certa posizione.
 * 2. Assegnare a una strada cosa è connessa.
 * 3. Fare una funzione che partendo da una strada scelta percorre la strada mostrado il
 * nume della via percorsa fino ad incontrare un incrocio e a quel punto chiede all'utente 
 * di scegliere dove andare tra le strade disponibili nell'incrocio, termina quando la strada 
 * non è connessa a niente.
*/
