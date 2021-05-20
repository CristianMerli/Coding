/*
 * Author: Cristian Merli
 * Code title: Cellar library header file
 * Code version: 3.0
 * Creation date: 10/05/2021
 * Last mod. date: 20/05/2021 
 */


/* Libraries */
#include "../lists/lib_lists.h"                                                                             // Import linked lists library header file
#include "../files/lib_files.h"                                                                             // Import files library header file
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file


/* Constants */
#define MIN_OBJ_NAME_CHRS           3                                                                       // Min number of object name chars 
#define BKP_FILE_SEP_SPACES_BLOCKS  2                                                                       // Number of blocks separation spaces in backup file (between title/elements number and objects in list)
#define BKP_FILE_SEP_SPACES_OBJS    1                                                                       // Number of objects separation spaces in backup file (between each object in list)
#define BKP_FILE_MIN_NAME_CHRS      3                                                                       // Min number of backup file name chars
#define BKP_FILE_TITLE_LBL          "-->  Backup name: "                                                    // Backup title label in backup file
#define BKP_FILE_OBJS_LBL           "-->  Number of objects in cellar: "                                    // Number of objects label in backup file
#define BKP_FILE_OBJ_LBL            "-> Object number: "                                                    // Object number label in backup file
#define BKP_FILE_OBJ_NAME_LBL       "   - Object name: "                                                    // Object name label in backup file
#define BKP_FILE_OBJ_DATE_LBL       "   - Object assignment date/time: "                                    // Object assignment date/time label in backup file


/* Enums & data-types */
typedef enum pos_typ {HEAD, TAIL, POS} pos_typ;                                                             // Position type to add element in list enum typedef


/* Library functions */
void add_obj_in_cellar(elem **objs_list_head, const char *name, const pos_typ pos_type, const int pos);     // Function to add object in cellar (non-zero index)

void add_ex_obj_in_cellar(elem **objs_list_head, const char *name,
                          const date_time *const assign_date, const pos_typ pos_type, const int pos);       // Function to add exsisting object in cellar (non-zero index)

void print_objects_in_cellar(elem *const *objs_list_head);                                                  // Function to print objects in cellar

void rmv_obj_name(elem **objs_list_head, const char *obj_name);                                             // Function to remove object by name

elem *rmv_obj_old_date(elem **objs_list_head, date_time *date);                                             // Remove elements older than defined date/time (return the list of elements to remove)

void save_objs_file(elem *const *objs_list_head, const char *filename);                                     // Function to save objects list on file

void load_objs_file(elem **objs_list_head, const char *filename);                                           // Function to load objects list from file
