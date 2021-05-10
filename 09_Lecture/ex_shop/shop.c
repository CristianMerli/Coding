/*
 * Author: Cristian Merli
 * Code title: Shop
 * Code version: 3.0
 * Creation date: 10/05/2021
 * Last mod. date: 10/05/2021
 * 
 * 
 * // Compile-commands:
 * gccW99_lib lib/shop/lib_shop.so lib/shop/lib_shop.c                                --> Create SHOP dynamic library object file
 * gccW99_lib lib/ui/lib_ui.so lib/ui/lib_ui.c                                        --> Create UI (TERMINAL I/O) dynamic library object file
 * gccW99_lib lib/files/lib_files.so lib/files/lib_files.c                            --> Create FILES dynamic library object file
 * gccW99_c shop.c                                                                    --> Create SOFTWARE object file
 * 
 * // Link-command:
 * gccW99_o shop shop.o lib/shop/lib_shop.so lib/ui/lib_ui.so lib/files/lib_files.so  --> LINK software and dynamic libraries object files to executable
 * 
 * // Aliases:
 * alias gccW99_o="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -o"
 * alias gccW99_c="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -c"
 * alias gccW99_lib="gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -fpic -shared -o"
 */


/* Libraries */
#include "lib/shop/lib_shop.h"                                                                              // Import shop library header file


/* Constants */
#define MAIN_LOOP_MIN_OPT 1                                                                                 // Main loop min allowed option val
#define MAIN_LOOP_MAX_OPT 10                                                                                // Main loop max allowed option val
#define INITIAL_CAGES_NUM 5                                                                                 // Initial number of cages in shop


/* Global vars */
cage *shop_cages = NULL;                                                                                    // Shop cages vector poinet
u_shrt num_shop_cages = 0;                                                                                  // Number of cages in shop
u_shrt unsaved_chgs_flg = 0;                                                                                // Unsaved changes flag


/* Main routines */
static void show_shop_status(){                                                                             // Show shop status routine
  /* Body */
  if (num_shop_cages > 0 && shop_cages != NULL){                                                            // If shop has been already created/loaded
    fbk_gn_cy("Listing cages in shop...");                                                                  // Listing shop cages fbk
    fbk_nl(1);                                                                                              // New line fbk
    shop_report(shop_cages, num_shop_cages);                                                                // Show shop stats report
  } else {                                                                                                  // Else if shop has not been already created/loaded
    fbk_err("Error! No shop loaded! Create new shop or load an existing one");                              // No shop loaded error fbk
  }
}


static void add_new_pet(){                                                                                  // Add new pet routine
  /* Body */
  pet_typ tmp_pet_typ;                                                                                      // Temporary pet type var
  byte exit_flg = 0;                                                                                        // Cage choice while-loop exit flag

  if (num_shop_cages > 0 && shop_cages != NULL){                                                            // If shop has been already created/loaded
    printf("\n    %s[1]%s CAT        %s[2]%s DOG        %s[3]%s HAMSTER        %s[4]%s RABBIT\n\n%s",
            LGY, OG, LGY, OG, LGY, OG, LGY, OG, ER);                                                        // Print frist options line
    printf(  "    %s[5]%s BACK\n\n%s",
            LGY, OG, ER);                                                                                   // Print second options line
    tmp_pet_typ = (byte)read_term_in_int_inrange(1, NUM_TYPE_OF_PETS, "Select pet type",
                                                 "Error! The option value");                                // Select pet in pet type options fbk
    if (tmp_pet_typ == NUM_TYPE_OF_PETS){                                                                   // If exit option has been selected
      fbk_gn_cy("Giong back to main menu...");                                                              // Back to main menu fbk
    } else {                                                                                                // If exit option has not been selected
      do{
        show_shop_status();                                                                                 // Print shop cages
        fbk_nl(1);                                                                                          // Print new line fbk
        u_shrt cg_n = (u_shrt)read_term_in_int_inrange(1, num_shop_cages, "Choose cage number for the new pet",
                                                       "Error! The cage number");                           // Define cage number for the new pet
        if (shop_cages[cg_n-1].pet_typ == EMPTY){                                                           // Check if selected cage is empty
          assign_pet_to_cage(shop_cages, cg_n, tmp_pet_typ);                                                // Assign pet to cage
          ++unsaved_chgs_flg;                                                                               // Set unsaved changes flag
          ++exit_flg;                                                                                       // Set cage choice while-loop exit flag 
        } else {                                                                                            // Else if selected cage is not empty
          fbk_err("Error! Selected cage is not empty");                                                     // Print cage not empty fbk
        }
      } while(!exit_flg);                                                                                   // Check cage choice while-loop exit flag
    }
  } else {                                                                                                  // Else if shop has not been already created/loaded
    fbk_err("Error! No shop loaded! Create new shop or load an existing one");                              // No shop loaded error fbk
  }
}


static void add_new_cages(){                                                                                // Add new cages routine
  /* Body */
  if (num_shop_cages > 0 && shop_cages != NULL){                                                            // If shop has been already created/loaded
    u_shrt num_cgs = (u_shrt)read_term_in_int_inrange(1, MAX_NUM_CGS_ADD, "Specify the number of cages to add",
                                                      "Error! The number of cages to add");                 // Define the number of cages to add
    shop_cages = reallocate_shop_cages(shop_cages, (u_shrt)(num_shop_cages+num_cgs));                       // Redefine the number of cages in shop
    ++unsaved_chgs_flg;                                                                                     // Set unsaved changes flag
    u_shrt delta_cages = (u_shrt)(num_shop_cages - num_cgs);                                                // Find number of new added cages in oGNer to initialize cages as empty
    num_shop_cages = (u_shrt)(num_shop_cages+num_cgs);                                                      // Upd num of shop cages
    for (u_shrt cg = (u_shrt)(num_shop_cages-1); cg > delta_cages; --cg){                                   // Initialize new added cages as empty
      shop_cages[cg].pet_typ = EMPTY;                                                                       // Set pet type as empty
    }
    fbk_gn_cy("New cages correctly added!");                                                                // New cages added fbk
  } else {                                                                                                  // Else if shop has not been already created/loaded
    fbk_err("Error! No shop loaded! Create new shop or load an existing one");                              // No shop loaded error fbk
  }
}


static void pet_sold(){                                                                                     // Pet sold routine
  /* Body */
  if (num_shop_cages > 0 && shop_cages != NULL){                                                            // If shop has been already created/loaded
    show_shop_status();                                                                                     // Show shop status routine call
    fbk_nl(1);                                                                                              // New line fbk
    u_shrt cg_n = (u_shrt)read_term_in_int_inrange(1, num_shop_cages, "Specify the cage number of sold pet",
                                                   "Error! The cage number sold pet");                      // Define the cage number of the sold pet
    free_cage(shop_cages, cg_n);                                                                            // Set defined cage as "free"
    ++unsaved_chgs_flg;                                                                                     // Set unsaved changes flag
  } else {                                                                                                  // Else if shop has not been already created/loaded
    fbk_err("Error! No shop loaded! Create new shop or load an existing one");                              // No shop loaded error fbk
  }
}


static void remove_cages(){                                                                                 // Remove cages routine
  /* Body */
  if (num_shop_cages > 1 && shop_cages != NULL){                                                            // If shop has been already created/loaded
    byte free_cgs_flg = 1;                                                                                  // Free cages flag (check if cages are empty before deletin' 'em)

    show_shop_status();                                                                                     // Show shop status routine call
    fbk_nl(1);                                                                                              // New line fbk
    u_shrt num_cgs = (u_shrt)read_term_in_int_inrange(1, num_shop_cages-1, "Number of cages to remove (from last)",
                                                      "Error! The number of cages to remove");              // Define the number of cages to remove
    for (int cg = num_shop_cages-1; cg >= num_shop_cages-num_cgs; --cg){                                    // Check if cages are free b4 deletin' 'em FOR cycle
      if (shop_cages[cg].pet_typ != EMPTY){                                                                 // Reset free cages flag triggerin' condition
        --free_cgs_flg;                                                                                     // Reset free cages flag
        break;                                                                                              // Quit from check-cages free b4 deletin' 'em cycle
      }
    }
    if (free_cgs_flg == 1){                                                                                 // Check if cages are empty before deletin' 'em (check free cages flag val)
      shop_cages = reallocate_shop_cages(shop_cages, (u_shrt)(num_shop_cages+num_cgs));                     // Redefine the number of cages in shop
      num_shop_cages = (u_shrt)(num_shop_cages-num_cgs);                                                    // Upd num of shop cages
      ++unsaved_chgs_flg;                                                                                   // Set unsaved changes flag
      fbk_gn_cy("Last defined cages correctly removed!");                                                   // Last defined cages removed fbk
    } else {                                                                                                // If selected cages are not empty
      fbk_err("Error! Trying to remove an occupied cage");                                                  // Print trying to remove an occupied cage error fbk
    }
  } else if (num_shop_cages == 1 && shop_cages != NULL){
    fbk_err("Error! There is only one cage! cannot remove it");                                             // One only cage remaning error fbk
  } else {                                                                                                  // Else if shop has not been already created/loaded
    fbk_err("Error! No shop loaded! Create new shop or load an existing one");                              // No shop loaded error fbk
  }
}


static void pet_bday(){                                                                                     // Pet birthday routine
  /* Body */
  if (num_shop_cages > 0 && shop_cages != NULL){                                                            // If shop has been already created/loaded
    show_shop_status();                                                                                     // Show shop status routine call
    fbk_nl(1);                                                                                              // New line fbk
    u_shrt cg_n = (u_shrt)read_term_in_int_inrange(1, num_shop_cages, "Insert pet cage number to increment age",
                                                   "Error! The cage number");                               // Define cage number of the pet to increment age
    pet_birthday(shop_cages, cg_n);                                                                         // Call pet b-day funct
    ++unsaved_chgs_flg;                                                                                     // Set unsaved changes flag
  } else {                                                                                                  // Else if shop has not been already created/loaded
    fbk_err("Error! No shop loaded! Create new shop or load an existing one");                              // No shop loaded error fbk
  }
}


static void save_shop_sts(){                                                                                // Save shop status routine
  /* Body */
  if (num_shop_cages > 0 && shop_cages != NULL){                                                            // If shop has been already created/loaded
    char *filename = read_term_in_min_chrs(BKP_FILE_MIN_NAME_CHRS, "Specify backup file name (overwrite mode)",
                                           "Backup file name");                                             // Define backup file name
    char *shopname = read_term_in_min_chrs(BKP_FILE_MIN_NAME_CHRS, "Specify shop name to backup",
                                           "Shop name");                                                    // Define shop name
    bkp_shop_on_file(shop_cages, num_shop_cages, filename, shopname);                                       // Call shop backup function
    fbk_gn_cy("Pet shop status correctly added!");                                                          // Shop status saved fbk
    unsaved_chgs_flg = 0;                                                                                   // Reset unsaved changes flag
  } else {                                                                                                  // Else if shop has not been already created/loaded
    fbk_err("Error! No shop loaded! Create new shop or load an existing one");                              // No shop loaded error fbk
  }
}


static void clear_memo(){                                                                                   // Clear allocated dynamic memory routine
  /* Body */
  free(shop_cages);                                                                                         // Clear allocated dynamic memory
  shop_cages = NULL;                                                                                        // Set shop cages vector pointer to null
  num_shop_cages = 0;                                                                                       // Set shop cages counter val to zero
}


static void allocate_new_shop(){                                                                            // Allocate new shop routine
  /* Body */
    shop_cages = allocate_shop_cages(INITIAL_CAGES_NUM);                                                    // Allocate new shop in dynamic memory
    num_shop_cages = INITIAL_CAGES_NUM;                                                                     // Define new shop cages number
    fbk_gn_lbu_ye_int("Creating new shop with predefined number of cages", (int)num_shop_cages);            // New shop with predefined number of cages fbk
    fbk_nl(1);                                                                                              // New line fbk
    fbk_gn_cy("New shop correctly initialized!");                                                           // New shop initialized fbk
    unsaved_chgs_flg = 0;                                                                                   // Reset unsaved changes flag
}


static void reastore_bkp(){                                                                                 // Restore backup routine
  /* Body */
    char *filename = read_term_in_min_chrs(BKP_FILE_MIN_NAME_CHRS, "Specify backup file name",
                                           "Error! Backup file name");                                      // Define backup file name to restore shop status
    shop_cages = load_shop_from_file(shop_cages, &num_shop_cages, filename);                                // Load shop from file function call
}


static void load_shop_sts(){                                                                                // Load shop status routine
  /* Body */
  if (num_shop_cages > 0 && shop_cages != NULL && !unsaved_chgs_flg){                                       // If there aren't unsaved changes and memo is not empty, clear memo and load shop from file
    clear_memo();                                                                                           // Clear allocated dynamic memory routine call
    reastore_bkp();                                                                                         // Restore backup routine call
  } else if (num_shop_cages > 0 && shop_cages != NULL && unsaved_chgs_flg > 0){                             // Case unsaved changes presence
    confirm answ = read_term_in_confirm("Do you want to save unsaved changes before loading an existing shop"); // Ask confirmation
    switch (answ)                                                                                           // Answer switch-case
    {
    case YES:                                                                                               // YES case
      save_shop_sts();                                                                                      // Save shop status routine call
      reastore_bkp();                                                                                       // Restore backup routine call
      break;
     ////////
     case NO:                                                                                               // NO case
      reastore_bkp();                                                                                       // Restore backup routine call
      break;
    ////////////
    case CANCEL:                                                                                            // CANCEL case
      break;                                                                                                // Skip
    }
  } else {                                                                                                  // Case empty memory
    reastore_bkp();                                                                                         // Restore backup routine call
  }
}


static void init_new_shop(){                                                                                // Initialize new shop routine
  /* Body */
  if (num_shop_cages > 0 && shop_cages != NULL && !unsaved_chgs_flg){                                       // If there aren't unsaved changes and memo is not empty, clear memo and create new shop
    clear_memo();                                                                                           // Clear allocated dynamic memory routine call
    allocate_new_shop();                                                                                    // Allocate new shop routine call
  } else if (num_shop_cages > 0 && shop_cages != NULL && unsaved_chgs_flg > 0){                             // Case unsaved changes presence
    confirm answ = read_term_in_confirm("Do you want to save unsaved changes before creating a new shop");  // Ask confirmation
    switch (answ)                                                                                           // Answer switch-case
    {
    case YES:                                                                                               // YES case
      save_shop_sts();                                                                                      // Save shop status routine call
      allocate_new_shop();                                                                                  // Allocate new shop routine call
      break;
     ////////
     case NO:                                                                                               // NO case
      allocate_new_shop();                                                                                  // Allocate new shop routine call
      break;
    ////////////
    case CANCEL:                                                                                            // CANCEL case
      break;                                                                                                // Skip
    }
  } else {                                                                                                  // Case empty memory
    allocate_new_shop();                                                                                    // Allocate new shop routine call
  }
}


/* Main cycle */
int main(){
  /* Main vars */
  byte exit_flg = 0;                                                                                        // Main while-loop exit flag
  byte sel_opt = 0;                                                                                         // Selected option choice val

  /* Code */
  logo(10, "PET SHOPS MANAGEMENT SOFTWARE", YE, '#', GN);                                                   // Print responsive-logo function call (start_spaces, text, txt_color, background_char, bkgchr_color)
  press_enter("Manage your pet shops");                                                                     // Press enter to start SW fbk

  do{
    printf("\n\n    %s[1]%s SHOP STATUS         %s[2]%s NEW PET             %s[3]%s NEW CAGES          %s[4]%s PET SOLD\n\n%s",
            LGY, OG, LGY, OG, LGY, OG, LGY, OG, ER);                                                                              // Print frist options line
    printf(    "    %s[5]%s REMOVE CAGES        %s[6]%s PET BIRTHDAY        %s[7]%s BACKUP SHOP        %s[8]%s LOAD SHOP\n\n%s",
            LGY, OG, LGY, OG, LGY, OG, LGY, OG, ER);                                                                              // Print second options line
    printf(    "    %s[9]%s NEW SHOP            %s[10]%s EXIT\n\n%s",
            LGY, OG, LGY, OG, ER);                                                                                                // Print third options line
    sel_opt = (byte)read_term_in_int_inrange(MAIN_LOOP_MIN_OPT, MAIN_LOOP_MAX_OPT,
                                             "Select an available option", "Error! The option value");                            // Call option choice function and print info fbk
    
    switch (sel_opt)                                                                                        // Selected option switch-case
    {
    case 1:                                                                                                 // Case SHOP STATUS
      show_shop_status();                                                                                   // Show shop status routine call
      break;
    ///////
    case 2:                                                                                                 // Case NEW PET
      add_new_pet();                                                                                        // Add new pet routine call
      break;
    ///////
    case 3:                                                                                                 // Case NEW CAGES
      add_new_cages();                                                                                      // Add new cages routine call
      break;
    ///////
    case 4:                                                                                                 // Case PET SOLD
      pet_sold();                                                                                           // Pet sold routine call
      break;
    ///////
    case 5:                                                                                                 // Case REMOVE CAGES
      remove_cages();                                                                                       // Remove cages routine call
      break;
    ///////
    case 6:                                                                                                 // Case PET BIRTHDAY
      pet_bday();                                                                                           // Pet birthday routine call
      break;
    ///////
    case 7:                                                                                                 // Case BACKUP SHOP
      save_shop_sts();                                                                                      // Save shop status routine call
      break;
    ///////
    case 8:                                                                                                 // Case LOAD SHOP
      load_shop_sts();                                                                                      // Load shop status routine call
      break;
    ///////
    case 9:                                                                                                 // Case NEW SHOP
      init_new_shop();                                                                                      // Initialize new shop routine call
      break;
    ///////
    case 10:                                                                                                // Case Exit
      if (num_shop_cages > 0 && shop_cages != NULL && !unsaved_chgs_flg){                                   // If there aren't unsaved changes and memo is not empty, clear memo and set main-loop exit flag
        clear_memo();                                                                                       // Clear allocated dynamic memory routine call
        ++exit_flg;                                                                                         // Set main while-loop exit flag
      } else if (num_shop_cages > 0 && shop_cages != NULL && unsaved_chgs_flg > 0){                         // Case unsaved changes presence
        confirm answ = read_term_in_confirm("Do you want to save unsaved changes before creating a new shop");  // Ask confirmation
        switch (answ)                                                                                       // Answer switch-case
        {
        case YES:                                                                                           // YES case
          save_shop_sts();                                                                                  // Save shop status routine call
          ++exit_flg;                                                                                       // Set main while-loop exit flag
          break;
        ////////
        case NO:                                                                                            // NO case
          ++exit_flg;                                                                                       // Set main while-loop exit flag
          break;
        ////////////
        case CANCEL:                                                                                        // CANCEL case
          break;                                                                                            // Skip
        }
      } else {                                                                                              // Case empty memory
        ++exit_flg;                                                                                         // Set main while-loop exit flag
      }
      break;
    ////////
    default:                                                                                                // Unknown case
      //
      fbk_err("Error! Unknown option selected in main menu, retry");                                        // Print unknown option selected error fbk
      break;
    }
  } while(!exit_flg);                                                                                       // Check main while-loop exit flag val
  
  free(shop_cages);                                                                                         // Clear allocated dynamic memory
  close_fbk();                                                                                              // Closin' SW fbk

  return 0;                                                                                                 // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/* 
 * Creare la struttura negozio che può contenere un vettore di gabbie.
 * Ogni gabbia può contenere al più un animale.
 * Gli animali sono del tipo GATTO, CANE, CRICETO, CONIGLIO
 * Ogni animale ha un nome.
 * Ogni animale ha un età in anni.
 * Il negozio comincia la sua attività con 5 gabbie.
 * Scrivere le seguenti funzioni:
 * 1. Funzione che mostra lo stato del negozio. Mostra il numero di gabbie e per ogni gabbia il suo contenuto.
 * 2. Funzione che assegna l'animale alla gabbia.
 * 3. Funzione che aumenta il numero di gabbie disponibile di N.
 * 4. Funzione che salva su file lo stato del negozio
 * 5. Funzione che carica da file un negozio
 * 6. Funzione che fa invecchiare gli animali di un anno
 * 7. Funzione che libera una gabbia, l'animale è venduto.
 * Definire un menù da riga di comando per gestire le opzioni definite
 */
