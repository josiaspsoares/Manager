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
        printf("\nErro: N�o foi poss�vel alocar mem�ria para a Lista!\n");
        exit(1);
    }

    do{
        opcao = menu();
        switch (opcao){
            case 1:
                cadastroProduto(DadosProduto);
                if(insereListaFinal(ListaEstoque, *DadosProduto) == 0){
                    printf("\nErro: N�o foi poss�vel inserir os dados na Lista!\n");
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
                    printf("\n\n\t\t\t\t\t<<< N�O H� PRODUTOS CADASTRADOS NO ESTOQUE >>>\n\n");
                    Sleep(2000);
                }
                else{
                    printf("\n\n\t\t\t\t\t\t====================================\n");
                    printf("\n\t\t\t\t\t\t*** MANAGER - REMO��O DE PRODUTOS ***\n");
                    printf("\n\t\t\t\t\t\t====================================\n\n");
                    printf("\n\t\t\t\t\t > Informe o c�digo do produto: ");
                    scanf("%d", &codigoRemover);
                    statusCode = consultaListaCodigo(ListaEstoque, codigoRemover, DadosProduto);
                    if(statusCode == 1){
                        printf("\n\t\t\t\t\t > Confirme a remo��o de %s", DadosProduto->nome);
                        printf("\t\t\t\t\t > ( 1 - SIM )  ( 0 - N�O )  --> ");
                        scanf("%d", &opcao);
                        system("cls");

                        if(opcao == 1){
                            removeLista(ListaEstoque, codigoRemover);
                            printf("\n\n\t\t\t\t\t<<< PRODUTO REMOVIDO COM SUCESSO >>>\n\n");
                            Sleep(2000);
                        }
                        else{
                            printf("\n\n\t\t\t\t\t<<< SOLICITA��O CANCELADA >>>\n\n");
                            Sleep(2000);
                        }
 
                    }
                    else{
                        system("cls");
                        printf("\n\n\t\t\t\t\t<<< A REMO��O FALHOU! PRODUTO N�O ENCONTRADO >>>\n\n");
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

	printf("\t*** MENU PROVIS�RIO ***\n\n");
	printf("-> Informe a op��o desejada:\n");
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
