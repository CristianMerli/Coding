/*
 * Author: Cristian Merli
 * Code title: Exercise 4 (es_strutture_2)
 * Code version: 3.0
 * Creation date: 21/04/2021
 * Last mod. date: 29/04/2021
 *  
 * Notes: To create shared libraries see: https://www.youtube.com/watch?v=Slfwk28vhws
 * 
 * gcc -Wall -c exercise4.c -o exercise4.o                        -->   Create software object file
 * gcc -Wall -fpic -shared libexercise4.c -o libexercise4.so      -->   Create library object file
 * gcc -Wall exercise4.o -o exercise4 "$(pwd)/libexercise4.so"    -->   Link software and library object files to executable
 */


/* Libraries import */
#include "libexercise4.h"                                                                                   // Library for exercise 4 import header file


/* Global vars declaration and definition */
struct overdim_space_weight ovrdim_sp_wght = { .dimens.x=400, .dimens.y=450,
                                               .dimens.z=150, .weight_fos=4 };                              // Overdimensioning parameters of the garage: space (x, y, z) to allow vehicle-parking operations and weight factor of safety (security coefficient) init


/* Main cycle */
int main(){
  /* Vars declaration and definition */
  struct vehicle empty_vehic = { .dimens.x=0, .dimens.y=0, .dimens.z=0, .weight=0 };                        // Empty vehicle obj init for empty garages

  /* Code */
  logo(4, "VEHICLES AND GARAGES", ye, '#', gn);                                                             // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)

  struct vehicle panda1 = { .dimens.x=2880, .dimens.y=1380, .dimens.z=1550, .weight=755 };                  // Vehicle1 obj init
  struct vehicle audi1 = { .dimens.x=3842, .dimens.y=1560, .dimens.z=1520, .weight=1920 };                  // Vehicle2 obj init
  struct vehicle panda2 = { .dimens.x=2925, .dimens.y=1430, .dimens.z=1620, .weight=985 };                  // Vehicle3 obj init
  struct vehicle audi2 = { .dimens.x=3850, .dimens.y=1580, .dimens.z=1460, .weight=2080 };                  // Vehicle4 obj init
  struct vehicle jeep1 = { .dimens.x=3100, .dimens.y=1670, .dimens.z=1560, .weight=1620 };                  // Vehicle5 obj init
  struct vehicle jeep2 = { .dimens.x=3250, .dimens.y=1680, .dimens.z=1660, .weight=1835 };                  // Vehicle6 obj init
  struct vehicle vehics[] = { panda1, audi1, panda2, audi2, jeep1, jeep2 };                                 // Vehicles vector creation and population
  shrt vehic_num = (sizeof(vehics) / sizeof(panda1));                                                       // Calculate Vehicles number in vector

  printf("\n\n%s>>>%s Weights of vehicles in vector [kg]:%s\n   ", gn, pu, er);                             // Weights of vehicles in vector fbk
  for (shrt k = 0; k < vehic_num; ++k)                                                                      // Weights of vehicles in vector print FOR cycle
    printf(" %s%lf%s ", bl, vehics[k].weight, er);                                                          // Print weights of vehicles in vector

  printf("\n\n\n%s>>>%s Heaviest vehicle in vector afer sorting [kg]: %s%lf%s\n",
          gn, pu, ye, heaviest_vehic(vehics, vehic_num).weight, er);                                        // Heaviest vehicle in vector fbk and find heaviest vehicle in vehicles vector function call

  printf("\n\n%s>>>%s Weights of vehicles in vector afer sorting [kg]:%s\n   ", gn, pu, er);                // Weights of vehicles in vector after sorting fbk
  for (shrt k = 0; k < vehic_num; ++k)                                                                      // Weights of vehicles in vector print FOR cycle
    printf(" %s%lf%s ", bl, vehics[k].weight, er);                                                          // Print weights of vehicles in vector

  printf("\n\n\n%s>>>%s Sizes of vehicles in vector [mm], [m^3]: %s\n", gn, pu, er);                        // Sizes of vehicles in vector fbk
  for (shrt k = 0; k < vehic_num; ++k)                                                                      // Sizes of vehicles in vector print FOR cycle
    printf("    %s(%lf, %lf, %lf), vol = %lf%s\n", bl, vehics[k].dimens.x, vehics[k].dimens.y,
            vehics[k].dimens.z, vehics[k].dimens.x*vehics[k].dimens.y*vehics[k].dimens.z*0.000000001, er);  // Print sizes of vehicles in vector
  
  biggest_vehic(vehics, vehic_num);                                                                         // Find biggest vehicle in vehicles vector (calculating volumes) function call
  printf("\n\n%s>>>%s Biggest vehicle in vector afer sorting [mm], [m^3]:\n    %s(%lf, %lf, %lf), vol = %lf%s",
          gn, pu, ye, vehics[0].dimens.x,vehics[0].dimens.y, vehics[0].dimens.z,
          vehics[0].dimens.x*vehics[0].dimens.y*vehics[0].dimens.z*0.000000001, er);                        // Biggest vehicle in vector fbk

  printf("\n\n\n%s>>>%s Sizes of vehicles in vector afer sorting [kg]:%s\n", gn, pu, er);                   // Sizes of vehicles in vector after sorting fbk
  for (shrt k = 0; k < vehic_num; ++k)                                                                      // Sizes of vehicles in vector print FOR cycle
    printf("   %s(%lf, %lf, %lf), vol = %lf%s\n", bl, vehics[k].dimens.x, vehics[k].dimens.y,
            vehics[k].dimens.z, vehics[k].dimens.x*vehics[k].dimens.y*vehics[k].dimens.z*0.000000001, er);  // Sizes of vehicles in vector fbk

  struct garage box1 = { .dimens.x=4500, .dimens.y=2350, .dimens.z=2150,
                         .found_strngth=16000, .parked_vehicle=empty_vehic };                               // Garage1 obj init with empty wehicle inside
  struct garage box2 = { .dimens.x=3920, .dimens.y=1810, .dimens.z=1850,
                         .found_strngth=8000, .parked_vehicle=empty_vehic };                                // Garage2 obj init with empty wehicle inside

  printf("\n\n%s>>>%s Trying to assign vehicle1 to garage1... %s", gn, pu, er);                             // Tryin' to assign vehicle1 to garage1 fbk
  vehic_garage_assign(panda1, &box1, ovrdim_sp_wght);                                                       // Tryin' to assign vehicle1 to garage1
  printf("    %sVehicle in box1: Sizes = (%lf, %lf, %lf) mm. Weight = %lf kg%s\n",
          og, box1.parked_vehicle.dimens.x, box1.parked_vehicle.dimens.y, box1.parked_vehicle.dimens.z,
          box1.parked_vehicle.weight, er);                                                                  // Print vehicle in box1 after vehicle1 assignment attempt

  printf("\n\n%s>>>%s Trying to assign vehicle2 to garage2... %s", gn, pu, er);                             // Tryin' to assign vehicle2 to garage2 fbk
  vehic_garage_assign(audi1, &box2, ovrdim_sp_wght);                                                        // Tryin' to assign vehicle2 to garage2
  printf("    %sVehicle in box2: Sizes = (%lf, %lf, %lf) mm. Weight = %lf kg%s\n",
          og, box2.parked_vehicle.dimens.x, box2.parked_vehicle.dimens.y, box2.parked_vehicle.dimens.z,
          box2.parked_vehicle.weight, er);                                                                  // Print vehicle in box2 after vehicle2 assignment attempt

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Scrivere un gruppo di funzioni che opera sulla struttura veicolo e garage.
 * Il veicolo è caratterizzato dal peso, e dalle sue dimensioni (x,y,z).
 * Il garage è caratterizzato dalla sua dimensione (x,y,z) e dalla resistenza delle fondamenta e
 * da quale veicolo contine. Un garage può contenere un solo veicolo.
 * Scrivere una funzione che controlla se un veicolo è adatto a quel garage cioè se le dimensioni
 * e la resistenza dell fondamenta sono adeguate al veicolo in questione.
 * Scrivere una funzione che dato un vettore di veicoli ritorna quello più pesante.
 * Scrivere una funzione che dato un vettore di veicoli ritorna quello più grande (maggior volume)
 * Scrivere una funzione assegna al garage il veicolo corrispondente.
 */
