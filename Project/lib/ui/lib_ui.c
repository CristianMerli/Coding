/*
 * Author: Cristian Merli
 * Code title: UI (terminal I/O) library
 * Code version: 3.0
 * Creation date: 06/05/2021
 * Last mod. date: 03/07/2021
 */


/* Libraries */
#include "lib_ui.h"                                                                                         // Import UI (terminal I/O) library header file


/* Global vars */
char term_in_buff[IN_BUFF_SIZE] = "";                                                                       // Terminal input buffer char array for scanf func
int unused __attribute__((unused));                                                                         // Unused var


/* Functions */
void logo(Cu_shrt start_sp, C_str txt, C_str txt_col, C_char bkg_chr, C_str bkg_col){                       // Print responsive-logo function
  /* Body */
  struct winsize w;                                                                                         // Window-size struct declaration
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);                                                                     // Save the number of terminal's rows/cloumns in window-size struct
  Cu_shrt vthck = (w.ws_row / 5);                                                                           // Logo bkg vertical thickness calc
  Cu_shrt lthck = (w.ws_col / 6);                                                                           // Logo bkg lateral thickness calc
  Cu_shrt lsp = (Cu_shrt)(w.ws_col - 2*lthck - 2*start_sp - (Cu_shrt)strlen(txt)) / 2;                      // Logo internal lateral spaces calc
  Cu_shrt len = (Cu_shrt)(2*lthck+2*lsp+(Cu_shrt)strlen(txt));                                              // Logo length calc
  // Print logo
  printf("\n%s", bkg_col);                                                                                  // New line fbk
  for (U_shrt i = 0; i < (4*vthck+1); ++i){                                                                 // Logo lines print FOR cycle
    for (U_shrt j = 0; j < start_sp; ++j){                                                                  // Initial spaces print FOR cycle
      printf(" ");                                                                                          // Print initial spaces
    }
    if ((i < vthck || i > (3*vthck)) && (i != (4*vthck)/2)){                                                // Full bkg logo lines print cond
      for (U_shrt h = 0; h < len; ++h){                                                                     // Full bkg logo lines print FOR cycle
        printf("%c", bkg_chr);                                                                              // Bkg logo char print
      }
      fbk_nl(1);                                                                                            // New line feedback function call
    } else if ((i >= vthck && i <= (3*vthck)) && (i != (4*vthck)/2)) {                                      // Partial-empty bkg logo lines print cond
      for (U_shrt l = 0; l < lthck; ++l){                                                                   // Partial-empty bkg logo lines, initial full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Partial-empty bkg logo lines, initial full part print
      }
      for (U_shrt m = 0; m < (len - 2*lthck); ++m){                                                         // Partial-empty bkg logo lines, central empty part print FOR cycle
        printf(" ");                                                                                        // Partial-empty bkg logo lines, central empty part print
      }
      for (U_shrt n = 0; n < lthck; ++n){                                                                   // Partial-empty bkg logo lines, final full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Partial-empty bkg logo lines, final full part print
      }
      fbk_nl(1);                                                                                            // New line feedback function call
    } else if (i == ((4*vthck)/2)) {                                                                        // Text logo line initial full part print cond
      for (U_shrt o = 0; o < lthck; ++o){                                                                   // Text logo line initial full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Text logo line initial full part print
      }
      for (U_shrt p = 0; p < lsp; ++p){                                                                     // Text logo line central empty part print FOR cycle
        printf(" ");                                                                                        // Text logo line central empty part print
      }
      printf("%s%s%s", txt_col, txt, bkg_col);                                                              // Text logo line central text part print
      for (U_shrt q = 0; q < lsp; ++q){                                                                     // Text logo line central empty part print FOR cycle
        printf(" ");                                                                                        // Text logo line central empty part print
      }
      for (U_shrt r = 0; r < lthck; ++r){                                                                   // Text logo line final full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Text logo line final full part print
      }
      fbk_nl(1);                                                                                            // New line feedback function call
    }
  }
  printf(ER);                                                                                               // New line fbk and erase logo bkg color
}


void press_enter(C_str req_str){                                                                            // Press enter function
  /* Body */
  printf("\n\n%s>>>%s %s! %sPress %sENTER%s to contine... %s;)%s",
          GN, PU, req_str, CY, YE, CY, RD, ER);                                                             // Build map, press enter key to start fbk
  read_term_in();                                                                                           // Wait enter key to start (read terminal input function call)
}


void fbk_nl(C_int num){                                                                                     // New line feedback function
  /* Body */
  for (int i = 0; i < num; ++i)
    printf("\n");                                                                                           // Print new line fbk
}


void fbk_gn_cy(C_str fbk_str){                                                                              // Green-cyan feedback function
  /* Body */
  printf("%s>>>%s %s%s", GN, CY, fbk_str, ER);                                                              // Print green-cyan string fbk
}


void fbk_gn_pu(C_str fbk_str){                                                                              // Green-purple feedback function
  /* Body */
  printf("%s>>>%s %s%s", GN, PU, fbk_str, ER);                                                              // Print green-purple string fbk
}


void fbk_gn_lbu_ye_int(C_str prfx_str_lbu, C_int val_ye){                                                   // Green-lightblue-yellow int val feedback function
  /* Body */
  printf("%s>>>%s %s: %s%d%s", GN, LBU, prfx_str_lbu, YE, val_ye, ER);                                      // Print green-lightblue-yellow int val feedback
}


void fbk_gn_lbu_ye_str(C_str prfx_str_lbu, C_str str_ye){                                                   // Green-lightblue-yellow str val feedback function
  /* Body */
  printf("%s>>>%s %s: %s%s%s", GN, LBU, prfx_str_lbu, YE, str_ye, ER);                                      // Print green-lightblue-yellow str val feedback
}


void fbk_gn_lbu_ye_real(C_str prfx_str_lbu, C_real val_ye){                                                 // Green-lightblue-yellow real val feedback function
  /* Body */
  printf("%s>>>%s %s: %s%g%s", GN, LBU, prfx_str_lbu, YE, val_ye, ER);                                      // Print green-lightblue-yellow real val feedback
}


void fbk_gn_lbu_ye_lreal(C_str prfx_str_lbu, Cl_real val_ye){                                               // Green-lightblue-yellow long real val feedback function
  /* Body */
  printf("%s>>>%s %s: %s%Lg%s", GN, LBU, prfx_str_lbu, YE, val_ye, ER);                                     // Print green-lightblue-yellow long real val feedback
}


void fbk_gn_lbu_ye_ptr(C_str prfx_str_lbu, C_ptr val_ye){                                                   // Green-lightblue-yellow ptr val feedback function
  /* Body */
  printf("%s>>>%s %s: %s%p%s", GN, LBU, prfx_str_lbu, YE, val_ye, ER);                                      // Print green-lightblue-yellow ptr val feedback
}


void fbk_err(C_str fbk_str){                                                                                // Error feedback function
  /* Body */
  printf("\n%s>>>%s %s!%s\n", OG, RD, fbk_str, ER);                                                         // Print error fbk
}


Str read_term_in(){                                                                                         // Read terminal input function
  /* Body */
  unused = scanf("%30[^\n]", term_in_buff);                                                                 // Reads the string 'till '\n' char, avoidin' scanf stop at space char and saving '\n' chr (str var definition) --> avoid buffer overflow assigning max input str size to (31-1)=30 for '\0' char
  while ((getchar()) != '\n');                                                                              // Instruction to clear input buffer when buffer overflow occurs, avoiding to save next char as new input
  return term_in_buff;                                                                                      // Return terminal input string
}


Str read_term_in_min_chrs(C_byte min_chrs, C_str req_str, C_str err_str){                                   // Read terminal input (min chars) function
  /* Body */
  Str in_str;                                                                                               // Terminal input string tmp var
  Byte exit_flg = 0;                                                                                        // Terminal input while-loop exit flag
  // Read input from terminal
  do{
    clr_term_in();                                                                                          // Clear terminal input buffer function call
    printf("%s>>>%s %s,%s at least %s%d%s char(s), max %s%d%s chars%s: %s",
            GN, PU, req_str, BU, OG, min_chrs, BU, OG, IN_BUFF_SIZE-1, BU, PU, ER);                         // Print request fbk
    in_str = read_term_in();                                                                                // Read terminal input function call
    exit_flg = (strlen(in_str) >= min_chrs);                                                                // Terminal input while-loop exit flag val upd
    // Chk xit flg
    if (!exit_flg)                                                                                          // Exit flag val chack
      printf("%s>>>%s %s must be at least %s%d%s char(s) long!%s\n",
              OG, RD, err_str, YE, min_chrs, RD, ER);                                                       // Print terminal input error fbk
  } while(!exit_flg);                                                                                       // Check while-loop exit flag val
  
  return in_str;                                                                                            // Return terminal input string
}


Confirm read_term_in_confirm(C_str req_str){                                                                // Read terminal input confirmation function
  /* Body */
  Str in_str;                                                                                               // Terminal input string tmp var
  Confirm answ;                                                                                             // Confirmation answer
  Byte exit_flg = 0;                                                                                        // Terminal input while-loop exit flag
  // Read input from terminal
  do{
    clr_term_in();                                                                                          // Clear terminal input buffer function call
    printf("%s>>>%s %s?%s Options %s(yes/no/cancel)%s%s: %s", GN, PU, req_str, BU, OG, BU, PU, ER);         // Print request fbk
    in_str = read_term_in();                                                                                // Read terminal input function call
    if (0 == strcmp(in_str, "yes") || 0 == strcmp(in_str, "YES") || 0 == strcmp(in_str, "Yes")){            // YES answer
      answ = YES;                                                                                           // Set answer = YES
      ++exit_flg;                                                                                           // Set exit flag
    } else if (0 == strcmp(in_str, "no") || 0 == strcmp(in_str, "NO") ||
               0 == strcmp(in_str, "No") || 0 == strcmp(in_str, "nO")){                                     // NO answer
      answ = NO;                                                                                            // Set answer = NO
      ++exit_flg;                                                                                           // Set exit flag
    } else if(0 == strcmp(in_str, "cancel") || 0 == strcmp(in_str, "CANCEL") ||
              0 == strcmp(in_str, "Cancel")){                                                               // CANCEL answer
      answ = CANCEL;                                                                                        // Set answer = CANCEL
      ++exit_flg;                                                                                           // Set exit flag
    }
    // Chk xit flg
    if (!exit_flg)                                                                                          // Exit flag val chack
      printf("%s>>>%s The answer must be %s(yes/no/cancel)%s!%s\n", OG, RD, YE, RD, ER);                    // Print terminal input error fbk
  } while(!exit_flg);                                                                                       // Check while-loop exit flag val
  
  return answ;                                                                                              // Return confirmation answer
}


Str read_term_in_min_chrs_exit_chr(C_byte min_chrs, C_str req_str, C_str err_str, C_char exit_chr){         // Read terminal input (min chars and exit char) function
  /* Body */
  Str in_str;                                                                                               // Terminal input string tmp var
  Byte exit_flg = 0;                                                                                        // Terminal input while-loop exit flag
  // Read terminal input
  do{
    clr_term_in();                                                                                          // Clear terminal input buffer function call
    printf("%s>>>%s %s %s(at least %s%d%s char(s) and max %s%d%s, type %s'%c'%s char to continue)%s: %s",
            GN, PU, req_str, BU, OG, min_chrs, BU, OG, IN_BUFF_SIZE-1, BU, OG, exit_chr, BU, PU, ER);       // Print request fbk
    in_str = read_term_in();                                                                                // Read terminal input function call
    exit_flg = (strlen(in_str) >= min_chrs) || (*in_str == exit_chr);                                       // Terminal input while-loop exit flag val upd
    // Chk xit flg
    if (!exit_flg)                                                                                          // Exit flag val chack
      printf("%s>>>%s %s must be at least %s%d%s char(s) long!%s\n",
              OG, RD, err_str, YE, min_chrs, RD, ER);                                                       // Print terminal input error fbk
  } while(!exit_flg);                                                                                       // Check while-loop exit flag val
  
  return in_str;                                                                                            // Return terminal input string
}


int read_term_in_int(){                                                                                     // Read terminal input INT function
  /* Body */
  return atoi(read_term_in());                                                                              // Return integer conversion of input string
}


int read_term_in_int_inrange(C_int min_val, C_int max_val, C_str req_str, C_str err_str){                   // Read terminal input INT (in-range) function
  /* Body */
  int val = 0;                                                                                              // Terminal input value
  Byte exit_flg = 0;                                                                                        // Terminal input while-loop exit flag
  // Read terminal input
  do{
    clr_term_in();                                                                                          // Clear terminal input buffer function call
    printf("%s>>>%s %s %s(min %s%d%s, max %s%d%s and NOT %s0%s)%s: %s",
            GN, PU, req_str, BU, OG, min_val, BU, OG, max_val, BU, OG, BU, PU, ER);                         // Enter the number of crosses to allocate fbk
    val = read_term_in_int();                                                                               // Read terminal input INT function call
    exit_flg = (val >= min_val && val <= max_val && val != 0);                                              // Terminal input while-loop exit flag val upd
    // Chk xit flg
    if (!exit_flg)                                                                                          // Exit flag val chack
      printf("%s>>>%s %s must be in %s[%d, %d]%s range!%s\n",
              OG, RD, err_str, YE, min_val, max_val, RD, ER);                                               // Print terminal input error fbk
  } while(!exit_flg);                                                                                       // Check while-loop exit flag val
    
  return val;                                                                                               // Return terminal input val
}


void clr_term_in(){                                                                                         // Clear terminal input buffer function
  /* Body */
  strcpy(term_in_buff, "\0");                                                                               // Clear input buffer char array
}


void dbg(){                                                                                                 // Fast debug function
  /* Body */
  printf("\n\n%s    >>>>>> %s/*** DEBUG PRINT ***/%s\n\n", LGN, LGN, ER);                                   // Print debug line
}


void dbg_print(C_str str){                                                                                  // Debug print function
  /* Body */
  printf("\n\n%s    >>>>>>%s %s %s/*** DEBUG PRINT ***/%s\n\n", LGN, YE, str, LGN, ER);                     // Print debug line
}


void dbg_str(C_str str, C_str val){                                                                         // Debug string val print function
  /* Body */
  printf("\n\n%s    >>>>>>%s %s: %s%s %s/*** DEBUG PRINT ***/%s\n\n", LGN, YE, str, OG, val, LGN, ER);      // Print debug line
}


void dbg_int(C_str str, C_int val){                                                                         // Debug int val print function
  /* Body */
  printf("\n\n%s    >>>>>>%s %s: %s%d %s/*** DEBUG PRINT ***/%s\n\n", LGN, YE, str, OG, val, LGN, ER);      // Print debug line
}


void dbg_real(C_str str, C_real val){                                                                       // Debug real val print function
  /* Body */
  printf("\n\n%s    >>>>>>%s %s: %s%g %s/*** DEBUG PRINT ***/%s\n\n", LGN, YE, str, OG, val, LGN, ER);      // Print debug line
}


void dbg_lreal(C_str str, Cl_real val){                                                                     // Debug long real val print function
  /* Body */
  printf("\n\n%s    >>>>>>%s %s: %s%Lg %s/*** DEBUG PRINT ***/%s\n\n", LGN, YE, str, OG, val, LGN, ER);     // Print debug line
}


void dbg_ptr(C_str str, C_ptr val){                                                                         // Debug ptr val print function
  /* Body */
  printf("\n\n%s    >>>>>>%s %s: %s%p %s/*** DEBUG PRINT ***/%s\n\n", LGN, YE, str, OG, val, LGN, ER);      // Print debug line
}


void close_err(){                                                                                           // Close software with error function
  /* Body */
  printf("\n%s>>>%s Closin' due to error... %sSorry! %s:(%s\n", OG, RD, CY, OG, ER);                        // Closin' due to error fbk
  exit(EXIT_FAILURE);                                                                                       // Close software
}


void close_fbk(){                                                                                           // Close feedback function
  /* Body */
  printf("\n\n%s>>>%s Closin'... %sBye! %s;)%s\n", GN, PU, CY, RD, ER);                                     // Closin' fbk
}


void close_keyboard_interrupt(C_int signal){                                                                // Function to close SW with fbk due to keyboard interrupt detected (ctrl+c)
  /* Body */
  printf("\n\n%s>>>%s Keyboard interrupt detected, closin'... %sBye! %s;)%s\n", GN, PU, CY, RD, ER);        // Closin' fbk
  exit(signal);                                                                                             // Exit SW with signal
}
