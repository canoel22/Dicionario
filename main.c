#include <stdio.h>
#include "./src/lista/lista.h"
#include "./src/avl/avl.h"
#include "./src/dicionario/dicionario.h"
#include "./src/menu/menu.h"

int main()
{
    Dicionario* dicionario = criaDicionario();
    char letra;
    char* palavra;

    tela_inicial(dicionario, palavra, letra);

/*
    inserirDicionario(dicionario, "abacate");
    inserirDicionario(dicionario, "banana");

    buscarDicionario(dicionario, "abacate");
    //buscarDicionario(dicionario, "batata");

    removerDicionario(dicionario, "abacate");
    //printaDicionario(dicionario);

*/

}
