#ifndef __lista_h
#define __lista_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/******************************* Estruturas ***********************************************/

typedef struct noLista
{
    char palavra[50];
    struct noLista *ant;
    struct noLista *prox;
} NoLista;

typedef struct lista
{
    NoLista *cabeca;
    int tam;
} Lista;

/******************************* Funções ***********************************************/

Lista *criaLista();
NoLista *criaNoLista(Lista *lista, char *palavra);

void insereLista(Lista *lista, char *palavra);
void removeLista(Lista *lista, char *palavra);
NoLista *buscaLista(Lista *lista, char *palavra);

void printaLista(Lista *lista);

#endif
