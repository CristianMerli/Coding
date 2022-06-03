/*
 * Author: Cristian Merli
 * Code title: Building library header file
 * Code version: 3.0
 * Creation date: 31/05/2022
 * Last mod. date: 03/06/2022 
 */


/* Include guards */
#pragma once                                                                                                // Avoid multiple inclusions
#ifndef _BUILDING_HPP_                                                                                      // Avoid multiple inclusions (old-alternative start)
#define _BUILDING_HPP_                                                                                      // Avoid multiple inclusions (old-alternative)


/* Dependencies */
#include "../ui/lib_ui.hpp"                                                                                 // Import UI (terminal I/O) library header file


/* Constants */
#define MIN_SURF_P_PERS_M2  8.0                                                                             // Min allowed value of surface/person [m^2/pers]
#define MIN_VOL_P_PERS_M3   10.0                                                                            // Min allowed value of volume/person [m^3/pers]
#define STD_ROOM_HEIGHT_M   2.70                                                                            // Standard (default) room height [m]
#define MIN_ROOMS_BUILDING  4                                                                               // Min number of rooms in building creation from terminal
#define ERR_PRINTING_FLAG   true                                                                            // Terminal errors printing flag


/* Floor parent class */
class Floor {
  public:                                                                                                   // Floor class PUBLIC section
    Floor();                                                                                                // Floor empty constructor
    Floor(C_real &l, C_real &w);                                                                            // Floor constructor
    ~Floor();                                                                                               // Floor destructor [EMPTY]
    Real get_l() const;                                                                                     // Floor method to get length [m]
    Real get_w() const;                                                                                     // Floor method to get width [m]
    Boolean set_l(C_real &new_l);                                                                           // Floor method to set length [m] (returns operation fbk)
    Boolean set_w(C_real &new_w);                                                                           // Floor method to set width [m] (returns operation fbk)
    Real calc_floor_area() const;                                                                           // Floor method to calculate floor area [m^2]
  protected:                                                                                                // Floor class PROTECTED section
    Real l, w;                                                                                              // Floor real attributes (length [m], width [m])
};


/* Room child class */
class Room : public Floor {
  public:                                                                                                   // Room class PUBLIC section
    Room();                                                                                                 // Room empty constructor
    Room(C_real &l, C_real &w, C_real &h=STD_ROOM_HEIGHT_M, C_integer &ppl=0);                              // Room constructor
    ~Room();                                                                                                // Room destructor [EMPTY]
    Room operator+(const Room &room2);                                                                      // Room method to redefine rooms add operator
    Real get_h() const;                                                                                     // Room method to get height [m]
    Boolean set_h(C_real &new_h);                                                                           // Room method to set height [m] (returns operation fbk)
    Real calc_walls_area() const;                                                                           // Room method to calculate walls area [m^2]
    Real calc_volume() const;                                                                               // Room method to calculate volume [m^3]
    Integer get_people() const;                                                                             // Room method to get people number
    Boolean is_empty() const;                                                                               // Room method to check if room is empty
    Boolean is_full(C_integer &n=0) const;                                                                  // Room method to check if room is full (and if there is space for other n people)
    Boolean add_people(C_integer &n=1);                                                                     // Room method to add people (return operation fbk)
    Boolean rm_people(C_integer &n=1);                                                                      // Room method to remove people (returns operation fbk)
    void rm_all_people();                                                                                   // Room method to remove all people
    void show_info() const;                                                                                 // Room method to show info
  protected:                                                                                                // Room class PROTECTED section
    Real h;                                                                                                 // Room real attribute (height [m])
    Integer ppl=0;                                                                                          // Room integer attribute (number of people in room)
};


/* Building parent class */
class Building {
  public:                                                                                                   // Building class PUBLIC section
    Building(const std::vector<Room> &rooms);                                                               // Building constructor
    ~Building();                                                                                            // Building destructor
    Room& operator[](C_integer &idx);                                                                       // Building squared-brackets operator redefinition to access building rooms (write)
    Room operator[](C_integer &idx) const;                                                                  // Building squared-brackets operator redefinition to access building rooms (read)
    Integer get_rooms_num() const;                                                                          // Building method to get rooms number
    Real calc_floors_area() const;                                                                          // Building method to calculate area [m^2]
    Real calc_walls_area() const;                                                                           // Building method to calculate walls area [m^2]
    Real calc_volume() const;                                                                               // Building method to calculate volume [m^3]
    Integer get_people() const;                                                                             // Building method to get people number
    Boolean add_people(C_integer &n=1);                                                                     // Building method to add people into the first available room (returns operation fbk)
    Boolean mv_people(Room &room1, Room &room2);                                                            // Building method to move people from a room to another (returns operation fbk)
    void rm_all_people();                                                                                   // Building method to remove all people
    void add_room(const Room &new_room);                                                                    // Building method to add room (back position)
    void add_new_room(C_real &l, C_real &w, C_real &h=STD_ROOM_HEIGHT_M, C_integer &ppl=0);                 // Building method to add new room (back position)
    std::vector<Room>& content();                                                                           // Building method to directly access building rooms collection container (write) [ADVANCED]
    const std::vector<Room>& content() const;                                                               // Building method to directly access building rooms collection container (read) [ADVANCED]
    void show_info() const;                                                                                 // Building method to show info
  protected:                                                                                                // Building class PROTECTED section
    std::vector<Room> rooms;                                                                                // Building rooms vector attribute (building rooms collection container)
};


/* Data-types */
typedef std::vector<Room> Rooms_collection;                                                                 // Rooms collection alias


/* Public functions */
//
Rooms_collection def_building_rooms_from_terminal();                                                        // Funct to define building rooms collection from terminal


#endif                                                                                                      // Avoid multiple inclusions (old-alternative end)
