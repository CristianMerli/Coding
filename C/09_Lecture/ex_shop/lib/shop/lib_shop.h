/*
 * Author: Cristian Merli
 * Code title: Shop library header file
 * Code version: 3.0
 * Creation date: 10/05/2021
 * Last mod. date: 10/05/2021 
 */


/* Libraries */
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file
#include "../files/lib_files.h"                                                                             // Import files library header file


/* Constants */
#define NUM_TYPE_OF_PETS            5                                                                       // Number of different types of pets
#define MIN_PET_NAME_CHRS           3                                                                       // Min pet name chars
#define MAX_NUM_CGS_ADD             99                                                                      // Max number of cages that can be added
#define MAX_PET_AGE                 50                                                                      // Max assignable pet age
#define PET_NAME_STR_LEN            30                                                                      // Pet name string length
#define BKP_FILE_IN_BUFF_SIZE       1024                                                                    // Backup file input buffer size
#define BKP_FILE_SEP_SPACES_BLOCKS  2                                                                       // Number of blocks separation spaces in backup file (between title/cages number and pets in cages)
#define BKP_FILE_SEP_SPACES_CAGES   1                                                                       // Number of cages separation spaces in backup file (between each pet in cage)
#define BKP_FILE_MIN_NAME_CHRS      3                                                                       // Min number of backup file name chars
#define BKP_FILE_TITLE_LBL          "-->  Shop name: "                                                      // Shop name label in backup file
#define BKP_FILE_CAGES_LBL          "-->  Number of cages in shop: "                                        // Number of cages label in backup file
#define BKP_FILE_TYPE_LBL           "-> Pet type: "                                                         // Pet type label in backup file
#define BKP_FILE_PET_NAME_LBL       "- Pet name: "                                                          // Pet name label in backup file
#define BKP_FILE_PET_AGE_LBL        "- Pet age: "                                                           // Pet age label in backup file


/* Enums & data-types */
typedef enum pet_typ{ EMPTY, CAT, DOG, HAMSTER, RABBIT } pet_typ;                                           // Pet type enum typedef
const char *pet_typ_str[NUM_TYPE_OF_PETS] = { "EMPTY", "CAT", "DOG", "HAMSTER", "RABBIT" };                 // Pet type strings vector associated to pet type enum


/* Unions & data-types */
typedef union pet                                                                                           // Pet union (cat, dog, hamster and rabbit structs)
{
  struct cat                                                                                                // Cat (name string and age val)
  {
    char name[PET_NAME_STR_LEN];                                                                            // Cat name
    byte age;                                                                                               // Cat age
  } cat;
  //////////
  struct dog                                                                                                // Dog (name string and age val)
  {
    char name[PET_NAME_STR_LEN];                                                                            // Dog name
    byte age;                                                                                               // Dog age
  } dog;
  //////////////
  struct hamster                                                                                            // Hamster (name string and age val)
  {
    char name[PET_NAME_STR_LEN];                                                                            // Hamster name
    byte age;                                                                                               // Hamster age
  } hamster;
  /////////////
  struct rabbit                                                                                             // Rabbit (name string and age val)
  {
    char name[PET_NAME_STR_LEN];                                                                            // Rabbit name
    byte age;                                                                                               // Rabbit age
  } rabbit;
} pet;


/* Structs & data-types */
typedef struct cage                                                                                         // Cage (pets pointer) typedef
{
  pet pet;                                                                                                  // Pet in cage (pet union)
  pet_typ pet_typ;                                                                                          // Pet type in cage (pet-type enum)
} cage;

typedef struct shop                                                                                         // Shop (cages vector pointer) typedef
{
  cage *cages;                                                                                              // Cages vector pointer
} shop;


/* Library functions */
void shop_report(cage *shop_cgs, const u_shrt num_cgs);                                                     // Shop report function

void assign_pet_to_cage(cage *shop_cgs, const u_shrt cg_n, const pet_typ tmp_pet_typ);                      // Assign pet to cage function (non-zero index)

cage *allocate_shop_cages(const u_shrt num_cgs);                                                            // Shop cages dyn memo alloc (calloc) function

cage *reallocate_shop_cages(cage *shop_cgs, const u_shrt num_cgs);                                          // Shop cages dyn memo realloc function

void bkp_shop_on_file(cage *shop_cgs, const u_shrt num_cgs, const char *filename, const char *shopname);    // Backup shop status on file function

cage *load_shop_from_file(cage *shop_cgs, u_shrt *num_cgs, const char *filename);                           // Load shop status from file function

void pet_birthday(cage *shop_cgs, const u_shrt cg_n);                                                       // Pet birthday function (non-zero index)

void free_cage(cage *shop_cgs, const u_shrt cg_n);                                                          // Free cage function (non-zero index)
