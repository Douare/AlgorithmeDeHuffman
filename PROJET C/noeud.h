#ifndef NOEUD_H
#define NOEUD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct noeud {
	void* val;
	struct noeud* g;
	struct noeud* d;
	void(*copier)(void*,void**);
	void(*afficher)(void*);
	void*(*fusion)(void*,void*);
	void(*detruire)(void** v);
	int(*comparer)(void*, void*);
	int(*estVide)(void*);
};

typedef struct noeud* arbre;

arbre creerArbre(void* v, void(*copier)(void*,void**),void(*afficher)(void*),void*(*fusion)(void*,void*),void(*detruire)(void** v),int(*comparer)(void*, void*),int(*estVide)(void*));
void afficherArbre(arbre a);
arbre fusionArbre(arbre a1, arbre a2);
void detruireArbre(arbre *a);
int comparerArbre(arbre a1, arbre a2);
int estArbreVide(arbre a);



#endif
