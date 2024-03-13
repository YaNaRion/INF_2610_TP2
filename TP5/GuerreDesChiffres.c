#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <semaphore.h>

bool flag_de_fin = false;
int nombreChiffreProduit = 0;
int* tampon;
int tailleDuTampon;
int ic = 0;
int ip = 0;
sem_t P;
sem_t C;
sem_t mutex; 

int chiffresProduits = 0;
int chiffresConsommes = 0;

void* producteur(void* pid) {

    srand(time( NULL ));
    int x = 0;
    int* somme = malloc(sizeof(int));

    while(!flag_de_fin) {
        
        sem_wait(&P);
        sem_wait(&mutex);

        if(!flag_de_fin) {
            x =(rand() % 9) + 1;
            chiffresProduits++;
            tampon[ip] = x; 
            ip = (ip+1) % tailleDuTampon; 
        }

        sem_post(&mutex);
        sem_post(&C);
    }
    pthread_exit((void*) somme);
}

void* consommateur(void* cid) {

    int* somme = malloc(sizeof(int));

    int valeurLue = 0;
    while (true) {

        sem_wait(&C);
        sem_wait(&mutex);

        valeurLue = tampon[ic];
        somme += valeurLue;
        ic = (ic+1) % tailleDuTampon;
        if (valeurLue != 0) {
            chiffresConsommes++;
        }
        printf("%d \n", valeurLue);
        sem_post(&mutex);
        sem_post(&P);
        
        if (valeurLue == 0) break;
    }

    pthread_exit((void*) somme);
}

void sigAlarmHandler(int signum) {
    flag_de_fin = true;
    printf("ALARME %d \n", signum);
}

int main(int argc, char* argv[]) {
    // Les paramètres du programme sont, dans l'ordre :
    // le nombre de producteurs, le nombre de consommateurs
    // et la taille du tampon.


    int nbProds =  atoi(argv[1]);
    int nbCons = atoi(argv[2]);
    int sommeProd[nbProds];
    int sommeCons[nbCons];
    tailleDuTampon = atoi(argv[3]);


    sem_init(&P,0,tailleDuTampon);
    sem_init(&C,0,0);
    sem_init(&mutex,0,1);
    tampon = malloc(tailleDuTampon*sizeof(int));

    // création des threads producteurs
    pthread_t prodThread[nbProds];
    for(int i = 0; i < nbProds; i++) {
        pthread_create(&prodThread[i], NULL, producteur, (void*) &i);
    }

    // création des threads consommateurs
    pthread_t consThread[nbCons];
    for(int i = 0; i < nbCons; i++) {
        pthread_create(&consThread[i], NULL, consommateur, (void*) &i);
    }

    // alarme de 1 secondes qui met la variable flag_de_fin à true
    signal(SIGALRM,sigAlarmHandler);
    alarm(1);

    // attente de la fin des producteurs
    for(int i = 0; i < nbProds; i++) {
        pthread_join(prodThread[i], (void**) &sommeProd[i]);
    }

    // tampon des consommateurs mis à 0 (pour les forcer à terminer)
    for (int i = 0; i <  nbCons; i++) {
        sem_wait(&P);
        sem_wait(&mutex);
        tampon[i] = 0;
        sem_post(&mutex);
        sem_post(&C);
    }
    

    // attente de la fin des consommateurs
    for(int i = 0; i < nbCons; i++) {
        pthread_join(consThread[i], (void**) &sommeCons[i]);
    }


    int sommeDesProducteurs = 0;
    for(int i = 0; i < nbProds; i++) {
        sommeDesProducteurs += sommeProd[i];
        // free(sommeProd[i]);
    }

    int sommeDesConsommateurs = 0;
    for(int i = 0; i < nbCons; i++) {
        sommeDesConsommateurs += sommeCons[i];
        // free(sommeCons[i]);
    }
    
    printf("somme des consommateurs: %d \n", sommeDesConsommateurs);
    printf("somme des producteurs: %d \n", sommeDesProducteurs);
    printf("nombre chiffres produits: %d \n", chiffresProduits);
    printf("nombre chiffres consommés: %d \n", chiffresConsommes);

    sem_destroy(&P);
    sem_destroy(&C);
    sem_destroy(&mutex);
    free(tampon);

    return 0;
}
