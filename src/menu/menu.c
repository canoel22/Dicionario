#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "../lista/lista.h"
#include "../avl/avl.h"
#include "../dicionario/dicionario.h"


/********************************* Menu ***********************************************/

int tela_inicial(Dicionario* dicionario, char* palavra, char letra)
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
            scanf("%c", palavra);
            inserirDicionario(dicionario, palavra);
            break;

        case 2:
            printf("\nDigite a palavra desejada: ");
            scanf("%c", palavra);
            removerDicionario(dicionario, palavra);
            break;

        case 3:
            printf("\nDigite a palavra desejada: ");
            scanf("%c", palavra);
            buscarDicionario(dicionario, palavra);
            break;

        case 4:
            printf("\nDigite a letra desejada: ");
            scanf("%c", &letra);
            printaLetra(dicionario, letra);
            break;

        case 5:
            printaDicionario(dicionario);
            break;

        default:
            system("clear");
            exit(0);
            break;
        }
        return 0;
    }
}