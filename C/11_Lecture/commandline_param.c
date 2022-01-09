/*
 * Author: Cristian Merli
 * Code title: Command-line parameters and ternary operator
 * Code version: 3.0
 * Creation date: 21/05/2021
 * Last mod. date: 24/05/2021
 */ 


/* Libraries */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <stdlib.h>                                                                                         // Standard library inclusion (EXIT_SUCCESS, EXIT_FAILURE)
#include <string.h>                                                                                         // String library inclusion (for strlen ecc.)


/* Main routines */
static int read_cl_param(int argc, char *argv[], int *idx){                                                 // Read command-line parameters routine
  /* Body */
  if (*idx >= argc){                                                                                        // If the number of this parameter is greater than total number of parameters
    printf("- No more parameters to read\n");                                                               // Print no more parameters to read fbk
    return EXIT_FAILURE;                                                                                    // Return exit
  }
  if (strlen(argv[*idx]) == 2 && argv[*idx][0] == '-'){                                                     // If parameter is 2 chars long ('-' char and then a flag identifying letter)
    switch (argv[*idx][1])                                                                                  // Divide in different cases dependin' on char after '-' (flag identifying letter)
    {
    case 'z':                                                                                               // Case 'z' flag
      printf("- Zero following parameters\n");                                                              // Print expecting zero parameters fbk
      ++*idx;                                                                                               // Increment command-line parameters scrollin' idx to read next flag 
      return EXIT_SUCCESS;                                                                                  // Retun ok
    /////////
    case 'o':                                                                                               // Case 'o' flag
      if (*idx+1 < argc){                                                                                   // If the following parameter is present
        printf("- One following parameter: %s\n", argv[*idx+1]);                                            // Print the expected parameter fbk
        *idx += 2;                                                                                          // Increment command-line parameters scrollin' idx to read next flag (skip the parameter)
        return EXIT_SUCCESS;                                                                                // Retun ok
      }
      break;
    /////////
    case 't':                                                                                               // Case 't' flag
      if (*idx+2 < argc){                                                                                   // If the two following parameters are present
        printf("- Two following parameter: %s, %s\n", argv[*idx+1], argv[*idx+2]);                          // Print the two expected parameters fbk
        *idx += 3;                                                                                          // Increment command-line parameters scrollin' idx to read next flag (skip the two parameters)
        return EXIT_SUCCESS;                                                                                // Retun ok
      }
      break;
    ////////
    default:                                                                                                // Case unknown flag
      printf("- Unrecognized parameter!\n");                                                                // Print unrecognized parameter fbk
      return EXIT_FAILURE;                                                                                  // Return exit
    }
    printf("- Wrong number of parameters!\n");                                                              // In case of no expected number of parameters after specific flag, print error fbk
    return EXIT_FAILURE;                                                                                    // Return exit
  } else {                                                                                                  // Else if the parameter flag structure is wrong
    printf("- Wrong parameter structure\n");                                                                // Print error fbk
    return EXIT_FAILURE;                                                                                    // Return exit
  }
}


/* Main cycle */
int main(int argc, char *argv[]){                                                                           // main(number of command-line parameters, command-line parameters string array)
  /* Main vars */
  int a = 0;                                                                                                // Int var for ternary operator example

  /* Code */
  // Ternary operator example
  a = (a >= 0) ? 3 : 6;                                                                                     // Ternary operator --> (var = cond ? true : false)

  // Commad-line parameters print FOR cycle
  for (int i = 0; i < argc; ++i)                                                                            // Print command-line parameters FOR cycle
    printf("--> Parameter number %d: %s\n", i, argv[i]);                                                    // Print command-line parameters (first param: program name, and then other parameters placed in command-line after program run command)
  printf("\n");                                                                                             // New line fbk

  // Command-line parameters management
  int idx = 1;                                                                                              // Bypass program name parameter (the first one)
  while(read_cl_param(argc, argv, &idx) == EXIT_SUCCESS);                                                   // Read command-line parameters routine call in while-loop

  return EXIT_SUCCESS;                                                                                      // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Command-line parameters and ternary operator
 */
