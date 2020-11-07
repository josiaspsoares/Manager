#include<stdlib.h>
#include<stdio.h>
#include<locale.h>
#include"ListaEstoque/ListaEstoque.h"

int menu();

int main(){
    setlocale(LC_ALL, "Portuguese");

    Lista *ListaEstoque;
    TipoProduto *DadosProduto = (TipoProduto*) malloc(sizeof(TipoProduto));
    int opcao;

    ListaEstoque = criaLista();

    if(ListaEstoque == NULL){
        printf("\nErro: Não foi possível alocar memória para a Lista!\n");
        exit(1);
    }

    do{
        opcao = menu();
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
                system("pause");
                break;
            case 3:
                verificarEstoque(ListaEstoque);
                system("pause");
                break;
            case 4:
                editarEstoque(ListaEstoque);
                system("pause");
                break;
            default: break;
        }

    }while(opcao != 0);
    
    liberaLista(ListaEstoque);

    return 0;
}

int menu(){
	int opcao;

	system("cls");

	printf("\t*** MENU PROVISÓRIO ***\n\n");
	printf("-> Informe a opção desejada:\n");
	printf("\n 1 - Cadastrar Produto");
    printf("\n 2 - Exibe Produtos");
    printf("\n 3 - Verificar Estoque");
    printf("\n 4 - Editar");
	printf("\n 0 - Sair");
	printf("\n\n  ---> ");
	scanf("%d", &opcao);

	if(opcao >= 0 && opcao < 5){
        system("cls");
		return opcao;
	}
	else{
		return menu();
	}

}
