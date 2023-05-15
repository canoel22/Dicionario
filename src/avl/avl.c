
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
    no->palavras = criarLista();
    no->fb = 0;
    no->altura = 0;
    return no;
}

/******************************* Printa a árvore em ordem ********************************************/

void percurso_emordem(NoAVL *raiz)
{
    if (raiz == NULL)
    {
        return;
    }

    percurso_emordem(raiz->esq);
    printf("\nNó: %c\n", raiz->letra);
    printarLista(raiz->palavras);
    percurso_emordem(raiz->dir);
}

/********************************* Buscar ***********************************************/

NoAVL *buscarAVL(NoAVL *aux, char letra)
{
    if (aux == NULL || letra == aux->letra)
    {
        return aux;
    }
    if (letra < aux->letra)
    {
        return buscarAVL(aux->esq, letra);
    }
    return buscarAVL(aux->dir, letra);
}
/********************************* Inserir ***********************************************/

void inserirAVL(ArvoreAVL *arvore, char letra)
{
    NoAVL *raiz = arvore->raiz;
    NoAVL *y = NULL;
    NoAVL *novoNo = criaNo(letra);

    while (raiz != NULL)
    {
        y = raiz;
        if (raiz->letra < letra)
        {
            raiz = raiz->dir;
        }
        else
        {
            raiz = raiz->esq;
        }
    }

    novoNo->pai = y;

    if (y == NULL)
    {
        arvore->raiz = novoNo;
    }
    else if (novoNo->letra < y->letra)
    {
        y->esq = novoNo;
    }
    else
    {
        y->dir = novoNo;
    }

    NoAVL *aux = novoNo->pai;

    while (aux != NULL)
    {
        int altura_esq = altura(aux->esq);
        int altura_dir = altura(aux->dir);

        atualizaAltura(aux, altura_esq, altura_dir);
        atualizaFB(aux, altura_esq, altura_dir);
        balanceamento(arvore, aux);
        aux = aux->pai;
    }
}

/********************************* Remover ***********************************************/

void removerAVL(ArvoreAVL *arvore, NoAVL *no)
{
    NoAVL *aux;
    if (no->esq == NULL)
    {
        transplante(arvore, no, no->dir);
        aux = no->pai;
    }
    else if (no->dir == NULL)
    {
        transplante(arvore, no, no->esq);
        aux = no->pai;
    }
    else
    {
        NoAVL *y = maximo(no->esq);

        if (y->pai != no)
        {
            aux = y->pai;
            transplante(arvore, y, y->esq);
            y->esq = no->esq;
            y->esq->pai = y;
        }
        else
        {
            aux = y;
        }
        transplante(arvore, no, y);
        y->dir = no->dir;
        y->dir->pai = y;
    }

    while (aux != NULL)
    {
        int altura_esq = altura(aux->esq);
        int altura_dir = altura(aux->dir);

        atualizaAltura(aux, altura_esq, altura_dir);
        atualizaFB(aux, altura_esq, altura_dir);
        balanceamento(arvore, aux);
        aux = aux->pai;
    }
    free(no);
}

/********************************* Transplante ***********************************************
Para movimentar subárvores dentro da árvore de busca binária, definimos uma subrotina TRANSPLANT, que substitui
uma subárvore como um filho de seu pai por uma outra subárvore. 
*/
void transplante(ArvoreAVL *arvore, NoAVL *u, NoAVL *v)
{
    if (u->pai == NULL)
    {
        arvore->raiz = v;
    }
    else if (u == u->pai->esq)
    {
        u->pai->esq = v;
    }
    else
    {
        u->pai->dir = v;
    }

    if (v != NULL)
    {
        v->pai = u->pai;
    }
}

/***************************** Calcula o maior *******************************************/

NoAVL *maximo(NoAVL *no)
{
    NoAVL *atual = no;

    while (atual->dir != NULL)
    {
        atual = atual->dir;
    }
    return atual;
}
/***************************** Faz o balanceamento *******************************************/

void balanceamento(ArvoreAVL *arvore, NoAVL *no)
{
    if (no->fb == 2)
    {
        if (no->esq != NULL && no->esq->fb < 0)
        {
            rotacionarRR(arvore, no->dir);
        }
        rotacionarLL(arvore, no);
    }
    else if (no->fb == -2)
    {
        if (no->dir != NULL && no->dir->fb > 0)
        {
            rotacionarLL(arvore, no->esq);
        }
        rotacionarRR(arvore, no);
    }
}

/*************************** Atualiza o FB *****************************************/

void atualizaFB(NoAVL *no, int altura_esq, int altura_dir)
{
    no->fb = altura_dir - altura_esq;
}

/*************************** Atualiza a altura *****************************************/

void atualizaAltura(NoAVL *no, int altura_esq, int altura_dir)
{
    no->altura = 1 + maior(altura_esq, altura_dir);
}

/*************************** Vê a altura do nó *****************************************/

int altura(NoAVL *no)
{
    if (no != NULL)
    {
        return no->altura;
    }
    return -1;
}

/*************************** Vê qual é o maior entre dois valores *****************************************/

int maior(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

/********************************* Rotação LL ***********************************************/

void rotacionarLL(ArvoreAVL *arvore, NoAVL *x)
{
    NoAVL *aux;

    aux = x->dir;
    x->dir = aux->esq;
    if (aux->esq != NULL)
    {
        aux->esq->pai = x;
    }
    aux->pai = x->pai;
    if (x->pai == NULL)
    {
        arvore->raiz = aux;
    }
    else if (x == x->pai->esq)
    {
        x->pai->esq = aux;
    }
    else
    {
        x->pai->dir = aux;
    }
    aux->esq = x;
    x->pai = aux;

    int altura_esq = altura(x->esq);
    int altura_dir = altura(x->dir);

    atualizaAltura(x, altura_esq, altura_dir);
    atualizaFB(x, altura_esq, altura_dir);
}

/********************************* Rotação RR ***********************************************/

void rotacionarRR(ArvoreAVL *arvore, NoAVL *x)
{
    NoAVL *aux;

    aux = x->esq;
    x->esq = aux->dir;
    if (aux->dir != NULL)
    {
        aux->dir->pai = x;
    }
    aux->pai = x->pai;
    if (x->pai == NULL)
    {
        arvore->raiz = aux;
    }
    else if (x == x->pai->dir)
    {
        x->pai->dir = aux;
    }
    else
    {
        x->pai->esq = aux;
    }
    aux->dir = x;
    x->pai = aux;

    int altura_esq = altura(x->esq);
    int altura_dir = altura(x->dir);

    atualizaAltura(x, altura_esq, altura_dir);
    atualizaFB(x, altura_esq, altura_dir);
}