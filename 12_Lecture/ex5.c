/*
 * Author: Cristian Merli
 * Code title: Exercise5
 * Code version: 3.0
 * Creation date: 25/05/2021
 * Last mod. date: 26/05/2021
 */


/* Libraries */
#include <stdio.h>                                                                                          // Standard I/O library inclusion
#include <stdlib.h>                                                                                         // Standard library inclusion (EXIT_SUCCESS, EXIT_FAILURE)


/* Constants */
#define SZ  15                                                                                              // Change coins vector size
#define ZR  0.005f                                                                                          // Zero soil (floatin'-point)


/* Global vars */
//


/* Main routines */
static void exit_dyn_memo_error(){                                                                          // Exit due to dynamic memory allocation error routine
  /* Body */
  perror("Error in dynamic memory management, closing software!");                                          // Print perror fbk
  exit(1);                                                                                                  // Close sw
}


static int calc_chg(const double cost_eur, const double payed_eur, double** chg_coins_eur){                 // Routine to calculate change with min number of coins
  /* Body */
  const double coins_eur[SZ] = {0.01, 0.02, 0.05, 0.10, 0.20, 0.50, 1.00, 2.00, \
                                5.00, 10.00, 20.00, 50.00, 100.00, 200.00, 500.00};                         // Coins vector (in euros) def
  int num_chg_coins[SZ] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};                                    // Number of change coins vect init
  double* tmp_chg_coins_eur_ptr = NULL;                                                                     // Tmp change coins vect (in euros) ptr init
  int chg_coins_eur_size = 0;                                                                               // Change coins vect (in euros) size init
  double chg_eur = payed_eur - cost_eur;                                                                    // Change calulation (in euros) init
  printf("\n- Cost: %.2lf €\n", cost_eur);                                                                  // Cost fbk
  printf("- Payed: %.2lf €\n", payed_eur);                                                                  // Payed fbk
  printf("- Change: %.2lf €\n", chg_eur);                                                                   // Change fbk

  if (chg_eur > -ZR){                                                                                       // If there's need to give back change
    while(1){                                                                                               // Cycle 'till change is equal to zero cents (exit with break)
      for (; chg_eur >= coins_eur[14]; chg_eur -= coins_eur[14], ++num_chg_coins[14]);                      // Calc 500 euros banknotes
      for (; chg_eur >= coins_eur[13]; chg_eur -= coins_eur[13], ++num_chg_coins[13]);                      // Calc 200 euros banknotes
      for (; chg_eur >= coins_eur[12]; chg_eur -= coins_eur[12], ++num_chg_coins[12]);                      // Calc 100 euros banknotes
      for (; chg_eur >= coins_eur[11]; chg_eur -= coins_eur[11], ++num_chg_coins[11]);                      // Calc 50 euros banknotes
      for (; chg_eur >= coins_eur[10]; chg_eur -= coins_eur[10], ++num_chg_coins[10]);                      // Calc 20 euros banknotes
      for (; chg_eur >= coins_eur[9]; chg_eur -= coins_eur[9], ++num_chg_coins[9]);                         // Calc 10 euros banknotes
      for (; chg_eur >= coins_eur[8]; chg_eur -= coins_eur[8], ++num_chg_coins[8]);                         // Calc 5 euros banknotes
      for (; chg_eur >= coins_eur[7]; chg_eur -= coins_eur[7], ++num_chg_coins[7]);                         // Calc 2 euros coins
      for (; chg_eur >= coins_eur[6]; chg_eur -= coins_eur[6], ++num_chg_coins[6]);                         // Calc 1 euro coins
      for (; chg_eur >= coins_eur[5]; chg_eur -= coins_eur[5], ++num_chg_coins[5]);                         // Calc 50 cents coins
      for (; chg_eur >= coins_eur[4]; chg_eur -= coins_eur[4], ++num_chg_coins[4]);                         // Calc 20 cents coins
      for (; chg_eur >= coins_eur[3]; chg_eur -= coins_eur[3], ++num_chg_coins[3]);                         // Calc 10 cents coins
      for (; chg_eur >= coins_eur[2]; chg_eur -= coins_eur[2], ++num_chg_coins[2]);                         // Calc 5 cents coins
      for (; chg_eur >= coins_eur[1]; chg_eur -= coins_eur[1], ++num_chg_coins[1]);                         // Calc 2 cents coins
      for (; chg_eur >= ZR; chg_eur -= coins_eur[0], ++num_chg_coins[0]);                                   // Calc 1 cent coins
      break;                                                                                                // Exit coins num calc while-loop
    }
    for(int k = SZ-1; chg_coins_eur_size >= 0 && num_chg_coins[k] == 0; --k)                                // Output vector size definition FOR cycle
      chg_coins_eur_size = k;                                                                               // Upd out vect size
    if (chg_coins_eur_size >= 1){                                                                           // If size is greater or equal than one
      tmp_chg_coins_eur_ptr = calloc((size_t)chg_coins_eur_size, sizeof(double));                           // Init and alloc change coins vect ptr (in euros) inside heap
      if (tmp_chg_coins_eur_ptr == NULL)                                                                    // Check heap vect ptr (if it's NULL)
        exit_dyn_memo_error();                                                                              // Exit due to dynamic memory allocation error routine call
    }
    for (int j = 0; j < chg_coins_eur_size; ++j)                                                            // Change coins vect ptr (in euros) elems calc FOR cycle
      tmp_chg_coins_eur_ptr[j] = num_chg_coins[j]*coins_eur[j];                                             // Change coins vect ptr (in euros) elems calc
  }
  printf("- Coins (euros):  \
          %.2lf €   %.2lf €   %.2lf €   %.2lf €   %.2lf €   %.2lf €   %.2lf €   %.2lf € \
          %.2lf €   %.2lf €   %.2lf €   %.2lf €   %.2lf €   %.2lf €   %.2lf €\n",
          coins_eur[0], coins_eur[1], coins_eur[2], coins_eur[3], coins_eur[4],
          coins_eur[5], coins_eur[6], coins_eur[7], coins_eur[8], coins_eur[9],
          coins_eur[10], coins_eur[11], coins_eur[12], coins_eur[13], coins_eur[14]);                       // Coins fbk
  printf("- Number of coins:\
          %d pcs    %d pcs    %d pcs    %d pcs    %d pcs    %d pcs    %d pcs    %d pcs  \
          %d pcs    %d pcs     %d pcs     %d pcs     %d pcs      %d pcs      %d pcs\n",
          num_chg_coins[0], num_chg_coins[1], num_chg_coins[2], num_chg_coins[3], num_chg_coins[4],
          num_chg_coins[5], num_chg_coins[6], num_chg_coins[7], num_chg_coins[8], num_chg_coins[9],
          num_chg_coins[10], num_chg_coins[11], num_chg_coins[12], num_chg_coins[13], num_chg_coins[14]);   // Change coins number fbk

  *chg_coins_eur = tmp_chg_coins_eur_ptr;                                                                   // Upd change coins vect (in euros) ptr
  return chg_coins_eur_size;                                                                                // Return change coins vect (in euros) size
}


/* Main cycle */
int main(){
  /* Main vars */
  double cost = 17.32, payed = 20.00;                                                                       // Double vars to test change calculation routine
  double* chg_vect = NULL;                                                                                  // Change vector

  /* Code */
  int chg_vect_size = calc_chg(cost, payed, &chg_vect);                                                     // Routine call to calculate change with min number of coins

  if (chg_vect != NULL && chg_vect_size >= 1){                                                              // If chage vector is not NULL and size is greater or equal than one
    printf("\n-->  [  ");                                                                                   // Print change vector first char
    for (int i = 0; i < chg_vect_size; ++i)                                                                 // Change vector elements print FOR cycle
      printf("%.2lf €  ", chg_vect[i]);                                                                     // Print change vector elements
    printf("]\n");                                                                                          // Print change vector last char
  } else if (chg_vect == NULL && chg_vect_size == -1)                                                       // Else if chage vector is NULL and size is -1
    printf("\n--> No change needed!\n");                                                                    // Print no change needed fbk
  else if (chg_vect == NULL && chg_vect_size == 0)                                                          // Else if chage vector is NULL and size is 0
    printf("\n--> Attention, payed value is less than cost value!\n");                                      // Print payed value is less than cost value fbk
  if (chg_vect != NULL)                                                                                     // Check if change vector ptr is not null
    free(chg_vect);                                                                                         // Free allocated memo inside heap

  return EXIT_SUCCESS;                                                                                      // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
}



/* Task */
/*
 * Creare un software che calcola il resto dato il costo di un prodotto, ed i soldi pagato dal compratore
 * Il resto deve essere dato con il minimo numero di monete (1cent, 2cents, 5cents, 10cents, 20cents, 50cents, 1euro, 2euro)
 * Ritorna NULL se l'importo pagato è minore del costo ( es. 17,32euro, 20euro --> [1,1,1,1,0,1,0,1] --> [0.01, 0.02, 0.05, 0.10, 0.5, 2.0] )
 */
