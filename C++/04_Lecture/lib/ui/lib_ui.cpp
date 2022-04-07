/*
 * Author: Cristian Merli
 * Code title: UI (terminal I/O) library
 * Code version: 3.0
 * Creation date: 07/04/2022
 * Last mod. date: 07/04/2022
 */


/* Dependencies */
#include "lib_ui.h"                                                                                         // Import UI (terminal I/O) library header file


/* Public vars */
Integer unused __attribute__((unused));                                                                     // Unused var


/* Private templates */
template <typename T>                                                                                       // Template T
void get_val_impl(C_string req_str, void *const val){                                                       // Funct impl to get user input value from terminal
  T *usr_in=(T *)val;                                                                                       // Define user input ptr (template data-type)
  do {                                                                                                      // Acq cycle
    term_print(req_str, REQ);                                                                               // Print req
    if (std::cin >> *usr_in){                                                                               // Chk in val
      PRINT_VAL("Value correctly acquired, inserted value", *usr_in);                                       // Print inserted val
      break;                                                                                                // Xit acq cycle
    } else {                                                                                                // If in-val ain't ok
      term_print("Invalid value! Please, retry...", ERR);                                                   // Print err
      std::cin.clear();                                                                                     // Clr in-buff
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');                                   // Ignore other chars and repeat req
    }
  } while (true);                                                                                           // Acq cycle xit cond managed usin' break
}


/* Public functions */
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
    for (U_short j=0; j<start_sp; ++j) std::cout << SP;                                                     // Initial spaces printin' cycle
    if ((i<vthck || i>(3*vthck)) && i!=(4*vthck)/2){                                                        // Full bkg title lines print cond
      for (U_short h=0; h<len; ++h) std::cout << bkg_chr;                                                   // Full bkg title lines printin' cycle and bkg title char print
    } else if ((i>=vthck && i<=(3*vthck)) && i!=(4*vthck)/2){                                               // Partial-empty bkg title lines print cond
      for (U_short l=0; l < lthck; ++l) std::cout << bkg_chr;                                               // Partial-empty bkg title lines, initial full part printin' cycle
      for (U_short m=0; m<(len-2*lthck); ++m) std::cout << SP;                                              // Partial-empty bkg title lines, central empty part printin' cycle
      for (U_short n=0; n<lthck; ++n) std::cout << bkg_chr;                                                 // Partial-empty bkg title lines, final full part printin' cycle
    } else if (i==(4*vthck)/2){                                                                             // Text title line initial full part print cond
      for (U_short o=0; o<lthck; ++o) std::cout << bkg_chr;                                                 // Text title line initial full part printin' cycle
      for (U_short p=0; p<lsp; ++p) std::cout << SP;                                                        // Text title line central empty part printin' cycle
      std::cout << txt_col << txt << bkg_col;                                                               // Text title line central text part print
      for (U_short q=0; q<lsp; ++q) std::cout << SP;                                                        // Text title line central empty part printin' cycle
      for (U_short r=0; r<lthck; ++r) std::cout << bkg_chr;                                                 // Text title line final full part printin' cycle
    }
    FBK_NL(1);                                                                                              // New line
  }
  std::cout << ER << std::endl;                                                                             // New line fbk and erase title bkg color
  term_print("\033[0;35mWelcome to the \033[1;33m'"+txt+"'\033[0;35m software! \033[1;33m;)\033[0;35m\n");  // Print welcome fbk
}


void term_print(C_string fbk_str, const Fbk typ){                                                           // Funct to print on terminal (default=FBK)
  std::cout << (typ==ERR ? YE : (typ==REQ ? OG : GN)) << ">>> " << (typ==ERR ? RD : (typ==REQ ? CY : PU));  // Print on terminal
  std::cout  << fbk_str << (typ==REQ ? " and then press \033[0;34m'ENTER'\033[0;36m: " : "\n") << ER;       // Print on terminal
}


void get_val(C_string req_str, const Data typ, void *const val){                                            // Funct impl to get user input value from terminal
  switch (typ){                                                                                             // Data-type switch-case
  case REAL: get_val_impl<Real>(req_str, val); break;                                                       // Real data-type template call
  case INTEGER: get_val_impl<Integer>(req_str, val); break;                                                 // Integer data-type template call
  case SHORT: get_val_impl<Short>(req_str, val); break;                                                     // Short data-type template call
  case BYTE: get_val_impl<Byte>(req_str, val); break;                                                       // Byte data-type template call
  case STRING: get_val_impl<String>(req_str, val); break;                                                   // String data-type template call
  case CHARACTER: get_val_impl<Character>(req_str, val); break;                                             // Character data-type template call
  default: term_print("Error, unknown data-type enum value specified in get_val() funct call!", ERR);       // Unknown data-type err print
  }
}


void close_err(C_string err_str){                                                                           // Funct to close software with error fbk
  if (err_str!="") {FBK_NL(1); term_print(err_str, ERR);}                                                   // Print err str
  std::cout << std::endl << YE << ">>> " << RD << "Closin' due to error...";                                // Closin' due to error fbk
  std::cout << CY << " Sorry! " << OG << ":(" << ER << std::endl << std::endl;                              // Closin' due to error fbk
  exit(EXIT_FAILURE);                                                                                       // Close software with OK code
}


void close_bye(C_string bye_str){                                                                           // Funct to close software with bye fbk
  if (bye_str!="") {FBK_NL(1); term_print(bye_str);}                                                        // Print bye str
  std::cout << std::endl << GN << ">>> " << PU << "Closin'...";                                             // Closin' fbk
  std::cout << CY << " Bye! " << OG << ";)" << ER << std::endl;                                             // Closin' fbk
  exit(EXIT_SUCCESS);                                                                                       // Close software with ERR code
}
