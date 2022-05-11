/*
 * Author: Cristian Merli
 * Code title: Lecture library header file
 * Code version: 3.0
 * Creation date: 11/05/2022
 * Last mod. date: 11/05/2022 
 */


/* Include guards */
#pragma once                                                                                                // Avoid multiple inclusions
#ifndef _LECTURE_H_                                                                                         // Avoid multiple inclusions (old-alternative start)
#define _LECTURE_H_                                                                                         // Avoid multiple inclusions (old-alternative)


/* Dependencies */
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file


/* Constants */
#define MIN_VOL_PER_PERSON  11.0                                                                            // Min volume per person [m^3]


/* Public classes */
class Room {                                                                                                // Room class
  private:                                                                                                  // Class private section
    Real l, w, h, v, a;                                                                                     // Class private real attributes
    Integer people;                                                                                         // Class private integer attributes
  public:                                                                                                   // Class public section
    Room(Real l, Real w, Real h);                                                                           // Class constructor method
    ~Room();                                                                                                // Class destructor method
    Real calc_area();                                                                                       // Class area calculation method
    Real calc_volume();                                                                                     // Class volume calculation method
    void add_person();                                                                                      // Class add person method
    void add_person(Integer n);                                                                             // Class add people method
    void rm_person();                                                                                       // Class remove person method
    void rm_person(Integer n);                                                                              // Class remove people method
    void rm_all_people();                                                                                   // Class remove all people method
    Integer get_people();                                                                                   // Class get people method
    bool is_empty();                                                                                        // Class is empty method
    bool is_full();                                                                                         // Class is full method
};


#endif                                                                                                      // Avoid multiple inclusions (old-alternative end)
