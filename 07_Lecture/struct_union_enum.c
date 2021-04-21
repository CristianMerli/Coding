/*
 * Author: Cristian Merli
 * Code title: Struct, union, enum and bitfields data types
 * Code version: 2.0
 * Creation date: 20/04/2021
 * Last mod. date: 21/04/2021
 */


/* Libraries import */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <string.h>                                                                                         // String library inclusion (for strlen ecc.)
#include <sys/ioctl.h>                                                                                      // System I/O control library inclusion (for ioctl ecc.)
#include <unistd.h>                                                                                         // UniStd library inclusion (for stdout ecc.)


/* Constants declaration and definition */
const char *rd = "\033[0;31m";                                                                              // Red color
const char *bl = "\033[0;34m";                                                                              // Blue color
const char *lb = "\033[1;34m";                                                                              // Light blue color
const char *pu = "\033[0;35m";                                                                              // Purple color
const char *cy = "\033[0;36m";                                                                              // Cyan color
const char *ye = "\033[1;33m";                                                                              // Yellow color
const char *og = "\033[0;33m";                                                                              // Orange color
const char *gn = "\033[0;32m";                                                                              // Green color
const char *lgn = "\033[1;32m";                                                                             // Light green color
const char *lgy = "\033[0;37m";                                                                             // Light gray color
const char *er = "\033[0m";                                                                                 // End color


/* Data-types declaration and definition */
typedef unsigned char   byte;                                                                               // Unsigned char alias (byte)


/* Enums declaration and definition */
enum tag{ A, B, C = 12, D };                                                                                // Tag enum declaration and definition (A=0, B=1, C=12, D=13, elements with CAPITAL LETTERS, convention)


/* Structs declaration and definition */
struct person                                                                                               // Person struct (declaration only)
{
  int age;                                                                                                  // Age element of the struct person
  char initial;                                                                                             // Initial element of the struct person
  char name[20];                                                                                            // Name element of the struct person
  char surname[20];                                                                                         // Surname element of the struct person
  double height;                                                                                            // Height element of the struct person
  double weight;                                                                                            // Weight element of the struct person
};

struct client                                                                                               // Client struct (declaration and definition, for antonio and marco)
{
  int age;                                                                                                  // Age element of the struct client
  char initial;                                                                                             // Initial element of the struct client
  char name[20];                                                                                            // Name element of the struct client
  char surname[20];                                                                                         // Surname element of the struct client
  double height;                                                                                            // Height element of the struct client
  double weight;                                                                                            // Weight element of the struct client
} antonio, marco;                                                                                           // Struct definition for antonio and marco as client

struct {                                                                                                    // Struct declaration and definition for unic without name, 1 only no-name struct can be defined
  int num;                                                                                                  // Num element of the struct unic
} unic;                                                                                                     // Unic no-name strut definition

struct person giorgio;                                                                                      // Giorgio person struct definition
struct person class[10];                                                                                    // Person struct vector definition, 10 person elements in class vector
struct person luca = {45, 'L', "Luca", "Rossi", 175, 75};                                                   // Fast and compact luca person struct initialization (definition)

struct var_type2{                                                                                           // Var_type2 struct declaration only
  int tipo_union;                                                                                           // Int variable inside var_type2 struct
  union {                                                                                                   // Union variable inside var_type2 struct declaration and definition for "elem"
    float   reale;                                                                                          // Float variable inside the "elem" union in a "var_type2" struct
    char    carattere;                                                                                      // Char variable inside the "elem" union in a "var_type2" struct
    int     intero;                                                                                         // Integer variable inside the "elem" union in a "var_type2" struct
  } elem;                                                                                                   // Elem union definition --> the size will be the same as float/int, max size data-types in the union (4 bytes = 32 bits)
};


/* Unions declaration and definition */
union generic                                                                                               // Generic union declaration and definition (allocates the size of the biggest data type, in this example double), then it can be defined either as an int or as a double data type --> NOTE THAT IF I WRITE THE VARIABLE AS DOUBLE, THEN I HAVE TO READ IT AS A DOUBLE! NOT AS INT
{
  double  val_real;                                                                                         // val_real double variable of the elem generic union
  int     val_int;                                                                                          // val_int int variable of the elem generic union
} elem;                                                                                                     // Elem generic union definition


/* Bitfields declaration and definition */
struct info                                                                                                 // Info (bitfield) struct declaration only, always allocates n*4 bytes (= n*32 bits) to perform optimized memo access, but allocation size can be overrided to define specific-sized variables, even single bits
{
  unsigned f:4;                                                                                             // 4 bits unsigned int, DO NOT USE DOUBLE AND FLOAT, INT ONLY
  signed g:2;                                                                                               // 2 bits signed int
  unsigned bool:1;                                                                                          // 1 bit unsigned bool value (0,1)
  signed s_bool:1;                                                                                          // 1 bit signed bool value (-1, 0) --> one first bit is reserved for the sign of the number
};                                                                                                          // Total number of bits = 8 --> allocates 32 bits (= 4 bytes)

/* Functions declaration and definition */
static void logo(const byte start_sp, const char *txt, const char *txt_col, const char bkg_chr,             // Static function (readable only in this .c file) and const param (not modified in function --> SW optimization at compile-time)
                 const char *bkg_col){                                                                      // Print responsive-logo function
  /* Function body */
  struct winsize w;                                                                                         // Window-size struct declaration
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);                                                                     // Save the number of terminal's rows/cloumns in window-size struct
  byte vthck = (w.ws_row / 5);                                                                              // Logo bkg vertical thickness calc
  byte lthck = (w.ws_col / 6);                                                                              // Logo bkg lateral thickness calc
  byte lsp = (w.ws_col - 2*lthck - 2*start_sp - strlen(txt)) / 2;                                           // Logo internal lateral spaces calc
  byte len = 2*lthck+2*lsp+strlen(txt);                                                                     // Logo length calc

  printf("\n%s", bkg_col);                                                                                  // New line fbk
  for (byte i = 0; i < (4*vthck+1); ++i){                                                                   // Logo lines print FOR cycle
    for (byte j = 0; j < start_sp; ++j){                                                                    // Initial spaces print FOR cycle
      printf(" ");                                                                                          // Print initial spaces
    }
    if ((i < vthck || i > (3*vthck)) && (i != (4*vthck)/2)){                                                // Full bkg logo lines print cond
      for (byte h = 0; h < len; ++h){                                                                       // Full bkg logo lines print FOR cycle
        printf("%c", bkg_chr);                                                                              // Bkg logo char print
      }
      printf("\n");                                                                                         // New line fbk
    } else if ((i >= vthck && i <= (3*vthck)) && (i != (4*vthck)/2)) {                                      // Partial-empty bkg logo lines print cond
      for (byte l = 0; l < lthck; ++l){                                                                     // Partial-empty bkg logo lines, initial full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Partial-empty bkg logo lines, initial full part print
      }
      for (byte m = 0; m < (len - 2*lthck); ++m){                                                           // Partial-empty bkg logo lines, central empty part print FOR cycle
        printf(" ");                                                                                        // Partial-empty bkg logo lines, central empty part print
      }
      for (byte n = 0; n < lthck; ++n){                                                                     // Partial-empty bkg logo lines, final full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Partial-empty bkg logo lines, final full part print
      }
      printf("\n");                                                                                         // New line fbk
    } else if (i == ((4*vthck)/2)) {                                                                        // Text logo line initial full part print cond
      for (byte o = 0; o < lthck; ++o){                                                                     // Text logo line initial full part print FOR cycle
        printf("%C", bkg_chr);                                                                              // Text logo line initial full part print
      }
      for (byte p = 0; p < lsp; ++p){                                                                       // Text logo line central empty part print FOR cycle
        printf(" ");                                                                                        // Text logo line central empty part print
      }
      printf("%s%s%s", txt_col, txt, bkg_col);                                                              // Text logo line central text part print
      for (byte q = 0; q < lsp; ++q){                                                                       // Text logo line central empty part print FOR cycle
        printf(" ");                                                                                        // Text logo line central empty part print
      }
      for (byte r = 0; r < lthck; ++r){                                                                     // Text logo line final full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Text logo line final full part print
      }
      printf("\n");                                                                                         // New line fbk
    }
  }
  printf("\033[0m\n");                                                                                      // New line fbk and erase logo bkg color
}


/* Main cycle */
int main(){
  /* Vars declaration and definition */
  //

  /* Code */
  logo(4, "STRUCT, UNION, ENUM AND BITFIELD", ye, '#', gn);                                                 // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  
  giorgio.age = 25;                                                                                         // Giorgio person struct, age element definition
  // Giorgio.name = "Giorgione";                                                                            // Wrong way to assign string value to struct! Use the strcpy() function as below!
  strcpy(giorgio.name, "Giorgione");                                                                        // Usin' strcpy() function, copy "Giorgione" string inside the "name" string element of "Giorgio" person struct
  struct person *el = &class[2];                                                                            // Extract the third person (in class vector) memory cell address and save it into the "el" pointer variable
  strcpy(el->name, "William");                                                                              // Write name "William" into the memory cell pointed by the "el" pointer (into the third person inside the class vector, see the previous line of code), using operator '->' to dereference the pointer "el", accessing pointed memory cell data
  strcpy((*el).name, "William");                                                                            // Equivalent, the same as the previous line of code (both "el->" and "*(el)" are two equivalent pointer dereferencing syntax to write values into the memory cell pointed by the "el" pointer)
  el->age = 22;                                                                                             // Use "el->" dereferencing syntax to initialize the "age" element of the pointes Person struct  ( in this case, the third inside the class vector of person(s) )
  el->weight = 65;                                                                                          // Use "el->" dereferencing syntax to initialize the "weight" element of the pointed Person struct  ( in this case, the third inside the class vector of person(s) )
  el->height = 172;                                                                                         // Use "el->" dereferencing syntax to initialize the "height" element of the pointed Person struct  ( in this case, the third inside the class vector of person(s) )
  strcpy(el->surname, "Bianchi");                                                                           // Use "el->" dereferencing syntax to initialize the "surname" element of the pointed Person struct  ( in this case, the third inside the class vector of person(s) )
  el->age++;                                                                                                // Use "el->" dereferencing syntax to increment the "age" element of the pointed Person struct  ( in this case, the third inside the class vector of person(s) )

  union generic var;                                                                                        // Define a "generic" union var
  printf("\n\n%s>>>%s The union size is equivalent to the max size of the data types in the union.%s\n",
          gn, pu, er);                                                                                      // Union sizes print fbk
  var.val_real = 23.5;                                                                                      // Assign to the "val_real" double variable of the "var" union a double number
  printf("\n\n%s>>>%s Union double: %svar = %f, %s'var.val_real' double size %ld, 'var' union size: %ld%s\n",
          gn, pu, bl, var.val_real, ye, sizeof(var.val_real), sizeof(var), er);                             // Print the "val_real" double variable size and the "var" union size
  var.val_int = 5;                                                                                          // Assign to the "val_int" integer variable of the "var" union an int number
  printf("\n\n%s>>>%s Union int: %svar = %d, %s'var.val_int' integer size %ld, 'var' union size: %ld%s\n",
          gn, pu, bl, var.val_int, ye, sizeof(var.val_int), sizeof(var), er);                               // Print the "val_int" integer variable size and the "var" union size

  enum car_type{                                                                                            // Enum "car_type" declaration only
    FAST,                                                                                                   // "FAST" element (with CAPITAL LETTERS, convention) of the "car_type" enum 
    SLOW                                                                                                    // "SLOW" element (with CAPITAL LETTERS, convention) of the "car_type" enum
  };
  char *type_str[] = {"Veloce","Lento"};                                                                    // If a string vector is defined with the same order of the enum created above, the enum elements can be used to access the string value (see below lines) 
  struct car{                                                                                               // Define "car" struct with "car_type" enum element
    enum car_type type;                                                                                     // Enum "car_type" definition inside "car" struct
  };
  struct car my = {SLOW};                                                                                   // "My" variable of type "car" struct definition with "SLOW" value from "car_type" enum
  printf("\n\n%s>>>%s My car type: %s%s\n", gn, pu, type_str[my.type], er);                                 // Print "my" struct "car" variable, accessing the "type" element of the "car_type" enum inside the "car" struct. Use this value as index to print the string inside the "type_str" vector.

  struct info2{                                                                                             // Info2 (bitfield) struct declaration only, always allocates n*4 bytes (= n*32 bits) to perform optimized memo access, but allocation size can be overrided to define specific-sized variables, even single bits
    unsigned f:4;                                                                                           // 4 bits unsigned int
    signed g:2;                                                                                             // 2 bits signed int
    signed t:1;                                                                                             // 1 bit signed bool value (-1, 0) --> one first bit is reserved for the sign of the number
    unsigned k:30;                                                                                          // 30 bits unsigned int
  };                                                                                                        // Total number of bits = 37 --> allocates 64 bits (= 8 bytes)

  struct info elem;                                                                                         // Elem info (bitfield) struct variable definition
  struct info2 elem2;                                                                                       // Elem2 info2 (bitfield) struct variable definition
  printf("\n\n%s>>>%s The (bitfield) struct allocation size is the next multiple of 4 bytes (32 bits).%s\n",
          gn, pu, er);                                                                                      // (Bitfields) struct sizes print fbk
  printf("\n\n%s>>>%s Elem info bitfiels %s(8 bits - 1 byte)%s, number allocated of bytes: %s%lu%s, total number of bits: %s%lu%s\n",
          gn, pu, bl, pu, ye, sizeof(elem), pu, ye, sizeof(elem)*8, er);                                    // Elem info (bitfield) struct allocated memory size
  printf("\n\n%s>>>%s Elem2 info bitfiels %s(37 bits - 5 byte)%s, number allocated of bytes: %s%lu%s, total number of bits: %s%lu%s\n",
          gn, pu, bl, pu, ye, sizeof(elem2), pu, ye, sizeof(elem2)*8, er);                                  // Elem2 info2 (bitfield) struct allocated memory size

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Struct, union, enum and bitfields data types lesson
 */
