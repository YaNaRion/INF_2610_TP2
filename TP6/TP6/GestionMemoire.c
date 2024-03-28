#include "./libs/lib.h"
#include "stdio.h"

unsigned int calculerNumeroDePage(unsigned long adresse) {
    return adresse >> 10;
}

unsigned long calculerDeplacementDansLaPage(unsigned long adresse) {
    return adresse % 1024;
}

unsigned long calculerAdresseComplete(unsigned int numeroDePage, unsigned long deplacementDansLaPage) {
    return (numeroDePage * 1024) + deplacementDansLaPage;
}

void rechercherTLB(struct RequeteMemoire* req, struct SystemeMemoire* mem) {

	unsigned long numeroDePage = calculerNumeroDePage(req->adresseVirtuelle);

	for (int i = 0; i < TAILLE_TLB; i++) {

		if(mem->tlb->numeroPage[i] == numeroDePage && mem->tlb->entreeValide[i]){
			unsigned long numeroDeCadre = mem->tlb->numeroCadre[i];
			unsigned long deplacement = calculerDeplacementDansLaPage(req->adresseVirtuelle);
			unsigned long addresseTraduite = calculerAdresseComplete(numeroDeCadre, deplacement);
			printf("numero de cadre: %ld", numeroDeCadre);
			printf("deplacement: %ld", deplacement);
			req->estDansTLB = 1;
			req->adressePhysique = &addresseTraduite;
			mem->tlb->dernierAcces[i] = req->date;
			return;
		}
	}

	req->adressePhysique = 0;
	// on recherche dans la TP si on ne trouve pas dans la TLB
	rechercherTableDesPages(req, mem);
	
}

void rechercherTableDesPages(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	// TODO
	unsigned long adressePhysique = 0;
	unsigned long deplacement = calculerDeplacementDansLaPage(req->adressePhysique);
	unsigned int numeroDePage = calculerNumeroDePage(req->adresseVirtuelle);
	if(mem->tp->entreeValide[numeroDePage]) {
		int numeroDeCadre = mem->tp->numeroCadre[numeroDePage];
		adressePhysique = calculerAdresseComplete(numeroDeCadre, deplacement);
		req->estDansTablePages = 1;
		mettreAJourTLB(req, mem);
	}else {
		req->estDansTablePages = 0;
		// ajouterDansMemoire(req, mem);
	}
}

void ajouterDansMemoire(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	unsigned int numeroPage = calculerNumeroDePage(req->adresseVirtuelle);
	unsigned int deplacementDansLaPage = calculerDeplacementDansLaPage(req->adressePhysique);
	unsigned int addrComplete = calculerAdresseComplete(numeroPage, deplacementDansLaPage);
	for (int i = 0; i < TAILLE_MEMOIRE; i++) {
		if (!mem->memoire[i].utilisee) {
			mem->memoire[i].numeroPage[addrComplete] = &numeroPage;
			mem->memoire[i].dernierAcces[addrComplete] = req->date;
			mem->memoire[i].dateCreation[addrComplete] = req->date;
			req->estDansTablePages = 1;
			mem->tp->numeroCadre[numeroPage] = &numeroPage;
			mem->tp->entreeValide[numeroPage] = 1;
			mettreAJourTLB(req, mem);
		}
	}
}	
	
void mettreAJourTLB(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	// TODO
	unsigned int plusVieuxEntreeIndice = 0;
	unsigned int plusVieilleEntreeDate = 0;
	char estAjoute = 0;
	for(int i = 0; i < TAILLE_TLB; i++) {
		if (!mem->tlb->entreeValide[i]) {
			unsigned int numeroPage = calculerNumeroDePage(req->adresseVirtuelle);
			mem->tlb->dateCreation[i] = req->date;
			mem->tlb->dernierAcces[i] = req->date;
			mem->tlb->numeroPage[i] = &numeroPage;
			mem->tlb->numeroCadre[i] = &numeroPage;
			estAjoute = 1;
		}
		if (!estAjoute && mem->tlb->dateCreation[i] > plusVieilleEntreeDate) {
			plusVieilleEntreeDate = mem->tlb->dateCreation[i];
			plusVieuxEntreeIndice = i;
		}
	}

	// la TLB est pleine
	if (!estAjoute) {
		unsigned int numeroPage = calculerNumeroDePage(req->adresseVirtuelle);
		mem->tlb->dateCreation[plusVieuxEntreeIndice] = req->date;
		mem->tlb->dernierAcces[plusVieuxEntreeIndice] = req->date;
		mem->tlb->numeroPage[plusVieuxEntreeIndice] = &numeroPage;
		mem->tlb->numeroCadre[plusVieuxEntreeIndice] = &numeroPage;
		mem->tlb->entreeValide[plusVieuxEntreeIndice] = 1;
	}
}

// NE PAS MODIFIER
int main() {
    evaluate(
		&calculerNumeroDePage, 
		&calculerDeplacementDansLaPage, 
		&calculerAdresseComplete, 
        &rechercherTLB, 
		&rechercherTableDesPages,
		&mettreAJourTLB,
		&ajouterDansMemoire
    );
    return 0;
}
