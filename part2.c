/*
 * Ecole polytechnique de Montreal - GIGL
 * Automne  2023
 * Initlab - part2.c
 *
 * ajoutez vos noms, prénoms et matricules
 * Julien Lavigne   2207643
 * Yann Druet       2198643
*/

#include <stdio.h>
#include <stdlib.h>
// Si besoin, ajouter ici les directives d'inclusion et les déclarations globales
// -------------------------------------------------
// TODO

#include <unistd.h>

// -------------------------------------------------
void part21 ()
{
 // TODO
    char messageWrite[] = "77dbcb01f571f1c32e196c3a7d26f62(printed using write)\n";
    char messagePrintf[] = "77dbcb01f571f1c32e196c3a7d26f62(printed using printf)";
    for (int i = 0; i < sizeof(messagePrintf)/sizeof(char); i++) {
        printf("%c", messagePrintf[i]);
    }
    write(1, messageWrite, sizeof(messageWrite));

}

void part22 ()
{
 // TODO
    char buff[1024];
    size_t size = 1024;
    setvbuf(stdout, buff, _IONBF, size);
    part21();
}

int main (int argc, char* argv[])
{
    if (argc!=2)
    {   printf("Le programme a un seul paramètre : 1 ou 2\n");
        return 1;
    }
    switch (atoi(argv[1])) {
         case 1:        part21();
                        break;
         case 2:        part22();
                        break;
        default:        printf(" Le paramètre du programme est invalide\n");
                        return 1;
    }
    return 0;
}