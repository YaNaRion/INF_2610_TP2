/*
 * Ecole polytechnique de Montreal - GIGL
 * Automne  2023
 * Initlab - part1.c
 * 
 * ajoutez vos noms, prénoms, matricules et votre section de laboratoire
 * Julien Lavigne 2207643
 * Yann Druet     2198643
 */

// TODO
// Si besoin, ajouter ici les directives d'inclusion et les déclarations globales
// -------------------------------------------------
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
   char* filename = "output2.txt";
   char* input_query = "Saisissez votre texte suivi de CTRL-D :\n";
// -------------------------------------------------

int main () {
    // TODO
    char userInput[50];
    int fd = open(filename,O_WRONLY,O_TRUNC);
    if (fd >= 0){
        printf("%s", input_query);
        int n = read(0, userInput, sizeof(userInput));
        write(fd, userInput, n);
        close(fd);
    }
    return 0;
}