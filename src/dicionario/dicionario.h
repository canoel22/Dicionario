#ifndef __dicionario_h
#define __dicionario_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../avl/avl.h"

/******************************* Estruturas ***********************************************/

typedef struct dicionario {
  ArvoreAVL* arvore;
  int qtd;
} Dicionario;

/******************************* Funções ***********************************************/

Dicionario* criaDicionario();
void BuscarDicionario(Dicionario* dicionario, char* palavra);
void InserirDicionario(Dicionario* dicionario, char* palavra);
void RemoverDicionario(Dicionario* dicionario, char* palavra);
void printaLetra(Dicionario* dicionario, char letra);
void printaDicionario(Dicionario* dicionario);

#endif