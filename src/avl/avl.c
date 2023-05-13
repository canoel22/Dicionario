
#include "avl.h"

/******************************* Cria a árvore ********************************************/

ArvoreAVL *criaArvore()
{
    ArvoreAVL *arvore = (ArvoreAVL *)malloc(sizeof(ArvoreAVL));
    arvore->raiz = NULL;
    return arvore;
}

/******************************* Cria a árvore ********************************************/

NoAVL *criaNo(char letra)
{
    NoAVL *no = (NoAVL *)malloc(sizeof(NoAVL));
    no->pai = NULL;
    no->dir = NULL;
    no->esq = NULL;
    no->letra = letra;
    no->palavras = criaLista();
    no->fb = 0;
    no->altura = 0;
    return no;
}

/********************************* Buscar ***********************************************/

NoAVL *buscar(NoAVL *aux, char* letra)
{
    if (aux == NULL || strcmp(letra, aux->letra))
    {
        return aux;
    }
    if (letra < aux->letra)
    {
        return buscar(aux->esq, letra);
    }
    return buscar(aux->dir, letra);
}
/********************************* Inserir ***********************************************/

void inserir(ArvoreAVL* arvore, char* letra )
{
    NoAVL* x = arvore -> raiz;
    NoAVL* y = NULL;
    NoAVL* novoNo = criaNo(letra);

    while (x != NULL){
        y = x;
        if (novoNo -> letra < x -> letra){
            x = x -> esq;
        } else{
            x = x -> dir;
        }
    }

    novoNo -> pai = y;
    if ( y == NULL){
        arvore -> raiz = novoNo;
    } else if (novoNo -> letra < y -> letra){
        y -> esq = novoNo;
    } else{
        y -> dir = novoNo;
    }

    NoAVL* aux = novoNo -> pai;

    while (aux != NULL){
    
        int altura_esq = altura(aux -> esq);
        int altura_dir = altura(aux -> dir);

        atualizaAltura(aux, altura_esq, altura_dir);
        atualizaFB(aux, altura_esq, altura_dir);
        balanceamento (arvore, aux);
        aux = aux -> pai;
    }

}

/********************************* Remover ***********************************************/
// precisa ajustar porque está pra int e precisa ser pra palavra, sendo um pseudocódigo

void remover(NoAVL *r, char *palavra)
{
}

/***************************** Faz o balanceamento *******************************************/

void balanceamento(ArvoreAVL* arvore, NoAVL *no)
{
    if (no->fb == 2)
    {
        if (no->esq->fb == -1)
        {
            rotacionarLL(arvore, no->esq);
        }
        rotacionarRR(arvore, no);
    }
    else if (no->fb == -2)
    {
        if (no->dir->fb == 1)
        {
            rotacionarRR(arvore, no->dir);
        }
        rotacionarLL(arvore, no);
    }
}

/*************************** Atualiza o FB *****************************************/

void atualizaFB(NoAVL* no, int altura_esq, int altura_dir)
{
    no -> fb = altura_dir - altura_esq;
}

/*************************** Atualiza a altura *****************************************/

void atualizaAltura(NoAVL* no, int altura_esq, int altura_dir)
{
    no -> altura = 1 + maior(altura_esq, altura_dir);

}

/*************************** Vê a altura do nó *****************************************/

int altura(NoAVL* no)
{
  if (no != NULL){
    return no->altura;
  }
  return -1;
}

/*************************** Vê qual é o maior entre dois valores *****************************************/

int maior(int a, int b)
{
    if (a > b){
        return a;
    }
    return b;
}

/********************************* Rotação LL ***********************************************/

void rotacionarLL(ArvoreAVL* arvore, NoAVL *x)
{
    NoAVL *aux;

    aux = x -> dir;
    x -> dir = aux -> esq;
    if (aux -> esq != NULL ){
        aux -> esq -> pai = x;
    }
    aux -> pai = x -> pai;
    if (x -> pai == NULL){
        arvore -> raiz = aux;
    } else if (x == x -> pai -> esq) {
        x -> pai -> esq = aux;
    } else{
        x -> pai -> dir = aux;
    }
    aux -> esq = x;
    x -> pai = aux;
}

/********************************* Rotação RR ***********************************************/

void rotacionarRR(ArvoreAVL* arvore, NoAVL *x)
{
    NoAVL *aux;

    aux = x -> esq;
    x -> esq = aux -> dir;
    if (aux -> dir != NULL ){
        aux -> dir -> pai = x;
    }
    aux -> pai = x -> pai;
    if (x -> pai == NULL){
        arvore -> raiz = aux;
    } else if (x == x -> pai -> dir) {
        x -> pai -> dir = aux;
    } else{
        x -> pai -> esq = aux;
    }
    aux -> dir = x;
    x -> pai = aux;
}

