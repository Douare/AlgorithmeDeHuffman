#ifndef LISTE_H
#define LISTE_H

struct liste {
    pm tete;
    void(*copierArbreListe)(void*, void**);
   	int (*comparerArbreList)(void*, void* );
   	void (*afficherArbreList)(void* );
   	void (*detruireArbreListe)(void**);
};

typedef struct liste* lst;

lst creerListe(void(*copier)(void*, void**),int (*comparerArbreList)(void* a1, void* a2),void (*afficherArbreList)(void* a),void (*detruireArbreListe)(void**));
void ajouterEnPlace(void* val,lst l);
void afficherListe(lst l);
void libererListeTete(lst l);
void detruireListe(lst* l);
#endif