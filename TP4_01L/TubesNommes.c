// Ajouter les directives d'inclusion nécessaires
#include <unistd.h> // pour write, read, pipe and close
#include <sys/wait.h> // pour wait
#include <fcntl.h> // pour open
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

int main() {

    mkfifo("secondPipe", 0666);
    mkfifo("firstPipe", 0666);
     // P3 diff - In.txt > Output.txt
     if(fork() == 0) {

        if (fork() == 0) {  // P2 tr [a-z] [A-Z]

            if (fork() == 0) { // P1  cat In.txt
                // Rediriger la sortie standard vers l'entrée du premier Pipe
                int firstWrite = open("firstPipe", O_WRONLY);
                dup2(firstWrite, STDOUT_FILENO);

                // Fermer le descripteur inutile
                close(firstWrite);

                execlp("cat", "cat", "In.txt", NULL);
            } 

            // rediriger la sortie standard vers le second Pipe
            // et entrée standard vers le premier pipe
            int secondWrite = open("secondPipe", O_WRONLY); 
            int firstRead = open("firstPipe", O_RDONLY);
            dup2(secondWrite, STDOUT_FILENO);
            dup2(firstRead, STDIN_FILENO);
            
            // Fermer les descripteurs inutiles
            close(secondWrite);
            close(firstRead);

            execlp("tr", "tr", "[a-z]", "[A-Z]", NULL);
        }   

        // rediriger la sortie de Diff (sortie standard) vers le fichier Outn.txt
        int outTxt = open("Outn.txt", O_WRONLY | O_CREAT| O_TRUNC, 0600);
        dup2(outTxt, STDOUT_FILENO);

        // remplace le "-" (entrée standard) par l'entrée du deuxième Pipe
        int secondRead = open("secondPipe", O_RDONLY);
        dup2(secondRead, STDIN_FILENO);

        // Fermer les descripteurs inutiles
        close(secondRead);
        close(outTxt);

        execlp("diff", "diff", "-","In.txt", NULL);
        }

    while (wait(NULL) > 0);
    // Fermer les pipes une fois le programme terminé
    unlink("firstPipe");
    unlink("secondPipe");
    return 0;
}
