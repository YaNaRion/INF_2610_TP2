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
    pid_t subparent1;
    pid_t subparent2;
    pid_t subparent3;
    pid_t child1;
    pid_t child2;
    pid_t child3;
    pid_t child4;
    pid_t child5;
    pid_t child6;
    int directChildCount = 0;
    int indirectChildCount = 0;
    int* tempChildCount = &indirectChildCount;


    registerProc(getpid(), getppid(), 0, 0);

   if((subparent1 = fork()) ==0){
    // 1.1
    registerProc(getpid(), getppid(), 1, 1);
    if ((child1 = fork()) == 0){
        // 2.1
        registerProc(getpid(), getppid(), 2, 1);
        _exit(0);
    }
    if ((child2 = fork()) == 0) {
        registerProc(getpid(), getppid(), 2, 2);
        _exit(0);
        // 2.2
    }

    while(wait(NULL)>0) {
    directChildCount++;
   };

    _exit(directChildCount);

   } // fin parent 1

   if((subparent2 = fork()) == 0){
    // 1.2
    registerProc(getpid(), getppid(), 1, 2);

    if ((child3 = fork()) ==0 ) {
        // 2.3
        registerProc(getpid(), getppid(), 2, 3);
        _exit(0);

    }

    while(wait(NULL)>0) {
    directChildCount++;
   };

    _exit(directChildCount);

   } // fin parent 2

   if((subparent3 = fork()) == 0){
    // TODO
    // 1.3
    registerProc(getpid(), getppid(), 1, 3);

    if ((child4 = fork()) == 0) {
        registerProc(getpid(), getppid(), 2, 4);
        _exit(0);
        // 2.4
    }
    if( (child5 = fork()) == 0){
        registerProc(getpid(), getppid(), 2, 5);
        _exit(0);        
        // 2.5
    }
    if( (child6 = fork()) == 0){
        registerProc(getpid(), getppid(), 2, 6);
        _exit(0);
        // 2.6
    }


    while(wait(NULL)>0) {
    directChildCount++;
   };
   
    _exit(directChildCount);

   } // fin parent 3


   while(wait(tempChildCount)>0) {
        directChildCount += (*tempChildCount) / 256 ; // ajout des indirects
        directChildCount++; // ajout des directs
   };


    printf("Nombre d'enfants attendus: %d \n", directChildCount);

    printProcRegistrations();


    _exit(0);
}
