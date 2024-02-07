/*
 * processlab - part1.c
 *
 * Ecole polytechnique de Montreal, GIGL, Hiver  2024
 * vos noms, prénoms et matricules
*/

#include "libprocesslab/libprocesslab.h"

// TODO
// Si besoin, ajouter ici les directives d'inclusion
// -------------------------------------------------

// -------------------------------------------------

void question1()
{
    int parent1;
    int parent2;
    int parent3;
   if((parent1 = fork()) ==0){
    // 1.1
    if (fork() == 0){
        // 2.1
    }
    if (fork() == 0) {
        // 2.2
    }

   }
   if((parent2 = fork()) == 0){
    // 1.2
    if (fork() ==0 ) {
        // 2.3
    }
   }
   if((parent3 = fork()) == 0){}
    // TODO
    // 1.3
    if (fork() == 0) {
        // 2.4
    }
    if( fork() == 0){
        // 2.5
    }
    if( fork() == 0){
        // 2.6
    }

    while(wait(NULL)>0);
    _exit(0);
}
