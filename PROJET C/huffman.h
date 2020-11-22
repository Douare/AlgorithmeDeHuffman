#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct huffman{
	char* l;
	int n;
};

typedef struct huffman* huff;

huff constructeurHuff(char* c,int i);
void detruireHuffman(huff* h);
void afficherHuffman(huff h);
huff fusionHuffman(huff h1, huff h2);
int comparerHuffman(huff h1, huff h2);
int estHuffmanVide(huff h);
int estDansHuffman(char c, char* s);



#endif
