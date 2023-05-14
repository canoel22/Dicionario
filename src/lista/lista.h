#ifndef __lista_h
#define __lista_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************* Estruturas ***********************************************/

typedef struct noLista
{
    char palavra[50];
    struct noLista *prox;
} NoLista;

typedef struct lista
{
    NoLista *cabeca; // cabeça como nó auxiliar
    int tam;
} Lista;

typedef struct resultadoBusca{
    NoLista* ant;
    NoLista* atual;
} ResultadoBusca;

/******************************* Funções ***********************************************/

Lista* criarLista();
int inserirLista(Lista *lista, char *palavra);
int removerLista(Lista *lista, char *palavra);
ResultadoBusca* buscarLista(Lista *lista, char *palavra);
void printarLista(Lista *lista);


#endif
