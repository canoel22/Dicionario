#include <stdio.h>
#include "./src/lista/lista.h"
#include "./src/avl/avl.h"
#include "./src/dicionario/dicionario.h"
#include "./src/menu/menu.h"

int main()
{
    Dicionario* dicionario = criaDicionario();
    char palavra[50];

    tela_inicial(dicionario, palavra);
}
