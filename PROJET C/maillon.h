#ifndef MAILLON_H
#define MAILLON_H

struct maillon {
    void* val;
    struct maillon* suivant;
};

typedef struct maillon* pm;

pm creerMaillon(void* _val, void(*copier)(void*, void**));
void afficherTout(pm m, void(*afficher)(void*));
int comparerMaillon(pm m1, pm m2, int(*comparer)(void* a1, void* a2));
void detruireTout(pm* m,void(*detruire)(void**));

#endif