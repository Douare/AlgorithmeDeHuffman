#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "maillon.h"

pm creerMaillon(void* v, void(*copier)(void*, void**)) {
    pm n = (pm)malloc(sizeof(struct maillon));
    copier(v, &(n->val));
    n->suivant = NULL;
    return n;
}

void afficherTout(pm m,void(*afficher)(void*)){
	assert (m!=NULL);
    assert (m->val != NULL);
    pm tmp = m;
    while(tmp->suivant!=NULL) {
        afficher(tmp->val);
        tmp = tmp->suivant;
    }
    afficher(tmp->val);
}

int comparerMaillon(pm m1, pm m2, int(*comparer)(void* a1, void* a2)){
	return comparer(m1->val,m2->val);
}

void detruireTout(pm* m,void(*detruire)(void**)) {
    if ((*m)!=NULL) {
        if ((*m)->suivant != NULL)
            detruireTout(&((*m)->suivant),detruire);
        detruire(&((*m)->val));
        free(*m);
        *m = NULL;
    }
}


