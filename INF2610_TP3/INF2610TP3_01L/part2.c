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
  printf("Valeur de p: %d \n", *(int*)p);
  for (int i = ((*(int*)p) * m / nb) + 1; i <= ((*(int*)p + 1) * m / nb); i++) {
    tempVal += i;
  }
  somme[*(int*)p] = tempVal;
    pthread_exit(NULL);
}


void question2( )
{
    // TODO
    pthread_t tid[nb];
    int thread_args[nb];

    for(int i = 0 ; i< nb; i++){
      thread_args[i] = i;
      pthread_create(&tid[i], NULL, contribution, &thread_args[i]);
  }

  for (int j = 0; j < nb; j++) {
      printf("Ceci est le résultat du join:  %d, thread numéro %d \n",pthread_join(tid[j], NULL), j );
  }

  printf("BAJOUR \n");

  long sommeTotale = 0;
  for (int i = 0; i < nb; i++){
    sommeTotale += somme[i];
  }
  printf("Somme avec threads: %ld \n", sommeTotale);

  long sommeConnue = (long)m * ( (long)m + 1 ) / 2;
  printf("Somme connue: %ld \n", sommeConnue);


 _exit(0);
}
