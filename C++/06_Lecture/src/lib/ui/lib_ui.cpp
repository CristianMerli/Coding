/*
 * Author: Cristian Merli
 * Code title: UI (terminal I/O) library
 * Code version: 3.0
 * Creation date: 07/04/2022
 * Last mod. date: 30/05/2022
 */


/* Dependencies */
#include "lib_ui.hpp"                                                                                       // Import UI (terminal I/O) library header file


/* Color const-vars */
C_string fbk_col[]={GN, PU, LBU};                                                                           // Terminal fbk print-colors
C_string req_col[]={OG, CY, BU};                                                                            // Terminal request print-colors
C_string err_col[]={YE, RD};                                                                                // Terminal error print-colors


/* Funct to read Real command-line parameters (returns err flg) */
Boolean read_cl_param(C_integer &argc, char *const argv[], Real param[], C_integer &param_sz) {
  Boolean err_flg=false;                                                                                    // Err flag declaration
  term_print("Loading main command-line parameter(s)...");                                                  // Print oper fbk
  if (argc-1==param_sz) {                                                                                   // Chk for expected num of main param, if ok
    String *p=alloc<String>(argc-1);                                                                        // Allocate commands str dyn vect inside heap
    for (Integer i=1; i<argc; ++i) {                                                                        // Param scrollin' cycle (skip prg name)
      p[i-1]=argv[i];                                                                                       // Def commands str vect
      err_flg=chk_numeric_str(p[i-1], "Expecting real value, not char! [Param"+S(i)+": "+p[i-1]+"]");       // Chk each param str character to make sure it's numeric
      if (!err_flg) param[i-1]=atof(argv[i]); else break;                                                   // If everything is ok conv param into out var, while in case of err flg set xit param scrollin' cycle
    } dealloc<String>(p);                                                                                   // Deallocate commands str dyn vect from heap
  } else {                                                                                                  // Case wrong num of param
    term_print("Wrong param num in main funct-call: expecting "+S(param_sz)+", got "+S(argc-1)+"!", ERR);   // Print err fbk
    err_flg=true;                                                                                           // Set err flg
  }
  return (!err_flg) ? EXIT_SUCCESS : EXIT_FAILURE;                                                          // If err flg ain't set: return OK code else if err flg is set: return ERR code
}


/* Funct to read String command-line parameters (returns err flg) */
Boolean read_cl_param(C_integer &argc, char *const argv[], String param[], C_integer &param_sz) {
  term_print("Loading main command-line parameter(s)...");                                                  // Print oper fbk
  if (argc-1==param_sz){                                                                                    // Chk for expected num of main param, if ok
    for (Integer i=1; i<argc; ++i) param[i-1]=argv[i];                                                      // Scroll param (skip prg name) and def commands str vect
    return EXIT_SUCCESS;                                                                                    // Return OK code
  } else {                                                                                                  // Else in case wrong num of param
    term_print("Wrong param num in main funct-call: expecting "+S(param_sz)+", got "+S(argc-1)+"!", ERR);   // Print err fbk
    return EXIT_FAILURE;                                                                                    // Return ERR code
  }
}


/* Funct to print responsive-title on terminal (title-txt, title-col, bkg-char, bkg-col) */
void term_print_title(C_string &title_txt, C_string &title_col, C_character &bkg_chr, C_string &bkg_col) {
  struct winsize w;                                                                                         // TERMINAL-DEFS: Window-size struct declaration
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);                                                                     // Save number of terminal's rows/columns in window-size struct
  CU_short vthck=w.ws_row/5;                                                                                // Title bkg vertical thickness calc
  CU_short lthck=w.ws_col/6;                                                                                // Title bkg lateral thickness calc
  CU_short l_sp=lthck/2;                                                                                    // Title lateral spaces calc
  CU_short lsp=(U_short)(w.ws_col-2*lthck-2*l_sp-title_txt.length())/2;                                     // Title internal lateral spaces calc
  CU_short len=(U_short)(2*lthck+2*lsp+title_txt.length());                                                 // Title length calc
  std::cout << std::endl << bkg_col;                                                                        // TITLE-PRINTIN': New line fbk
  for (U_short i=0; i<(4*vthck+1); ++i) {                                                                   // Title lines printin' cycle
    for (U_short j=0; j<l_sp; ++j) std::cout << SP;                                                         // Initial spaces printin' cycle
    if ((i<vthck || i>(3*vthck)) && i!=(4*vthck)/2) {                                                       // Full bkg title lines print cond
      for (U_short h=0; h<len; ++h) std::cout << bkg_chr;                                                   // Full bkg title lines printin' cycle and bkg title char print
    } else if ((i>=vthck && i<=(3*vthck)) && i!=(4*vthck)/2) {                                              // Partial-empty bkg title lines print cond
      for (U_short l=0; l < lthck; ++l) std::cout << bkg_chr;                                               // Partial-empty bkg title lines, initial full part printin' cycle
      for (U_short m=0; m<(len-2*lthck); ++m) std::cout << SP;                                              // Partial-empty bkg title lines, central empty part printin' cycle
      for (U_short n=0; n<lthck; ++n) std::cout << bkg_chr;                                                 // Partial-empty bkg title lines, final full part printin' cycle
    } else if (i==(4*vthck)/2) {                                                                            // Text title line initial full part print cond
      for (U_short o=0; o<lthck; ++o) std::cout << bkg_chr;                                                 // Text title line initial full part printin' cycle
      for (U_short p=0; p<lsp; ++p) std::cout << SP;                                                        // Text title line central empty part printin' cycle
      std::cout << title_col << title_txt << bkg_col;                                                       // Text title line central text part print
      for (U_short q=0; q<lsp; ++q) std::cout << SP;                                                        // Text title line central empty part printin' cycle
      for (U_short r=0; r<lthck; ++r) std::cout << bkg_chr;                                                 // Text title line final full part printin' cycle
    }
    term_print_nl(1);                                                                                       // New line
  }
  term_print_nl(1);                                                                                         // New line
  term_print(fbk_col[1]+"Welcome to "+title_col+"'"+title_txt+ \
             "'"+fbk_col[1]+" software! "+title_col+";)"+"\n"+ER);                                          // Print welcome fbk
}


/* Funct to perform terminal print (default print-typ=FBK) */
void term_print(C_string &fbk_str, C_print_typ &typ) {
  (typ==ERR ? std::cerr : std::cout) << (typ==ERR ? err_col[0] : (typ==REQ ? req_col[0] : fbk_col[0])) \
  << ">>> " << (typ==ERR ? err_col[1] : (typ==REQ ? req_col[1] : fbk_col[1])) << fbk_str << \
  (typ==REQ ? " and then press "+req_col[2]+"'ENTER'"+req_col[1]+": " : "\n") << ER;                        // Print on terminal
}


/* Funct to perform new-lines terminal print */
void term_print_nl(C_integer &n) {
  for (Byte i=0; i<n; ++i) std::cout << std::endl;                                                          // Terminal new lines printing macro
}


/* Funct to close software terminal with error fbk */
void term_close_err(C_string &err_str) {
  term_print_nl(1); if (err_str!="") {term_print(err_str, ERR);}                                            // Print err str
  std::cout << err_col[0] << ">>> " << err_col[1] << "Closin' due to error..." << \
  req_col[1] << " Sorry! " << req_col[0] << ":(" << ER << std::endl << std::endl;                           // Closin' due to error fbk
  exit(EXIT_FAILURE);                                                                                       // Close software with ERR code
}


/* Funct to close software terminal with bye fbk */
void term_close_bye(C_string &bye_str) {
  term_print_nl(1); if (bye_str!="") {term_print(bye_str);}                                                 // Print bye str
  std::cout << fbk_col[0] << ">>> " << fbk_col[1] << "Closin'..." << \
  req_col[1] << " Bye! " << req_col[0] << ";)" << ER << std::endl;                                          // Closin' fbk
  exit(EXIT_SUCCESS);                                                                                       // Close software with OK code
}


/* Funct to check numerical string (returns err flg) */
Boolean chk_numeric_str(C_string &str, C_string &err_str) {
  Byte dots=0;                                                                                              // Decimal dots cnt var
  const size_t str_sz=str.length();                                                                         // Calc str size
  for (size_t i=0; i<str_sz; ++i) {                                                                         // Str scrollin' cycle
    if (str[i]=='.') ++dots;                                                                                // In case of decimal dot detected upd cnt
    if (isdigit(str[i])==0 && ((str[i]!='.' && str[i]!='+' && str[i]!='-') || \
        dots>1 || ((str[i]=='+' || str[i]=='-') && i!=0) || \
        (str.length()==1 && (str[0]=='.' || str[0]=='+' || str[0]=='-')) || \
        (str.length()==2 && (str[0]=='+' || str[0]=='-') && str[1]=='.'))) {                                // Detect unexpected chars in num str: allow decimal dot and +/- signs
      term_print(err_str, ERR);                                                                             // In case of unexpected chars detected, print err fbk
      return EXIT_FAILURE;                                                                                  // Return ERR code
    }
  }
  return EXIT_SUCCESS;                                                                                      // Else in case of str ok, return OK code
}


/* Funct to check if real val is equal to zero */
Boolean real_eq_z(C_real &val) {
  return (fabs(val)<REAL_EPSILON ? true : false);                                                           // Chk and return if Real val is equal to zero
}


/* Funct to check if real val is different from zero */
Boolean real_df_z(C_real &val) {
  return (fabs(val)>REAL_EPSILON ? true : false);                                                           // Chk and return if real val is different from zero
}
