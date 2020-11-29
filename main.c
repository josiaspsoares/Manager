#include<stdlib.h>
#include<stdio.h>
#include<locale.h>
#include<windows.h>
#include"ListaVendas/ListaVendas.h"

int menu();

int main(){
    setlocale(LC_ALL, "Portuguese");

    TipoProduto *DadosProduto = (TipoProduto*) malloc(sizeof(TipoProduto));
    int opcao;

    ListaProdutos *ListaEstoque;
    ListaVendas *ListaVendido;
    ListaEstoque = criaLista();
    ListaVendido =criaListaVendas();

    if(ListaEstoque == NULL || ListaVendido == NULL){
        printf("\nErro: Não foi possível alocar memória para a Lista!\n");
        exit(1);
    }

    do{
        system("cls");
        opcao = menu();
        system("cls");
        switch (opcao){
            case 1:
                cadastroProduto(DadosProduto);
                if(insereListaFinal(ListaEstoque, *DadosProduto) == 0){
                    printf("\nErro: Não foi possível inserir os dados na Lista!\n");
                    exit(1);
                }
                break;
            case 2:
                exibirEstoque(ListaEstoque);
                break;
            case 3:
                verificarEstoque(ListaEstoque);
                break;
            case 4:
                editarEstoque(ListaEstoque);
                break;
            case 5:
                removeProdutoEstoque(ListaEstoque);
                break;
            case 6:
                realizarVenda(ListaEstoque, ListaVendido);
                system("pause");
                break;
            case 7:
                fechamentoDeCaixa(ListaVendido);
                system("pause");
                break;
            default: system("cls");
        }


    }while(opcao != 0);

    liberaLista(ListaEstoque);
    liberaListaVendas(ListaVendido);

    return 0;
}

int menu(){
	int opcao;

	system("cls");

	printf("\n\n\t\t\t=================================\n");
    printf("\n\t\t\t*** MANAGER - MENU PRINCIPAL ***\n");
    printf("\n\t\t\t=================================\n\n\n");
	printf("  -> Informe a opção desejada:\n");
	printf("\n 1 - Cadastrar Produto");
    printf("\n 2 - Consultar Produto");
    printf("\n 3 - Verificar Estoque");
    printf("\n 4 - Editar Produto");
    printf("\n 5 - Remover Produto");
    printf("\n 6 - Realizar Venda");
    printf("\n 7 - Fechamento de Caixa");
	printf("\n 0 - Sair");
	printf("\n\n  ---> ");
	scanf("%d", &opcao);

    return opcao;

}

