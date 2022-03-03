/*
 * Author: Cristian Merli
 * Code title: UI (terminal I/O) library
 * Code version: 3.0
 * Creation date: 03/02/2022
 * Last mod. date: 03/02/2022
 */


/* Libraries */
#include "lib_ui.h"                                                                                         // Import UI (terminal I/O) library header file


/* Public functions */
void fbk_nl(C_int num){                                                                                     // Funct to print new-lines fbk
  for (int i = 0; i < num; ++i)                                                                             // Printin' FOR cycle
    std::cout << std::endl;                                                                                 // Print new lines fbk
}


void logo(Cu_shrt start_sp, C_str txt, C_str txt_col, C_char bkg_chr, C_str bkg_col){                       // Funct to print responsive-logo
  // Terminal defs
  struct winsize w;                                                                                         // Window-size struct declaration
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);                                                                     // Save the number of terminal's rows/cloumns in window-size struct
  Cu_shrt vthck = (w.ws_row/5);                                                                             // Logo bkg vertical thickness calc
  Cu_shrt lthck = (w.ws_col/6);                                                                             // Logo bkg lateral thickness calc
  Cu_shrt lsp = (U_shrt)(w.ws_col-2*lthck-2*start_sp-strlen(txt))/2;                                        // Logo internal lateral spaces calc
  Cu_shrt len = (U_shrt)(2*lthck+2*lsp+strlen(txt));                                                        // Logo length calc
  // Print logo
  printf("\n%s", bkg_col);                                                                                  // New line fbk
  for (U_shrt i = 0; i < (4*vthck+1); ++i){                                                                 // Logo lines print FOR cycle
    for (U_shrt j = 0; j < start_sp; ++j)                                                                   // Initial spaces print FOR cycle
      std::cout << ' ';                                                                                     // Print initial spaces
    if ((i < vthck || i > (3*vthck)) && (i != (4*vthck)/2)){                                                // Full bkg logo lines print cond
      for (U_shrt h = 0; h < len; ++h)                                                                      // Full bkg logo lines print FOR cycle
        printf("%c", bkg_chr);                                                                              // Bkg logo char print
      fbk_nl(1);                                                                                            // New line fbk funct call
    } else if ((i >= vthck && i <= (3*vthck)) && (i != (4*vthck)/2)){                                       // Partial-empty bkg logo lines print cond
      for (U_shrt l = 0; l < lthck; ++l)                                                                    // Partial-empty bkg logo lines, initial full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Partial-empty bkg logo lines, initial full part print
      for (U_shrt m = 0; m < (len-2*lthck); ++m)                                                            // Partial-empty bkg logo lines, central empty part print FOR cycle
        std::cout << ' ';                                                                                   // Partial-empty bkg logo lines, central empty part print
      for (U_shrt n = 0; n < lthck; ++n)                                                                    // Partial-empty bkg logo lines, final full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Partial-empty bkg logo lines, final full part print
      fbk_nl(1);                                                                                            // New line fbk funct call
    } else if (i == ((4*vthck)/2)){                                                                         // Text logo line initial full part print cond
      for (U_shrt o = 0; o < lthck; ++o)                                                                    // Text logo line initial full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Text logo line initial full part print
      for (U_shrt p = 0; p < lsp; ++p)                                                                      // Text logo line central empty part print FOR cycle
        std::cout << ' ';                                                                                   // Text logo line central empty part print
      printf("%s%s%s", txt_col, txt, bkg_col);                                                              // Text logo line central text part print
      for (U_shrt q = 0; q < lsp; ++q)                                                                      // Text logo line central empty part print FOR cycle
        std::cout << ' ';                                                                                   // Text logo line central empty part print
      for (U_shrt r = 0; r < lthck; ++r)                                                                    // Text logo line final full part print FOR cycle
        printf("%c", bkg_chr);                                                                              // Text logo line final full part print
      fbk_nl(1);                                                                                            // New line fbk funct call
    }
  }
  printf(ER);                                                                                               // New line fbk and erase logo bkg color
}


void fbk_gn_cy(CStr fbk_str){                                                                               // Funct to print green-cyan feedback
  std::cout << GN << ">>> " << CY << fbk_str << ER;                                                         // Print green-cyan string fbk
  fbk_nl(1);                                                                                                // New line fbk funct call
}


void close_err(){                                                                                           // Funct to close software with error fbk
  fbk_nl(1);                                                                                                // New line fbk funct call
  std::cout << OG << ">>> " << RD << "Closin' due to error..." << CY << " Sorry! " << OG << ":(" << ER;     // Closin' due to error fbk
  fbk_nl(1);                                                                                                // New line fbk funct call
  exit(EXIT_FAILURE);                                                                                       // Close software
}


void close_bye(){                                                                                           // Funct to close software with bye fbk
  fbk_nl(1);                                                                                                // New line fbk funct call
  std::cout << GN << ">>> " << PU << "Closin'..." << CY << " Bye! " << RD << ";)" << ER;                    // Closin' fbk
  fbk_nl(1);                                                                                                // New line fbk funct call
  exit(EXIT_SUCCESS);                                                                                       // Close software
}
