#include "./dicionario.h"

/******************************* Cria dicionário ***********************************************/

Dicionario* criaDicionario() {
  Dicionario* d = (Dicionario*) malloc(sizeof(Dicionario));
  d -> arvore = criaArvore();
  d -> qtd = 0;
  return d;
}

/******************************* Busca palavra no dicionário ***********************************************/

void BuscarDicionario(Dicionario* dicionario, char* palavra){
  char letra = palavra[0];
  NoAVL* no = buscarAVL(dicionario->arvore->raiz, letra);

  if (no == NULL){
    printf ("A palavra não está aqui :(");
    return;
  }

  NoLista* noLista = buscarLista(no->palavras, palavra);

  if (noLista == no->palavras->cabeca || strcmp(palavra, noLista->palavra != 0)){
    printf("A palavra não está aqui :(");
    return;
  }
  
  printf("A palavra foi encontrada! :)");

}

/******************************* Insere palavra no dicionário ***********************************************/

void InserirDicionario(Dicionario* dicionario, char* palavra){
    char letra = palavra[0];
    NoAVL* no = buscarAVL(dicionario->arvore->raiz, letra);

    if (no == NULL){
        inserirAVL(dicionario->arvore, letra);
        no = buscarAVL(dicionario->arvore->raiz, letra);
    }

    if (inserirLista(no->palavras, palavra)){
            dicionario -> qtd += 1;
    }
}

/******************************* Remove palavra no dicionário ***********************************************/

void RemoverDicionario(Dicionario* dicionario, char* palavra){
  char letra = palavra[0];
    NoAVL* no = buscarAVL(dicionario->arvore->raiz, letra);

    if (no == NULL){
        printf("A palavra não está no dicionário\n");
        return;
    }

    if (removerLista(no->palavras, palavra)){
            printf("A palavra foi excluída com sucesso!");
            dicionario -> qtd -= 1;
    }

}

/******************************* Printa palavras com a letra ***********************************************/

void printaLetra(Dicionario* dicionario, char letra){
  NoAVL* no = buscarAVL(dicionario->arvore->raiz, letra);

  if (no != NULL){
    printf("\nPalavras com a letra %c: ", no->letra);
    printarLista(no->palavras);
  } else{
    printf("\nA letra ainda não conta em nosso dicionário... Que tal adicioná-la?");
  }
}

/******************************* Printa o dicionário todo ***********************************************/

void printaDicionario(Dicionario* dicionario){
  percurso_emordem(dicionario->arvore->raiz);
}