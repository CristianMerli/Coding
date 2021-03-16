/*
 * Author: Cristian Merli
 * Code title: Operazioni matematiche, binarie, di confronto e logiche
 * Code version 1.0
 * Creation date: 16/03/2021
 * Last mod. date: 16/03/2021
 */

#include <stdio.h> // Standard I/O library inclusion 

int main(){ // Main cycle
  /* Vars declaration */
  char ciao_mondo, ciaoMondo; // Convenzioni scrittura variabili composte da più nomi (USO LA PRIMA O LA SECONDA)
  int a = 4, b = 5, c;        // Dichiarazione variabili intere (a e b vengono dichiarate e definite/inizializzate --> allocazione in memoria, mentre c viene solo dichiarata) ecc

  /* Code */
  c = 1;                      // Definizione della variabile c gia dichiarata
  ciao_mondo = 'a';           // Definisco variabili dichiarate per evitare warning
  ciaoMondo = 'b';            // Definisco variabili dichiarate per evitare warning

  // Operazioni matematiche
  a = b + c;                  // Somma
  a = b - c;                  // Differenza
  a = b * c;                  // Moltiplicazione
  a = b / c;                  // Divisione intera es. (come int(10 / 4) ==> 2)
  a = b % c;                  // (b modulo c) --> restituisce il resto della divisione intera tra b e c
  // Operazioni contratte
  a++;                        // Somma breve equivale ad (a = a + 1)
  a--;                        // Differenza breve equivale a (a = a - 1)
  // ATTENZIONE !!!
  c = a++;                    // PRIORITA --> Prima assegna (c = a) e poi esegue (a = a + 1) e si avra c diverso da a, uso comando sottostante
  c = ++a;                    // DIVERSO per via della priorita degli operatori, esegue prima (a = a + 1) e poi (c = a) --> operatore di assegnazione ha priorita maggiore di quello di addizione (nel dubbio uso le parentesi, vedi riga sottostante)
  c = (a++);                  // Evita i problemi di priorita visti nelle due righe precedenti con uso delle parentesi
  // Operazioni con assegnamento
  a += c;                     // Equivale ad (a = a + c)
  a *= c;                     // Equivale ad (a = a * c)
  a -= c;                     // Equivale ad (a = a - c)
  a /= c;                     // Equivale ad (a = a / c)
  a %= c;                     // Equivale ad (a = a % c)

  // Operazioni bit a bit
  c = a & b;                  // AND (1 solo se entrambi bit = 1)
  c = a | b;                  // OR  (1 solo se uno dei bit = 1)
  c = a ^ b;                  // XOR (1 solo se bit diversi)
  c = b>>1;                   // Right shift (inserisce zero a sx) --> Equivale a int(b/2)
  c = b<<1;                   // Left shift (inserisce zero a dx) -->  Equivale a int(b*2)
  c <<= 1;                    // Left shift equivale a (c = c << 1)
  c = ~b;                     // Operazione NOT su ogni bit (se bit=0-->1 / bit=1-->0)

  // Operazioni di confronto
  c = (a == b);               // Ritorna 1 se a (a = b) bit a bit
  c = (a != b);               // Ritorna 1 se a (a diverso da b) bit a bit
  c = (a <= b);               // Ritorna 1 se a (a <= b)
  c = (a >= b);               // Ritorna 1 se a (a >= b)
  c = (a < b);                // Ritorna 1 se a (a < b)
  c = (a > b);                // Ritorna 1 se a (a > b)

  // Operazioni logiche
  a = 1, b = 0;               // 0 e 1 equivalgono a true e false per quanto riguarda le operazioni logiche con variabili non booleane
  c = (a && b);               // Risulta true se a AND b sono true (o diverse da zero) --> AND logico
  c = (a || b);               // Risulta true se a OR b sono true (o diverse da zero) --> OR logico
  c = (!a);                   // Risulta true se a = false e vice-versa --> NOT logico
  c = !((a > b) && (a < c));  // Combinazione di operazioni logiche e di confronto

  return 0; // Check errors --> if=0 (NO ERRORS) / if=1 (ERRORS)
} // End main cycle
