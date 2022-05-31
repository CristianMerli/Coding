/*
 * Author: Cristian Merli
 * Code title: Lecture library
 * Code version: 3.0
 * Creation date: 11/05/2022
 * Last mod. date: 30/05/2022
 */


/* Dependencies */
#include "lib_lecture.hpp"                                                                                  // Import lecture library header file


/* Room class constructor method */
Room::Room(C_real &l, C_real &w, C_real &h) {
  if (l>0 && w>0 && h>0) {                                                                                  // If room dimensions are ok: def room class private attributes
    this->l=l;                                                                                              // Init room length
    this->w=w;                                                                                              // Init room width
    this->h=h;                                                                                              // Init room height
    this->people=0;                                                                                         // Init people inside the room
  } else term_close_err("Error, can't create a room with negative/null dimensions!");                       // Else if room dimensions ain't ok: close terminal UI with err fbk
}


/* Room class destructor method [UNUSED] */
Room::~Room() {
  // Clr alloc dyn-memo [UNUSED]
}


/* Room class area calculation method */
Real Room::calc_area() const {
  return l*w;                                                                                               // Return room area
}


/* Room class volume calculation method */
Real Room::calc_volume() const {
  return l*w*h;                                                                                             // Return room volume
}


/* Room class add people method */
void Room::add_people(C_integer &n) {
  if (n>0) people+=n;                                                                                       // If specified number is positive: add people in room
  else term_print("Error, the number of people to add in room must be positive!", ERR);                     // Else if specified number is negative: print err fbk
}


/* Room class remove people method */
void Room::rm_people(C_integer &n) {
  if (people-n>=0) people-=n;                                                                               // If there're enough people in room: remove people
  else term_print("Error, can't remove more people than number of people inside the room!", ERR);           // Else if there aren't enough people in room: print err fbk
}


/* Room class remove all people method */
void Room::rm_all_people() {
  people=0;                                                                                                 // Empty room
}


/* Room class get people method */
Integer Room::get_people() const {
  return people;                                                                                            // Return the number of people in room
}


/* Room class is empty method */
bool Room::is_empty() const {
  return ((people==0) ? true : false);                                                                      // If room is empty return ok, else if it ain't empty return not-ok
}


/* Room class is full method */
bool Room::is_full() const {
  return (is_empty() ? false : ((calc_volume()/people > MIN_VOL_PER_PERSON) ? false : true));               // If room ain't empty and if min-vol-per-person ain't verified return ok (room is full), else if it's verified or room is empty return not-ok (room ain't full)
}
