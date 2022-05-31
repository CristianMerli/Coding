/*
 * Author: Cristian Merli
 * Code title: UI (terminal I/O) library templates file
 * Code version: 3.0
 * Creation date: 30/05/2022
 * Last mod. date: 31/05/2022
 */


/* Include guards */
#pragma once                                                                                                // Avoid multiple inclusions
#ifndef _UI_TPP_                                                                                            // Avoid multiple inclusions (old-alternative start)
#define _UI_TPP_                                                                                            // Avoid multiple inclusions (old-alternative)


/* Dependencies */
#include "lib_ui.hpp"                                                                                       // Import UI (terminal I/O) library header file


/* Template to print val on terminal */
template<typename T>
void term_print(C_string &fbk_str, const T &val) {
  std::cout << fbk_col[0] << ">>> " << fbk_col[1] << fbk_str << \
  ": " << fbk_col[2] << val << std::endl << ER;                                                             // Print val on terminal
}


/* Template to print val on terminal with details */
template<typename T>
void term_print(C_string &fbk_str, const T &val, C_string &fbk_str2) {
  std::cout << fbk_col[0] << ">>> " << fbk_col[1] << fbk_str << \
  ": " << fbk_col[2] << val << SP << fbk_str2 << std::endl << ER;                                           // Print val on terminal with details
}


/* Template to get user input val from terminal */
template<typename T>
T term_get_val(C_string &req_str) {
  T val;                                                                                                    // Val tmp-var
  do {                                                                                                      // Acq cycle
    term_print(req_str, REQ);                                                                               // Print req
    if (std::cin >> val) {                                                                                  // Chk in val
      term_print("Value correctly acquired, inserted value", val);                                          // Print inserted val
      break;                                                                                                // Xit acq cycle
    } else {                                                                                                // If in-val ain't ok
      term_print("Invalid value! Please retry...", ERR);                                                    // Print err
      std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');                 // Clr in-buff and ignore other chars and repeat req
    }
  } while (true);                                                                                           // Acq cycle xit cond managed usin' break
  return val;                                                                                               // Return val tmp-var
}


/* Template to allocate dynamic-memo */
template<typename T>
T *alloc(C_integer &sz) {
  T *ptr=new (std::nothrow) T[sz]; if (ptr==NULL) term_close_err("Error in dynamic-memo allocation!");      // Allocate dynamic-memo
  return ptr;                                                                                               // Return ptr to the first allocated memory cell
}


/* Template to deallocate dynamic-memo */
template<typename T>
void dealloc(const T *const ptr) {
  (ptr!=NULL) ? (delete[] ptr) : (term_print("Error, can't deallocate NULL ptr from dynamic-memo!", ERR));  // Deallocate dynamic-memo
}


/* Template to calculate max-val */
template<typename T>
const T &max_val(const T &val1, const T &val2) {
  return (val1>val2 ? val1 : val2);                                                                         // Return max-val
}


/* Template to calculate min-val */
template<typename T>
const T &min_val(const T &val1, const T &val2) {
  return (val1<val2 ? val1 : val2);                                                                         // Return min-val
}


/* Template to swap values */
template<typename T>
void swap_val(T &val1, T &val2) {
  const T tmp=val1;                                                                                         // Def tmp val
  val1=val2;                                                                                                // Redef val1
  val2=tmp;                                                                                                 // Redef val2
}


/* Template to calculate array size (not for pointers/references) */
template<typename T>
Integer array_sz(const T &arr) {
  return sizeof(arr)/sizeof(arr[1]);                                                                        // Return array size
}


#endif                                                                                                      // Avoid multiple inclusions (old-alternative end)
