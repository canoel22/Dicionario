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
void inserirLista(Lista *lista, char *palavra);
void removerLista(Lista *lista, char *palavra);
ResultadoBusca* buscarLista(Lista *lista, char *palavra);
void printarLista(Lista *lista);


#endif
