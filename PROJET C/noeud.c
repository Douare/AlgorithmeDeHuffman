#include "noeud.h"

arbre creerArbre(void* v, void(*copier)(void*,void**),void(*afficher)(void*),void*(*fusion)(void*,void*),void(*detruire)(void** v),int(*comparer)(void*,void*),int(*estVide)(void*)){
	arbre a = (arbre) malloc(sizeof(struct noeud));
	a->g=NULL;
	a->d=NULL;
	a->copier=copier;
	a->afficher=afficher;
	a->fusion=fusion;
	a->detruire=detruire;
	a->comparer=comparer;
	a->estVide=estVide;
	a->copier(v,&(a->val));
	return a;
}

void afficherArbre(arbre a){
	if(a==NULL){
		printf("Arbre vide.\n");
	}else{
		if(a->g != NULL){
			afficherArbre(a->g);
		}
		if (a->d != NULL){
			afficherArbre(a->d);
		}
		a->afficher(a->val);
	}
}

void detruireArbre(arbre* a){
	if((*a)==NULL){
	printf("Arbre vide(Rien à supprimer).\n");
	}else{
		if((*a)->g != NULL){
			detruireArbre(&((*a)->g));
		}
		if ((*a)->d != NULL){
			detruireArbre(&((*a)->d));
		}
		(*a)->detruire(&((*a)->val));
		free(*a);
		*a=NULL;
	}
}

arbre fusionArbre(arbre a1,arbre a2){
	void* v = a1->fusion(a1->val,a2->val);
	arbre a = creerArbre(&v,a1->copier,a1->afficher,a1->fusion,a1->detruire,a1->comparer,a1->estVide);
	a->g=a1;
	a->d=a2;
	return a;
}

int comparerArbre(arbre a1, arbre a2){
	if( (a1 != NULL) && (a2 != NULL) ){
		return a1->comparer(a1->val,a2->val);
	} else {
		return -2;
	}
}

int estArbreVide(arbre a){
	return a->estVide(a->val);
}