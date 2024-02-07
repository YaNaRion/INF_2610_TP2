  /*
 * processlab - part2.c
 *
 * Ecole polytechnique de Montreal, GIGL, Hiver  2024
 * vos noms, prénoms et matricules
*/

// TODO
// Si besoin, ajouter ici les directives d'inclusion
// -------------------------------------------------

// -------------------------------------------------

#include "./libprocesslab/libprocesslab.h"

#define m 1000000
// question2 calcule la somme des m premiers nombres naturels 1+2+...+m

// nb est le nombre de threads qui vont contribuer au calcul
#define nb 4

//tableau somme est utilisé pour le calcul des sommes patielles par les threads
long somme[nb];


// fonction exécutée par chaque thread créé
void* contribution(void*p)
{
    // TODO
  long tempVal = 0;
  printf("Valeur de p: %ld \n", (long)p);
  for (int i = ((long)p * m / nb) + 1; i < ((long)p + 1)  * m / nb; i++) {
    tempVal += i;
  }
  somme[(long)p] = tempVal;
  pthread_exit(NULL);
  return NULL;
}


void question2( )
{
    // TODO
    pthread_t tid[nb];
  for(int i = 0 ; i< nb; i++){
      pthread_create(&tid[i], NULL, contribution, &i);

  }
    
  for(int i = 0 ; i< nb; i++){
    pthread_join(tid[i], NULL);
  }


  int sommeTotale = 0;
  for (int i = 0; i < nb; i++){
    sommeTotale += somme[i];
  }
  printf("Somme avec threads: %d", sommeTotale);

  int sommeConnue = ( m + 1 ) / 2;
  printf("Somme connue: %d", sommeConnue);
 _exit(0);
}
