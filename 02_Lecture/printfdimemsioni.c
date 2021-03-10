/*

*/

#include <stdio.h> // Standard I/O library inclusion 

int main(){ // Main cycle

  int   a; //
  char  b; //
  short c; //

  printf("\n- INT --> sizeof(a) = %lu, bits = %lu\n", sizeof(a), sizeof(a)*8); // Print size of a (INT) in bytes
  printf("- CHAR --> sizeof(b) = %lu, bits = %lu\n", sizeof(b), sizeof(b)*8); // Print size of b (CHAR) in bytes
  printf("- SHORT --> sizeof(c) = %lu, bits = %lu\n", sizeof(c), sizeof(c)*8); // Print size of c (SHORT) in bytes

  return 0; // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
} // End main cycle