/*
 * Author: Cristian Merli
 * Code title: Printf, sizeof e variabili
 * Code version: 3.0
 * Creation date: 09/03/2021
 * Last mod. date: 11/03/2021
 */

/* Libraries import */
#include <stdio.h> // Standard I/O library inclusion 

int main(){ // Main cycle
  /* Vars declaration */
  char        a; // CHAR (C standard data type) variable
  int         b; // INT (C standard data type) variable
  short       c; // SHORT (C standard data type) variable
  long        d; // LONG (C standard data type) variable
  long long   e; // LONG LONG (C standard data type) variable
  float       f; // FLOAT (C standard data type) variable
  double      g; // DOUBLE (C standard data type) variable
  long double h; // LONG DOUBLE (C standard data type) variable

  /* Code */
  printf("\n> Memo requirement for standard C data types:\n\n");
  printf("- CHAR          -->     sizeof(char) in bytes = %lu           (%lu bits)\n", sizeof(a), sizeof(a)*8); // Print size of a (CHAR) in bytes and bits
  printf("- INT           -->     sizeof(int) in bytes = %lu            (%lu bits)\n", sizeof(b), sizeof(b)*8); // Print size of b (INT) in bytes and bits
  printf("- SHORT         -->     sizeof(short) in bytes = %lu          (%lu bits)\n", sizeof(c), sizeof(c)*8); // Print size of c (SHORT) in bytes and bits
  printf("- LONG          -->     sizeof(long) in bytes = %lu           (%lu bits)\n", sizeof(d), sizeof(d)*8); // Print size of d (LONG) in bytes and bits
  printf("- LONG LONG     -->     sizeof(long long) in bytes = %lu      (%lu bits)\n", sizeof(e), sizeof(e)*8); // Print size of e (LONG LONG) in bytes and bits
  printf("- FLOAT         -->     sizeof(float) in bytes = %lu          (%lu bits)\n", sizeof(f), sizeof(f)*8); // Print size of f (FLOAT) in bytes and bits
  printf("- DOUBLE        -->     sizeof(double) in bytes = %lu         (%lu bits)\n", sizeof(g), sizeof(g)*8); // Print size of g (DOUBLE) in bytes and bits
  printf("- LONG DOUBLE   -->     sizeof(long double) in bytes = %lu   (%lu bits)\n", sizeof(h), sizeof(h)*8);  // Print size of h (LONG DOUBLE) in bytes and bits

  return 0; // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
} // End main cycle



/* Links */
/*
 * Classroom:
 * https://classroom.google.com/u/0/c/Mjg1NDUwNDU3NTE2
 *
 * Moodle:
 * https://didatticaonline.unitn.it/dol/course/view.php?id=31321
 *
 * Esterni:
 * https://publications.gbdirect.co.uk/c_book/
 * https://books.goalkicker.com/CBook/
 * https://en.wikibooks.org/wiki/A_Little_C_Primer
 *
 * Tipi Base:
 * https://en.wikipedia.org/wiki/C_data_types
 *
 * Librerie:
 * https://www.cplusplus.com/reference/clibrary/
 *
 * Tabella ASCII:
 * http://www.brescianet.com/appunti/vari/tabellaascii/ascii.htm
 *
 * Numeri Binari:
 * https://it.wikipedia.org/wiki/Sistema_numerico_binario
 * http://www.ripmat.it/mate/p/pb/pbfd.html
 */
