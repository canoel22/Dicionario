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
NoAVL* criaNo();

NoAVL* buscar();
void inserir ();
void remover (NoAVL *r, char* palavra);

void balanceamento(NoAVL* no);
void rotacionarLL(NoAVL* d);
void rotacionarRR(NoAVL* d);


#endif

