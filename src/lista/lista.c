#include "lista.h"

//funções relacionadas ao uso de lista duplamente encadeada 

/*************************************** Cria a lista *************************************************/

Lista* criaLista()
{
    Lista* lista = (Lista*) malloc (sizeof(Lista));
    lista -> cabeca = NULL;
    lista -> tam = 0;
    return lista;
}

/************************************* Cria o nó da lista ***********************************************/

NoLista* criaNoLista(Lista* lista, char* palavra)
{
    NoLista* noLista = (NoLista*) malloc (sizeof(NoLista));
    strcpy(noLista->palavra, palavra);
    noLista -> ant = NULL;
    noLista -> prox = NULL;
    return noLista;
}

/************************************* Insere um nó da lista ***********************************************/

void insereLista(Lista* lista, char* palavra){
    NoLista *novaPalavra = criaNoLista(lista, palavra);
    novaPalavra -> prox = lista -> cabeca -> prox;
    lista -> cabeca -> prox -> ant = novaPalavra;
    lista -> cabeca -> prox = novaPalavra;
    novaPalavra -> ant = lista -> cabeca;
}

/************************************* Busca um nó da lista ***********************************************/

NoLista *buscaLista(Lista* lista, char* palavra){
    NoLista* aux = lista -> cabeca -> prox;
    while (aux != lista -> cabeca && !(strcmp(aux->palavra, palavra))){
        aux = aux -> prox;
    }
    return aux;
}

/************************************* Remove um nó da lista ***********************************************/

void removeLista(Lista* lista, char* palavra){
    NoLista* aux = buscaLista(lista, palavra);
    aux -> ant -> prox = aux -> prox;
    aux -> prox -> ant = aux -> ant;
    free (aux);
}

/************************************* Insere um nó da lista ***********************************************/

void printaLista(Lista* lista){
    NoLista* aux = lista -> cabeca -> prox;
    while (aux != lista -> cabeca){
        printf("%s\n", aux->palavra);
        aux = aux -> prox;
    }
}

