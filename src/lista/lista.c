#include "lista.h"

Lista* criarLista() {
    Lista *l = (Lista *) malloc(sizeof(Lista));
    l -> cabeca = (NoLista *) malloc(sizeof(NoLista));
    l -> cabeca -> prox =  NULL;
    return l;
}

int inserirLista(Lista *lista, char *palavra) {
    ResultadoBusca *res = buscarLista(lista, palavra);
    NoLista *atual = res->atual;
    NoLista *ant = res->ant;

    if (atual == NULL) {
        NoLista *novoNo = (NoLista *) malloc(sizeof(NoLista));
        strcpy(novoNo->palavra, palavra);
        novoNo -> prox = ant->prox;
        ant->prox = novoNo;
        lista->tam += 1;
        return 1;
    }
    return 0;
}

int removerLista(Lista *lista, char *palavra) {
    ResultadoBusca *res = buscarLista(lista, palavra);
    NoLista *atual = res->atual;
    NoLista *ant = res->ant;

    if (atual != NULL) {
        ant->prox = atual->prox;
        free(atual);
        lista -> tam -= 1;
        return 1;
    }
    return 0;
}

ResultadoBusca* buscarLista(Lista *lista, char *palavra) {
    NoLista *ant = lista -> cabeca;
    NoLista *atual = NULL;
    NoLista *aux = lista -> cabeca -> prox;

    while (aux != NULL) {
        if (strcmp(aux->palavra, palavra) < 0) {
            ant = aux;
            aux = aux->prox;
        } else {
            if (strcmp(aux->palavra, palavra) == 0) {
                atual = aux;
            }
            break;
        }
    }

    ResultadoBusca *resultado = (ResultadoBusca *) malloc(sizeof(ResultadoBusca));
    resultado -> atual = atual;
    resultado -> ant = ant;

    return resultado;
}

void printarLista(Lista *lista) {
    NoLista *atual = lista->cabeca->prox;

    while (atual != NULL)
    {
        printf("%s\n", atual->palavra);
        atual = atual->prox;
    }
}