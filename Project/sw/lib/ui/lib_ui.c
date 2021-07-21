/*
 * Author: Cristian Merli
 * Code title: UI (terminal I/O) library
 * Code version: 3.0
 * Creation date: 06/05/2021
 * Last mod. date: 13/07/2021
 */


/* Libraries */
#include "lib_ui.h"                                                                                         // Import UI (terminal I/O) library header file
#include <limits.h>                                                                                         // Include limits library (to check int/long terminal input values in limits)
#include <errno.h>                                                                                          // -


/* Public vars */
/// <b>Public-variable description:</b> Terminal-input buffer string variabile (size defined with #IN_BUFF_SIZE macro), mainly used by scanf() function in terminal-input reading operations.
char term_in_buff[IN_BUFF_SIZE] = "";                                                                       // Terminal input buffer char array for scanf func
/// <b>Public-variable description:</b> Unused variabile to avoid compile-errors when a function has an unused return value, like scanf().
int unused __attribute__((unused));                                                                         // Unused var


/* Public functions */
/*!
 * @brief               <p><b>Function description:</b></p> Function to print responsive-logo on terminal depending on teminal size.
 * 
 * @param[in] start_sp  Start (left) spaces in logo print; try to do the same on the right-side, rounding calculation result to integer value.
 * @param[in] txt       Title text string.
 * @param[in] txt_col   Title text color (requires color macro).
 * @param[in] bkg_chr   Logo backgroung char.
 * @param[in] bkg_col   Logo backgroung color (requires color macro).
 * 
 * @return              None.
 */
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


/*!
 * @brief         <p><b>Function description:</b></p> Function to print responsive text-separator on terminal depending on teminal size.
 * 
 * @param[in] chr Char to use in order to create the text-separator.
 * @param[in] col Color to use in order to create the text-separator (requires color macro).
 * 
 * @return        None.
 */
void fbk_separator(C_char chr, C_str col){                                                                  // Separator feedback function
  /* Body */
  struct winsize w;                                                                                         // Window-size struct declaration
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);                                                                     // Save the number of terminal's rows/cloumns in window-size struct
  for (int i = 0; i < w.ws_col; ++i)                                                                        // Chars printin' FOR cycle
    printf("%s%c%s", col, chr, ER);                                                                         // Print space fbk
}


/*!
 * @brief             <p><b>Function description:</b></p> Function to request 'ENTER' key button to start software with request string printing on terminal.
 * 
 * @param[in] req_str Request string to print when asking for 'ENTER' key to start software.
 * 
 * @return            None.
 */
void press_enter(C_str req_str){                                                                            // Press enter function
  /* Body */
  printf("\n\n%s>>>%s %s! %sPress %sENTER%s to contine... %s;)%s",
          GN, PU, req_str, CY, YE, CY, RD, ER);                                                             // Build map, press enter key to start fbk
  read_term_in();                                                                                           // Wait enter key to start (read terminal input function call)
}


/*!
 * @brief         <p><b>Function description:</b></p> Function to print new-lines feedback on terminal.
 * 
 * @param[in] num Number of new-lines to print.
 * 
 * @return        None.
 */
void fbk_nl(C_int num){                                                                                     // New lines feedback function
  /* Body */
  for (int i = 0; i < num; ++i)                                                                             // Chars printin' FOR cycle
    printf("\n");                                                                                           // Print new line fbk
}


/*!
 * @brief         <p><b>Function description:</b></p> Function to print spaces feedback on terminal.
 * 
 * @param[in] num Number of spaces to print.
 * 
 * @return        None.
 */
void fbk_spaces(C_int num){                                                                                 // Spces feedback function
  /* Body */
  for (int i = 0; i < num; ++i)                                                                             // Chars printin' FOR cycle
    printf(" ");                                                                                            // Print space fbk
}


/*!
 * @brief         <p><b>Function description:</b></p> Function to print tabs feedback on terminal.
 * 
 * @param[in] num Number of tabs to print.
 * 
 * @return        None.
 */
void fbk_tabs(C_int num){                                                                                   // Tabs feedback function
  /* Body */
  for (int i = 0; i < num; ++i)                                                                             // Chars printin' FOR cycle
    printf("\t");                                                                                           // Print tab fbk
}


/*!
 * @brief             <p><b>Function description:</b></p> Function to print green/purple feedback on terminal (generally used to print operation-start feedbacks).
 * 
 * @param[in] fbk_str Feedback string to print.
 * 
 * @return            None.
 */
void fbk_gn_pu(C_str fbk_str){                                                                              // Green-purple feedback function
  /* Body */
  printf("%s>>>%s %s%s", GN, PU, fbk_str, ER);                                                              // Print green-purple string fbk
}


/*!
 * @brief             <p><b>Function description:</b></p> Function to print green/cyan feedback on terminal (generally used to print operation-completed feedbacks).
 * 
 * @param[in] fbk_str Feedback string to print.
 * 
 * @return            None.
 */
void fbk_gn_cy(C_str fbk_str){                                                                              // Green-cyan feedback function
  /* Body */
  printf("%s>>>%s %s%s", GN, CY, fbk_str, ER);                                                              // Print green-cyan string fbk
}


/*!
 * @brief                   <p><b>Function description:</b></p> Function to print light-blue/yellow feedback on terminal (generally used to print integer feedbacks).
 * 
 * @param[in] prfx_str_lbu  Prefix feedback string to print (in light-blue color).
 * @param[in] val_ye        Integer value to print (in yellow color).
 * 
 * @return                  None.
 */
void fbk_gn_lbu_ye_int(C_str prfx_str_lbu, C_int val_ye){                                                   // Green-lightblue-yellow int val feedback function
  /* Body */
  printf("%s>>>%s %s: %s%d%s", GN, LBU, prfx_str_lbu, YE, val_ye, ER);                                      // Print green-lightblue-yellow int val feedback
}


/*!
 * @brief                   <p><b>Function description:</b></p> Function to print light-blue/yellow feedback on terminal (generally used to print string feedbacks).
 * 
 * @param[in] prfx_str_lbu  Prefix feedback string to print (in light-blue color).
 * @param[in] val_ye        String value to print (in yellow color).
 * 
 * @return                  None.
 */
void fbk_gn_lbu_ye_str(C_str prfx_str_lbu, C_str str_ye){                                                   // Green-lightblue-yellow str val feedback function
  /* Body */
  printf("%s>>>%s %s: %s%s%s", GN, LBU, prfx_str_lbu, YE, str_ye, ER);                                      // Print green-lightblue-yellow str val feedback
}


/*!
 * @brief                   <p><b>Function description:</b></p> Function to print light-blue/yellow feedback on terminal (generally used to print #Real feedbacks).
 * 
 * @param[in] prfx_str_lbu  Prefix feedback string to print (in light-blue color).
 * @param[in] val_ye        #Real value to print (in yellow color).
 * 
 * @return                  None.
 */
void fbk_gn_lbu_ye_real(C_str prfx_str_lbu, C_real val_ye){                                                 // Green-lightblue-yellow real val feedback function
  /* Body */
  printf("%s>>>%s %s: %s%g%s", GN, LBU, prfx_str_lbu, YE, val_ye, ER);                                      // Print green-lightblue-yellow real val feedback
}


/*!
 * @brief                   <p><b>Function description:</b></p> Function to print light-blue/yellow feedback on terminal (generally used to print #L_real feedbacks).
 * 
 * @param[in] prfx_str_lbu  Prefix feedback string to print (in light-blue color).
 * @param[in] val_ye        #L_real value to print (in yellow color).
 * 
 * @return                  None.
 */
void fbk_gn_lbu_ye_lreal(C_str prfx_str_lbu, Cl_real val_ye){                                               // Green-lightblue-yellow long real val feedback function
  /* Body */
  printf("%s>>>%s %s: %s%Lg%s", GN, LBU, prfx_str_lbu, YE, val_ye, ER);                                     // Print green-lightblue-yellow long real val feedback
}


/*!
 * @brief                   <p><b>Function description:</b></p> Function to print light-blue/yellow feedback on terminal (generally used to print #Ptr feedbacks).
 * 
 * @param[in] prfx_str_lbu  Prefix feedback string to print (in light-blue color).
 * @param[in] val_ye        #Ptr value to print (in yellow color).
 * 
 * @return                  None.
 */
void fbk_gn_lbu_ye_ptr(C_str prfx_str_lbu, C_ptr val_ye){                                                   // Green-lightblue-yellow ptr val feedback function
  /* Body */
  printf("%s>>>%s %s: %s%p%s", GN, LBU, prfx_str_lbu, YE, val_ye, ER);                                      // Print green-lightblue-yellow ptr val feedback
}


/*!
 * @brief             <p><b>Function description:</b></p> Function to print error feedback on terminal using red color.
 * 
 * @param[in] fbk_str Error feedback string to print (in red color with exclamation mark following).
 * 
 * @return            None.
 */
void fbk_err(C_str fbk_str){                                                                                // Error feedback function
  /* Body */
  printf("\n%s>>>%s %s!%s\n", OG, RD, fbk_str, ER);                                                         // Print error fbk
}


/*!
 * @brief   <p><b>Function description:</b></p> Function to read user terminal-input using buffer defined in library (#term_in_buff).
 * 
 * @return  Return user-input string inside #term_in_buff.
 */
Str read_term_in(){                                                                                         // Read terminal input function
  /* Body */
  unused = scanf("%30[^\n]", term_in_buff);                                                                 // Reads the string 'till '\n' char, avoidin' scanf stop at space char and saving '\n' chr (str var definition) --> avoid buffer overflow assigning max input str size to (31-1)=30 for '\0' char
  while ((getchar()) != '\n');                                                                              // Instruction to clear input buffer when buffer overflow occurs, avoiding to save next char as new input
  return term_in_buff;                                                                                      // Return terminal input string
}


/*!
 * @brief   <p><b>Function description:</b></p> Function to clear terminal-input buffer (#term_in_buff).
 * 
 * @return  None.
 */
void clr_term_in(){                                                                                         // Clear terminal input buffer function
  /* Body */
  strcpy(term_in_buff, "\0");                                                                               // Clear input buffer char array
}


/*!
 * @brief               <p><b>Function description:</b></p> Function to read user terminal-input expecting defined min number of chars.
 *                      In addition, print request string and eventually, error string (in case the number of expected chars has not been
 *                      reached - new request in loop until min number of expected chars has been reached).
 * 
 * @param[in] min_chrs  Min number of expected chars in user terminal-input.
 * @param[in] req_str   Request string to print in green/purple color.
 * @param[in] err_str   Error string to print in red color.
 * 
 * @return              Return user-input string from #read_term_in() function.
 */
Str read_term_in_min_chrs(C_byte min_chrs, C_str req_str, C_str err_str){                                   // Read terminal input (min chars) function
  /* Body */
  Str in_str;                                                                                               // Terminal input string tmp var
  Byte exit_flg = 0;                                                                                        // Terminal input while-loop exit flag
  // Read input from terminal
  do{
    clr_term_in();                                                                                          // Clear terminal input buffer function call
    printf("\n%s>>>%s %s,%s at least %s%d%s char(s), max %s%d%s chars%s: %s",
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


/*!
 * @brief               <p><b>Function description:</b></p> Function to read user terminal-input expecting defined min number of chars.
 *                      In addition, print request string and eventually, error string (in case the number of expected chars has not been
 *                      reached - new request in loop until min number of expected chars has been reached). Alternatively, exit acquisition
 *                      loop when exit-char is detected. 
 * 
 * @param[in] min_chrs  Min number of expected chars in user terminal-input.
 * @param[in] req_str   Request string to print in green/purple color.
 * @param[in] err_str   Error string to print in red color.
 * @param[in] exit_chr  Acquisition loop exit-char.
 * 
 * @return              Return user-input string from #read_term_in() function.
 */
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


/*!
 * @brief   <p><b>Function description:</b></p> Function to read integer terminal-input, converting string returned by #read_term_in() function using strtol().
 * 
 * @return  Terminal input string converted into integer (value in LONG/INT range and string correctly converted).
 */
int read_term_in_int(){                                                                                     // Read terminal input INT function
  /* Body */
  char *tmp_ptr = NULL;                                                                                     // Tmp ptr var to check str-long conversion OK
  long val = 0;                                                                                             // Long converted value (then casted into integer value)
  errno = 0;                                                                                                // Error lib-var
  Byte err_flg = 0;                                                                                         // Error flag to quit acqisition cycle
  // Read input from terminal
  do {
    fbk_nl(1);  fbk_gn_pu("Please insert a value: ");                                                       // Print acquisition request fbk
    val = strtol(read_term_in(), &tmp_ptr, 10);                                                             // Base-10 string-to-long conversion
    // Chk err flg rst cond
    if (err_flg != 0){                                                                                      // Check err flg val, if it requires reset
      err_flg = 0;                                                                                          // Rst it
    }
    if (tmp_ptr == term_in_buff){                                                                           // If no characters were converted these pointers are equal
      fbk_err("Ops! Encountered error during string to numerical value conversion from terminal-input");    // Print error fbk
      perror("Found error during string to value conversion using strtol()! Can't convert string!");        // Print perror fbk
      ++err_flg;                                                                                            // Set err flg
    } else if ((val == LONG_MAX || val == LONG_MIN) && errno == ERANGE){                                    // If sizeof(int) == sizeof(long), we have to explicitly check for overflows
      fbk_err("Ops! Encountered error during string to long value conversion from terminal-input");         // Print error fbk
      perror("Found error during string to long conversion using strtol()! Number out of range for LONG!"); // Print perror fbk
      ++err_flg;                                                                                            // Set err flg
    } else if (val > INT_MAX || val < INT_MIN){                                                             // Because strtol produces a long, check for overflow
      fbk_err("Ops! Encountered error during string to int value conversion from terminal-input");          // Print error fbk
      perror("Found error during string to int conversion using strtol()! Number out of range for INT!");   // Print perror fbk
      ++err_flg;                                                                                            // Set err flg
    }
  } while(err_flg != 0);                                                                                    // Check while-loop exit flag val (no errs)

  return (int)val;                                                                                          // Return integer conversion of input string
}


/*!
 * @brief   <p><b>Function description:</b></p> Function to read integer terminal-input in range (between min and max specified values - included), string to integer conversion with #read_term_in_int() function.
 * 
 * @param[in] min_val Min integer range limit value.
 * @param[in] max_val Max integer range limit value.
 * @param[in] req_str Request string to print in green/purple color.
 * @param[in] err_str Error string to print in red color.
 * 
 * @return  Return terminal input string converted into integer value, using function #read_term_in_int().
 */
int read_term_in_int_inrange(C_int min_val, C_int max_val, C_str req_str, C_str err_str){                   // Read terminal input INT (in-range) function
  /* Body */
  int val = 0;                                                                                              // Terminal input value
  Byte exit_flg = 0;                                                                                        // Terminal input while-loop exit flag
  // Read terminal input
  do{
    clr_term_in();                                                                                          // Clear terminal input buffer function call
    printf("%s>>>%s %s %s(min %s%d%s, max %s%d%s)%s... %s",
            GN, PU, req_str, BU, OG, min_val, BU, OG, max_val, BU, PU, ER);                                 // Enter the number of crosses to allocate fbk
    val = read_term_in_int();                                                                               // Read terminal input INT function call
    exit_flg = (val >= min_val && val <= max_val);                                                          // Terminal input while-loop exit flag val upd
    // Chk xit flg
    if (!exit_flg)                                                                                          // Exit flag val chack
      printf("%s>>>%s %s must be in %s[%d, %d]%s range!%s\n\n",
              OG, RD, err_str, YE, min_val, max_val, RD, ER);                                               // Print terminal input error fbk
  } while(!exit_flg);                                                                                       // Check while-loop exit flag val
    
  return val;                                                                                               // Return terminal input val
}


/*!
 * @brief             <p><b>Function description:</b></p> Function to read user terminal-input confirmation (YES/NO/CANEL).
 *                    In addition, print request string and eventually, standard error string (in case the of unexpected answer from #read_term_in() function).
 * 
 * @param[in] req_str Request string to print in green/purple color.
 * 
 * @return            Return user-defined confirmation (by means of #confirm enum).
 */
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


/*!
 * @brief   <p><b>Function description:</b></p> Function to print debug symbol on terminal (light-green colored debug feedback).
 * 
 * @return  None.
 */
void dbg(){                                                                                                 // Fast debug function
  /* Body */
  printf("\n\n%s    >>>>>> %s/*** DEBUG PRINT ***/%s\n\n", LGN, LGN, ER);                                   // Print debug line
}


/*!
 * @brief         <p><b>Function description:</b></p> Function to print debug feedback on terminal (light-green/yellow colored debug feedback).
 * 
 * @param[in] str String value to print (in yellow color).
 * 
 * @return        None.
 */
void dbg_print(C_str str){                                                                                  // Debug print function
  /* Body */
  printf("\n\n%s    >>>>>>%s %s %s/*** DEBUG PRINT ***/%s\n\n", LGN, YE, str, LGN, ER);                     // Print debug line
}


/*!
 * @brief         <p><b>Function description:</b></p> Function to print string debug feedback on terminal (light-green/yellow/orange colored debug feedback).
 * 
 * @param[in] str String to print (in yellow color).
 * @param[in] val String value to print (in orange color)
 * 
 * @return        None.
 */
void dbg_str(C_str str, C_str val){                                                                         // Debug string val print function
  /* Body */
  printf("\n\n%s    >>>>>>%s %s: %s%s %s/*** DEBUG PRINT ***/%s\n\n", LGN, YE, str, OG, val, LGN, ER);      // Print debug line
}


/*!
 * @brief         <p><b>Function description:</b></p> Function to print integer debug feedback on terminal (light-green/yellow/orange colored debug feedback).
 * 
 * @param[in] str String to print (in yellow color).
 * @param[in] val Integer value to print (in orange color)
 * 
 * @return        None.
 */
void dbg_int(C_str str, C_int val){                                                                         // Debug int val print function
  /* Body */
  printf("\n\n%s    >>>>>>%s %s: %s%d %s/*** DEBUG PRINT ***/%s\n\n", LGN, YE, str, OG, val, LGN, ER);      // Print debug line
}


/*!
 * @brief         <p><b>Function description:</b></p> Function to print #Real debug feedback on terminal (light-green/yellow/orange colored debug feedback).
 * 
 * @param[in] str String to print (in yellow color).
 * @param[in] val #Real value to print (in orange color)
 * 
 * @return        None.
 */
void dbg_real(C_str str, C_real val){                                                                       // Debug real val print function
  /* Body */
  printf("\n\n%s    >>>>>>%s %s: %s%g %s/*** DEBUG PRINT ***/%s\n\n", LGN, YE, str, OG, val, LGN, ER);      // Print debug line
}


/*!
 * @brief         <p><b>Function description:</b></p> Function to print #L_real debug feedback on terminal (light-green/yellow/orange colored debug feedback).
 * 
 * @param[in] str String to print (in yellow color).
 * @param[in] val #L_real value to print (in orange color)
 * 
 * @return        None.
 */
void dbg_lreal(C_str str, Cl_real val){                                                                     // Debug long real val print function
  /* Body */
  printf("\n\n%s    >>>>>>%s %s: %s%Lg %s/*** DEBUG PRINT ***/%s\n\n", LGN, YE, str, OG, val, LGN, ER);     // Print debug line
}


/*!
 * @brief         <p><b>Function description:</b></p> Function to print #Ptr debug feedback on terminal (light-green/yellow/orange colored debug feedback).
 * 
 * @param[in] str String to print (in yellow color).
 * @param[in] val #Ptr value to print (in orange color)
 * 
 * @return        None.
 */
void dbg_ptr(C_str str, C_ptr val){                                                                         // Debug ptr val print function
  /* Body */
  printf("\n\n%s    >>>>>>%s %s: %s%p %s/*** DEBUG PRINT ***/%s\n\n", LGN, YE, str, OG, val, LGN, ER);      // Print debug line
}


/*!
 * @brief         <p><b>Function description:</b></p> Function to close software with error feedback on terminal before closing (red colored error feedback).
 * 
 * @return        None.
 */
void close_err(){                                                                                           // Function to close software with error feedback
  /* Body */
  printf("\n%s>>>%s Closin' due to error... %sSorry! %s:(%s\n", OG, RD, CY, OG, ER);                        // Closin' due to error fbk
  exit(EXIT_FAILURE);                                                                                       // Close software
}


/*!
 * @brief         <p><b>Function description:</b></p> Function to close software with goodbye feedback on terminal before closing (multicolor closing feedback).
 * 
 * @return        None.
 */
void close_fbk(){                                                                                           // Function to close software with feedback
  /* Body */
  printf("\n\n%s>>>%s Closin'... %sBye! %s;)%s\n", GN, PU, CY, RD, ER);                                     // Closin' fbk
  exit(EXIT_SUCCESS);                                                                                       // Close software
}


/*!
 * @brief             <p><b>Function description:</b></p> Function to manage close keyboard interrupt signal, printing feedback to terminal and closing software with 'signal' value.
 *                    Function called by #terminate_keyboard() routine.
 * 
 * @param[in] signal  Keyboard interrupt signal.
 * 
 * @return            None.
 */
void close_keyboard_interrupt(C_int signal){                                                                // Function to close SW with fbk due to keyboard interrupt detected (ctrl+c)
  /* Body */
  printf("\n\n%s>>>%s Keyboard interrupt detected, closin'... %sBye! %s;)%s\n", GN, PU, CY, RD, ER);        // Closin' fbk
  exit(signal);                                                                                             // Exit SW with signal
}
