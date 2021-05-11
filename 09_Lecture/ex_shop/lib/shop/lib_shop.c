/*
 * Author: Cristian Merli
 * Code title: Shop library
 * Code version: 3.0
 * Creation date: 07/05/2021
 * Last mod. date: 07/05/2021
 */


/* Libraries */
#include "lib_shop.h"                                                                                       // Import shop library header file


/* Functions */
void shop_report(cage *shop_cgs, const u_shrt num_cgs){                                                     // Shop report function
  /* Body */
  fbk_gn_lbu_ye_int("Total number of cages", (int)num_cgs);                                                 // Print total number of cages fbk
  for (u_shrt cg = 0; cg < num_cgs; ++cg){                                                                  // Cages scroll FOR cycle
    fbk_nl(1);                                                                                              // Print new line fbk
    switch (shop_cgs[cg].pet_typ)                                                                           // Pet type switch-case
    {
    case EMPTY:                                                                                             // Case pet type in cage = empty
      fbk_gn_lbu_ye_int(" - Empty cage number", (int)cg+1);                                                 // Print empty cage number fbk
      break;
    /////////
    case CAT:                                                                                               // Case pet type in cage = cat
      fbk_gn_lbu_ye_int(" - Cat in cage number", (int)cg+1);                                                // Print cat cage number fbk
      fbk_nl(1);                                                                                            // New line fbk
      fbk_gn_lbu_ye_str("   Cat name", shop_cgs[cg].pet.cat.name);                                          // Print cat name fbk
      fbk_nl(1);                                                                                            // New line fbk
      fbk_gn_lbu_ye_int("   Cat age", (int)shop_cgs[cg].pet.cat.age);                                       // Print cat age fbk
      break;
    /////////
    case DOG:                                                                                               // Case pet type in cage = dog
      fbk_gn_lbu_ye_int(" - Dog in cage number", (int)cg+1);                                                // Print dog cage number fbk
      fbk_nl(1);                                                                                            // New line fbk
      fbk_gn_lbu_ye_str("   Dog name", shop_cgs[cg].pet.dog.name);                                          // Print dog name fbk
      fbk_nl(1);                                                                                            // New line fbk
      fbk_gn_lbu_ye_int("   Dog age", (int)shop_cgs[cg].pet.dog.age);                                       // Print dog age fbk
      break;
    /////////////
    case HAMSTER:                                                                                           // Case pet type in cage = hamster
      fbk_gn_lbu_ye_int(" - Hamster in cage number", (int)cg+1);                                            // Print hamster cage number fbk
      fbk_nl(1);                                                                                            // New line fbk
      fbk_gn_lbu_ye_str("   Hamster name", shop_cgs[cg].pet.hamster.name);                                  // Print hamster name fbk
      fbk_nl(1);                                                                                            // New line fbk
      fbk_gn_lbu_ye_int("   Hamster age", (int)shop_cgs[cg].pet.hamster.age);                               // Print hamster age fbk
      break;
    ////////////
    case RABBIT:                                                                                            // Case pet type in cage = rabbit
      fbk_gn_lbu_ye_int(" - Rabbit in cage number", (int)cg+1);                                             // Print rabbit cage number fbk
      fbk_nl(1);                                                                                            // New line fbk
      fbk_gn_lbu_ye_str("   Rabbit name", shop_cgs[cg].pet.rabbit.name);                                    // Print rabbit name fbk
      fbk_nl(1);                                                                                            // New line fbk
      fbk_gn_lbu_ye_int("   Rabbit age", (int)shop_cgs[cg].pet.rabbit.age);                                 // Print rabbit age fbk
      break;
    ////////
    default:                                                                                                // Case pet type in cage = unknown
      fbk_err("Error! Unknown element in cage found during shop report");                                   // Print unknown element error fbk
      break;
    }
  }
}


void assign_pet_to_cage(cage *shop_cgs, const u_shrt cg_n, const pet_typ tmp_pet_typ){                      // Assign pet to cage function (non-zero index)
  /* Body */
  char *pet_name = NULL;                                                                                    // Pet name var
  byte pet_age = 0;                                                                                         // Pet age var

  switch (tmp_pet_typ)                                                                                      // Pet type switch-case
  {
  case CAT:                                                                                                 // Case pet type in cage = cat
    pet_name = read_term_in_min_chrs(MIN_PET_NAME_CHRS, "Specify cat name", "Error! Cat name");             // Define cat name
    shop_cgs[cg_n-1].pet_typ = CAT;                                                                         // Define cat pet type
    strcpy(shop_cgs[cg_n-1].pet.cat.name, pet_name);                                                        // Set cat name in defined cage
    pet_age = (byte)read_term_in_int_inrange(1, MAX_PET_AGE, "Specify cat age", "Error! Cat age");          // Define cat age
    shop_cgs[cg_n-1].pet.cat.age = pet_age;                                                                 // Set cat age in defined cage
    fbk_gn_lbu_ye_int("New cat correctly assigned to cage number", (int)cg_n);                              // Print cat cage number fbk
    break;
  /////////
  case DOG:                                                                                                 // Case pet type in cage = dog
    pet_name = read_term_in_min_chrs(MIN_PET_NAME_CHRS, "Specify dog name", "Error! Dog name");             // Define dog name
    shop_cgs[cg_n-1].pet_typ = DOG;                                                                         // Define dog pet type
    strcpy(shop_cgs[cg_n-1].pet.dog.name, pet_name);                                                        // Set dog name in defined cage
    pet_age = (byte)read_term_in_int_inrange(1, MAX_PET_AGE, "Specify dog age", "Error! Dog age");          // Define dog age
    shop_cgs[cg_n-1].pet.dog.age = pet_age;                                                                 // Set dog age in defined cage
    fbk_gn_lbu_ye_int("New dog correctly assigned to cage number", (int)cg_n);                              // Print dog cage number fbk
    break;
  /////////////
  case HAMSTER:                                                                                             // Case pet type in cage = hamster
    pet_name = read_term_in_min_chrs(MIN_PET_NAME_CHRS, "Specify hamster name", "Error! Hamster name");     // Define hamster name
    shop_cgs[cg_n-1].pet_typ = HAMSTER;                                                                     // Define hamster pet type
    strcpy(shop_cgs[cg_n-1].pet.hamster.name, pet_name);                                                    // Set hamster name in defined cage
    pet_age = (byte)read_term_in_int_inrange(1, MAX_PET_AGE, "Specify hamster age", "Error! Hamster age");  // Define hamster age
    shop_cgs[cg_n-1].pet.hamster.age = pet_age;                                                             // Set hamster age in defined cage
    fbk_gn_lbu_ye_int("New hamster correctly assigned to cage number", (int)cg_n);                          // Print hamster cage number fbk
    break;
  ////////////
  case RABBIT:                                                                                              // Case pet type in cage = rabbit
    pet_name = read_term_in_min_chrs(MIN_PET_NAME_CHRS, "Specify rabbit name", "Error! Rabbit name");       // Define rabbit name
    shop_cgs[cg_n-1].pet_typ = RABBIT;                                                                      // Define rabbit pet type
    strcpy(shop_cgs[cg_n-1].pet.rabbit.name, pet_name);                                                     // Set rabbit name in defined cage
    pet_age = (byte)read_term_in_int_inrange(1, MAX_PET_AGE, "Specify rabbit age", "Error! Rabbit age");    // Define rabbit age
    shop_cgs[cg_n-1].pet.rabbit.age = pet_age;                                                              // Set rabbit age in defined cage
    fbk_gn_lbu_ye_int("New rabbit correctly assigned to cage number", (int)cg_n);                           // Print rabbit cage number fbk
    break;
  ////////
  default:                                                                                                  // Case pet type in cage = unknown
    fbk_err("Error! Unknown element selected in cage assignment");                                          // Print unknown element error fbk
    break;
  }
}


cage *allocate_shop_cages(const u_shrt num_cgs){                                                            // Shop cages dyn memo alloc (calloc) function
  /* Body */
  cage *ptr = calloc((size_t)num_cgs, sizeof(cage));                                                        // Cage ptr creation to point first shop cages allocated memo cell inside heap
  
  if (ptr == NULL){                                                                                         // Check calloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during shop cages data management");                                     // Error fbk
    perror("Error in shop cages dynamic memory allocation with calloc!");                                   // print perror fbk
    close_err();                                                                                            // Close software with error function call
  }
  return ptr;                                                                                               // Return first shop cages allocated memo cell inside heap (pointer)
}


cage *reallocate_shop_cages(cage *shop_cgs, const u_shrt num_cgs){                                          // Shop cages dyn memo realloc function
  /* Body */
  cage *ptr = realloc(shop_cgs, (size_t)num_cgs*sizeof(cage));                                              // Cage ptr creation to point first shop cages reallocated memo cell inside heap
  
  if (ptr == NULL){                                                                                         // Check realloc funct output to detect dynamic memory allocation errors
    fbk_err("Ops! Encountred error during shop cages data management");                                     // Error fbk
    perror("Error in shop cages dynamic memory reallocation with realloc!");                                // Print perror fbk
    close_err();                                                                                            // Close software with error function call
  }
  return ptr;                                                                                               // Return first shop cages reallocated memo cell inside heap (pointer)
}


void bkp_shop_on_file(cage *shop_cgs, const u_shrt num_cgs, const char *filename, const char *shopname){    // Backup shop status on file function
  /* Body */
  fl bkp_file = open_file(filename, "w");                                                                   // Open file in write mode (clear text)

  if (bkp_file != NULL) {                                                                                   // Check file open status
    write_str_on_file(bkp_file, BKP_FILE_TITLE_LBL);                                                        // Write shop name label in first line of backup file
    write_str_on_file(bkp_file, shopname);                                                                  // Write shop name in first line of backup file
    write_nl_on_file(bkp_file);                                                                             // Write new line in backup file
    write_str_on_file(bkp_file, BKP_FILE_CAGES_LBL);                                                        // Write number of cages in the shop label in backup file
    write_int_on_file(bkp_file, (int)num_cgs);                                                              // Write number of cages in the shop in backup file

    for (u_shrt i = 0; i <= BKP_FILE_SEP_SPACES_BLOCKS; ++i){                                               // Blocks spaces (new lines) in backup file print for cycle
      write_nl_on_file(bkp_file);                                                                           // Write new line in backup file
    }

    for (u_shrt cg = 0; cg < num_cgs; ++cg){                                                                // Cages print FOR cycle
      write_str_on_file(bkp_file, BKP_FILE_TYPE_LBL);                                                       // Write pet type label in backup file
      write_str_on_file(bkp_file, pet_typ_str[shop_cgs[cg].pet_typ]);                                       // Write pet type in backup file
      write_nl_on_file(bkp_file);                                                                           // Write new line in backup file

      switch (shop_cgs[cg].pet_typ)                                                                         // Pet type switch-case
      {
      case EMPTY:                                                                                           // Case pet type in cage = empty
        write_str_on_file(bkp_file, BKP_FILE_PET_NAME_LBL);                                                 // Write pet name label in backup file
        write_str_on_file(bkp_file, pet_typ_str[shop_cgs[cg].pet_typ]);                                     // Write EMPTY name in backup file
        write_nl_on_file(bkp_file);                                                                         // Write new line in backup file
        write_str_on_file(bkp_file, BKP_FILE_PET_AGE_LBL);                                                  // Write pet age label in backup file
        write_str_on_file(bkp_file, pet_typ_str[shop_cgs[cg].pet_typ]);                                     // Write EMPTY age in backup file
        break;
      /////////
      case CAT:                                                                                             // Case pet type in cage = cat
        write_str_on_file(bkp_file, BKP_FILE_PET_NAME_LBL);                                                 // Write pet name label in backup file
        write_str_on_file(bkp_file, shop_cgs[cg].pet.cat.name);                                             // Write cat name in backup file
        write_nl_on_file(bkp_file);                                                                         // Write new line in backup file
        write_str_on_file(bkp_file, BKP_FILE_PET_AGE_LBL);                                                  // Write pet age label in backup file
        write_int_on_file(bkp_file, (int)shop_cgs[cg].pet.cat.age);                                         // Write cat age in backup file
        break;
      /////////
      case DOG:                                                                                             // Case pet type in cage = dog
        write_str_on_file(bkp_file, BKP_FILE_PET_NAME_LBL);                                                 // Write pet name label in backup file
        write_str_on_file(bkp_file, shop_cgs[cg].pet.dog.name);                                             // Write dog name in backup file
        write_nl_on_file(bkp_file);                                                                         // Write new line in backup file
        write_str_on_file(bkp_file, BKP_FILE_PET_AGE_LBL);                                                  // Write pet age label in backup file
        write_int_on_file(bkp_file, (int)shop_cgs[cg].pet.dog.age);                                         // Write dog age in backup file
        break;
      /////////////
      case HAMSTER:                                                                                         // Case pet type in cage = hamster
        write_str_on_file(bkp_file, BKP_FILE_PET_NAME_LBL);                                                 // Write pet name label in backup file
        write_str_on_file(bkp_file, shop_cgs[cg].pet.hamster.name);                                         // Write hamster name in backup file
        write_nl_on_file(bkp_file);                                                                         // Write new line in backup file
        write_str_on_file(bkp_file, BKP_FILE_PET_AGE_LBL);                                                  // Write pet age label in backup file
        write_int_on_file(bkp_file, (int)shop_cgs[cg].pet.hamster.age);                                     // Write hamster age in backup file
        break;
      ////////////
      case RABBIT:                                                                                          // Case pet type in cage = rabbit
        write_str_on_file(bkp_file, BKP_FILE_PET_NAME_LBL);                                                 // Write pet name label in backup file
        write_str_on_file(bkp_file, shop_cgs[cg].pet.rabbit.name);                                          // Write rabbit name in backup file
        write_nl_on_file(bkp_file);                                                                         // Write new line in backup file
        write_str_on_file(bkp_file, BKP_FILE_PET_AGE_LBL);                                                  // Write pet age label in backup file
        write_int_on_file(bkp_file, (int)shop_cgs[cg].pet.rabbit.age);                                      // Write rabbit age in backup file
        break;
      ////////
      default:                                                                                              // Case pet type in cage = unknown
        fbk_err("Error! Unknown element in cage found during shop backup on file");                         // Print unknown element error fbk
        break;
      }

      for (u_shrt i = 0; i <= BKP_FILE_SEP_SPACES_CAGES; ++i){                                              // Cages spaces (new lines) in backup file print for cycle
        write_nl_on_file(bkp_file);                                                                         // Write new line in backup file
      }
    }
    close_file(bkp_file);                                                                                   // Close file
  }
}


cage *load_shop_from_file(cage *shop_cgs, u_shrt *num_cgs, const char *filename){                           // Load shop status from file function
  /* Body */
  char file_in_buff[BKP_FILE_IN_BUFF_SIZE];                                                                 // File input buffer
  const u_int shop_name_line_idx = 1;                                                                       // Shop name line index
  const u_int num_shop_cgs_line_idx = 2;                                                                    // Number of shop cages line index
  u_int pet_typ_line = (u_int)(shop_name_line_idx+num_shop_cgs_line_idx+BKP_FILE_SEP_SPACES_BLOCKS);        // Pet type line index
  u_int pet_name_line = pet_typ_line+1;                                                                     // Pet name line index
  u_int pet_age_line = pet_name_line+1;                                                                     // Pet age line index
  int tmp_num = 0;                                                                                          // Temporary numeric var
  int cg_cnt = 0;                                                                                           // Cage counter
  byte corr_file_flg = 0;                                                                                   // Corrupted file flag

  fl bkp_file = open_file(filename, "r");                                                                   // Open file in read-only mode (clear text)
  if (bkp_file != NULL){                                                                                    // Check file obj not null
    u_int line_num = 0;                                                                                     // Line number counter
    while ( fgets(file_in_buff, FILE_IN_BUFF_SIZE, bkp_file) != NULL ){                                     // In case of file found, scan lines 'till null line (last one)
      char *txt = file_in_buff;                                                                             // Text pointer
      ++line_num;                                                                                           // Line number val upd
      
      // Extract data from shop name line
      if (line_num == shop_name_line_idx){                                                                  // If line number is = to shop name line index
        for (int i = 0; i < (int)strlen(BKP_FILE_TITLE_LBL); ++i){                                          // Check backup file title label FOR cycle
          if (file_in_buff[i] != BKP_FILE_TITLE_LBL[i])                                                     // Compare each label char
            ++corr_file_flg;                                                                                // Set corrupted file flag
        }
        txt += (int)strlen(BKP_FILE_TITLE_LBL);                                                             // Extract shop name removing shop name prefix label
        if(strlen(txt) > BKP_FILE_MIN_NAME_CHRS+1 && !corr_file_flg)                                        // Check file name length to detect corrupted file
          fbk_gn_lbu_ye_str("Loading shop from backup file, shop name", txt);                               // Print shop name fbk
        else                                                                                                // If file is corrupted
          ++corr_file_flg;                                                                                  // Set corrupted file flag
      
      // Extract data from number of cages in shop line
      } else if (line_num == num_shop_cgs_line_idx && !corr_file_flg){                                      // If line number is = number of shop cages line index and file is not corrupted
        for (int i = 0; i < (int)strlen(BKP_FILE_CAGES_LBL); ++i){                                          // Check backup file cages number label FOR cycle
          if (file_in_buff[i] != BKP_FILE_CAGES_LBL[i])                                                     // Compare each label char
            ++corr_file_flg;                                                                                // Set corrupted file flag
        }
        txt += (int)strlen(BKP_FILE_CAGES_LBL);                                                             // Extract number of shop cages removing shop cages prefix label
        tmp_num = atoi(txt);                                                                                // Save loaded number of cages in shop inside a tmp var
        if (tmp_num > 0 && !corr_file_flg){                                                                 // Check number of cages tmp var val to detect corrupted file
          *num_cgs = (u_shrt)tmp_num;                                                                       // If file is OK, redefine the number of cages in shop
          shop_cgs = allocate_shop_cages(*num_cgs);                                                         // Allocate in dynamic memory a new shop
          fbk_gn_lbu_ye_int("New number of cages in shop", (int)*num_cgs);                                  // Print shop name fbk
        } else {                                                                                            // If file is corrupted
          ++corr_file_flg;                                                                                  // Set corrupted file flag
        }
      
      // Extract data from pet type line
      } else if (line_num == pet_typ_line && !corr_file_flg){                                               // After havin' loaded shop name and number of cages, load pet type
        for (int i = 0; i < (int)strlen(BKP_FILE_TYPE_LBL); ++i){                                           // Check backup file pet type label FOR cycle
          if (file_in_buff[i] != BKP_FILE_TYPE_LBL[i])                                                      // Compare each label char
            ++corr_file_flg;                                                                                // Set corrupted file flag
        }
        txt += (int)strlen(BKP_FILE_TYPE_LBL);                                                              // Extract pet type removing pet type prefix label
        if(strlen(txt) > 3 && !corr_file_flg){                                                              // Check pet type length to detect corrupted file
          txt[strlen(txt)-1] = '\0';                                                                        // Remove last char ('\n' char) from the pet-type extracted string
          if (0 == strcmp(txt, pet_typ_str[EMPTY])){                                                        // If pet type = empty
            shop_cgs[cg_cnt].pet_typ = EMPTY;                                                               // Set empty pet type in cage
            fbk_nl(1);  fbk_gn_lbu_ye_str("Loading pet from backup file, pet type", pet_typ_str[EMPTY]);    // New line fbk + print pet type fbk
          } else if (0 == strcmp(txt, pet_typ_str[CAT])){                                                   // If pet type = cat
            shop_cgs[cg_cnt].pet_typ = CAT;                                                                 // Set cat pet type in cage
            fbk_nl(1);  fbk_gn_lbu_ye_str("Loading pet from backup file, pet type", pet_typ_str[CAT]);      // New line fbk + print pet type fbk
          } else if (0 == strcmp(txt, pet_typ_str[DOG])){                                                   // If pet type = dog
            shop_cgs[cg_cnt].pet_typ = DOG;                                                                 // Set dog pet type in cage
            fbk_nl(1);  fbk_gn_lbu_ye_str("Loading pet from backup file, pet type", pet_typ_str[DOG]);      // New line fbk + print pet type fbk
          } else if (0 == strcmp(txt, pet_typ_str[HAMSTER])){                                               // If pet type = hamster
            shop_cgs[cg_cnt].pet_typ = HAMSTER;                                                             // Set hamster pet type in cage
            fbk_nl(1);  fbk_gn_lbu_ye_str("Loading pet from backup file, pet type", pet_typ_str[HAMSTER]);  // New line fbk + print pet type fbk
          } else if (0 == strcmp(txt, pet_typ_str[RABBIT])){                                                // If pet type = rabbit
            shop_cgs[cg_cnt].pet_typ = RABBIT;                                                              // Set rabbit pet type in cage
            fbk_nl(1);  fbk_gn_lbu_ye_str("Loading pet from backup file, pet type", pet_typ_str[RABBIT]);   // New line fbk + print pet type fbk
          } else {                                                                                          // In case of unknown pet type
            ++corr_file_flg;                                                                                // Set corrupted file flag
          }
        } else {                                                                                            // If file is corrupted
          ++corr_file_flg;                                                                                  // Set corrupted file flag
        }
        pet_typ_line += (3+BKP_FILE_SEP_SPACES_CAGES);                                                      // Pet type line idx val upd
      
      // Extract data from pet name line
      } else if (line_num == pet_name_line && !corr_file_flg){                                              // After havin' loaded pet type, load pet name
        for (int i = 0; i < (int)strlen(BKP_FILE_PET_NAME_LBL); ++i){                                       // Check backup file pet name label FOR cycle
          if (file_in_buff[i] != BKP_FILE_PET_NAME_LBL[i])                                                  // Compare each label char
            ++corr_file_flg;                                                                                // Set corrupted file flag
        }
        txt += (int)strlen(BKP_FILE_PET_NAME_LBL);                                                          // Extract pet name removing pet name prefix label
        if(strlen(txt) > MIN_PET_NAME_CHRS+1 && !corr_file_flg){                                            // Check pet name length to detect corrupted file
          txt[strlen(txt)-1] = '\0';                                                                        // Remove last char ('\n' char) from extracted pet name string
          switch (shop_cgs[cg_cnt].pet_typ)                                                                 // Pet type switch-case
          {
          case EMPTY:                                                                                       // Case pet type = empty
            break;                                                                                          // Skip
          /////////
          case CAT:                                                                                         // Case pet type = cat
            strcpy(shop_cgs[cg_cnt].pet.cat.name, txt);                                                     // Set cat name in cage
            break;
          /////////
          case DOG:                                                                                         // Case pet type = dog
            strcpy(shop_cgs[cg_cnt].pet.dog.name, txt);                                                     // Set dog name in cage
            break;
          /////////////
          case HAMSTER:                                                                                     // Case pet type = hamster
            strcpy(shop_cgs[cg_cnt].pet.hamster.name, txt);                                                 // Set hamster name in cage
            break;
          ////////////
          case RABBIT:                                                                                      // Case pet type = rabbit
            strcpy(shop_cgs[cg_cnt].pet.rabbit.name, txt);                                                  // Set rabbit name in cage
            break;
          ////////
          default:                                                                                          // In case of unknown pet type
            ++corr_file_flg;                                                                                // Set corrupted file flag
            break;
          }
          fbk_nl(1);  fbk_gn_lbu_ye_str("                              pet name", txt);                     // New line fbk + print pet name fbk
        } else {                                                                                            // If file is corrupted
          ++corr_file_flg;                                                                                  // Set corrupted file flag
        }
        pet_name_line += (3+BKP_FILE_SEP_SPACES_CAGES);                                                     // Pet name line idx val upd
      
      // Extract data from pet age line
      } else if (line_num == pet_age_line && !corr_file_flg){                                               // After havin' loaded pet name, load pet age
        for (int i = 0; i < (int)strlen(BKP_FILE_PET_AGE_LBL); ++i){                                        // Check backup file pet age label FOR cycle
          if (file_in_buff[i] != BKP_FILE_PET_AGE_LBL[i])                                                   // Compare each label char
            ++corr_file_flg;                                                                                // Set corrupted file flag
        }
        txt += (int)strlen(BKP_FILE_PET_AGE_LBL);                                                           // Extract pet age removing pet age prefix label
        txt[strlen(txt)-1] = '\0';                                                                          // Remove last char ('\n' char) from extracted pet age string
        if (0 != strcmp(txt, pet_typ_str[EMPTY])){                                                          // Check if cage is not empty
          tmp_num = atoi(txt);                                                                              // Save loaded pet age inside a tmp var
          if (tmp_num > 1 && tmp_num < MAX_PET_AGE && !corr_file_flg){                                      // Check pet age tmp var val to detect corrupted file
            switch (shop_cgs[cg_cnt].pet_typ)                                                               // Pet type switch-case
            {
            case EMPTY:                                                                                     // Case pet type = empty
              break;                                                                                        // Skip
            /////////
            case CAT:                                                                                       // Case pet type = cat
              shop_cgs[cg_cnt].pet.cat.age = (byte)tmp_num;                                                 // Set cat age in cage
              break;
            /////////
            case DOG:                                                                                       // Case pet type = dog
              shop_cgs[cg_cnt].pet.dog.age = (byte)tmp_num;                                                 // Set dog age in cage
              break;
            /////////////
            case HAMSTER:                                                                                   // Case pet type = hamster
              shop_cgs[cg_cnt].pet.hamster.age = (byte)tmp_num;                                             // Set hamster age in cage
              break;
            ////////////
            case RABBIT:                                                                                    // Case pet type = rabbit
              shop_cgs[cg_cnt].pet.rabbit.age = (byte)tmp_num;                                              // Set rabbit age in cage
              break;
            ////////
            default:                                                                                        // In case of unknown pet type
              ++corr_file_flg;                                                                              // Set corrupted file flag
              break;
            }
            fbk_nl(1);  fbk_gn_lbu_ye_str("                              pet age", txt);                    // New line fbk + print pet age fbk
          }
        } else if (0 == strcmp(txt, pet_typ_str[EMPTY])){                                                   // If cage is empty, skip printin' fbk
          fbk_nl(1);  fbk_gn_lbu_ye_str("                              pet age", txt);                      // New line fbk + print pet age fbk
        } else {                                                                                            // If file is corrupted
          ++corr_file_flg;                                                                                  // Set corrupted file flag
        }
        pet_age_line += (3+BKP_FILE_SEP_SPACES_CAGES);                                                      // Pet age line idx val upd
        ++cg_cnt;                                                                                           // Cage counter val upd
      }
      if (!corr_file_flg && cg_cnt > *num_cgs)                                                              // Check if non-expected lines has been added at the end of the file
        ++corr_file_flg;                                                                                    // Set corrupted file flag
    }
    if (corr_file_flg){
      fbk_nl(1);                                                                                            // New line fbk                                                                                     // If file corrupted flag has been set
      fbk_err("Error! Shop loading from file failed! Backup file corrupted");                               // Print error fbk
    }
    else if (line_num == 0){                                                                                // If file is empty
      fbk_err("Error! Shop loading from file failed! File is empty");                                       // Print error fbk
    }
    if (corr_file_flg || line_num == 0){                                                                    // In case of data not correctly loaded
      if (*num_cgs > 0){                                                                                    // And dynamic memory has already been allocated
        free(shop_cgs);                                                                                     // Clear allocated memo
        shop_cgs = NULL;                                                                                    // Set shop cages memo ptr to null
        *num_cgs = 0;                                                                                       // Set cages number to 0
        fbk_gn_lbu_ye_int("Number of cages in shop set back to", (int)*num_cgs);                            // Print shop name fbk
      }
    }
  } else {                                                                                                  // If file obj is null
    fbk_err("Error! Null file found during file read operation");                                           // Error fbk
    perror("Null file found during file read operation!");                                                  // Print perror fbk
  }
  close_file(bkp_file);                                                                                     // Close file
  return shop_cgs;                                                                                          // Return shop cages
}


void pet_birthday(cage *shop_cgs, const u_shrt cg_n){                                                       // Pet birthday function (non-zero index)
  /* Body */
  switch (shop_cgs[cg_n-1].pet_typ)                                                                         // Pet type switch-case
  {
  case EMPTY:                                                                                               // Case pet type in cage = empty
    fbk_err("Error! The selected cage is empty");                                                           // Print selected cage empty error fbk
    break;
  /////////
  case CAT:                                                                                                 // Case pet type in cage = cat
    shop_cgs[cg_n-1].pet.cat.age++;                                                                         // Increment cat age
    fbk_gn_lbu_ye_int("Cat in cage number", (int)cg_n);                                                     // Print cat cage number fbk
    fbk_nl(1);                                                                                              // New line fbk
    fbk_gn_lbu_ye_int("New cat age", (int)shop_cgs[cg_n-1].pet.cat.age);                                    // Print cat age fbk
    break;
  /////////
  case DOG:                                                                                                 // Case pet type in cage = dog
    shop_cgs[cg_n-1].pet.dog.age++;                                                                         // Increment dog age
    fbk_gn_lbu_ye_int("Dog in cage number", (int)cg_n);                                                     // Print dog cage number fbk
    fbk_nl(1);                                                                                              // New line fbk
    fbk_gn_lbu_ye_int("New dog age", (int)shop_cgs[cg_n-1].pet.dog.age);                                    // Print dog age fbk
    break;
  /////////////
  case HAMSTER:                                                                                             // Case pet type in cage = hamster
    shop_cgs[cg_n-1].pet.hamster.age++;                                                                     // Increment hamster age
    fbk_gn_lbu_ye_int("Hamster in cage number", (int)cg_n);                                                 // Print hamster cage number fbk
    fbk_nl(1);                                                                                              // New line fbk
    fbk_gn_lbu_ye_int("New hamster age", (int)shop_cgs[cg_n-1].pet.hamster.age);                            // Print hamster age fbk
    break;
  ////////////
  case RABBIT:                                                                                              // Case pet type in cage = rabbit
    shop_cgs[cg_n-1].pet.rabbit.age++;                                                                      // Increment rabbit age
    fbk_gn_lbu_ye_int("Rabbit in cage number", (int)cg_n);                                                  // Print rabbit cage number fbk
    fbk_nl(1);                                                                                              // New line fbk
    fbk_gn_lbu_ye_int("New rabbit age", (int)shop_cgs[cg_n-1].pet.rabbit.age);                              // Print rabbit age fbk
    break;
  ////////
  default:                                                                                                  // Case pet type in cage = unknown
    fbk_err("Error! Unknown element in cage found during pet age increment");                               // Print unknown element error fbk
    break;
  }
}


void free_cage(cage *shop_cgs, const u_shrt cg_n){                                                          // Free cage function (non-zero index)
  /* Body */
  if (shop_cgs[cg_n-1].pet_typ != EMPTY){                                                                   // Check if selected cage contains something
    shop_cgs[cg_n-1].pet_typ = EMPTY;                                                                       // Set empty pet type
    fbk_gn_cy("Pet correctly removed!");                                                                    // Pet removed fbk
  } else {
    fbk_err("Error! The selected cage is already empty");                                                   // Already empry cage selected
  }
}
