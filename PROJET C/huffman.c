#include "huffman.h"

huff constructeurHuff(char* c,int i){
	huff h = (huff) malloc(sizeof(struct huffman));
	int n = strlen(c);
	h->l = (char*) malloc(n * sizeof(char) +1);
	strcpy(h->l,c);
	h->n = i;
	return h;
}

void detruireHuffman(huff* h){
	free((*h)->l); 
	(*h)->l=NULL;

	free(*h);
	*h=NULL;
}

void afficherHuffman(huff h){
	if (h==NULL){
		printf("Huffman Vide.\n" );
	}else{
		printf("%s : %d\n", h->l, h->n);
	}
}

huff fusionHuffman(huff h1, huff h2){
	int i = (h1->n) + (h2 -> n);
	int t = strlen(h1->l) + strlen(h2->l);
	char* c = (char*) malloc(t * sizeof(char) +1);
	strcpy(c,h1->l);
	strcat(c,h2->l);
	huff h = constructeurHuff(c,i);
	free(c);
	c=NULL;
	return h;
}

int comparerHuffman(huff h1, huff h2){
	if( (h1 != NULL) && (h2 != NULL) ){
		if ( (h1->n) < (h2->n) ){
			return -1;
		}else {
			if ( (h1->n) > (h2->n) ){
				return 1;
			}else {
				if( (h1->l[0]) < (h2->l[0]) ){ //les 0° char ne peuvent pas etre egaux.
					return -1;
				}else {
					return 1;
				}
			}
		}
	} else {
		return -2;
	}
}

int estHuffmanVide(huff h){
	if (h == NULL){
		return 1;
	}else{
		return -1;
	}
}

int estDansHuffman(char c, char* s){
	for(unsigned int i=0; i<strlen(s); i++){
		if(s[i] == c){
			return 1;
		}
	}
	return 0;
}