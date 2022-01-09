// Input output
#include <stdio.h>
//Include atoi
#include <stdlib.h>

void stampa_vettore(int vett[], int size){
    //Indice per il for
    int j;
    //Controllo vettore vuoto
    if(size == 0){
        printf("Il vettore è vuoto\n");
        return;
    }
    //Stampare il contenuto di vett
    printf("Il vettore è composto da:\n[");
    for(j = 0 ; j < size - 1 ; j++){
        printf("%d,",vett[j]);
    }
    printf("%d]\n",vett[j]);
}

int inserisci_elemento(int *vett, int *ind){
    //Stringa 
    char s[5];
    //Intero letto
    int n;
    
    printf("Inserisci un numero:");
    //c = getchar(); getchar(); 
    // Leggo una stringa
    scanf(" %s",s);
    printf("Strina letta: %s\n",s);
    
    //Controllo per verifare se ho letto 'f'
    if( s[0] == 'f' ){
        return 1;
    }

    //Conversione della stringa s in intero
    //https://en.cppreference.com/w/cpp/string/byte/atoi
    n = atoi(s);
    //Inserisco l'elemento dentro al vettore
    vett[(*ind)++] = n;

    return 0;
}

static void bubble_sort(int *const vett, const int size){                                     // Bubble sort algorithm
  /* CODICE */
  int i, j, tmp;                                                                              // Indexes and tmp var to swap elems
  for (i = 0; i < size-1; ++i)                                                                // Array scrollin' FOR cycle
    for (j = i+1; j < size; ++j)                                                              // Unsorted sub-array scrollin' FOR cycle
      if (vett[i] > vett[j]){                                                                 // If elements swap is needed
        tmp = vett[i];                                                                        // Save first val in tmp var
        vett[i] = vett[j];                                                                    // Save second val in first val
        vett[j] = tmp;                                                                        // Save old first val (from tmp var) in second val
      }
}

static void insertion_sort(int *const vett, const int size){                                  // Insertion sort algorithm
  /* CODICE */
  int i, j, tmp;                                                                              // Indexes and tmp var to swap elems
  for (i = 1; i < size; ++i){                                                                 // Array scrollin' FOR cycle
    tmp = vett[i];                                                                            // Save the first unsorted elem in tmp var
    for (j = i-1; tmp < vett[j] && j >= 0; --j){                                              // Find place of val to sort FOR cycle
      vett[j+1] = vett[j];                                                                    // Swap val to sort with the one in its place
      vett[j] = tmp;                                                                          // Complete swap operation
    }
  }
}

static void selection_sort(int *const vett, const int size){                                  // Selection sort algorithm
  /* CODICE */
  int i, j, min_idx, tmp;                                                                     // Indexes and tmp var to swap elems
  for (i = 0; i < size-1; ++i){                                                               // Array scrollin' FOR cycle
    min_idx = i;                                                                              // Min val idx preset
    for (j = i+1; j < size; ++j)                                                              // Unsorted sub-array scrollin' FOR cycle
      if (vett[j] < vett[min_idx])                                                            // Condition to detect min val in unorted sub-array
        min_idx = j;                                                                          // Set min val idx in unsorted sub-array to swap elems
    tmp = vett[i];                                                                            // Save val to swap in tmp var
    vett[i] = vett[min_idx];                                                                  // Swap min val with val to swap
    vett[min_idx] = tmp;                                                                      // Complete swap operation
  }
}


void scelgo_algoritmo(int vett[], int size){
    //Carattere da leggere
    char c;
    //Variabile di ciclo
    int fine = 0;
    do{
        printf("Scegli l'algoritmo: [b,s,i]\n");
        printf("b - per bubble sort\n");
        printf("i - per selection sort\n");
        printf("s - per insertion sort\n");

        //Leggo un char
        scanf(" %c", &c);

        switch (c)
        {
            case 'b':
                bubble_sort(vett, size);
                fine = 1;
                break;

            case 's':
                selection_sort(vett, size);
                fine = 1;
                break;

            case 'i':
                insertion_sort(vett, size);
                fine = 1;
                break;

            default:
                printf("Carattere errato.\n");
                break;
        }
    }while(fine == 0);
}

int main(){
    printf("Inizio Programma\n");
    //Vettore di interi
    int vett[10];
    //Indice del vettore
    int ind = 0; 
    //Fine programma
    int fine = 0;

    //Controllo valore indice e se non ho letto 'f'
    while( fine == 0 && ind < 10){
        //Inserisci elemento dentro al vettore
        fine = inserisci_elemento(vett, &ind);
        //Stampa vettorels
        stampa_vettore(vett, ind);
    }
    //Scelgo algoritmo di ordinamento
    scelgo_algoritmo(vett, ind);
    //Stampa vettore
    stampa_vettore(vett, ind);

    printf("Fine Programma\n");
}
