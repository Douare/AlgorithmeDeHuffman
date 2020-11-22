#include <stdio.h>
#include <stdlib.h>
#include "maillon.h"
#include "liste.h"

lst creerListe(void(*copierArbreListe)(void*, void**),int (*comparerArbreList)(void* a1, void* a2),void (*afficherArbreList)(void* a),void (*detruireArbreListe)(void**)) {
    lst l = (lst)malloc(sizeof(struct liste));
    l->tete = NULL;
    l->copierArbreListe = copierArbreListe;
    l->comparerArbreList = comparerArbreList;
    l->afficherArbreList = afficherArbreList;
    l->detruireArbreListe = detruireArbreListe;
    return l;
}

void ajouterEnPlace(void* val,lst l){
    pm n = creerMaillon(val,l->copierArbreListe);
    if (l->tete==NULL) {
        l->tete = n;
    }else {
        if(comparerMaillon(n,l->tete,l->comparerArbreList) == -1){
            n->suivant=l->tete;
            l->tete=n;
        }else{
           pm tmp = l->tete;
           while((tmp->suivant != NULL) && (comparerMaillon(n,tmp->suivant,l->comparerArbreList) == 1)){
                tmp=tmp->suivant;
           }
           n->suivant=tmp->suivant;
           tmp->suivant=n;
        }
    }
}

void afficherListe(lst l){
    afficherTout(l->tete,l->afficherArbreList);
}

void libererListeTete(lst l){
    l->tete->val=NULL;
    pm ft = l->tete->suivant;
    l->tete->suivant=NULL;
    free(l->tete);
    l->tete=ft;
}

void detruireListe(lst* l){
    detruireTout(&((*l)->tete),(*l)->detruireArbreListe);
    free(*l);
    (*l)=NULL;
}
