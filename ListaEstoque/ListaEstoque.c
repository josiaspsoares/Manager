#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#include"ListaEstoque.h"

ListaProdutos* criaLista(){
    ListaProdutos* ListaEstoque = (ListaProdutos*) malloc(sizeof(ListaProdutos));

    if(ListaEstoque != NULL){
        ListaEstoque->primeiro = NULL;
        ListaEstoque->ultimo = NULL;
        ListaEstoque->quantidade = 0;
    }

    return ListaEstoque;
}

void liberaLista(ListaProdutos* ListaEstoque){
    if(ListaEstoque != NULL){
        ElementoProduto* no;

        while(ListaEstoque->primeiro != NULL){
            no = ListaEstoque->primeiro;
            ListaEstoque->primeiro = ListaEstoque->primeiro->proximo;
            free(no); // Libera cada nó(elementoPrElementoProduto) da Lista
        }

        free(ListaEstoque);
    }
}

int listaVazia(ListaProdutos* ListaEstoque){
    if(ListaEstoque == NULL) return 1;
    if(ListaEstoque->primeiro == NULL) return 1;
    return 0;
}

int tamanhoLista(ListaProdutos* ListaEstoque){
    if(ListaEstoque == NULL) return 0;
    return ListaEstoque->quantidade;
}

int insereListaInicio(ListaProdutos* ListaEstoque, TipoProduto DadosProduto){
    if(ListaEstoque == NULL) return 0;

    ElementoProduto* no = (ElementoProduto*) malloc(sizeof(ElementoProduto));
    if(no == NULL) return 0;
    no->Dados = DadosProduto;

    if(listaVazia(ListaEstoque)){
		ListaEstoque->primeiro = no;
		ListaEstoque->ultimo = no;
	}
	else{
		no->proximo = ListaEstoque->primeiro;
		ListaEstoque->primeiro->anterior = no;
		ListaEstoque->primeiro = no;
	}

    ListaEstoque->quantidade++;
    return 1;
}

int insereListaFinal(ListaProdutos* ListaEstoque, TipoProduto DadosProduto){
    if(ListaEstoque == NULL) return 0;

    ElementoProduto* no = (ElementoProduto*) malloc(sizeof(ElementoProduto));
    if(no == NULL) return 0;
    no->Dados = DadosProduto;

    if(listaVazia(ListaEstoque)){
        free(no);
		return insereListaInicio(ListaEstoque, DadosProduto);
	}
	else{
		ListaEstoque->ultimo->proximo = no;
		no->anterior = ListaEstoque->ultimo;
		ListaEstoque->ultimo = no;
        ListaEstoque->quantidade++;
        return 1;
	}
}

int insereListaOrdenada(ListaProdutos* ListaEstoque, TipoProduto DadosProduto){
    if(ListaEstoque == NULL) return 0;

    ElementoProduto* no = (ElementoProduto*) malloc(sizeof(ElementoProduto));
    if(no == NULL) return 0;
    no->Dados = DadosProduto;

    if(listaVazia(ListaEstoque)){
        free(no);
        return insereListaInicio(ListaEstoque, DadosProduto);
    }
    else{
		ElementoProduto *anterior, *atual = ListaEstoque->primeiro;

		while(atual != NULL && atual->Dados.codigo < DadosProduto.codigo){
			anterior = atual;
			atual = atual->proximo;
		}

		if(atual == ListaEstoque->primeiro){
			no->anterior = NULL;
			ListaEstoque->primeiro->anterior = no;
			no->proximo = ListaEstoque->primeiro;
			ListaEstoque->primeiro = no;
		}
		else{
			no->proximo = anterior->proximo;
			no->anterior = anterior;
			anterior->proximo = no;

			if(atual != NULL)
				atual->anterior = no;
		}

        ListaEstoque->quantidade++;
        return 1;
	}
}

int removeListaInicio(ListaProdutos* ListaEstoque){
    if(ListaEstoque == NULL) return 0;
    if((ListaEstoque->primeiro) == NULL) return 0;

    ElementoProduto *no = ListaEstoque->primeiro;
    ListaEstoque->primeiro = no->proximo;

	if(no->proximo != NULL){
        no->proximo->anterior = NULL;
    }

    ListaEstoque->quantidade--;
    free(no);
    return 1;
}

int removeListaFinal(ListaProdutos* ListaEstoque){
    if(ListaEstoque == NULL) return 0;
    if((ListaEstoque->primeiro) == NULL) return 0;

    ElementoProduto *no = ListaEstoque->ultimo;

    if(no == ListaEstoque->primeiro){
        free(no);
        return removeListaInicio(ListaEstoque);
    }
    else{
        ListaEstoque->ultimo->anterior->proximo = NULL;
        ListaEstoque->ultimo = ListaEstoque->ultimo->anterior;
        ListaEstoque->quantidade--;
        free(no);
        return 1;
    }
}

int removeLista(ListaProdutos* ListaEstoque, int codigo){
    if(ListaEstoque == NULL) return 0;

    ElementoProduto *no = ListaEstoque->primeiro;
    while(no != NULL && no->Dados.codigo != codigo){
        no = no->proximo;
    }

    if(no == NULL) return 0;
    if(no == ListaEstoque->primeiro){
        free(no);
        return removeListaInicio(ListaEstoque);
    }
    else if(no == ListaEstoque->ultimo){
        free(no);
        return removeListaFinal(ListaEstoque);
    }
    else{
        no->anterior->proximo = no->proximo;
        no->proximo->anterior = no->anterior;
        ListaEstoque->quantidade--;
        free(no);
        return 1;
    }
}

void removeProdutoEstoque(ListaProdutos *ListaEstoque){
    if(ListaEstoque->quantidade == 0){
        printf("\n\n\t\t<<< NÃO HÁ PRODUTOS CADASTRADOS NO ESTOQUE >>>\n\n");
        Sleep(2000);
    }
    else{
        int codigoRemover, statusCode, opcao;
        TipoProduto *DadosProduto = (TipoProduto*) malloc(sizeof(TipoProduto));

        printf("\n\n\t\t\t=====================================\n");
        printf("\n\t\t\t*** MANAGER - REMOÇÃO DE PRODUTOS ***\n");
        printf("\n\t\t\t=====================================\n\n");
        printf("\n  > Informe o código do produto: ");
        scanf("%d", &codigoRemover);
        statusCode = consultaListaCodigo(ListaEstoque, codigoRemover, DadosProduto);
        if(statusCode == 1){
            printf("\n  > Confirme a remoção de %s: ( 1 - SIM )  ( 0 - NÃO )\n\n", DadosProduto->nome);
            printf("\t---> ");
            scanf("%d", &opcao);
            system("cls");

            if(opcao == 1){
                removeLista(ListaEstoque, codigoRemover);
                printf("\n\n\t\t<<< PRODUTO REMOVIDO COM SUCESSO >>>\n\n");
                Sleep(2000);
            }
            else{
                printf("\n\n\t\t<<< SOLICITAÇÃO CANCELADA >>>\n\n");
                Sleep(2000);
            }

        }
        else{
            system("cls");
            printf("\n\n\t\t<<< A REMOÇÃO FALHOU! PRODUTO NÃO ENCONTRADO >>>\n\n");
            Sleep(2000);
        }
    }
}

int consultaListaCodigo(ListaProdutos* ListaEstoque, int codigo, TipoProduto *DadosProduto){
    if(ListaEstoque == NULL) return 0;

    ElementoProduto *no = ListaEstoque->primeiro;
    while(no != NULL && no->Dados.codigo != codigo){
        no = no->proximo;
    }

    if(no == NULL){
        return 0;
    }
    else{
         // Obtem os dados do produto consultado através de um ponteiro
        *DadosProduto = no->Dados;
        return 1;
    }
}

void  verificarEstoque (ListaProdutos *ListaEstoque){
    int opcao;
    ElementoProduto *elementoAuxiliar;
    system("cls");

    if (ListaEstoque->quantidade==0){
        printf("\n\n\t\t<<< NÃO HÁ PRODUTOS CADASTRADOS >>>\n\n");
        Sleep(2000);
        return;
    }

    printf("\n\n\t\t\t========================================\n");
    printf("\n\t\t\t*** MANAGER - VERIFICAÇÃO DE ESTOQUE ***\n");
    printf("\n\t\t\t========================================\n\n");
    printf("\n  > O que você deseja?\n\n");
    printf(" 1) Ver o estoque de todos os produtos\n");
    printf(" 2) Ver produtos com estoque baixo\n\n");

    printf(" ---> ");
    scanf("%d", &opcao);
    system("cls");

    printf("\n\n\t\t\t========================================\n");
    printf("\n\t\t\t*** MANAGER - VERIFICAÇÃO DE ESTOQUE ***\n");
    printf("\n\t\t\t========================================\n\n");
    switch(opcao){
        case 1:
            printf("  >>> Imprimindo estoque de todos os produtos:\n\n");
            elementoAuxiliar=ListaEstoque->primeiro;
            while(elementoAuxiliar!=NULL){
                printf("Código %d | %.15s | Estoque %d\n", elementoAuxiliar->Dados.codigo, elementoAuxiliar->Dados.nome, elementoAuxiliar->Dados.quantidade);
                elementoAuxiliar=elementoAuxiliar->proximo;
            };
            printf("\n");
            system("pause");
            break;
        case 2:
            printf("  >>> Imprimindo produtos com estoque baixo:\n\n");
            elementoAuxiliar=ListaEstoque->primeiro;

            while(elementoAuxiliar!=NULL){
                if (elementoAuxiliar->Dados.quantidade<4){
                    printf("Código %d | %.15s | Estoque %d\n", elementoAuxiliar->Dados.codigo, elementoAuxiliar->Dados.nome, elementoAuxiliar->Dados.quantidade);
                }
                elementoAuxiliar=elementoAuxiliar->proximo;
            };
            printf("\n");
            system("pause");
            break;
        default:
            printf("\n\n\t\t\t<<< OPÇÃO INVÁLIDA! RETORNANDO AO MENU >>>\n\n");
            Sleep(2000);
            break;
    }

}

void exibirItem(ElementoProduto *auxiliar)
{
    printf(" - Nome: %s\n",auxiliar->Dados.nome);
    printf(" - Data de Validade: %s\n",auxiliar->Dados.dataValidade);
    printf(" - Quantidade : %d\n",auxiliar->Dados.quantidade);
    printf(" - Código : %d\n",auxiliar->Dados.codigo);
    printf(" - Valor de entrada : %.2f\n",auxiliar->Dados.valorDeEntrada);
    printf(" - Valor de saida: %.2f\n\n",auxiliar->Dados.valorDeSaida);
}

void exibirEstoque(ListaProdutos *ListaEstoque)
{
    int opcao,cod,controle=0;
    float preco;
    char nome[200];
    ElementoProduto *auxiliar;

    auxiliar=ListaEstoque->primeiro;

    if (ListaEstoque->quantidade==0){
        printf("\n\n\t\t<<< NÃO HÁ PRODUTOS CADASTRADOS >>>\n\n");
        Sleep(2000);
        return;
    }

    printf("\n\n\t\t\t======================================\n");
    printf("\n\t\t\t*** MANAGER - CONSULTA DE PRODUTOS ***\n");
    printf("\n\t\t\t======================================\n\n");
    printf("\n  > O que você deseja?\n\n");
    printf(" 1) Tecle 1 para procurar por nome do produto\n");
    printf(" 2) Tecle 2 para procurar por codigo do produto\n");
    printf(" 3) Tecle 3 para procurar por preço\n\n");

    printf(" ---> ");
    scanf("%d", &opcao);
    system("cls");

    printf("\n\n\t\t\t======================================\n");
    printf("\n\t\t\t*** MANAGER - CONSULTA DE PRODUTOS ***\n");
    printf("\n\t\t\t======================================\n\n");
    switch(opcao)
    {
        case 1:
            printf("\n  > Digite o nome do produto que deseja buscar:\n\n");
            fflush(stdin);
            printf(" ---> ");
            gets(nome);
            printf("\n");

            while(auxiliar!=NULL)
            {
                if(strcmp(nome,auxiliar->Dados.nome) == 0)
                {
                    exibirItem(auxiliar);
                    controle=1;
                }

                auxiliar=auxiliar->proximo;
            }
            system("pause");
            break;
        case 2:
            printf("\n  > Digite o código do produto que deseja buscar:\n\n");
            printf(" ---> ");
            scanf("%d",&cod);
            printf("\n");

            while(auxiliar!=NULL)
            {
                if(cod==auxiliar->Dados.codigo)
                {
                    exibirItem(auxiliar);
                    controle=1;
                }
                auxiliar=auxiliar->proximo;
            }
            system("pause");
            break;
        case 3:
            printf("\n  > Digite o preço do produto que deseja buscar:\n\n");
            printf(" ---> ");
            scanf("%f",&preco);
            printf("\n");

            while(auxiliar!=NULL)
            {
                if(preco==auxiliar->Dados.valorDeSaida)
                {
                    exibirItem(auxiliar);
                    controle=1;
                }
                auxiliar=auxiliar->proximo;
            }
            system("pause");
            break;
        default:
            printf("\n\n\t\t\t<<< OPÇÃO INVÁLIDA! RETORNANDO AO MENU >>>\n\n");
            Sleep(2000);
            break;
    }

    if(controle==0)
    {
        printf("\n\n\t\t\t<<< NÃO FOI ENCONTRADO O PRODUTO >>>\n\n");
        Sleep(2000);
    }
}

void editarEstoque(ListaProdutos *ListaEstoque)
{
    int opcao, controle=0;
    char nome[100];
    ElementoProduto *auxiliar;
    ElementoProduto *aux;

    auxiliar=ListaEstoque->primeiro;

    if (ListaEstoque->quantidade==0){
        printf("\n\n\t\t<<< NÃO HÁ PRODUTOS CADASTRADOS >>>\n\n");
        Sleep(2000);
        return;
    }

    printf("\n\n\t\t\t====================================\n");
    printf("\n\t\t\t*** MANAGER - EDIÇÃO DE PRODUTO ***\n");
    printf("\n\t\t\t====================================\n\n");
    printf("\n  > Digite o nome do produto que deseja buscar:\n\n");
    printf(" ---> ");
    fflush(stdin);
    gets(nome);
    printf("\n");

    while(auxiliar!=NULL)
    {
        if(strcmp(nome,auxiliar->Dados.nome) == 0)
        {
            exibirItem(auxiliar);
            controle=1;
            aux=auxiliar;
        }
        auxiliar=auxiliar->proximo;
    }
    
    if(controle==1)
    {
        do
        {   
            printf("\n  > O que você deseja?\n\n");
            printf(" 1) Tecle 1 para alterar a Validade do produto\n");
            printf(" 2) Tecle 2 para alterar a quantidade do produto\n");
            printf(" 3) Tecle 3 para alterar o valor de entrada\n");
            printf(" 4) Tecle 4 para alterar o valor de saída\n");
            printf(" 5) Tecle 5 para sair\n\n");
            printf(" ---> ");
            scanf("%d", &opcao);
            printf("\n");

            system("cls");
            printf("\n\n\t\t\t====================================\n");
            printf("\n\t\t\t*** MANAGER - EDIÇÃO DE PRODUTO ***\n");
            printf("\n\t\t\t====================================\n\n");
            switch(opcao)
            {
                case 1:
                printf("\t\t\t> Data de Validade atual: %s\n\n",aux->Dados.dataValidade);
                printf("\t-> Digite uma nova data:\n\n");
                printf(" ---> ");
                fflush(stdin);
                gets(aux->Dados.dataValidade);
                break;

                case 2:
                printf("\t\t\t> Quantidade de produtos atual: %d\n\n",aux->Dados.quantidade);
                printf("\t-> Digite uma nova quantidade:\n\n");
                printf(" ---> ");
                scanf("%d",&aux->Dados.quantidade);
                break;

                case 3:
                printf("\t\t\t> Valor de entrada atual: %.2f\n\n",aux->Dados.valorDeEntrada);
                printf("\t-> Digite um novo valor de entrada:\n\n");
                printf(" ---> R$ ");
                scanf("%f",&aux->Dados.valorDeEntrada);
                break;

                case 4:
                printf("\t\t\t> Valor de saída atual: %.2f\n\n",aux->Dados.valorDeSaida);
                printf("\t-> Digite um novo valor de saída:\n\n");
                printf(" ---> R$ ");
                scanf("%f",&aux->Dados.valorDeSaida);
                break;

            }
            system("cls");

            printf("\n\n\t\t\t====================================\n");
            printf("\n\t\t\t*** MANAGER - EDIÇÃO DE PRODUTO ***\n");
            printf("\n\t\t\t====================================\n\n");
            exibirItem(aux);
        }while(opcao!=5);
    }

    else
    {
        printf("\n\t\t\t<<< NÃO FOI ENCONTRADO O PRODUTO >>>\n\n");
        Sleep(2000);
    }
}

void cadastroProduto(TipoProduto* DadosProduto){
	printf("\n\n\t\t\t=====================================\n");
    printf("\n\t\t\t*** MANAGER - CADASTRO DE PRODUTO ***\n");
    printf("\n\t\t\t=====================================\n\n\n");
	printf(" > Nome: ");
	fflush(stdin);
	gets(DadosProduto->nome);
	printf(" > Data de Validade: ");
	fflush(stdin);
	gets(DadosProduto->dataValidade);
	printf(" > Valor de Entrada: R$ ");
	fflush(stdin);
	scanf(" %f", &DadosProduto->valorDeEntrada);
	printf(" > Valor de Saida: R$ ");
	fflush(stdin);
	scanf(" %f", &DadosProduto->valorDeSaida);
	printf(" > Quantidade: ");
	fflush(stdin);
	scanf(" %d", &DadosProduto->quantidade);
	printf(" > Codigo: ");
	fflush(stdin);
	scanf(" %d", &DadosProduto->codigo);

    system("cls");
    printf("\n\n\t\t<<< PRODUTO CADASTRADO COM SUCESSO >>>\n\n");
    Sleep(2000);
}


