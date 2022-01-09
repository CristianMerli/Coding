/*
 * Author: Cristian Merli
 * Code title: Pointers
 * Code version: 3.0
 * Creation date: 13/04/2021
 * Last mod. date: 15/04/2021
 */


/* Libraries import */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <string.h>                                                                                         // String library inclusion (for strlen ecc.)


/* Constants declaration and definition */
const char R[] = "\033[0;31m";                                                                              // Red color
const char B[] = "\033[0;34m";                                                                              // Blue color
const char LB[] = "\033[1;34m";                                                                             // Light blue color
const char P[] = "\033[0;35m";                                                                              // Purple color
const char C[] = "\033[0;36m";                                                                              // Cyan color
const char Y[] = "\033[1;33m";                                                                              // Yellow color
const char O[] = "\033[0;33m";                                                                              // Orange color
const char G[] = "\033[0;32m";                                                                              // Green color
const char LGN[] = "\033[1;32m";                                                                            // Light green color
const char LGY[] = "\033[0;37m";                                                                            // Light gray color
const char E[] = "\033[0m";                                                                                 // End color


/* Functions declaration and definition */
void logo(unsigned char vthck, unsigned char lthck_vthik_r, unsigned char start_sp, unsigned char lsp,
          char txt[], const char txt_col[], char bkg_chr, const char bkg_col[]){                            // Print logo function
  /* Function body */
  printf("\n%s", bkg_col);                                                                                  // New line
  unsigned char len = 2*lthck_vthik_r*vthck+2*lsp+strlen(txt);                                              // Logo length calc
  for (unsigned char i = 0; i < (4*vthck+1); i++){                                                          // Logo lines print FOR cycle
    for (unsigned char j = 0; j < start_sp; j++){                                                           // Initial spaces print FOR cycle
      printf(" ");                                                                                          // Print initial spaces
    }
    if ((i < vthck || i > (3*vthck)) && (i != (4*vthck)/2)){                                                // Full bkg logo lines print cond
      for (unsigned char h = 0; h < len; h++){                                                              // Full bkg logo lines print FOR cycle
        printf("%c", bkg_chr);                                                                              // Bkg logo char print
      }
      printf("\n");                                                                                         // New line
    } else if ((i >= vthck && i <= (3*vthck)) && (i != (4*vthck)/2)) {                                      // Partial-empty bkg logo lines print cond
      for (unsigned char l = 0; l < lthck_vthik_r*vthck; l++){                                              // Partial-empty bkg logo lines, initial full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Partial-empty bkg logo lines, initial full part print
      }
      for (unsigned char m = 0; m < (len - 2*lthck_vthik_r*vthck); m++){                                    // Partial-empty bkg logo lines, central empty part print FOR cycle
        printf(" ");                                                                                        // Partial-empty bkg logo lines, central empty part print
      }
      for (unsigned char n = 0; n < lthck_vthik_r*vthck; n++){                                              // Partial-empty bkg logo lines, final full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Partial-empty bkg logo lines, final full part print
      }
      printf("\n");                                                                                         // New line
    } else if (i == ((4*vthck)/2)) {                                                                        // Text logo line initial full part print cond
      for (unsigned char o = 0; o < lthck_vthik_r*vthck; o++){                                              // Text logo line initial full part print FOR cycle
        printf("%C", bkg_chr);                                                                              // Text logo line initial full part print
      }
      for (unsigned char p = 0; p < lsp; p++){                                                              // Text logo line central empty part print FOR cycle
        printf(" ");                                                                                        // Text logo line central empty part print
      }
      printf("%s%s%s", txt_col, txt, bkg_col);                                                              // Text logo line central text part print
      for (unsigned char q = 0; q < lsp; q++){                                                              // Text logo line central empty part print FOR cycle
        printf(" ");                                                                                        // Text logo line central empty part print
      }
      for (unsigned char r = 0; r < lthck_vthik_r*vthck; r++){                                              // Text logo line final full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Text logo line final full part print
      }
      printf("\n");                                                                                         // New line
    }
  }
  printf("\033[0m\n");                                                                                      // New line and erase logo bkg color
}

void funct(int (*c)[10]){                                                                                   // Pointer function (pointer array of 10 (int) elements as parameter)
  /* Function body */
  (*c)[0] = 4;                                                                                              // Define the first val of the array = 4 using pointer
}

void funct2(int *c){                                                                                        // Pointer function 2
//void funct2(int c[]){                                                                                       // Pointer function 2 --> SAME AS ABOVE
  /* Function body */
  c[3] = 4;                                                                                                 // Define the first val of the array/pointer to 4 --> Pointer logics and arrays are equivalent, but array's size must be known at code compilation stage
  *(c+3) = 4;                                                                                               // Define the first val of the array/pointer to 4 --> Equivalent as ABOVE, but be careful!! (+3*data-type dimension in bit defined by pointer data-type, in this case INT)
}


/* Main cycle */
int main(){
  /* Vars declaration and definition */
  int arr[10], *p;                                                                                          // Int vars declaration and definition

  /* Code */
  logo(5, 3, 8, 22, "POINTERS", Y, 'X', G);                                                                 // Print logo function call (vert_thick, lat_thick_vert_thick_ratio, start_spaces, lat_spaces, text, txt_color, background_char, bkgchr_color)
  printf("\n\n%s>>>%s Pointers lesson\n%s", G, P, E);                                                       // Poiniters lesson fbk

  p = &arr[0];                                                                                              // Set pointer val equal to the first cell addr of the array
  (*p) = 3;                                                                                                 // Set val in pointed memo cell to 3
  printf("\n\n%s-->%s Print array/pointer after setting first val to 3: %s\n", O, C, E);                    // Print array fbk
  for (int i = 0; i < 10; i++){                                                                             // Array print for cycle
    printf("%d ",*(arr+i));                                                                                 // Array elements print
    //printf("%d ", arr[i]);                                                                                  // Same thing as ABOVE to print array as a pointer
  }
  
  //p = &arr;                                                                                                 // Gives WARNING 'cuz arr is not an int, but set pointer val equal to the first cell addr of the array, see BELOW
  int (*pp)[10];                                                                                            // Set pointer specifically for a 10 elements array
  pp = &arr;                                                                                                // Set pointer val equal to the first cell addr of the array NO WARNING, correct way
  printf("\n\n%s-->%s Print array/pointer memo cell hex code: %s\n", O, C, E);                              // Print array/pointer memo cell hex code fbk
  printf("%p", pp);                                                                                         // Print pointer val (memo cell hex addr)
  
  funct(&arr);                                                                                              // Pass to the pointer function an array (which is also a pointer, equivalent)
  printf("\n\n%s-->%s Print array/pointer after setting first val to 4 with function 1: %s\n", O, C, E);    // Print array fbk
  for (int i = 0; i < 10; i++){                                                                             // Array print for cycle
    printf("%d ", arr[i]);                                                                                  // Array elements print
  }

  p = arr;                                                                                                  // An array can be associated to apointer, same data-type --> NO ERROR
  funct2(p);                                                                                                // Pass to the pointer function 2 an pointer (which is also an array, equivalent)
  printf("\n\n%s-->%s Print array/pointer after setting third val to 4 with function 2: %s\n", O, C, E);    // Print array fbk
  for (int i = 0; i < 10; i++){                                                                             // Array print for cycle
    printf("%d ", arr[i]);                                                                                  // Array elements print
  }

  int arr2d[5][4];                                                                                          // Define 2d array
  for (int i = 0; i < 5; i++){                                                                              // 2d array definition lines for cycle
    for (int j = 0; j < 4; j++){                                                                            // 2d array definition columns for cycle
      arr2d[i][j] = j+i*4+1;                                                                                // 2d array elements definition
    }
  }
  printf("\n\n%s-->%s Print array/pointer after setting values: %s\n", O, C, E);                            // Print array fbk
  for (int i = 0; i < 5; i++){                                                                              // 2d array print lines for cycle
    for (int j = 0; j < 4; j++){                                                                            // 2d array print columns for cycle
      printf("%d ", arr2d[i][j]);                                                                           // 2d array elements print
    }
    printf("\n");                                                                                           // New line
  }

  int (*arr4i)[4];                                                                                          // Create a suitable pointer for the above defined matrix (lines matrix pointer, first-level pointer, which in C coding language corrisponds to lines) --> Move between lines (with four columns)
  for (arr4i = arr2d; arr4i <= &(arr2d[4]); arr4i++){                                                       // Select each matrix line, from the first (arr2d --> which is equivalent to &ar2d[0]), 'till last line &(arr2d[4])
    (*arr4i)[2] = 0;                                                                                        // Pointer dereferencing, write in each third column of each line in mat
  }
  printf("\n%s-->%s Print array/pointer after setting third column values to 0: %s\n", O, C, E);            // Print array fbk
  for (int i = 0; i < 5; i++){                                                                              // 2d array print lines for cycle
    for (int j = 0; j < 4; j++){                                                                            // 2d array print columns for cycle
      printf("%d ", arr2d[i][j]);                                                                           // 2d array elements print
    }
    printf("\n");                                                                                           // New line
  }

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * -
 */
