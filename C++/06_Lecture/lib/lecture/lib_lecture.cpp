/*
 * Author: Cristian Merli
 * Code title: Lecture library
 * Code version: 3.0
 * Creation date: 11/05/2022
 * Last mod. date: 11/05/2022
 */


/* Dependencies */
#include "lib_lecture.h"                                                                                    // Import lecture library header file


/* Public classes methods */
Room::Room(Real l, Real w, Real h){                                                                         // Room class constructor method
  if (l>0 && w>0 && h>0){                                                                                   // If room dimensions are ok: def room class private attributes
    this->l=l;                                                                                              // Def room length
    this->w=w;                                                                                              // Def room width
    this->h=h;                                                                                              // Def room height
    this->a=l*w;                                                                                            // Def room area
    this->v=a*h;                                                                                            // Def room volume
    this->people=0;                                                                                         // Def people inside the room
  } else close_err("Error, can't create a room with negative/null dimensions!");                            // Else if room dimensions ain't ok: close SW with err fbk
}


Room::~Room(){                                                                                              // Room class destructor method
  // Clr alloc dyn-memo
}


Real Room::calc_area(){                                                                                     // Room class area calculation method
  return a;                                                                                                 // Return room area
}


Real Room::calc_volume(){                                                                                   // Room class volume calculation method
  return v;                                                                                                 // Return room volume
}


void Room::add_person(){                                                                                    // Room class add person method
  ++people;                                                                                                 // Add person in room
}


void Room::add_person(Integer n){                                                                           // Room class add people method
  if (n>0) people+=n;                                                                                       // If specified number is positive: add people in room
  else term_print("Error, the number of people to add in room must be positive!", ERR);                     // Else if specified number is negative: print err fbk
}


void Room::rm_person(){                                                                                     // Room class remove person method
  if (people>0) --people;                                                                                   // If there's at least one person in room: remove a person
  else term_print("Error, can't remove more people than number of people inside the room!", ERR);           // Else if room is empty: print err fbk
}


void Room::rm_person(Integer n){                                                                            // Room class remove people method
  if (people-n>=0) people-=n;                                                                               // If there're enough people in room: remove people
  else term_print("Error, can't remove more people than number of people inside the room!", ERR);           // Else if there aren't enough people in room: print err fbk
}


void Room::rm_all_people(){                                                                                 // Room class remove all people method
  people=0;                                                                                                 // Empty room
}


Integer Room::get_people(){                                                                                 // Room class get people method
  return people;                                                                                            // Return the number of people in room
}


bool Room::is_empty(){                                                                                      // Room class is empty method
  return ((people==0) ? true : false);                                                                      // If room is empty return ok, else if it ain't empty return not-ok
}


bool Room::is_full(){                                                                                       // Room class is full method
  if (!is_empty()) return ((v/people < MIN_VOL_PER_PERSON) ? true : false);                                 // If room ain't empty and if min-vol-per-person ain't verified return ok (room is full), else if it's verified return not-ok (room ain't full)
  else return false;                                                                                        // Else if room is empty return return not-ok (room ain't full)
}
