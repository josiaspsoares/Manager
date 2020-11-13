#include<stdlib.h>
#include<stdio.h>
#include<string.h>
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
        ListaEstoque->quantidade--;
    }

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
        printf("\n\nNão há produtos cadastrados.\n\n");
        return;
    }

    printf("<<MENU>>");
    printf("\n O que você deseja?\n\n");
    printf("1) Ver o estoque de todos os produtos\n");
    printf("2) Ver produtos com estoque baixo\n");

    scanf("%d", &opcao);

    switch(opcao){
        case 1:
            printf("Imprimindo estoque de todos os produtos:\n\n");
            elementoAuxiliar=ListaEstoque->primeiro;
            while(elementoAuxiliar!=NULL){
                printf("Código %d | %.15s | Estoque %d\n", elementoAuxiliar->Dados.codigo, elementoAuxiliar->Dados.nome, elementoAuxiliar->Dados.quantidade);
                elementoAuxiliar=elementoAuxiliar->proximo;
            };

            break;
        case 2:

            printf("Imprimindo produtos com estoque baixo:\n\n");
            elementoAuxiliar=ListaEstoque->primeiro;

            while(elementoAuxiliar!=NULL){
                if (elementoAuxiliar->Dados.quantidade<4){
                    printf("Código %d | %.15s | Estoque %d\n", elementoAuxiliar->Dados.codigo, elementoAuxiliar->Dados.nome, elementoAuxiliar->Dados.quantidade);
                }
                elementoAuxiliar=elementoAuxiliar->proximo;
            };

            break;
        default:
            printf("Opção inválida, retornando ao menu.");
            break;
    }

}

void exibirItem(ElementoProduto *auxiliar)
{
    printf("Nome: %s\n",auxiliar->Dados.nome);
    printf("Data de Validade: %s\n",auxiliar->Dados.dataValidade);
    printf("Quantidade : %d\n",auxiliar->Dados.quantidade);
    printf("Código : %d\n",auxiliar->Dados.codigo);
    printf("Valor de entrada : %.2f\n",auxiliar->Dados.valorDeEntrada);
    printf("Valor de saida: %.2f\n\n",auxiliar->Dados.valorDeSaida);
}

void exibirEstoque(ListaProdutos *ListaEstoque)
{
    int opcao,cod,controle=0;
    float preco;
    char nome[200];
    ElementoProduto *auxiliar;

    auxiliar=ListaEstoque->primeiro;

    if (ListaEstoque->quantidade==0){
        printf("\n\nNão há produtos cadastrados.\n\n");
        return;
    }

    printf("<<MENU>>");
    printf("\n O que você deseja?\n\n");
    printf("1) Tecle 1 para procurar por nome do produto\n");
    printf("2) Tecle 2 para procurar por codigo do produto\n");
    printf("3) Tecle 3 para procurar por preço\n");

    scanf("%d", &opcao);

    switch(opcao)
    {
        case 1:

        printf("\nDigite o nome do produto que deseja buscar:\n\n");
        fflush(stdin);
        gets(nome);

                while(auxiliar!=NULL)
                {   
                    if(strcmp(nome,auxiliar->Dados.nome) == 0)
                    {
                        exibirItem(auxiliar);
                        controle=1;
                    }

                    auxiliar=auxiliar->proximo;
                }
        break;

        case 2:
        printf("\nDigite o código do produto que deseja buscar:\n\n");
        scanf("%d",&cod);

                while(auxiliar!=NULL)
                {
                    if(cod==auxiliar->Dados.codigo)
                     {
                       exibirItem(auxiliar);
                    }
                     auxiliar=auxiliar->proximo;
                }

        break;

        case 3:
        {
            printf("\nDigite o preço do produto que deseja buscar:\n\n");
            scanf("%f",&preco);

                while(auxiliar!=NULL)
                    {
                        if(preco==auxiliar->Dados.valorDeSaida)
                         {
                            exibirItem(auxiliar);
                            controle=1;
                        }
                         auxiliar=auxiliar->proximo;
                    }

        break;

        }

        default:
        printf("\nOpção inválida\n\n");
        break;
    }

    if(controle==0)
    {
        printf("Não foi encontrado o produto\n\n");
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
        printf("\n\nNão há produtos cadastrados.\n\n");
        return;
    }

    printf("\nDigite o nome do produto que deseja buscar:\n\n");
    fflush(stdin);
    gets(nome);

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
            printf("\n\n<<MENU>>");
            printf("\n O que você deseja?\n\n");
            printf("1) Tecle 1 para alterar a Validade do produto\n");
            printf("2) Tecle 2 para alterar a quantidade do produto\n");
            printf("3) Tecle 3 para alterar o valor de entrada\n");
            printf("4) Tecle 4 para alterar o valor de saída\n");
            printf("5) Tecle 5 para sair\n\n");
            scanf("%d", &opcao);

            switch(opcao)
            {
                case 1:
                printf("Data de Validade atual: %s\n\n",aux->Dados.dataValidade);
                printf("\t->Digite uma nova data:\n\n");
                gets(aux->Dados.dataValidade);
                break;

                case 2:
                printf("Quantidade de produtos atual: %d\n\n",aux->Dados.quantidade);
                printf("\t->Digite uma nova quantidade:\n\n");
                scanf("%d",&aux->Dados.quantidade);
                break;

                case 3:
                printf("Valor de entrada atual: %.2f\n\n",aux->Dados.valorDeEntrada);
                printf("\t->Digite um novo valor de entrada:\n\n");
                scanf("%f",&aux->Dados.valorDeEntrada);
                break;

                case 4:
                printf("Valor de saída atual: %.2f\n\n",aux->Dados.valorDeSaida);
                printf("\t->Digite um novo valor de entrada:\n\n");
                scanf("%f",&aux->Dados.valorDeSaida);
                break;

            }
        }while(opcao!=5);
    }

    else
    {
        printf("Não foi encontrado o produto\n\n");
    }
}

void cadastroProduto(TipoProduto* DadosProduto){
	printf("\n * CADASTRO DE PRODUTO *\n");
	printf(" Nome:");
	fflush(stdin);
	gets(DadosProduto->nome);
	printf(" Data de Validade:");
	fflush(stdin);
	gets(DadosProduto->dataValidade);
	printf(" Valor de Entrada:");
	fflush(stdin);
	scanf(" %f", &DadosProduto->valorDeEntrada);
	printf(" Valor de Saida:");
	fflush(stdin);
	scanf(" %f", &DadosProduto->valorDeSaida);
	printf(" Quantidade:");
	fflush(stdin);
	scanf(" %d", &DadosProduto->quantidade);
	printf(" Codigo:");
	fflush(stdin);
	scanf(" %d", &DadosProduto->codigo);
	printf(" ***\n");
}

void cadastroVenda(TipoProduto* DadosProduto){
	printf("\n * CADASTRO DE VENDA *\n");
	printf(" Nome:");
	fflush(stdin);
	gets(DadosProduto->nome);
	printf(" Data de Validade:");
	fflush(stdin);
	gets(DadosProduto->nome);
	printf(" Valor de Entrada:");
	fflush(stdin);
	scanf(" %f", &DadosProduto->valorDeEntrada);
	printf(" Valor de Saida:");
	fflush(stdin);
	scanf(" %f", &DadosProduto->valorDeSaida);
	printf(" Quantidade:");
	fflush(stdin);
	scanf(" %d", &DadosProduto->quantidade);
	printf(" Codigo:");
	fflush(stdin);
	scanf(" %d", &DadosProduto->codigo);
	printf(" ****\n");
}