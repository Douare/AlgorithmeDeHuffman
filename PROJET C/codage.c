#include "huffman.h"
#include "noeud.h"
#include "liste.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Debut methode intermediare noeud
void detruire(void** h){
	detruireHuffman((huff*) (h));
	*h=NULL;
}

void copier(void* v, void** h){
	*h=constructeurHuff( (*( (huff*) v))->l ,(*((huff*) v))->n );
	detruireHuffman((huff*) v);
}

void afficher(void* h){
	afficherHuffman((huff) h);
}

void* fusion(void* h1, void* h2){
	return fusionHuffman((huff) h1, (huff) h2);
}

int comparer(void* h1, void* h2){
	return comparerHuffman((huff) h1, (huff) h2);
}

int estVide(void* h1){
	return estHuffmanVide((huff) h1);
} 
// Fin methode intermediare pour noeud

// Debut methode intermediare liste
void copierArbreListe(void* val,void** adr){
	arbre a = (arbre) val;
	huff tmp = a -> val;
	huff h=constructeurHuff(tmp->l,tmp->n);
	arbre a1 = creerArbre(&h,&copier,&afficher,&fusion,&detruire,&comparer,&estVide);
	a1->g=a->g;
	a1->d=a->d;
	a->g=NULL;
	a->d=NULL;
	detruireArbre(&a);
	*adr=a1;
}

int comparerArbreList(void* a1, void* a2){
	return comparerArbre((arbre) a1, (arbre) a2);
}

void afficherArbreList(void* a){
	afficherArbre((arbre) a);
}

void detruireArbreListe(void** val){
	detruireArbre((arbre*) val);
}


// Fin methode intermediare pour liste


///////////////////////////////////////////////////////////////////////

void concatener(char** des, char* src){
	*des = realloc(*des,(strlen(*des)+1)*sizeof(char)+1);
	strcat(*des,src);
}

void codeChar(char c, arbre a,char** str){ //renvoit le code de c donné par a
	if(a->g != NULL && a->d != NULL){ //a n'est pas une feuille
		if(estDansHuffman(c,((huff)((a->g)->val))->l) == 1) {
			concatener(str,"0");
			codeChar(c,a->g,str);
		}else {
			if(estDansHuffman(c,((huff)((a->d)->val))->l) == 1){
				concatener(str,"1");
				codeChar(c,a->d,str);
			}else{
				concatener(str,"\0");
			}
		}
	}
}

char* codeStr(char* s, arbre a){ //donne le code pour une chaine de caractère 
	char* str = (char*) malloc(sizeof(char) +1);
	strcpy(str,"");
	for (unsigned int i =0; i<strlen(s); i++){
		codeChar(s[i], a,&str);
	}
	return str;
}

char* decodeStr(char* s, arbre a){
	char* str = (char*) malloc(sizeof(char) +1);
	strcpy(str,"");
	arbre b=a;
	for(unsigned int i=0; i<strlen(s); i++){
		if(s[i]=='0'){
			b=b->g;
		}else{
			b=b->d;
		}
		if(b->g == NULL && b->d == NULL){ 
			concatener(&str,((huff)(b->val))->l);
			b=a;
		}
	}
	return str;
}

int occurrencePremierChar(char* s){ //renvoit le nombre d'occurrence du premier caractère de s
	if(strlen(s)!=0){
		char c = s[0];
		int occ = 1;
		for(unsigned int i=1; i<(strlen(s)); i++){
			if(s[i]==c){
				occ=occ+1;
			}else{
				break;
			}
		}
		return occ;

	}else{
		return 0;
	}
}

int comparerChar(const void * a, const void * b){
    return ( (*(char*)a) - (*(char*)b) ); 
} //return un nb négatif si a<b, 0 si a=b, un nb positif sinon


char* trierChaine(char * str){
	char* s = (char*) malloc(strlen(str)*sizeof(char) +1); 
	strcpy(s,str);
	qsort( s, strlen(s) , sizeof(*s), comparerChar );

	return s;
}

char* tronquerChaine(char* msg){
	int occ = occurrencePremierChar(msg);
	int taille = (int) strlen(msg);
	int newTaille = taille-occ;
	char* newChaine = malloc(newTaille*sizeof(char)+1);
	for (int i = 0; i <= newTaille; ++i){
		newChaine[i]=msg[i+occ];
	}
	free(msg);
	msg=NULL;
	return newChaine;
}


arbre creerFeuille(char* s){
	char c[2];
	c[0]=s[0];
	c[1]='\0';
	int occ = occurrencePremierChar(s);
	huff h = constructeurHuff(c,occ);
	arbre a = creerArbre(&h,&copier,&afficher,&fusion,&detruire,&comparer,&estVide);
	return a;
}


lst construireListeArbre(char* msg){
	char* s = trierChaine(msg);
	lst l = creerListe(&copierArbreListe, &comparerArbreList, &afficherArbreList, &detruireArbreListe);
	while(strlen(s)>0){
		arbre a = creerFeuille(s);
		ajouterEnPlace(a, l);
		s = tronquerChaine(s);	
	}
	free(s);
	return l;
}

arbre construireArbreListe(lst l){
	arbre a=NULL;
	if(l != NULL){
		if (l->tete != NULL){
			if (l->tete->suivant != NULL){
				while(l->tete->suivant != NULL){
					a = fusionArbre(l->tete->val,l->tete->suivant->val);
					ajouterEnPlace(a,l);
					libererListeTete(l);
					libererListeTete(l);
				}
			}
			a=l->tete->val;
		}
	}
	return a;
}

char* lire() {
	printf("Une chaine dont la taille est superieure à 2 est attendue..\n");
	char* read = malloc(sizeof(char));
	strcpy(read,"");
	char c = getchar();
	char s[2];
	s[0]=c;
	s[1]='\0';
	while (c != '\n' && c != EOF){ //tant que le buffer n'est pas vide faire ...		
		concatener(&read,s);
		c = getchar();
		s[0]=c;
		s[1]='\0';
	}
	concatener(&read,"\0");
	if ( strlen(read) > 2 ){
		return read;
	}else{
		return lire();
	}
}

char* encodage(char* msg){
	lst l = construireListeArbre(msg);
	arbre a = construireArbreListe(l);
	char* str = codeStr(msg,a);
	detruireListe(&l);
	return str;
}

void viderBuffer(){
    int c = 0;
    while (c != '\n' && c != EOF){
        c = getchar();
    }
}

int lireEntier() {
printf("Saisir 0 ou 1.\n");
int n = getchar()-48; 
char verif = getchar(); 
//vérifie que le buffer ne contient qu'un char
	if(verif == '\n'|| verif==EOF){
		if(n== 0 || n== 1){
			return n;
		}else{
			return lireEntier();
		}	
	}else{
		viderBuffer();
		return lireEntier();
	} 
}



char* lireFichier(char* fileName){
	FILE* fp;
	int size = 0;
	char* text;

	fp = fopen(fileName, "r");
	// On recupere la taille en allant a la fin du fichier
	fseek(fp, 0, SEEK_END); // on va a la fin du fichier
	size = ftell(fp); // cb de bits on a parcouru
	rewind(fp); // retour au debut

	text = malloc((size+1) * sizeof(char));

	fread(text, size, 1, fp);
	text[size] = '\0';
	fclose(fp);
	return text;
}

void ecrireFichier(char* contenu){
	FILE* fich = NULL;
	char* nomFich = "";
	printf("Saisir le nom du fichier dans lequel vous voulez ecrire.(Sans l'extention)\n");
	nomFich=lire();
	fich = fopen(nomFich, "w");
	if(fich != NULL){
		printf("Le fichier %s est créé\n", nomFich);
		fprintf(fich,"%s",contenu);
	}
	free(nomFich);
	fclose(fich);
}

char* existeFichier(){
	FILE* fp;
	char* fich;
	printf("Saisissez le fichier en question.\n");
	fich = lire();
	fp = fopen(fich, "r");
	if(fp==NULL){	
		return existeFichier();
	}else{
		fclose(fp);
		char* res = lireFichier(fich);
		free(fich);
		return res;
	}
}





void ecrireFichierListe(lst l){
	pm tmp = l->tete;
	FILE* fich = NULL;
	fich = fopen("arbre.txt", "w");
	if(fich != NULL){
		while(tmp != NULL){
		arbre a = (arbre) tmp->val;
		huff h = (huff) a->val;
		fprintf(fich,"(%s %d)\n", h->l,h->n);
		tmp=tmp->suivant;
		}
	}
	fprintf(fich,"(%s %d)\n", "K",-1);
	fclose(fich);
	printf("\n\tVotre arbre est entregistré dans un fichier nommé arbre.txt.\n\n");
}

lst construireFichierListe(char* nomFich){
	FILE* fich = NULL;
	fich = fopen(nomFich, "r");

	if(fich != NULL){
		lst l = creerListe(&copierArbreListe, &comparerArbreList, &afficherArbreList, &detruireArbreListe);
		int n = 0;
		char z[2];
		z[0]='a';
		z[1]='\0';
		while( n != -1){
			fscanf(fich, "(%c %d)\n", &z[0], &n);
			huff h = constructeurHuff(z,n);
			arbre a = creerArbre(&h,&copier,&afficher,&fusion,&detruire,&comparer,&estVide);
			if ( n != -1) {
				ajouterEnPlace(a,l);
			} else {
				detruireArbre(&a);
				break;
			}
		}
	printf("\n\n");
		fclose(fich);
		return l;
	} else {
		puts("ERREUR");
		fclose(fich);
		return NULL;
	}
}

void decodageStandard(){
	printf("Veuillez saisir le codage Huffman en binaire de \nvotre message precedemment codé\net le nom du fichier contenant son arbre binaire.\n\n");
	char* codeHuff = lire();
	printf("Veuillez saisir le nom du fichier contenant l'arbre\ndu message que vous souhaitez decoder.\n");
	char* nomFich = lire();
	lst l = construireFichierListe(nomFich);
	arbre a = construireArbreListe(l);
	char * msg = decodeStr(codeHuff, a);
	detruireListe(&l);
	printf("Voici votre message : %s\n", msg);
	free(msg);
	msg=NULL;
	free(nomFich);
	nomFich=NULL;
	free(codeHuff);
	codeHuff=NULL;
}



void encodageStandard(){
	printf("Veuillez saisir votre message..\n\n\n");
	char* msg = lire();
	lst l = construireListeArbre(msg);
	ecrireFichierListe(l);
	arbre a = construireArbreListe(l);
	char* codeHuff = codeStr(msg,a);
	detruireListe(&l);
	free(msg);
	msg=NULL;
	printf("Voici votre codage Huffman en binaire : %s\n\n\n\n", codeHuff);
	free(codeHuff);
	codeHuff=NULL;
}


void encodageFichier(){
	printf("Veuillez saisir le nom du fichier contenant\nle message a coder.");
	char* contenuFichier = existeFichier();
	lst l = construireListeArbre(contenuFichier);
	ecrireFichierListe(l);
	arbre a = construireArbreListe(l);
	char* codeHuff = codeStr(contenuFichier,a);
	detruireListe(&l);
	free(contenuFichier);
	contenuFichier=NULL;
	ecrireFichier(codeHuff);
	free(codeHuff);
	codeHuff=NULL;
}

void decodageFichier(){
	printf("Veuillez saisir le nom du fichier contenant\nle code d'un message codé");
	char* codeHuff = existeFichier();
	printf("Veuillez saisir le nom du fichier contenant l'arbre\ndu message que vous souhaitez decoder.\n");
	char* nomFich = lire();
	lst l = construireFichierListe(nomFich);
	arbre a = construireArbreListe(l);

	char* contenuFichier = decodeStr(codeHuff, a);
	detruireListe(&l);
	ecrireFichier(contenuFichier);
	
	free(contenuFichier);
	contenuFichier=NULL;
	free(nomFich);
	nomFich=NULL;
	free(codeHuff);
	codeHuff=NULL;
}

void saisieFichier(){
	int choix = -1;
	printf("Saisir 1 pour encoder un message\nOu saisir 0 pour decoder.\n\n\n");
	choix=lireEntier();
	if (choix == 1){
		encodageFichier();
	} else {
		decodageFichier();
	}
}



void saisieStandard(){			
	int choix = -1;
	printf("Saisir 1 pour encoder un message\nOu saisir 0 pour decoder.\n\n\n");
	choix=lireEntier();
	if (choix == 1){
		encodageStandard();
	} else {
		decodageStandard();
	}
}
