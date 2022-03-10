/*
 * Author: Cristian Merli
 * Code title: UI (terminal I/O) library
 * Code version: 3.0
 * Creation date: 03/02/2022
 * Last mod. date: 09/02/2022
 */


/* Libraries */
#include "lib_ui.h"                                                                                         // Import UI (terminal I/O) library header file


/* Public vars */
int unused __attribute__((unused));                                                                         // Unused var


/* Public functions */
void fbk_nl(C_integer num){                                                                                 // Funct to print new-lines fbk
  for (int i=0; i<num; ++i)                                                                                 // Printin' cycle
    std::cout << std::endl;                                                                                 // Print new lines fbk
}


void term_print(C_string fbk_str, Fbk typ){                                                                 // Funct to print on terminal (default=FBK)
  std::cout << (typ==ERR ? YE : (typ==REQ ? OG : GN)) << ">>> " << (typ==ERR ? RD : (typ==REQ ? CY : PU));  // Print on terminal
  std::cout  << fbk_str << (typ==REQ ? " and then press \033[0;34m'ENTER'\033[0;36m: " : "\n") << ER;       // Print on terminal
}


void title(CU_short start_sp, C_string txt, C_string txt_col, C_byte bkg_chr, C_string bkg_col){            // Funct to print responsive-title
  // Terminal defs
  struct winsize w;                                                                                         // Window-size struct declaration
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);                                                                     // Save the number of terminal's rows/columns in window-size struct
  CU_short vthck = (w.ws_row/5);                                                                            // Title bkg vertical thickness calc
  CU_short lthck = (w.ws_col/6);                                                                            // Title bkg lateral thickness calc
  CU_short lsp = (U_short)(w.ws_col-2*lthck-2*start_sp-txt.length())/2;                                     // Title internal lateral spaces calc
  CU_short len = (U_short)(2*lthck+2*lsp+txt.length());                                                     // Title length calc
  // Title printin'
  std::cout << std::endl << bkg_col;                                                                        // New line fbk
  for (U_short i=0; i<(4*vthck+1); ++i){                                                                    // Title lines printin' cycle
    for (U_short j=0; j<start_sp; ++j)                                                                      // Initial spaces printin' cycle
      std::cout << ' ';                                                                                     // Print initial spaces
    if ((i<vthck || i>(3*vthck)) && i!=(4*vthck)/2){                                                        // Full bkg title lines print cond
      for (U_short h=0; h<len; ++h)                                                                         // Full bkg title lines printin' cycle
        std::cout << bkg_chr;                                                                               // Bkg title char print
      fbk_nl(1);                                                                                            // New line
    } else if ((i>=vthck && i<=(3*vthck)) && i!=(4*vthck)/2){                                               // Partial-empty bkg title lines print cond
      for (U_short l=0; l < lthck; ++l)                                                                     // Partial-empty bkg title lines, initial full part printin' cycle
        std::cout << bkg_chr;                                                                               // Partial-empty bkg title lines, initial full part print
      for (U_short m=0; m<(len-2*lthck); ++m)                                                               // Partial-empty bkg title lines, central empty part printin' cycle
        std::cout << ' ';                                                                                   // Partial-empty bkg title lines, central empty part print
      for (U_short n=0; n<lthck; ++n)                                                                       // Partial-empty bkg title lines, final full part printin' cycle
        std::cout << bkg_chr;                                                                               // Partial-empty bkg title lines, final full part print
      fbk_nl(1);                                                                                            // NeNew line
    } else if (i==(4*vthck)/2){                                                                             // Text title line initial full part print cond
      for (U_short o=0; o<lthck; ++o)                                                                       // Text title line initial full part printin' cycle
        std::cout << bkg_chr;                                                                               // Text title line initial full part print
      for (U_short p=0; p<lsp; ++p)                                                                         // Text title line central empty part printin' cycle
        std::cout << ' ';                                                                                   // Text title line central empty part print
      std::cout << txt_col << txt << bkg_col;                                                               // Text title line central text part print
      for (U_short q=0; q<lsp; ++q)                                                                         // Text title line central empty part printin' cycle
        std::cout << ' ';                                                                                   // Text title line central empty part print
      for (U_short r=0; r<lthck; ++r)                                                                       // Text title line final full part printin' cycle
        std::cout << bkg_chr;                                                                               // Text title line final full part print
      fbk_nl(1);                                                                                            // New line
    }
  }
  std::cout << ER << std::endl;                                                                             // New line fbk and erase title bkg color
  term_print("\033[0;35mWelcome to the \033[1;33m'"+txt+"'\033[0;35m software! \033[1;33m;)\033[0;35m\n");  // Print welcome fbk
}


void int_term_print(C_string str, C_integer val){                                                           // Funct to print integer value
  std::cout << GN << ">>> " << PU << str << ": " << LBU << val << std::endl << ER;                          // Print on terminal
}


Integer int_usr_in(C_string req_str){                                                                       // Funct to get integer user input value
  Integer usr_in=0;                                                                                         // Usr-in integer val
  while (true){                                                                                             // Cycle 'till acq-value is ok
    term_print(req_str, REQ);                                                                               // Print req
    if(std::cin >> usr_in){                                                                                 // Chk in val
      int_term_print("Value correctly acquired, inserted value", usr_in);                                   // Print inserted val
      break;                                                                                                // Xit acq-cycle
    } else {                                                                                                // If in-val ain't ok
      term_print("Invalid value! Please, retry...", ERR);                                                   // Print err
      std::cin.clear();                                                                                     // Clr in-buff
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');                                   // Ignore other chars and repeat req
    }
  }
  return usr_in;                                                                                            // Ret usr-in integer val
}


void close_err(){                                                                                           // Funct to close software with error fbk
  std::cout << std::endl << OG << ">>> " << RD << "Closin' due to error...";                                // Closin' due to error fbk
  std::cout << CY << " Sorry! " << OG << ":(" << ER << std::endl;                                           // Closin' due to error fbk
  exit(EXIT_FAILURE);                                                                                       // Close software
}


void close_bye(){                                                                                           // Funct to close software with bye fbk
  std::cout << std::endl << GN << ">>> " << PU << "Closin'...";                                             // Closin' fbk
  std::cout << CY << " Bye! " << RD << ";)" << ER << std::endl;                                             // Closin' fbk
  exit(EXIT_SUCCESS);                                                                                       // Close software
}
