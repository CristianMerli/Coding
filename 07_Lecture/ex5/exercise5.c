/*
 * Author: Cristian Merli
 * Code title: Exercise 5 (es_generico)
 * Code version: 2.0
 * Creation date: 22/04/2021
 * Last mod. date: 25/04/2021
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
const byte strts_in_cross = 4;                                                                              // Number of streets for each cross
union conn tmp_connection;                                                                                  // Temporary connection var to assign streets connection


/* Main cycle */
int main(){
  /* Vars declaration and definition */
  street cross1[strts_in_cross];                                                                            // Cross1 vector of streets init
  street cross2[strts_in_cross];                                                                            // Cross2 vector of streets init
  street street1 = { .name="High street", .connection.type=NONE };                                          // Street1 struct init
  street street2 = { .name="Wall street", .connection.type=NONE };                                          // Street2 struct init
  street street3 = { .name="London street", .connection.type=NONE };                                        // Street3 struct init
  street street4 = { .name="Oxford street", .connection.type=NONE };                                        // Street4 struct init
  street street5 = { .name="Cambridge street", .connection.type=NONE };                                     // Street5 struct init
  street street6 = { .name="Victoria's street", .connection.type=NONE };                                    // Street6 struct init
  street street7 = { .name="Freedom street", .connection.type=NONE };                                       // Street7 struct init
  street street8 = { .name="Somethingelse street", .connection.type=NONE };                                 // Street8 struct init
  street street9 = { .name="9th street", .connection.type=NONE };                                           // Street9 struct init
  street street10 = { .name="10th street", .connection.type=NONE };                                         // Street10 struct init
  street street11 = { .name="11th street", .connection.type=NONE };                                         // Street11 struct init

  /* Code */
  logo(4, "CROSSES AND STREETS", ye, '#', gn);                                                              // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)

  printf("\n\n%s>>>%s Assigning streets 1-2-3-4 to cross1 in 1st-2nd-3rd-4th position...%s\n", gn, pu, er); // Assigning street1, street2, street3 and street4 to cross1 fbk
  assign_strt_to_crss(street1, cross1, strts_in_cross, FIRST);                                              // Assign street1 to cross1 in 1st position functio call
  assign_strt_to_crss(street2, cross1, strts_in_cross, SECOND);                                             // Assign street2 to cross1 in 2nd position functio call
  assign_strt_to_crss(street3, cross1, strts_in_cross, THIRD);                                              // Assign street3 to cross1 in 3rd position functio call
  assign_strt_to_crss(street4, cross1, strts_in_cross, FOURTH);                                             // Assign street4 to cross1 in 4th position functio call
  printf("\n\n%s>>>%s Street names of cross1's streets:%s\n   ", gn, pu, er);                               // Street names in cross1 fbk
  print_crs_strt_nanes(cross1, strts_in_cross);                                                             // Print street names in cross function call

  printf("\n\n%s>>>%s Assigning streets 5-6-7-8 to cross2 in 1st-2nd-3rd-4th position...%s\n", gn, pu, er); // Assigning street5, street6, street7 and street8 to cross2 fbk
  assign_strt_to_crss(street5, cross2, strts_in_cross, FIRST);                                              // Assign street5 to cross2 in 1st position functio call
  assign_strt_to_crss(street6, cross2, strts_in_cross, SECOND);                                             // Assign street6 to cross2 in 2nd position functio call
  assign_strt_to_crss(street7, cross2, strts_in_cross, THIRD);                                              // Assign street7 to cross2 in 3rd position functio call
  assign_strt_to_crss(street8, cross2, strts_in_cross, FOURTH);                                             // Assign street8 to cross2 in 4th position functio call
  printf("\n\n%s>>>%s Street names of cross2's streets:%s\n   ", gn, pu, er);                               // Street names in cross2 fbk
  print_crs_strt_nanes(cross2, strts_in_cross);                                                             // Print street names in cross function call

  tmp_connection.strt = &street5; assign_conn_to_strt(&street1, &tmp_connection, STREET);                   // Assign street1 connection function call (connect street1 to street5)
  printf("\n\n%s>>>%s Assigned street1 connection (other street): %s%s%s\n",
          gn, pu, ye, street1.connection.conn.strt->name, er);                                              // Assigning street1 connection fbk

  tmp_connection.cross = cross2; assign_conn_to_strt(&street2, &tmp_connection, CROSS);                     // Assign street2 connection function call (connect street2 to cross2)
  printf("\n\n%s>>>%s Assigned street2 connection (cross), streets names in cross:\n    %s| %s |  | %s |  | %s |  | %s |%s\n",
          gn, pu, ye, street2.connection.conn.cross[FIRST].name, street2.connection.conn.cross[SECOND].name,
          street2.connection.conn.cross[THIRD].name, street2.connection.conn.cross[FOURTH].name, er);       // Assigning street2 connection fbk

  tmp_connection.strt = &street9;   assign_conn_to_strt(&street5, &tmp_connection, STREET);                 // Assign street5 connection function call (connect street9 to street5)
  tmp_connection.strt = &street2;   assign_conn_to_strt(&street9, &tmp_connection, STREET);                 // Assign street9 connection function call (connect street2 to street9)
  tmp_connection.cross = cross1;   assign_conn_to_strt(&street2, &tmp_connection, CROSS);                   // Assign street2 connection function call (connect cross1 to street2)
  tmp_connection.strt = &street10;  assign_conn_to_strt(&street1, &tmp_connection, STREET);                 // Assign street1 connection function call (connect street10 to street1)
  tmp_connection.strt = &street11;  assign_conn_to_strt(&street10, &tmp_connection, STREET);                // Assign street10 connection function call (connect street11 to street10)
  printf("\n\n%s>>>%s Navigation through streets and crosses starting from %s%s%s:%s\n",
          gn, pu, ye, street5.name, pu, er);                                                                // Navigation through streets and crosses starting from street1 fbk
//// DEBUG
/*  printf("\n\n%s>>>%s Cross1 street 3:\n    %s| %s |, type %d%s\n",
          gn, pu, ye, street5.connection.conn.strt->connection.conn.strt->connection.conn.cross[FIRST].connection.conn.strt->name, street5.connection.conn.strt->connection.conn.strt->connection.conn.cross[FIRST].connection.conn.strt->connection.type, er);
  printf("\n\n%s>>>%s Cross1 street 3:\n    %s| %s |, type %d%s\n",
          gn, pu, ye, cross1[FIRST].connection.conn.strt->name, cross1[FIRST].connection.conn.strt->connection.type, er);
//// DEBUG */
  navigate(street5, strts_in_cross);                                                                        // Navigate through streets and crosses function call

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
