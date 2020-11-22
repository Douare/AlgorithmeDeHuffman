#include "noeud.h"
#include "huffman.h"
#include "maillon.h"
#include "liste.h"  
#include "codage.c"

 

int main(void){

	int choix = 0;
	printf("Saisir 0 pour utiliser E/S standard\nSaisir 1 pour utiliser des fichiers.\n\n\n\n");
	choix=lireEntier();
	if(choix==0){
		saisieStandard();    
	}else{
		saisieFichier();
	}


	



	return 0;
	
}

