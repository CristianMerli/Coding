/*
 * Author: Cristian Merli
 * Code title: Lecture library header file
 * Code version: 3.0
 * Creation date: 11/05/2022
 * Last mod. date: 20/05/2022 
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
  public:                                                                                                   // Room class public section
    Room(C_real &l, C_real &w, C_real &h, const Term &term);                                                // Room class constructor method
    ~Room();                                                                                                // Room class destructor method
    Real calc_area() const;                                                                                 // Room class area calculation method
    Real calc_volume() const;                                                                               // Room class volume calculation method
    void add_people(C_integer &n=1);                                                                        // Room class add people method
    void rm_people(C_integer &n=1);                                                                         // Room class remove people method
    void rm_all_people();                                                                                   // Room class remove all people method
    Integer get_people() const;                                                                             // Room class get people method
    bool is_empty() const;                                                                                  // Room class is empty method
    bool is_full() const;                                                                                   // Room class is full method
  private:                                                                                                  // Room class private section (if not specified, the attributes are visible but inaccessible)
    Real l, w, h;                                                                                           // Room class private real attributes
    Integer people;                                                                                         // Room class private integer attributes
    const Term &term;                                                                                       // --- Room class private terminal UI object (to print info & fbk)
};


#endif                                                                                                      // Avoid multiple inclusions (old-alternative end)
