/*
 * Author: Cristian Merli
 * Code title: Exercise 5 (es_generico) library
 * Code version: 2.0
 * Creation date: 22/04/2021
 * Last mod. date: 25/04/2021
 */


/* Libraries import */
#include "libexercise5.h"                                                                                   // Library for exercise 5 import header file


/* Functions declaration and definition */
void logo(const byte start_sp, const char *txt, const char *txt_col, const char bkg_chr,
          const char *bkg_col){                                                                             // Print responsive-logo function
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


void delay(const unsigned long time_ms){                                                                    // Delay [ms] function
  // Pause time [ms] calculation considering val update time
  clock_t start_time = clock();                                                                             // Start time = software execution time
  
  while ((clock() - start_time) < (time_ms * (CLOCKS_PER_SEC / 1000)));                                     // Check if elapsed time [ms] (time - start_time) is greater or equal to pause time, pause time calculated considering the number of clocks per second
}


shrt iaddr(const u_shrt i, const u_shrt j, const u_shrt lda){                                               // Arrays/vectors memo addressing
  /* Function body */
  return (i*lda)+j;                                                                                         // Return index number
}


void assign_strt_to_crss(street strt, street *cross, const street_in_cross strts_in_cross, const byte pos){ // Assign street to cross function
  /* Function body */
  *(cross+iaddr(V, pos, strts_in_cross)) = strt;                                                            // Assign the input street in specified position of the input cross (streets array)
  cross[pos].connection.type = STREET;                                                                      // Street connection type
}


void print_crs_strt_nanes(const street *strt, const byte strts_in_cross){                                   // Print street names in cross function
  /* Function body */
  printf("%s", ye);                                                                                         // Set color
  for (street_in_cross i = 0; i < strts_in_cross; ++i){
    printf(" | %s | ", strt[i].name);                                                                       // Prtint each street name in cross (vector of streets)
  }
  printf("%s\n", er);                                                                                       // New line fbk and erase color
}


void assign_conn_to_strt(street *strt, union conn *conn, const conn_typ type){                              // Assign connection to street function
  /* Function body */
  switch (type)                                                                                             // Connecttion type swith-case
  {
    case STREET:                                                                                            // Case STREET connection type
      strt->connection.conn.strt = conn->strt;                                                              // Assign to the given street, the given street connection
      strt->connection.type = STREET;                                                                       // Assign to the given street, STREET connection type
      break;
    case CROSS:                                                                                             // Case CROSS connection type
      strt->connection.conn.cross = conn->cross;                                                            // Assign to the given street, the given cross connection
      strt->connection.type = CROSS;                                                                        // Assign to the given street, CROSS connection type
      break;
    case NONE:                                                                                              // Case NONE connection type
      printf("\n%s    Error in street connection definition! Connection type not defined!%s\n", rd, er);    // Connection type not defined error fbk
      break;
    default:                                                                                                // Default-case connection type
      printf("\n%s    Error in street connection definition! Unknown connection type!%s\n", rd, er);        // Unknown connection type error fbk
      break;
  }
}


void navigate(const street start_strt, const byte strts_in_cross){                                          // Navigate through streets and crosses function
  /* Function body */
  street nav_strt = start_strt;                                                                             // Assign starting street to navigation street
  char in_buff[3];                                                                                          // Input buffer char array for scanf func
  byte sel_srtr = 0;                                                                                        // Selected street in cross to continue navigation

  while (nav_strt.connection.type != NONE){                                                                 // Streets and crosses navigation while cycle (exit condition --> next street connection empty)
    switch (nav_strt.connection.type)                                                                       // Navigation street connection type swith-case
    {
      case STREET:                                                                                          // Case STREET connection type
        printf("%s    --> %sNow you are in %s%s%s, continuing...%s\n",
                og, cy, lb, nav_strt.name, cy, er);                                                         // Print this street name fbk
        nav_strt = *nav_strt.connection.conn.strt;                                                          // Go into next street
        break;
      case CROSS:                                                                                           // Case CROSS connection type
        while (sel_srtr <= 0 || sel_srtr > strts_in_cross){                                                 // Check if sel street val is in allowed range
          printf("%s    --> %sCross with %s%d streets%s found, choose a street to continue... %s\n",
                  og, cy, lb, strts_in_cross, cy, er);                                                      // Print cross found fbk
          printf("\n    %s[1] %s%s,   %s[2] %s%s,   %s[3] %s%s,   %s[4] %s%s%s",
                rd, og, nav_strt.connection.conn.cross[FIRST].name,
                rd, og, nav_strt.connection.conn.cross[SECOND].name,
                rd, og, nav_strt.connection.conn.cross[THIRD].name,
                rd, og, nav_strt.connection.conn.cross[FOURTH].name, er);                                   // Print streets in cross options fbk
          printf("\n\n%s    --> %sChoose a street to continue %s(max 2 numbers, value between 1 and %d)%s: ",
                  og, bl, lgn, strts_in_cross, bl);                                                         // Print choose street in cross to continue navigation fbk
          scanf("%2[^\n]", in_buff);                                                                        // Reads the string 'till '\n' char, avoidin' scanf stop at space char and saving '\n' chr (str var definition) --> avoid buffer overflow assigning max input str size to 3-1 for '\0' char
          while ((getchar()) != '\n');                                                                      // Instruction to clear input buffer when buffer overflow occurs, avoiding to save next char as new input
          sel_srtr = atoi(in_buff);                                                                         // String conversion to byte and val save into selected street var
        }
        nav_strt = nav_strt.connection.conn.cross[sel_srtr-1];                                              // Proceed going into selected street
        break;
      default:                                                                                              // Default-case connection type
        printf("\n%s    Error in street connection definition! Unknown connection type!%s\n", rd, er);      // Unknown connection type error fbk
        break;
    }
    delay(1000);                                                                                            // Delay [ms] function call
  }
  printf("    %s\n", nav_strt.name);                                                                        // Last street name fbk
  printf("\n%s    Navigation completed, the road trip is terminated%s\n", og, er);                          // Navigation completed fbk
}
