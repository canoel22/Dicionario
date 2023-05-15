#include <stdio.h>
#include <stdlib.h>


#include "menu.h"
#include "../lista/lista.h"
#include "../avl/avl.h"
#include "../dicionario/dicionario.h"


/********************************* Menu ***********************************************/

int tela_inicial(Dicionario* dicionario, char* palavra)
{   int menu = 1;
    while (menu != 6)
    {
        system("clear");
        printf("Bem vindo ao dicionário!\n");
        printf("\n(1) Buscar palavra\n(2) Inserir palavra\n(3) Remover palavra\n(4) Imprimir palavras com uma letra\n(5) Imprimir dicionário\n(6) Sair\n\nDigite a opção que deseja: ");
        scanf("%d", &menu);

   switch (menu)
        {
        case 1:
            printf("\nDigite a palavra desejada: ");
            scanf("%s", palavra);
            buscarDicionario(dicionario, palavra);
            break;

        case 2:
            printf("\nDigite a(s) palavra(s) desejada(s): ");
            while (1)
            {
                scanf("%s", palavra);
                if (strcmp(palavra, "0") != 0) 
                {
                inserirDicionario(dicionario, palavra);
                }
                break;
            }
            break;

        case 3:
            printf("\nDigite a palavra desejada: ");
            scanf("%s", palavra);
            removerDicionario(dicionario, palavra);
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