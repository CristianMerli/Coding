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
  private:                                                                                                  // Class private section (if not specified, the attributes are visible but inaccessible)
    Real l, w, h;                                                                                           // Class private real attributes
    Integer people;                                                                                         // Class private integer attributes
  public:                                                                                                   // Class public section
    Room(C_real& l, C_real& w, C_real& h);                                                                  // Class constructor method
    ~Room();                                                                                                // Class destructor method
    Real calc_area() const;                                                                                 // Class area calculation method
    Real calc_volume() const;                                                                               // Class volume calculation method
    void add_people(C_integer n=1);                                                                         // Class add people method
    void rm_people(C_integer n=1);                                                                          // Class remove people method
    void rm_all_people();                                                                                   // Class remove all people method
    Integer get_people() const;                                                                             // Class get people method
    bool is_empty() const;                                                                                  // Class is empty method
    bool is_full() const;                                                                                   // Class is full method
};


#endif                                                                                                      // Avoid multiple inclusions (old-alternative end)
