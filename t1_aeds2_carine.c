#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/******************************* ESTRUTURAS ***********************************************/

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

typedef struct resultadoBusca
{ // struct para o resultado da busca na lista
    NoLista *ant;
    NoLista *atual;
} ResultadoBusca;

typedef struct noAVL
{
    char letra;
    Lista *palavras;
    int fb; // fator de balanceamento
    int altura;
    struct noAVL *pai;
    struct noAVL *esq;
    struct noAVL *dir;
} NoAVL;

typedef struct arvoreAVL
{
    NoAVL *raiz;
} ArvoreAVL;

typedef struct dicionario
{
    ArvoreAVL *arvore;
    int qtd;
} Dicionario;

/********************************** FUNÇÕES **************************************************/

/********************************* Cria lista ***********************************************/

Lista *criarLista()
{
    Lista *l = (Lista *)malloc(sizeof(Lista));
    l->cabeca = (NoLista *)malloc(sizeof(NoLista));
    l->cabeca->prox = NULL;
    return l;
}

/********************************* Busca na lista ***********************************************/

ResultadoBusca *buscarLista(Lista *lista, char *palavra)
{
    NoLista *ant = lista->cabeca;
    NoLista *atual = NULL;
    NoLista *aux = lista->cabeca->prox;

    while (aux != NULL)
    {
        if (strcmp(aux->palavra, palavra) < 0)
        {
            ant = aux;
            aux = aux->prox;
        }
        else
        {
            if (strcmp(aux->palavra, palavra) == 0)
            {
                atual = aux;
            }
            break;
        }
    }

    ResultadoBusca *resultado = (ResultadoBusca *)malloc(sizeof(ResultadoBusca));
    resultado->atual = atual;
    resultado->ant = ant;

    return resultado;
}
/********************************* Insere na lista ********************************************/

int inserirLista(Lista *lista, char *palavra)
{
    ResultadoBusca *res = buscarLista(lista, palavra);
    NoLista *atual = res->atual;
    NoLista *ant = res->ant;

    if (atual == NULL)
    {
        NoLista *novoNo = (NoLista *)malloc(sizeof(NoLista));
        strcpy(novoNo->palavra, palavra);
        novoNo->prox = ant->prox;
        ant->prox = novoNo;
        lista->tam += 1;
        return 1;
    }
    return 0;
}

/********************************* Remove da lista ********************************************/

int removerLista(Lista *lista, char *palavra)
{
    ResultadoBusca *res = buscarLista(lista, palavra);
    NoLista *atual = res->atual;
    NoLista *ant = res->ant;

    if (atual != NULL)
    {
        ant->prox = atual->prox;
        free(atual);
        lista->tam -= 1;
        return 1;
    }
    return 0;
}

/********************************* Printa a lista ***********************************************/

void printarLista(Lista *lista)
{
    NoLista *atual = lista->cabeca->prox;

    while (atual != NULL)
    {
        printf("%s\n", atual->palavra);
        atual = atual->prox;
    }
}

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
/*************************** Atualiza o FB *****************************************/

void atualizaFB(NoAVL *no, int altura_esq, int altura_dir)
{
    no->fb = altura_dir - altura_esq;
}
/***************************** Calcula o menor *******************************************/

NoAVL *maximo(NoAVL *no)
{
    NoAVL *atual = no;

    while (atual->dir != NULL)
    {
        atual = atual->dir;
    }
    return atual;
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

/*************************** Atualiza a altura *****************************************/

void atualizaAltura(NoAVL *no, int altura_esq, int altura_dir)
{
    no->altura = 1 + maior(altura_esq, altura_dir);
}
/********************************* Rotação LL + ajustes no fb/altura ***********************************************/

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

/********************************* Rotação RR + ajustes no fb/altura ***********************************************/

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

/********************************* Transplante ***********************************************/

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

/******************************* Cria dicionário ***********************************************/

Dicionario *criaDicionario()
{
    Dicionario *d = (Dicionario *)malloc(sizeof(Dicionario));
    d->arvore = criaArvore();
    d->qtd = 0;
    return d;
}

/******************************* Busca palavra no dicionário ***********************************************/

void buscarDicionario(Dicionario *dicionario, char *palavra)
{
    char letra = palavra[0];
    NoAVL *no = buscarAVL(dicionario->arvore->raiz, letra);

    if (no == NULL)
    {
        printf("A palavra não está aqui :(\n");
        sleep(3);
        return;
    }

    ResultadoBusca *noLista = buscarLista(no->palavras, palavra);

    if (noLista->atual == NULL)
    {
        printf("A palavra não está aqui :(\n");
        sleep(3);
        return;
    }

    printf("A palavra foi encontrada! :)\n");
    sleep(3);
}

/******************************* Insere palavra no dicionário ***********************************************/

void inserirDicionario(Dicionario *dicionario, char *palavra)
{
    char letra = palavra[0];
    NoAVL *no = buscarAVL(dicionario->arvore->raiz, letra);

    if (no == NULL)
    {
        inserirAVL(dicionario->arvore, letra);
        no = buscarAVL(dicionario->arvore->raiz, letra);
    }

    if (inserirLista(no->palavras, palavra))
    {
        printf("A palavra foi inserida com sucesso!\n");
        sleep(3);
        dicionario->qtd += 1;
    }
}

/******************************* Remove palavra no dicionário ***********************************************/

void removerDicionario(Dicionario *dicionario, char *palavra)
{
    char letra = palavra[0];
    NoAVL *no = buscarAVL(dicionario->arvore->raiz, letra);

    if (no == NULL)
    {
        printf("A palavra não está no dicionário\n");
        sleep(3);
        return;
    }

    if (removerLista(no->palavras, palavra))
    {
        printf("A palavra foi excluída com sucesso!\n");
        sleep(3);
        dicionario->qtd -= 1;
    }
}

/******************************* Printa palavras com a letra ***********************************************/

void printaLetra(Dicionario *dicionario, char letra)
{
    NoAVL *no = buscarAVL(dicionario->arvore->raiz, letra);

    if (no != NULL)
    {
        printf("\nPalavras com a letra %c:\n", no->letra);
        printarLista(no->palavras);
        printf("\n\nDigite enter para sair.");
        scanf("%*c");
        getchar();
    }
    else
    {
        printf("\nA letra ainda não conta em nosso dicionário... Que tal adicioná-la?");
        sleep(5);
    }
}

/******************************* Printa o dicionário todo ***********************************************/

void printaDicionario(Dicionario *dicionario)
{
    percurso_emordem(dicionario->arvore->raiz);
    printf("\n\nDigite enter para sair.");
    scanf("%*c");
    getchar();
}

/********************************* Menu ***********************************************/

int tela_inicial(Dicionario *dicionario, char *palavra)
{
    int menu = 1;
    while (menu != 6)
    {
        system("clear");
        printf("Bem vindo ao dicionário!\n");
        printf("\n(1) Inserir palavra\n(2) Remover palavra\n(3) Buscar palavra\n(4) Imprimir palavras com uma letra\n(5) Imprimir dicionário\n(6) Sair\n\nDigite a opção que deseja: ");
        scanf("%d", &menu);

        switch (menu)
        {
        case 1:
            printf("\nDigite a palavra desejada: ");
            scanf("%s", palavra);
            inserirDicionario(dicionario, palavra);
            break;

        case 2:
            printf("\nDigite a palavra desejada: ");
            scanf("%s", palavra);
            removerDicionario(dicionario, palavra);
            break;

        case 3:
            printf("\nDigite a palavra desejada: ");
            scanf("%s", palavra);
            buscarDicionario(dicionario, palavra);
            break;

        case 4:
            printf("\nDigite a letra desejada: ");
            scanf("%s", palavra);
            printaLetra(dicionario, palavra[0]);
            break;

        case 5:
            printaDicionario(dicionario);
            break;

        default:
            system("clear");
            exit(0);
            break;
        }
    }
    return 0;
}

/********************************* Main ***********************************************/

int main()
{
    Dicionario *dicionario = criaDicionario();
    char palavra[50];

    tela_inicial(dicionario, palavra);
}
