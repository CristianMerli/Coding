/*
 * Author: Cristian Merli
 * Code title: UI (terminal I/O) library
 * Code version: 3.0
 * Creation date: 07/04/2022
 * Last mod. date: 20/05/2022
 */


/* Dependencies */
#include "lib_ui.h"                                                                                         // Import UI (terminal I/O) library header file


/* Public vars */
Integer unused __attribute__((unused));                                                                     // Unused var


/* Terminal class constructor method */
Term::Term(C_string &title, C_string &title_col, C_byte &bkg_chr, C_string &bkg_col, CU_short &start_sp) {
  this->title_txt=title;                                                                                    // Init terminal logo title text
  this->title_col=title_col;                                                                                // Init terminal logo title color
  this->bkg_chr=bkg_chr;                                                                                    // Init terminal logo background char
  this->bkg_col=bkg_col;                                                                                    // Init terminal logo background char color
  this->start_sp=start_sp;                                                                                  // Init terminal logo lateral spaces (left)
  this->print_responsive_title();                                                                           // Call terminal class method to print responsive-title
}


/* Terminal class destructor method */
Term::~Term() {
  // Clr alloc dyn-memo [UNUSED]
}


/* Terminal class method to perform terminal print (default print-typ=FBK) */
void Term::print(C_string &fbk_str, const Print_typ &typ) const {
  (typ==ERR ? std::cerr : std::cout) << (typ==ERR ? err_col1 : (typ==REQ ? req_col1 : fbk_col1)) << \
  ">>> " << (typ==ERR ? err_col2 : (typ==REQ ? req_col2 : fbk_col2)) << fbk_str << \
  (typ==REQ ? " and then press "+req_col3+"'ENTER'"+req_col2+": " : "\n") << ER;                            // Print on terminal
}


/* Terminal class method to print real user output val to terminal */
void Term::print(C_string &fbk_str, C_real &val, C_string &post_str) const {
  std::cout << fbk_col1 << ">>> " << fbk_col2 << fbk_str << \
  ": " << fbk_col3 << val << SP << post_str << std::endl << ER;                                             // Print val on terminal
}


/* Terminal class method to print integer user output val to terminal */
void Term::print(C_string &fbk_str, C_integer &val, C_string &post_str) const {
  std::cout << fbk_col1 << ">>> " << fbk_col2 << fbk_str << \
  ": " << fbk_col3 << val << SP << post_str << std::endl << ER;                                             // Print val on terminal
}


/* Terminal class method to print short user output val to terminal */
void Term::print(C_string &fbk_str, C_short &val, C_string &post_str) const {
  std::cout << fbk_col1 << ">>> " << fbk_col2 << fbk_str << \
  ": " << fbk_col3 << val << SP << post_str << std::endl << ER;                                             // Print val on terminal
}


/* Terminal class method to print string user output to terminal */
void Term::print(C_string &fbk_str, C_string &val, C_string &post_str) const {
  std::cout << fbk_col1 << ">>> " << fbk_col2 << fbk_str << \
  ": " << fbk_col3 << val << SP << post_str << std::endl << ER;                                             // Print val on terminal
}


/* Terminal class method to print character user output to terminal */
void Term::print(C_string &fbk_str, C_character &val, C_string &post_str) const {
  std::cout << fbk_col1 << ">>> " << fbk_col2 << fbk_str << \
  ": " << fbk_col3 << val << SP << post_str << std::endl << ER;                                             // Print val on terminal
}


/* Terminal class method to perform new-lines terminal print */
void Term::print_nl(C_integer &n) const {
  for (Byte i=0; i<n; ++i) std::cout << std::endl;                                                          // Terminal new lines printing macro
}


/* Terminal class method to get user input real val from terminal */
Real Term::get_real(C_string &req_str) const {
  Real val;                                                                                                 // Val tmp-var
  do {                                                                                                      // Acq cycle
    print(req_str, REQ);                                                                                    // Print req
    if (std::cin >> val) {                                                                                  // Chk in val
      print("Real value correctly acquired, inserted value", val);                                          // Print inserted val
      break;                                                                                                // Xit acq cycle
    } else {                                                                                                // If in-val ain't ok
      print("Invalid real value! Please, retry...", ERR);                                                   // Print err
      std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');                 // Clr in-buff and ignore other chars and repeat req
    }
  } while (true);                                                                                           // Acq cycle xit cond managed usin' break
  return val;                                                                                               // Return val tmp-var
}


/* Terminal class method to get user input integer val from terminal */
Integer Term::get_integer(C_string &req_str) const {
  Integer val;                                                                                              // Val tmp-var
  do {                                                                                                      // Acq cycle
    print(req_str, REQ);                                                                                    // Print req
    if (std::cin >> val) {                                                                                  // Chk in val
      print("Integer value correctly acquired, inserted value", val);                                       // Print inserted val
      break;                                                                                                // Xit acq cycle
    } else {                                                                                                // If in-val ain't ok
      print("Invalid integer value! Please, retry...", ERR);                                                // Print err
      std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');                 // Clr in-buff and ignore other chars and repeat req
    }
  } while (true);                                                                                           // Acq cycle xit cond managed usin' break
  return val;                                                                                               // Return val tmp-var
}


/* Terminal class method to get user input short val from terminal */
Short Term::get_short(C_string &req_str) const {
  Short val;                                                                                                // Val tmp-var
  do {                                                                                                      // Acq cycle
    print(req_str, REQ);                                                                                    // Print req
    if (std::cin >> val) {                                                                                  // Chk in val
      print("Short value correctly acquired, inserted value", val);                                         // Print inserted val
      break;                                                                                                // Xit acq cycle
    } else {                                                                                                // If in-val ain't ok
      print("Invalid short value! Please, retry...", ERR);                                                  // Print err
      std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');                 // Clr in-buff and ignore other chars and repeat req
    }
  } while (true);                                                                                           // Acq cycle xit cond managed usin' break
  return val;                                                                                               // Return val tmp-var
}


/* Terminal class method to get user input string from terminal */
String Term::get_str(C_string &req_str) const {
  String val;                                                                                               // Val tmp-var
  do {                                                                                                      // Acq cycle
    print(req_str, REQ);                                                                                    // Print req
    if (std::cin >> val) {                                                                                  // Chk in val
      print("String correctly acquired, inserted string", val);                                             // Print inserted val
      break;                                                                                                // Xit acq cycle
    } else {                                                                                                // If in-val ain't ok
      print("Invalid string! Please, retry...", ERR);                                                       // Print err
      std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');                 // Clr in-buff and ignore other chars and repeat req
    }
  } while (true);                                                                                           // Acq cycle xit cond managed usin' break
  return val;                                                                                               // Return val tmp-var
}


/* Terminal class method to get user input character from terminal */
Character Term::get_char(C_string &req_str) const {
  Character val;                                                                                            // Val tmp-var
  do {                                                                                                      // Acq cycle
    print(req_str, REQ);                                                                                    // Print req
    if (std::cin >> val) {                                                                                  // Chk in val
      print("Character correctly acquired, inserted character", val);                                       // Print inserted val
      break;                                                                                                // Xit acq cycle
    } else {                                                                                                // If in-val ain't ok
      print("Invalid character! Please, retry...", ERR);                                                    // Print err
      std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');                 // Clr in-buff and ignore other chars and repeat req
    }
  } while (true);                                                                                           // Acq cycle xit cond managed usin' break
  return val;                                                                                               // Return val tmp-var
}


/* Terminal class method to check numeric string (return err flg) */
Boolean Term::chk_num_str(C_string &str, C_string &err_str) const {
  Byte dots=0;                                                                                              // Decimal dots cnt var
  const size_t str_sz=str.length();                                                                         // Calc str size
  for (size_t i=0; i<str_sz; ++i) {                                                                         // Str scrollin' cycle
    if (str[i]=='.') ++dots;                                                                                // In case of decimal dot detected upd cnt
    if (isdigit(str[i])==0 && ((str[i]!='.' && str[i]!='+' && str[i]!='-') || \
        dots>1 || ((str[i]=='+' || str[i]=='-') && i!=0) || \
        (str.length()==1 && (str[0]=='.' || str[0]=='+' || str[0]=='-')) || \
        (str.length()==2 && (str[0]=='+' || str[0]=='-') && str[1]=='.'))) {                                // Detect unexpected chars in num str: allow decimal dot and +/- signs
      print(err_str, ERR);                                                                                  // In case of unexpected chars detected, print err fbk
      return EXIT_FAILURE;                                                                                  // Return ERR code
    }
  }
  return EXIT_SUCCESS;                                                                                      // Else in case of str ok, return OK code
}


/* Terminal class method to close software with error fbk */
void Term::close_err(C_string &err_str) const {
  print_nl(1); if (err_str!="") {print(err_str, ERR);}                                                      // Print err str
  std::cout << err_col1 << ">>> " << err_col2 << "Closin' due to error..." << \
  req_col2 << " Sorry! " << req_col1 << ":(" << ER << std::endl << std::endl;                               // Closin' due to error fbk
  exit(EXIT_FAILURE);                                                                                       // Close software with OK code
}


/* Terminal class method to close software with bye fbk */
void Term::close_bye(C_string &bye_str) const {
  print_nl(1); if (bye_str!="") {print(bye_str);}                                                           // Print bye str
  std::cout << fbk_col1 << ">>> " << fbk_col2 << "Closin'..." << \
  req_col2 << " Bye! " << req_col1 << ";)" << ER << std::endl;                                              // Closin' fbk
  exit(EXIT_SUCCESS);                                                                                       // Close software with ERR code
}


/* Private terminal class method to print responsive-title */
void Term::print_responsive_title() const {
  struct winsize w;                                                                                         // TERMINAL-DEFS: Window-size struct declaration
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);                                                                     // Save the number of terminal's rows/columns in window-size struct
  CU_short vthck = (w.ws_row/5);                                                                            // Title bkg vertical thickness calc
  CU_short lthck = (w.ws_col/6);                                                                            // Title bkg lateral thickness calc
  CU_short lsp = (U_short)(w.ws_col-2*lthck-2*start_sp-title_txt.length())/2;                               // Title internal lateral spaces calc
  CU_short len = (U_short)(2*lthck+2*lsp+title_txt.length());                                               // Title length calc
  std::cout << std::endl << bkg_col;                                                                        // TITLE-PRINTIN': New line fbk
  for (U_short i=0; i<(4*vthck+1); ++i) {                                                                   // Title lines printin' cycle
    for (U_short j=0; j<start_sp; ++j) std::cout << SP;                                                     // Initial spaces printin' cycle
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
    print_nl(1);                                                                                            // New line
  }
  print_nl(1);                                                                                              // New line
  print(fbk_col2+"Welcome to the "+title_col+"'"+ \
        title_txt+"'"+fbk_col2+" software! "+title_col+";)"+"\n"+ER);                                       // Print welcome fbk
}
