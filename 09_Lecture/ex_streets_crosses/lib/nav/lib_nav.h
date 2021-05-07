/*
 * Author: Cristian Merli
 * Code title: Navigator library header file
 * Code version: 3.0
 * Creation date: 04/05/2021
 * Last mod. date: 04/05/2021 
 */


/* Libraries */
#include "../ui/lib_ui.h"                                                                                   // Import UI (terminal I/O) library header file
#include "../timer/lib_timer.h"                                                                             // Import timer library header file


/* Constants */
#define STRTS_NUM 4                                                                                         // Number of streets associated to each cross
#define MIN_CRSS  1                                                                                         // Minimum allowed number of allocated crosses inside crosses collection
#define MAX_CRSS  50                                                                                        // Maximum allowed number of allocated crosses inside crosses collection
#define STR_LEN   30                                                                                        // String length used to define street name


/* Enums & data-types */
typedef enum conn_typ{ NONE, STREET, CROSS } conn_typ;                                                      // Street-connection type enum typedef
typedef enum strts_in_crss{ FIRST, SECOND, THIRD, FOURTH } strts_in_crss;                                   // Streets in cross type enum typedef


/* Unions & data-types */
typedef union conn                                                                                          // Connection union (street or cross)
{
  struct street *strt;                                                                                             // Street connection to other street
  struct cross *cross;                                                                                             // Street connection to cross
} conn;


/* Structs & data-types */
typedef struct street                                                                                       // Street (name, connection type and connection) typedef
{
  char name[STR_LEN];                                                                                       // Street name
  conn_typ conn_typ;                                                                                        // Connection type enum
  conn conn;                                                                                                // Connection element (street or cross by reference with union-pointers)
} street;

typedef struct cross                                                                                        // Cross (STR_NUM streets vector) typedef
{
  street *cross_strts[STRTS_NUM];                                                                           // Streets vector in cross (4 streets per cross)
} cross;


/* Library functions */
void assign_strt_to_crss(street *strt, cross *cross, const byte pos);                                       // Assign street to cross function

void assign_conn_to_strt(street *strt, const union conn *conn, const conn_typ type);                        // Assign connection to street function

void navigate(const street *start_strt);                                                                    // Navigate through streets and crosses function

void print_crs_strts_names(const cross *cross);                                                             // Print street names in cross function

street *create_strts_collection(const u_int num_strts, const char *name);                                   // Dyn memo alloc (calloc) function for streets collection init

street *realloc_strts_collection(street *strts_collec, const u_int num_strts);                              // Dyn memo realloc function for streets collection

void add_strt_in_strts_collection(street *strts_collec, const char *strt_name, const u_int pos);            // Add street in streets collection function

cross *create_crss_collection(const u_int num_crss);                                                        // Dyn memo alloc (calloc) function for crosses collection init

cross *realloc_crss_collection(cross *crss_collec, const u_int num_crss);                                   // Dyn memo realloc function for crosses collection

void print_strts_names_idxs(street *strts_collec, const u_int num_strts);                                   // Print streets names and indexes function

void clear_map(street *strts_collec, cross *crss_collec);                                                   // Clear map from heap (free allocated dyn memo) function
