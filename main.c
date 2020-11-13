#include<stdlib.h>
#include<stdio.h>
#include<locale.h>
#include<windows.h>
#include"ListaEstoque/ListaEstoque.h"

int menu();

int main(){
    setlocale(LC_ALL, "Portuguese");

    ListaProdutos *ListaEstoque;
    TipoProduto *DadosProduto = (TipoProduto*) malloc(sizeof(TipoProduto));
    int opcao, codigoRemover, statusCode;

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
            case 5:
                if(ListaEstoque->quantidade == 0){
                    printf("\n\n\t\t\t\t\t<<< NÃO HÁ PRODUTOS CADASTRADOS NO ESTOQUE >>>\n\n");
                    Sleep(2000);
                }
                else{
                    printf("\n\n\t\t\t\t\t\t====================================\n");
                    printf("\n\t\t\t\t\t\t*** MANAGER - REMOÇÃO DE PRODUTOS ***\n");
                    printf("\n\t\t\t\t\t\t====================================\n\n");
                    printf("\n\t\t\t\t\t > Informe o código do produto: ");
                    scanf("%d", &codigoRemover);
                    statusCode = consultaListaCodigo(ListaEstoque, codigoRemover, DadosProduto);
                    if(statusCode == 1){
                        printf("\n\t\t\t\t\t > Confirme a remoção de %s", DadosProduto->nome);
                        printf("\t\t\t\t\t > ( 1 - SIM )  ( 0 - NÃO )  --> ");
                        scanf("%d", &opcao);
                        system("cls");

                        if(opcao == 1){
                            removeLista(ListaEstoque, codigoRemover);
                            printf("\n\n\t\t\t\t\t<<< PRODUTO REMOVIDO COM SUCESSO >>>\n\n");
                            Sleep(2000);
                        }
                        else{
                            printf("\n\n\t\t\t\t\t<<< SOLICITAÇÃO CANCELADA >>>\n\n");
                            Sleep(2000);
                        }
 
                    }
                    else{
                        system("cls");
                        printf("\n\n\t\t\t\t\t<<< A REMOÇÃO FALHOU! PRODUTO NÃO ENCONTRADO >>>\n\n");
                        Sleep(2000);
                    }
                }
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
    printf("\n 5 - Remover Produto");
	printf("\n 0 - Sair");
	printf("\n\n  ---> ");
	scanf("%d", &opcao);

	if(opcao >= 0 && opcao < 6){
        system("cls");
		return opcao;
	}
	else{
		return menu();
	}

}
