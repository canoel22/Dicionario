#include <stdio.h>
#include "./src/lista/lista.h"
#include "./src/avl/avl.h"

int main()
{
    ArvoreAVL *arvoreAVL = criaArvore();

    inserir(arvoreAVL, 'a');
    inserir(arvoreAVL, 'b');
    inserir(arvoreAVL, 'c');
    inserir(arvoreAVL, 'd');
    inserir(arvoreAVL, 'e');
    inserir(arvoreAVL, 'f');
    inserir(arvoreAVL, 'g');
    inserir(arvoreAVL, 'h');
    inserir(arvoreAVL, 'i');
    inserir(arvoreAVL, 'j');
    inserir(arvoreAVL, 'k');
    inserir(arvoreAVL, 'l');
    inserir(arvoreAVL, 'm');
    inserir(arvoreAVL, 'n');
    inserir(arvoreAVL, 'o');

    NoAVL *no = buscar(arvoreAVL->raiz, 'h');
    remover(arvoreAVL, no);
    
    no = buscar(arvoreAVL->raiz, 'k');
    remover(arvoreAVL, no);

    no = buscar(arvoreAVL->raiz, 'l');
    remover(arvoreAVL, no);

    no = buscar(arvoreAVL->raiz, 'i');
    remover(arvoreAVL, no);

    no = buscar(arvoreAVL->raiz, 'g');
    remover(arvoreAVL, no);

    no = buscar(arvoreAVL->raiz, 'e');
    remover(arvoreAVL, no);

    percurso_preordem(arvoreAVL->raiz);
}
