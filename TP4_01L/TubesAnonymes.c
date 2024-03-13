// Ajouter les directives d'inclusion nécessaires
#include <stdio.h> // pour printf
#include <stdlib.h> // pour rand and srand
#include <time.h> // pour time
#include <unistd.h> // pour write, read, pipe and close
#include <sys/wait.h> // pour wait
#include <fcntl.h> // pour open
#include <sys/types.h> // pour mkfifo
#include <sys/stat.h> // pour mkfifoint exo1() { // Exercice sur tupe anonyme
#include <signal.h>

int main() {
     // P3 diff - In.txt > Output.txt
     if(fork() == 0) {
        int secondPipe[2];  
        pipe(secondPipe);

        if (fork() == 0) {  // P2 tr [a-z] [A-Z]
            int firstPipe[2];
            pipe(firstPipe);
            
            if (fork() == 0) { // P1  cat In.txt
                dup2(firstPipe[1], STDOUT_FILENO);
                close(firstPipe[0]);
                close(firstPipe[1]);
                execlp("cat", "cat", "In.txt", NULL);
            } 
            dup2(firstPipe[0], STDIN_FILENO);
            dup2(secondPipe[1], STDOUT_FILENO);
            close(firstPipe[0]);
            close(firstPipe[1]);
            close(secondPipe[0]);
            close(secondPipe[1]);
            execlp("tr", "tr", "[a-z]", "[A-Z]", NULL);
        }   

        // rediriger la sortie de Diff (sortie standard) vers le fichier Out.txt
        int outTxt = open("Out.txt", O_WRONLY | O_CREAT| O_TRUNC, 0600);
        dup2(outTxt, STDOUT_FILENO);
        close(outTxt);

        // remplace le "-" (entrée standard) par l'entrée du deuxième Pipe
        dup2(secondPipe[0], STDIN_FILENO);

        close(secondPipe[0]);
        close(secondPipe[1]);
        execlp("diff", "diff", "-","In.txt", NULL);
        }

    while (wait(NULL) > 0);
    return 0;
}
