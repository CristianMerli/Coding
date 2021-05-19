/*
 * Author: Cristian Merli
 * Code title: Cellar library
 * Code version: 2.0
 * Creation date: 10/05/2021
 * Last mod. date: 19/05/2021
 */


/* Libraries */
#include "lib_cellar.h"                                                                                     // Import cellar library header file


/* Functions */
void add_obj_in_cellar(elem **objs_list_head, const char *name, const pos_typ pos_type, const int pos){     // Function to add object in cellar (non-zero index)
  /* Body */
  elem *new_el = allocate_obj(1);                                                                           // Allocate new element inside heap
  strcpy(new_el->obj.name, name);                                                                           // Copy object name in element to add in list
  new_el->obj.date = get_date_time(); fbk_nl(1);                                                            // Get now date/time
  // Add object in specified list position
  switch (pos_type)                                                                                         // Position type to add element in list switch-case
  {
  case HEAD:                                                                                                // Head position case
    fbk_gn_pu("Adding object in list head position");                                                       // Adding element fbk
    add_elem_head(objs_list_head, new_el);                                                                  // Add new elment in objects list (head position)
    break;
  /////////
  case POS:                                                                                                 // Specific position case
    fbk_gn_pu("Adding object in list specific position");                                                   // Adding element fbk
    add_elem_pos(objs_list_head, new_el, pos);                                                              // Add new elment in objects list (specified position, non-zero index)
    break; 
  //////////
  case TAIL:                                                                                                // Tail position case
    fbk_gn_pu("Adding object in list tail position");                                                       // Adding element fbk
    add_elem_tail(objs_list_head, new_el);                                                                  // Add new elment in objects list (tail position)
    break;
  ////////
  default:                                                                                                  // Unknown position type
    if (new_el != NULL){                                                                                    // If heap memo has been correctly allocated
      free(new_el);                                                                                         // Clear new element heap allocated memo
      fbk_err("Error, Unknown specified list position to add new element");                                 // Print error fbk
    }
    break;
  }
}


void add_ex_obj_in_cellar(elem **objs_list_head, const char *name,
                          const date_time *const assign_date, const pos_typ pos_type, const int pos){       // Function to add exsisting object in cellar (non-zero index)
  /* Body */
  elem *new_el = allocate_obj(1);                                                                           // Allocate new element inside heap
  strcpy(new_el->obj.name, name);                                                                           // Copy object name in element to add in list
  new_el->obj.date = *assign_date; fbk_nl(1);                                                               // Set new object assignation date/time equal to passed assignation date/time
  // Add object in specified list position
  switch (pos_type)                                                                                         // Position type to add element in list switch-case
  {
  case HEAD:                                                                                                // Head position case
    fbk_gn_pu("Adding object in list head position");                                                       // Adding element fbk
    add_elem_head(objs_list_head, new_el);                                                                  // Add new elment in objects list (head position)
    break;
  /////////
  case POS:                                                                                                 // Specific position case
    fbk_gn_pu("Adding object in list specific position");                                                   // Adding element fbk
    add_elem_pos(objs_list_head, new_el, pos);                                                              // Add new elment in objects list (specified position, non-zero index)
    break; 
  //////////
  case TAIL:                                                                                                // Tail position case
    fbk_gn_pu("Adding object in list tail position");                                                       // Adding element fbk
    add_elem_tail(objs_list_head, new_el);                                                                  // Add new elment in objects list (tail position)
    break;
  ////////
  default:                                                                                                  // Unknown position type
    if (new_el != NULL){                                                                                    // If heap memo has been correctly allocated
      free(new_el);                                                                                         // Clear new element heap allocated memo
      fbk_err("Error, Unknown specified list position to add new element");                                 // Print error fbk
    }
    break;
  }
}


void print_objects_in_cellar(elem *const *objs_list_head){                                                  // Function to print objects in cellar
  /* Body */
  if (*objs_list_head != NULL){                                                                             // In case objects list has been already initialized
    fbk_nl(1);  fbk_gn_pu("Printing objects in cellar..."); fbk_nl(2);                                      // Printing objects fbk
    // Table print
    const char *table_body_col = OG;                                                                        // Table body color
    const char *table_databody_col = GN;                                                                    // Table data-body color
    const char *table_titles_col = BU;                                                                      // Table titles text color
    const char *table_idx_col = CY;                                                                         // Table indexes text color
    const char *table_data_col = LBU;                                                                       // Table data text color
    int idx = 0;                                                                                            // Table element index
    printf("%s    +------+--------------------------------+-------------------------------+%s\n",
            table_body_col, ER);                                                                            // Top-line of the table
    printf("%s    | %s%4s %s|          %s%12s          %s|        %s%15s        %s|%s\n",
           table_body_col, table_titles_col, "Numb", table_body_col, table_titles_col, "Object names",
           table_body_col, table_titles_col, "Assignment date", table_body_col, ER);                        // First line of the table (column identification)
    printf("%s    +------+--------------------------------+-------------------------------+%s\n",
           table_body_col, ER);                                                                             // Top-line of the data inside the table
    for (elem *tmp_el = *objs_list_head; tmp_el != NULL; tmp_el = tmp_el->nxt, ++idx){                      // Data print FOR cycle
      printf("%s    | %s%4d %s| %s%30s%s | %s%9d%c%2d%c%2d%c%2d%c%2d%c%2d%s      |%s\n",
            table_body_col, table_idx_col, idx+1, table_body_col, table_data_col, tmp_el->obj.name,
            table_databody_col, table_data_col, tmp_el->obj.date.yy, DATE_DELIM_CHR, tmp_el->obj.date.mn,
            DATE_DELIM_CHR, tmp_el->obj.date.dd, DATE_TIME_DELIM_CHR, tmp_el->obj.date.hh-1, TIME_DELIM_CHR,
            tmp_el->obj.date.mm-1, TIME_DELIM_CHR, tmp_el->obj.date.ss-1, table_databody_col, ER);          // Data print (hours, minutes, seconds are +1 to detect errors in atoi when reading objs from file)
      printf("%s    +------+%s--------------------------------+-------------------------------+%s\n",
              table_body_col, table_databody_col, ER);                                                      // Bottom-line of the data inside the table
    }
    fbk_nl(1);                                                                                              // New line fbk
  } else {                                                                                                  // Else if objects list hasn't been already initialized
    fbk_err("Error! List is empty, nothing to print");                                                      // Print error fbk
  }
}


void rmv_obj_name(elem **objs_list_head, const char *obj_name){                                             // Function to remove object by name
  /* Body */
  fbk_nl(1);  fbk_gn_lbu_ye_str("Searching object in list to remove it, searching by name", obj_name);      // Searching element in list fbk
  if (*objs_list_head != NULL && strlen(obj_name) > 0){                                                     // In case objects list has been already initialized and object name string length is greater than zero
    int el_pos = position_by_name(objs_list_head, obj_name);                                                // Find element position in list by obj name (non-zero index)
    fbk_nl(1);                                                                                              // New line fbk
    if (el_pos == 0){                                                                                       // If element position is equal to zero --> no match found
      fbk_gn_lbu_ye_str("No match found! No results for object name", obj_name);                            // Print no match found fbk
    } else {                                                                                                // Else if element position is different from zero --> match found
      fbk_gn_lbu_ye_int("Match fond! First result in list position", el_pos);                               // Print match found and elem pos fbk
      elem *el_rmv = rmv_elem_pos(objs_list_head, el_pos);                                                  // Remove element in determined position (non-zero index)
      fbk_nl(1);  fbk_gn_lbu_ye_str("Name of the removed element", el_rmv->obj.name);                       // Print name of removed element
      free(el_rmv);                                                                                         // Free allocated memo inside heap
    }
  } else if (*objs_list_head == NULL){                                                                      // If list is empty
    fbk_err("Error! Nothing to remove, the list is empty");                                                 // Print error fbk
  } else {                                                                                                  // If object name string length isn't greater than zero
    fbk_err("Error! Name length must be greater than zero");                                                // Print error fbk
  }
}


elem *rmv_obj_old_date(elem **objs_list_head, date_time *date){                                             // Remove elements older than defined date/time (return the list of elements to remove)
  /* Body */
  if (*objs_list_head != NULL){                                                                             // In case objects list has been already initialized
    selection_sort_time(objs_list_head, DECREASING);                                                        // Sort elements by date decreasing order (older elements at the bottom of the list)
    elem *rmv_list_head = *objs_list_head;                                                                  // List of elements to remove (list head ptr)
    int *rmv_list_date_ptr = &rmv_list_head->obj.date.yy, *date_ptr = &date->yy;                            // -
    // -
    for (; rmv_list_head != NULL && *rmv_list_date_ptr <= *date_ptr; rmv_list_head = rmv_list_head->nxt){   // -
      rmv_list_date_ptr = &rmv_list_head->obj.date.yy;                                                      // -
      date_ptr = &date->yy;                                                                                 // -
      for (byte idx = 1; *rmv_list_date_ptr == *date_ptr && idx < 6; ++idx){                                // Compare and redefine element1 and element2 propriety ptrs FOR cylce (cycle 'till years/months/days/hours/minutes/seconds are different)
        switch (idx)                                                                                        // Redefinition index switch-case
        {
        case 1:                                                                                             // If years are equivalents, check months
          rmv_list_date_ptr = &rmv_list_head->obj.date.mn;                                                  // -
          date_ptr = &date->mn;                                                                             // -
          break;
        ///////
        case 2:                                                                                             // If months are equivalents, check days
          rmv_list_date_ptr = &rmv_list_head->obj.date.dd;                                                  // -
          date_ptr = &date->dd;                                                                             // -
          break;
        ///////
        case 3:                                                                                             // If days are equivalents, check hours
          rmv_list_date_ptr = &rmv_list_head->obj.date.hh;                                                  // -
          date_ptr = &date->hh;                                                                             // -
          break;
        ///////
        case 4:                                                                                             // If hours are equivalents, check minutes
          rmv_list_date_ptr = &rmv_list_head->obj.date.mm;                                                  // -
          date_ptr = &date->mm;                                                                             // -
          break;
        ///////
        case 5:                                                                                             // If minutes are equivalents, check seconds
          rmv_list_date_ptr = &rmv_list_head->obj.date.ss;                                                  // -
          date_ptr = &date->ss;                                                                             // -
          break;        
        }
      }
    }
    fbk_nl(1);  fbk_gn_pu("Objects to remove...");                                                          // -
    fbk_nl(1);  fbk_gn_lbu_ye_str("First elem name", rmv_list_head->obj.name);                              // -
    return rmv_list_head;                                                                                   // -
  } else {                                                                                                  // Else if objects list hasn't been already initialized
    fbk_err("Error! Nothing to remove, the list is empty");                                                 // Print error fbk
    return NULL;                                                                                            // Return NULL ptr
  }
}


void save_objs_file(elem *const *objs_list_head, const char *filename){                                     // Function to save objects list on file
  /* Body */
  if (*objs_list_head != NULL && strlen(filename) >= BKP_FILE_MIN_NAME_CHRS){                               // In case objects list has been already initialized and filename string length is greater than zero
    fl bkp_file = open_file(filename, "w+");                                                                // Open file in write mode (clear text)

    elem *tmp_el = *objs_list_head;                                                                         // Tmp element ptr var (objs list copy)
    int objs_num = 1; for (; tmp_el->nxt != NULL; tmp_el = tmp_el->nxt, ++objs_num);                        // Scroll list to determine the number of objects
    fbk_nl(1);  fbk_gn_lbu_ye_str("Exporting objects list on file, file name", filename);                   // Exporting objects list on file fbk

    if (bkp_file != NULL) {                                                                                 // Check file open status
      write_str_on_file(bkp_file, BKP_FILE_TITLE_LBL);                                                      // Write backup title label in first line of backup file
      write_str_on_file(bkp_file, filename);                                                                // Write backup filename in first line of backup file
      write_nl_on_file(bkp_file);                                                                           // Write new line in backup file
      write_str_on_file(bkp_file, BKP_FILE_OBJS_LBL);                                                       // Write number of objects label in backup file
      write_int_on_file(bkp_file, objs_num);                                                                // Write number of objects in backup file

      for (u_shrt i = 0; i <= BKP_FILE_SEP_SPACES_BLOCKS; ++i){                                             // Blocks spaces (new lines) in backup file print for cycle
        write_nl_on_file(bkp_file);                                                                         // Write new line in backup file
      }

      for (tmp_el = *objs_list_head, objs_num = 1; tmp_el != NULL; tmp_el = tmp_el->nxt, ++objs_num){       // Scroll list to write data on file element by element
        write_str_on_file(bkp_file, BKP_FILE_OBJ_LBL);                                                      // Write object number label in backup file
        write_int_on_file(bkp_file, objs_num);                                                              // Write the object number in backup file
        write_nl_on_file(bkp_file);                                                                         // Write new line in backup file
        write_str_on_file(bkp_file, BKP_FILE_OBJ_NAME_LBL);                                                 // Write object name label in backup file
        write_str_on_file(bkp_file, tmp_el->obj.name);                                                      // Write object name in backup file
        write_nl_on_file(bkp_file);                                                                         // Write new line in backup file
        write_str_on_file(bkp_file, BKP_FILE_OBJ_DATE_LBL);                                                 // Write object assignment date/time label in backup file
        char date_time_str[DATE_TIME_STR_LEN];                                                              // Str var to store date/time b4 file write operation
        snprintf(date_time_str, DATE_TIME_STR_LEN, "%d%c%d%c%d%c%d%c%d%c%d", tmp_el->obj.date.yy,
                 DATE_DELIM_CHR, tmp_el->obj.date.mn, DATE_DELIM_CHR, tmp_el->obj.date.dd,
                 DATE_TIME_DELIM_CHR, tmp_el->obj.date.hh, TIME_DELIM_CHR, tmp_el->obj.date.mm,
                 TIME_DELIM_CHR, tmp_el->obj.date.ss);                                                      // Convert obj assignation date/time to str
        write_str_on_file(bkp_file, date_time_str);                                                         // Write obj assignation date/time in backup file

        for (u_shrt i = 0; i <= BKP_FILE_SEP_SPACES_OBJS; ++i){                                             // Spaces between objects (new lines) in backup file print for cycle
          write_nl_on_file(bkp_file);                                                                       // Write new line in backup file
        }
      }
      close_file(bkp_file); open_file(filename, "r"); fbk_nl(1);                                            // Close file and re-open it in read mode
      read_from_file(bkp_file);                                                                             // Read and print data written on file
      close_file(bkp_file);                                                                                 // Close file
      fbk_nl(1);  fbk_gn_cy("Objects list export operation completed!");                                    // Objects list export on file completed fbk
    }
  } else if (*objs_list_head == NULL){                                                                      // If list is empty
    fbk_err("Error! Nothing to save, the list is empty");                                                   // Print error fbk
  } else {                                                                                                  // If filename string length isn't greater than zero
    fbk_err("Error! Filename length must be greater than the minimum defined value");                       // Print error fbk
  }
}


void load_objs_file(elem **objs_list_head, const char *filename){                                           // Function to load objects list from file
  /* Body */
  const u_int objs_bkp_name_line_idx = 1;                                                                   // Objects list backup name line index
  const u_int num_objs_line_idx = 2;                                                                        // Number of objects in list line index
  u_int obj_num_line = (u_int)(objs_bkp_name_line_idx+num_objs_line_idx+BKP_FILE_SEP_SPACES_BLOCKS);        // Object number (in list) line index
  u_int obj_name_line = obj_num_line+1;                                                                     // Object name line index
  u_int obj_date_line = obj_name_line+1;                                                                    // Object assignment date/time line index
  u_int max_line_num = num_objs_line_idx;                                                                   // Max line number in file
  int tmp_num = 0;                                                                                          // Temporary numeric var
  int obj_cnt = 0;                                                                                          // Objects counter
  int num_objs = 0;                                                                                         // Number of objects in list
  char obj_name[IN_BUFF_SIZE] = "";                                                                         // Object name tmp var
  byte corr_file_flg = 0;                                                                                   // Corrupted file flag

  fl bkp_file = open_file(filename, "r");                                                                   // Open file in read-only mode (clear text)
  if (bkp_file != NULL){                                                                                    // Check file ptr not null
    u_int line_num = 0;                                                                                     // Line number counter
    while (fgets(file_in_buff, FILE_IN_BUFF_SIZE, bkp_file) != NULL){                                       // In case of file found, scan lines 'till null line (last one)
      char *txt = file_in_buff;                                                                             // Text pointer
      ++line_num;                                                                                           // Line number val upd
      if (line_num > max_line_num)                                                                          // If line number is greater than max line number
        ++corr_file_flg;                                                                                    // Set corrupted file flag
      // Extract data from objects list backup name line
      if (line_num == objs_bkp_name_line_idx){                                                              // If line number is = objects list backup name line index
        for (int i = 0; i < (int)strlen(BKP_FILE_TITLE_LBL); ++i)                                           // Check backup file title label FOR cycle
          if (file_in_buff[i] != BKP_FILE_TITLE_LBL[i])                                                     // Compare each label char
            ++corr_file_flg;                                                                                // Set corrupted file flag
        txt += (int)strlen(BKP_FILE_TITLE_LBL);                                                             // Extract objects list backup name removing objects list backup name prefix label
        txt[strlen(txt)-1] = '\0';                                                                          // Remove last char ('\n' char) from the objects list backup name string
        if(strlen(txt) > BKP_FILE_MIN_NAME_CHRS && 0 == strcmp(txt, filename) && !corr_file_flg){           // Check backup file name length and val to detect corrupted file
          fbk_nl(1);  fbk_gn_lbu_ye_str("Loading objects list from backup file, backup name", txt);         // Print shop name fbk
        } else                                                                                              // Else if file is corrupted
          ++corr_file_flg;                                                                                  // Set corrupted file flag
      // Extract data from number of objects (in list) line
      } else if (line_num == num_objs_line_idx && !corr_file_flg){                                          // If line number is = number of objects in list line index
        for (int i = 0; i < (int)strlen(BKP_FILE_OBJS_LBL); ++i)                                            // Check backup file objects number label FOR cycle
          if (file_in_buff[i] != BKP_FILE_OBJS_LBL[i])                                                      // Compare each label char
            ++corr_file_flg;                                                                                // Set corrupted file flag
        txt += (int)strlen(BKP_FILE_OBJS_LBL);                                                              // Extract number of objects in list removing number of objects in list prefix label
        tmp_num = atoi(txt);                                                                                // Save loaded number of objects in list inside a tmp var
        if (tmp_num > 0 && !corr_file_flg){                                                                 // Check number of objects in list tmp var val to detect corrupted file
          num_objs = (u_shrt)tmp_num;                                                                       // If file is OK, redefine the number of objects in list
          max_line_num += (BKP_FILE_SEP_SPACES_BLOCKS+BKP_FILE_SEP_SPACES_OBJS+
                          (u_int)num_objs*(BKP_FILE_SEP_SPACES_OBJS+3)-1);                                  // Set max number of line in file to detect corrupted file
        } else                                                                                              // Else if file is corrupted
          ++corr_file_flg;                                                                                  // Set corrupted file flag
      // Extract data from object number (in list) line
      } else if (line_num == obj_num_line && !corr_file_flg){                                               // After havin' loaded backup name and number of objects in list, load object number
        for (int i = 0; i < (int)strlen(BKP_FILE_OBJ_LBL); ++i)                                             // Check backup file object number label FOR cycle
          if (file_in_buff[i] != BKP_FILE_OBJ_LBL[i])                                                       // Compare each label char
            ++corr_file_flg;                                                                                // Set corrupted file flag
        txt += (int)strlen(BKP_FILE_OBJ_LBL);                                                               // Extract object number removing object number prefix label
        tmp_num = atoi(txt);                                                                                // Save loaded object number inside a tmp var
        if(tmp_num == obj_cnt+1 && tmp_num <= num_objs && !corr_file_flg)                                   // Check object number to detect corrupted file
            ++obj_cnt;                                                                                      // If object number is OK, upd obj counter val
        else                                                                                                // Else if file is corrupted
          ++corr_file_flg;                                                                                  // Set corrupted file flag
        obj_num_line += (3+BKP_FILE_SEP_SPACES_OBJS);                                                       // Object number line idx val upd
      // Extract data from object name line
      } else if (line_num == obj_name_line && !corr_file_flg){                                              // After havin' loaded number of objects in list and object number, load object name
        for (int i = 0; i < (int)strlen(BKP_FILE_OBJ_NAME_LBL); ++i)                                        // Check backup file object name label FOR cycle
          if (file_in_buff[i] != BKP_FILE_OBJ_NAME_LBL[i])                                                  // Compare each label char
            ++corr_file_flg;                                                                                // Set corrupted file flag
        txt += (int)strlen(BKP_FILE_OBJ_NAME_LBL);                                                          // Extract object name removing object name prefix label
        if(strlen(txt) > MIN_OBJ_NAME_CHRS && strlen(txt) <= IN_BUFF_SIZE && !corr_file_flg){               // Check object name length to detect corrupted file
          txt[strlen(txt)-1] = '\0';                                                                        // Remove last char ('\n' char) from the object name extracted string
          strcpy(obj_name, txt);                                                                            // Copy object name in tmp var to allocate new obj in heap (when obj assignation date has been loaded from bkp file)
        } else                                                                                              // Else if file is corrupted
          ++corr_file_flg;                                                                                  // Set corrupted file flag
        obj_name_line += (3+BKP_FILE_SEP_SPACES_OBJS);                                                      // Object name line idx val upd
      // Extract data from object assignment date/time line
      } else if (line_num == obj_date_line && !corr_file_flg){                                              // After havin' loaded object number and name, load object assignment date/time
        for (int i = 0; i < (int)strlen(BKP_FILE_OBJ_DATE_LBL); ++i)                                        // Check backup file object assignment date/time label FOR cycle
          if (file_in_buff[i] != BKP_FILE_OBJ_DATE_LBL[i])                                                  // Compare each label char
            ++corr_file_flg;                                                                                // Set corrupted file flag
        txt += (int)strlen(BKP_FILE_OBJ_DATE_LBL);                                                          // Extract object assignment date/time removing object assignment date/time prefix label
        if (strlen(txt) <= DATE_TIME_STR_LEN && strlen(txt) > 14 && !corr_file_flg){                        // Check object assignment date/time string length to detect corrupted file
          txt[strlen(txt)-1] = '\0';                                                                        // Remove last char ('\n' char) from extracted object assignment date/time string
          int date_delim_cnt = 0, date_time_delim_cnt = 0, time_delim_cnt = 0;                              // Tmp vars to check date/time structure
          for (int i = 0; i < (int)strlen(txt); ++i){                                                       // Date/time structure check FOR cycle
            if (txt[i] == DATE_DELIM_CHR)                                                                   // If sel chr is date delimiter
              ++date_delim_cnt;                                                                             // Upd date delimiter cnt
            else if (txt[i] == TIME_DELIM_CHR)                                                              // Else if sel chr is time delimiter
              ++time_delim_cnt;                                                                             // Upd time delimiter cnt
            else if (txt[i] == DATE_TIME_DELIM_CHR)                                                         // Else if sel chr is date/time delimiter
              ++date_time_delim_cnt;                                                                        // Upd date/time delimiter cnt
          }
          if (date_delim_cnt == 2 && date_time_delim_cnt == 1 && time_delim_cnt == 2){                      // If date/time structure is correct
            const char date_delim[] = { DATE_DELIM_CHR, '\0' };                                             // Date delimiter string
            const char date_time_delim[] = { DATE_TIME_DELIM_CHR, '\0' };                                   // Date/time delimiter string
            const char time_delim[] = { TIME_DELIM_CHR, '\0' };                                             // Time delimiter string
            char *date_str = strtok(txt, date_time_delim);                                                  // Extract date str by date/time delimiter char
            char *time_str = strtok(NULL, date_time_delim);                                                 // Extract time str by date/time delimiter char
            date_time tmp_date;                                                                             // Tmp assignation date/time var
            if (strlen(date_str) >= 8 && strlen(date_str) <= 10 &&
                strlen(time_str) >= 5 && strlen(time_str) <= 8){                                            // If date and time strings length are coherent
              date_str = strtok(date_str, date_delim);                                                      // Extract years val by date delimiter char
              tmp_date.yy = atoi(date_str);                                                                 // Save years val in tmp assignation date/time var
              date_str = strtok(NULL, date_delim);                                                          // Extract months val by date delimiter char
              tmp_date.mn = atoi(date_str);                                                                 // Save months val in tmp assignation date/time var
              date_str = strtok(NULL, date_delim);                                                          // Extract days val by date delimiter char
              tmp_date.dd = atoi(date_str);                                                                 // Save days val in tmp assignation date/time var
              time_str = strtok(time_str, time_delim);                                                      // Extract hours val by time delimiter char
              tmp_date.hh = atoi(time_str);                                                                 // Save hours val in tmp assignation date/time var
              time_str = strtok(NULL, time_delim);                                                          // Extract minutes val by time delimiter char
              tmp_date.mm = atoi(time_str);                                                                 // Save minutes val in tmp assignation date/time var
              time_str = strtok(NULL, time_delim);                                                          // Extract seconds val by time delimiter char
              tmp_date.ss = atoi(time_str);                                                                 // Save seconds val in tmp assignation date/time var
              if (chk_date_in_range(tmp_date))                                                              // Check if date/time vals are in range
                add_ex_obj_in_cellar(objs_list_head, obj_name, &tmp_date, TAIL, 0);                         // Add existing object in cellar (add object in list tail position)
              else                                                                                          // If date/time vals aren't in range
                ++corr_file_flg;                                                                            // Set corrupted file flag
            } else                                                                                          // Else if date and time strings length aren't coherent
              ++corr_file_flg;                                                                              // Set corrupted file flag
          } else                                                                                            // Else if date/time structure is incorrect
            ++corr_file_flg;                                                                                // Set corrupted file flag
        } else                                                                                              // If file is corrupted
          ++corr_file_flg;                                                                                  // Set corrupted file flag
        obj_date_line += (3+BKP_FILE_SEP_SPACES_OBJS);                                                      // Pet age line idx val upd
      // Check empty lines
      } else {                                                                                              // Check empty lines in file (spaces between blocks and objects)
        if (0 != strcmp(txt, "\n"))                                                                         // If line isn't empty
          ++corr_file_flg;                                                                                  // Set error flag
      }
    }
    if (line_num != max_line_num)                                                                           // If line number is different from max line number
      ++corr_file_flg;                                                                                      // Set corrupted file flag
    // Check corrupted file flag status and manage empty file case
    if (corr_file_flg){                                                                                     // If file corrupted flag has been set)
      fbk_nl(1);  fbk_err("Error! Objects list loading from file failed! Backup file corrupted");           // Print error fbk
    }
    else if (line_num == 0){                                                                                // Else if file is empty
      fbk_err("Error! Objects list loading from file failed! File is empty");                               // Print error fbk
    }
    if ((corr_file_flg || line_num == 0) && *objs_list_head != NULL){                                       // In case of data not correctly loaded and dynamic memory has already been allocated
      elem *tmp_el = *objs_list_head;                                                                       // Tmp var to clear allocated memo
      for (; tmp_el != NULL; tmp_el = tmp_el->nxt)                                                          // List scrollin' FOR cycle to clear heap allocated memo
        free(tmp_el);                                                                                       // Clear allocated elements
      *objs_list_head = NULL;                                                                               // Set elements liste head to null
      fbk_err("Allocated memory cleared");                                                                  // Print error fbk
    }
    close_file(bkp_file);                                                                                   // Close file
  } else {                                                                                                  // Else if file obj is null
    fbk_err("Error! Null file found during file read operation");                                           // Error fbk
    perror("Null file found during file read operation!");                                                  // Print perror fbk
  }
}
