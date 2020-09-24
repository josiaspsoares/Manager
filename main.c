#include<stdlib.h>
#include<stdio.h>
#include<locale.h>
#include"ListaEstoque/ListaEstoque.h"

int main(){
    setlocale(LC_ALL, "Portuguese");

    Lista *ListaEstoque;
    TipoProduto DadosProduto;

    ListaEstoque = criaLista();

    printf("O programa executou com sucesso!!!");
    
    liberaLista(ListaEstoque);

    return 0;
}
