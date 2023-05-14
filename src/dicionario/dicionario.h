#ifndef __dicionario_h
#define __dicionario_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "../avl/avl.h"

/******************************* Estruturas ***********************************************/

typedef struct dicionario {
  ArvoreAVL* arvore;
  int qtd;
} Dicionario;

/******************************* Funções ***********************************************/

Dicionario* criaDicionario();
void buscarDicionario(Dicionario* dicionario, char* palavra);
void inserirDicionario(Dicionario* dicionario, char* palavra);
void removerDicionario(Dicionario* dicionario, char* palavra);
void printaLetra(Dicionario* dicionario, char letra);
void printaDicionario(Dicionario* dicionario);

#endif