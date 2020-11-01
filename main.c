#include<stdlib.h>
#include<stdio.h>
#include<locale.h>
#include"ListaEstoque/ListaEstoque.h"

int main(){
    setlocale(LC_ALL, "Portuguese");

    Lista *ListaEstoque;
    TipoProduto DadosProduto;

    ListaEstoque = criaLista();

    verificarEstoque(ListaEstoque);

    printf("O programa executou!!!");
    
    liberaLista(ListaEstoque);

    return 0;
}
