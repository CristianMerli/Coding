/*
 * Author: Cristian Merli
 * Code title: Building library
 * Code version: 3.0
 * Creation date: 31/05/2022
 * Last mod. date: 03/06/2022
 */


/* Dependencies */
#include "lib_building.hpp"                                                                                 // Import building library header file


/* Floor empty constructor */
Floor::Floor() {
    this->l=0.0;                                                                                            // Init floor length [m]
    this->w=0.0;                                                                                            // Init floor width [m]
}


/* Floor constructor */
Floor::Floor(C_real &l, C_real &w) {
  if (l>=0) {                                                                                               // If floor length is ok
    this->l=l;                                                                                              // Def floor length [m]
  } else {                                                                                                  // Else if floor length ain't ok
    this->l=0.0;                                                                                            // Override floor length [m]
    if (ERR_PRINTING_FLAG)                                                                                  // If err printin' flg is set
      term_print("Error, can't create a floor with negative length! Value forced to zero!", ERR);           // Print err fbk
  }
  if (w>=0) {                                                                                               // If floor width is ok
    this->w=w;                                                                                              // def floor width [m]
  } else {                                                                                                  // Else if floor width ain't ok
    this->w=0.0;                                                                                            // Override floor width [m]
    if (ERR_PRINTING_FLAG)                                                                                  // If err printin' flg is set
      term_print("Error, can't create a floor with negative width! Value forced to zero!", ERR);            // Print err fbk
  }
}


/* Floor destructor [EMPTY] */
Floor::~Floor() {}


/* Floor method to get length [m] */
Real Floor::get_l() const {
  return l;                                                                                                 // Return floor length [m]
}


/* Floor method to get width [m] */
Real Floor::get_w() const {
  return w;                                                                                                 // Return floor width [m]
}


/* Floor method to set length [m] (returns operation fbk) */
Boolean Floor::set_l(C_real &new_l) {
  if (new_l>=0) {                                                                                           // If new floor length is ok
    l=new_l;                                                                                                // Upd floor length value [m]
    return EXIT_SUCCESS;                                                                                    // Return OK code (floor length correctly upd)
  } else {                                                                                                  // Else if new floor length ain't ok
    if (ERR_PRINTING_FLAG)                                                                                  // If err printin' flg is set
      term_print("Error, can't update floor length with negative value! Old-val restored!", ERR);           // Print err fbk
    return EXIT_FAILURE;                                                                                    // Return ERR code (floor length not upd)
  }
}


/* Floor method to set width [m] (returns operation fbk) */
Boolean Floor::set_w(C_real &new_w) {
  if (new_w>=0) {                                                                                           // If new floor width is ok
    w=new_w;                                                                                                // Upd floor width value [m]
    return EXIT_SUCCESS;                                                                                    // Return OK code (floor width correctly upd)
  } else {                                                                                                  // Else if new floor width ain't ok
    if (ERR_PRINTING_FLAG)                                                                                  // If err printin' flg is set
      term_print("Error, can't update floor width with negative value! Old-val restored!", ERR);            // Print err fbk
    return EXIT_FAILURE;                                                                                    // Return ERR code (floor width not upd)
  }
}


/* Floor method to calculate floor area [m^2] */
Real Floor::calc_floor_area() const {
  return l*w;                                                                                               // Return floor area [m^2]
}


/* Room empty constructor */
Room::Room() : Floor() {
  this->h=0.0;                                                                                              // Init room height [m]
  this->ppl=0;                                                                                              // Init people number in room
}


/* Room constructor */
Room::Room(C_real &l, C_real &w, C_real &h, C_integer &ppl) : Floor(l, w) {
  if (h>=0) {                                                                                               // If room height is ok
    this->h=h;                                                                                              // Def room height [m]
  } else {                                                                                                  // Else if room height ain't ok
    this->h=0.0;                                                                                            // Override room height [m]
    if (ERR_PRINTING_FLAG)                                                                                  // If err printin' flg is set
      term_print("Error, can't create a room with negative height! Value forced to zero!", ERR);            // Print err fbk
  }
  if (ppl>=0 && !is_full(ppl)) {                                                                            // If people number in room is ok and there's space
    this->ppl=ppl;                                                                                          // Def people number in room
  } else if (is_full(ppl)) {                                                                                // Else if there ain't enough space
    if (ERR_PRINTING_FLAG)                                                                                  // If err printin' flg is set
      term_print("Error, not enough space in room for given people number! Not added in room!", ERR);       // Print err fbk
    this->ppl=0;                                                                                            // Override people number in room
  } else {                                                                                                  // Else if people number in room ain't ok
    this->ppl=0;                                                                                            // Override people number in room
    if (ERR_PRINTING_FLAG)                                                                                  // If err printin' flg is set
      term_print("Error, can't create a room with negative number of people! Value forced to zero!", ERR);  // Print err fbk
  }
}


/* Room destructor [EMPTY] */
Room::~Room() {}


/* Room method to redefine rooms add operator */
Room Room::operator+(const Room &room2) {
  C_real room2_l=room2.get_l();                                                                             // Room2 length
  C_real room2_w=room2.get_w();                                                                             // Room2 width
  if (real_df(l, room2_l) && real_df(w, room2_w)) {                                                         // If rooms ain't compatible
    if (ERR_PRINTING_FLAG)                                                                                  // If err printin' flg is set
      term_print("Error, can't add rooms with no dimensions in common! Returning empty room!", ERR);        // Print err fbk
    return Room{};                                                                                          // And return empty room, else if rooms are compatible: return add-resulting room
  }
  C_real tmp_l=(real_df(l, room2_l)) ? l+room2_l : l;                                                       // Def tmp-room length [m]
  C_real tmp_w=(real_eq(tmp_l, l)) ? w+room2_w : w;                                                         // Def tmp-room width [m]
  return Room{tmp_l, tmp_w, max_val(h, room2.get_h()), ppl+room2.get_people()};                             // Return  new room object as sum of room1 (this) and room2
}


/* Room method to get width [m] */
Real Room::get_h() const {
  return h;                                                                                                 // Return room height [m]
}


/* Room method to set height [m] (returns operation fbk) */
Boolean Room::set_h(C_real &new_h) {
  if (new_h>=0) {                                                                                           // If new room height is ok
    h=new_h;                                                                                                // Upd room height value [m]
    return EXIT_SUCCESS;                                                                                    // Return OK code (room height correctly upd)
  } else {                                                                                                  // Else if new room height ain't ok
    if (ERR_PRINTING_FLAG)                                                                                  // If err printin' flg is set
      term_print("Error, can't update room height with a negative value! Old-val restored!", ERR);          // Print err fbk
    return EXIT_FAILURE;                                                                                    // Return ERR code (room height not upd)
  }
}


/* Room method to calculate walls area [m^2] */
Real Room::calc_walls_area() const {
  return 2*h*(l+w);                                                                                         // Return room walls area [m^2]
}


/* Room method to calculate volume [m^3] */
Real Room::calc_volume() const {
  return l*w*h;                                                                                             // Return room volume [m^3]
}


/* Room method to get people number */
Integer Room::get_people() const {
  return ppl;                                                                                               // Return the number of people in room
}


/* Room method to check if room is empty */
Boolean Room::is_empty() const {
  return ((ppl==0) ? true : false);                                                                         // If room is empty return ok, else if it ain't empty return not-ok
}


/* Room method to check if room is full (and if there is space for other n people) */
Boolean Room::is_full(C_integer &n) const {
  if (n<0) term_close_err("Error, can't check if room 'll be full with a negative number of new people!");  // If specified number extra of people in room is negative: close SW with err fbk, else if specified number extra of people in room ain't negative: return requested fbk
  C_boolean min_surf_violation=calc_floor_area()/(ppl+n) < MIN_SURF_P_PERS_M2;                              // Tmp var to detect min-surf-per-person violation
  C_boolean min_vol_violation=calc_volume()/(ppl+n) < MIN_VOL_P_PERS_M3;                                    // Tmp var to detect min-vol-per-person violation
  return (((!is_empty() || n!=0) && (min_surf_violation || min_vol_violation)) ? true : false);             // If room ain't empty and min-surf-per-person or min-vol-per-person ain't verified return ok (room is full), else return not-ok (room ain't full)
}


/* Room method to add peopled (returns operation fbk) */
Boolean Room::add_people(C_integer &n) {
  if (n>0 && !is_full(n)) {                                                                                 // If specified number of people to add in room is positive and there's space
    ppl+=n;                                                                                                 // Add people in room
    return EXIT_SUCCESS;                                                                                    // Return OK code (people added)
  } else if (is_full(n)) {                                                                                  // Else if there ain't enough space
    if (ERR_PRINTING_FLAG)                                                                                  // If err printin' flg is set
      term_print("Error, not enough space in room for given people number! Not added in room!", ERR);       // Print err fbk
  } else {                                                                                                  // Else if specified number of people to add in room is ok and there's enough space
    if (ERR_PRINTING_FLAG)                                                                                  // If err printin' flg is set
      term_print("Error, number of people to add in room must be positive! People not added!", ERR);        // Print err fbk
  }
  return EXIT_FAILURE;                                                                                      // Return ERR code (people not added)
}


/* Room method to remove people (returns operation fbk) */
Boolean Room::rm_people(C_integer &n) {
  if (ppl-n>=0) {                                                                                           // If there're enough people in room
    ppl-=n;                                                                                                 // Remove people from room
    return EXIT_SUCCESS;                                                                                    // Return OK code (people removed)
  } else {                                                                                                  // Else if there ain't enough people in room
    if (ERR_PRINTING_FLAG)                                                                                  // If err printin' flg is set
      term_print("Error, can't remove more people than the ones in the room! Not removed!", ERR);           // Print err fbk
    return EXIT_FAILURE;                                                                                    // Return ERR code (people not removed)
  }
}


/* Room method to remove all people */
void Room::rm_all_people() {
  ppl=0;                                                                                                    // Empty room
}


/* Room method to show info */
void Room::show_info() const {
  term_print("Room length", l, "[m]");                                                                      // Print room length
  term_print("Room width", w, "[m]");                                                                       // Print room width
  term_print("Room height", h, "[m]");                                                                      // Print room height
  term_print("Room floor area", calc_floor_area(), "[m^2]");                                                // Print room floor area
  term_print("Room walls area", calc_walls_area(), "[m^2]");                                                // Print room walls area
  term_print("Room volume", calc_volume(), "[m^3]");                                                        // Print room volume
  term_print("Number of people", get_people());                                                             // Print number of people in room
  term_print("Room empty", is_empty() ? "YES" : "NO");                                                      // Print room empty status
  term_print("Room full", is_full() ? "YES" : "NO");                                                        // Print room full status
}


/* Building constructor */
Building::Building(const std::vector<Room> &rooms) {
  if (!rooms.empty()) {                                                                                     // If rooms collection ain't empty
    this->rooms=rooms;                                                                                      // Def building rooms collection
  } else {                                                                                                  // Else if rooms collection is empty
    if (ERR_PRINTING_FLAG)                                                                                  // If err printin' flg is set
      term_print("Error, can't create a building without rooms! Creating a new empty room!", ERR);          // Print err fbk
    this->rooms=Rooms_collection{Room{}};                                                                   // Override rooms collection with one containing an empty room
  }
}


/* Building destructor */
Building::~Building() {
  Rooms_collection().swap(rooms);                                                                           // Clear building rooms collection container allocated memo
}


/* Building squared-brackets operator redefinition to access building rooms (write) */
Room& Building::operator[](C_integer &idx) {
  return rooms.at(static_cast<size_t>(idx));                                                                // Return address to room at specified index in building rooms collection
}


/* Building squared-brackets operator redefinition to access building rooms (read) */
Room Building::operator[](C_integer &idx) const {
  return rooms.at(static_cast<size_t>(idx));                                                                // Return room at specified index in building rooms collection
}


/* Building method to get rooms number */
Integer Building::get_rooms_num() const {
  return static_cast<Integer>(rooms.size());                                                                // Return number of rooms in the building
}


/* Building method to calculate floors area [m^2] */
Real Building::calc_floors_area() const {
  Real tmp_area=0;                                                                                          // Define tmp area var
  for (const auto &room : rooms) tmp_area+=room.calc_floor_area();                                          // Scroll rooms in building and increment area in tmp var
  return tmp_area;                                                                                          // Return tmp area var
}


/* Building method to calculate walls area [m^2] */
Real Building::calc_walls_area() const {
  Real tmp_area=0;                                                                                          // Define tmp area var
  for (const auto &room : rooms) tmp_area+=room.calc_walls_area();                                          // Scroll rooms in building and increment area in tmp var
  return tmp_area;                                                                                          // Return tmp area var
}


/* Building method to calculate volume [m^3] */
Real Building::calc_volume() const {
  Real tmp_vol=0;                                                                                           // Define tmp volume var
  for (const auto &room : rooms) tmp_vol+=room.calc_volume();                                               // Scroll rooms in building and increment volume in tmp var
  return tmp_vol;                                                                                           // Return tmp volume var
}


/* Building method to get people number */
Integer Building::get_people() const {
  Integer tmp_ppl=0;                                                                                        // Define tmp people number var
  for (const auto &room : rooms) tmp_ppl+=room.get_people();                                                // Scroll rooms in building and increment people number in tmp var
  return tmp_ppl;                                                                                           // Return tmp people number var
}


/* Building method to add people into the first available room (returns operation fbk) */
Boolean Building::add_people(C_integer &n) {
  for (auto &room : rooms)                                                                                  // Scroll rooms in building
    if (!room.is_full(n)) {                                                                                 // If there's enough space in current room
      room.add_people(n);                                                                                   // Add people in current room
      return EXIT_SUCCESS;                                                                                  // Return OK code (people correctly added)
    }
  if (ERR_PRINTING_FLAG)                                                                                    // If err printin' flg is set
    term_print("Error, can't add people in building! Not enough space in rooms, people not added!", ERR);   // Print err fbk
  return EXIT_FAILURE;                                                                                      // Return ERR code (people not added)
}


/* Building method to move people from a room to another (returns operation fbk) */
Boolean Building::mv_people(Room &room1, Room &room2) {
  C_integer ppl_room1=room1.get_people();                                                                   // Get people number in room1
  if (!room2.is_full(ppl_room1)) {                                                                          // If there's enough space in room2 for people in room1
    room1.rm_all_people();                                                                                  // Remove people from room1
    room2.add_people(ppl_room1);                                                                            // And add them into room2
    return EXIT_SUCCESS;                                                                                    // Return OK code (people correctly moved)
  }
  if (ERR_PRINTING_FLAG)                                                                                    // If err printin' flg is set
    term_print("Error, can't move people in the specified room! People not moved, not enough space!", ERR); // Print err fbk
  return EXIT_FAILURE;                                                                                      // Return ERR code (people not moved)
}


/* Building method to remove all people */
void Building::rm_all_people() {
  for (auto &room : rooms) room.rm_all_people();                                                            // Scroll rooms in building rooms collection and remove everyone
}


/* Building method to add room (back position) */
void Building::add_room(const Room &new_room) {
  rooms.push_back(new_room);                                                                                // Add room in building rooms collection at back position
}


/* Building method to add new room (back position) */
void Building::add_new_room(C_real &l, C_real &w, C_real &h, C_integer &ppl) {
  rooms.emplace_back(l, w, h, ppl);                                                                         // Add new room in building rooms collection at back position
}


/* Building method to directly access building rooms collection container (write) [ADVANCED] */
std::vector<Room>& Building::content() {
  return rooms;                                                                                             // Return access to building rooms collection container
}


/* Building method to directly access building rooms collection container (read) [ADVANCED] */
const std::vector<Room>& Building::content() const {
  return rooms;                                                                                             // Return access to building rooms collection container
}


/* Building method to show info */
void Building::show_info() const {
  term_print("********************");                                                                       // Print graphics
  term_print("* BUILDING DETAILS *");                                                                       // Print building section title
  term_print("********************");                                                                       // Print graphics
  term_print("Number of rooms", get_rooms_num());                                                           // Print building rooms number
  term_print("Total floors area", calc_floors_area(), "[m^2]");                                             // Print building rooms floor area
  term_print("Total walls area", calc_walls_area(), "[m^2]");                                               // Print building rooms walls area
  term_print("Total volume", calc_volume(), "[m^3]");                                                       // Print building rooms volume
  term_print("Total number of people", get_people());                                                       // Print number of people in building rooms
  term_print("*****************");                                                                          // Print graphics
  term_print("* ROOMS DETAILS *");                                                                          // Print room section title
  term_print("*****************");                                                                          // Print graphics
  U_short i=0;                                                                                              // Room idx init
  for (const auto &room : rooms) {                                                                          // Building rooms scrollin' cycle
    ++i;                                                                                                    // Room idx upd
    term_print("- ROOM "+S(i)+":");                                                                         // Print room number in building
    room.show_info();                                                                                       // Show room info
  }
  term_print("***************");                                                                            // Print graphics
  term_print("* LAW DETAILS *");                                                                            // Print laws section title
  term_print("***************");                                                                            // Print graphics
  term_print("Min surf/person", MIN_SURF_P_PERS_M2, "[m^2/pers]");                                          // Print min-surf-per-person
  term_print("Min vol/person", MIN_VOL_P_PERS_M3, "[m^3/pers]");                                            // Print min-vol-per-person
}


/* Funct to define building rooms collection from terminal */
Rooms_collection def_building_rooms_from_terminal() {
  Integer num_rooms;                                                                                        // Tmp-var declaration to contain number of rooms in building
  Real room_l, room_w, room_h;                                                                              // Tmp-vars declaration to initialize building rooms dimensions
  Rooms_collection building_rooms;                                                                          // Tmp-rooms-collection definition
  TERM_ACQ_CYCLE("Insert the number of building rooms", Integer, num_rooms, num_rooms<MIN_ROOMS_BUILDING, \
                 "Error, the number of rooms in building must be at least "+S(MIN_ROOMS_BUILDING)+"!");     // Number of rooms in building tmp-var definition
  for (Byte i=0; i<num_rooms; ++i) {                                                                        // Cycle to populate building tmp-rooms-collection
    TERM_ACQ_CYCLE("Insert building room"+S(i+1)+" length [m]", Real, room_l, room_l<=0.0, \
                   "Error, building room"+S(i+1)+" length [m] must be positive!");                          // Define tmp-room length [m]
    TERM_ACQ_CYCLE("Insert building room"+S(i+1)+" width [m]", Real, room_w, room_w<=0.0, \
                   "Error, building room"+S(i+1)+" width [m] must be positive!");                           // Define tmp-room width [m]
    TERM_ACQ_CYCLE("Insert building room"+S(i+1)+" height [m]", Real, room_h, room_h<=0.0, \
                   "Error, building room"+S(i+1)+" height [m] must be positive!");                          // Define tmp-room height [m]
    building_rooms.emplace_back(room_l, room_w, room_h);                                                    // Add defined tmp-room in building tmp-rooms-collection
  }
  return building_rooms;                                                                                    // Return tmp-rooms-collection
}
