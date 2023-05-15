#ifndef __avl_h
#define __avl_h

#include <stdio.h>
#include <stdlib.h>
#include "../lista/lista.h"

/******************************* Estruturas ***********************************************/

typedef struct noAVL
{
    char letra;
    Lista* palavras;
    int fb; //fator de balanceamento
    int altura; 
    struct noAVL* pai;
    struct noAVL* esq;
    struct noAVL* dir;
} NoAVL;

typedef struct arvoreAVL
{
    NoAVL* raiz;
} ArvoreAVL;

/********************************* Funções ***********************************************/

ArvoreAVL* criaArvore();
NoAVL* criaNo(char letra);

void percurso_emordem(NoAVL* raiz);

NoAVL *buscarAVL(NoAVL *aux, char letra);
void inserirAVL(ArvoreAVL *arvore, char letra);
void removerAVL(ArvoreAVL* arvore, NoAVL *raiz);

void balanceamento(ArvoreAVL* arvore, NoAVL *no);
void atualizaFB(NoAVL* no, int altura_esq, int altura_dir);
void atualizaAltura(NoAVL* no, int altura_esq, int altura_dir);
int altura(NoAVL* no);
int maior(int a, int b);
NoAVL* maximo(NoAVL* no);

void rotacionarLL(ArvoreAVL* arvore, NoAVL *x);
void rotacionarRR(ArvoreAVL* arvore, NoAVL *x);

void transplante(ArvoreAVL *arvore, NoAVL *u, NoAVL* v);

#endif

