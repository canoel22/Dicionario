#include "./dicionario.h"

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
    printf("\nPalavras com a letra %c: \n", no->letra);
    printarLista(no->palavras);
    printf("\n\nDigite enter para sair.");
    scanf("%*c");
    getchar();
  }
  else
  {
    printf("\nA letra ainda não conta em nosso dicionário... Que tal adicioná-la?");
    sleep(3);
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