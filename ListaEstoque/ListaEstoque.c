#include<stdlib.h>
#include<stdio.h>
#include"ListaEstoque.h"

void  verificarEstoque (Lista *ListaEstoque){
    int opcao;
    Elemento *elementoAuxiliar;
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

Lista* criaLista(){
    Lista* ListaEstoque = (Lista*) malloc(sizeof(Lista));

    if(ListaEstoque != NULL){
        ListaEstoque->primeiro = NULL;
        ListaEstoque->ultimo = NULL;
        ListaEstoque->quantidade = 0;
    }

    return ListaEstoque;
}

void liberaLista(Lista* ListaEstoque){
    if(ListaEstoque != NULL){
        Elemento* no;

        while(ListaEstoque->primeiro != NULL){
            no = ListaEstoque->primeiro;
            ListaEstoque->primeiro = ListaEstoque->primeiro->proximo;
            free(no); // Libera cada nó(elemento) da Lista
        }

        free(ListaEstoque);
    }
}

int listaVazia(Lista* ListaEstoque){
    if(ListaEstoque == NULL) return 1;
    if(ListaEstoque->primeiro == NULL) return 1;
    return 0;
}

int tamanhoLista(Lista* ListaEstoque){
    if(ListaEstoque == NULL) return 0;
    return ListaEstoque->quantidade;
}

int insereListaInicio(Lista* ListaEstoque, TipoProduto DadosProduto){
    if(ListaEstoque == NULL) return 0;
    
    Elemento* no = (Elemento*) malloc(sizeof(Elemento));
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

int insereListaFinal(Lista* ListaEstoque, TipoProduto DadosProduto){
    if(ListaEstoque == NULL) return 0;

    Elemento* no = (Elemento*) malloc(sizeof(Elemento));
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

int insereListaOrdenada(Lista* ListaEstoque, TipoProduto DadosProduto){
    if(ListaEstoque == NULL) return 0;
    
    Elemento* no = (Elemento*) malloc(sizeof(Elemento));
    if(no == NULL) return 0;
    no->Dados = DadosProduto;

    if(listaVazia(ListaEstoque)){
        free(no);
        return insereListaInicio(ListaEstoque, DadosProduto);
    }
    else{
		Elemento *anterior, *atual = ListaEstoque->primeiro;

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

int removeListaInicio(Lista* ListaEstoque){
    if(ListaEstoque == NULL) return 0;
    if((ListaEstoque->primeiro) == NULL) return 0;
    
    Elemento *no = ListaEstoque->primeiro;
    ListaEstoque->primeiro = no->proximo;	

	if(no->proximo != NULL){
        no->proximo->anterior = NULL;	
        ListaEstoque->quantidade--;
    }

    free(no);
    return 1;		
}

int removeListaFinal(Lista* ListaEstoque){
    if(ListaEstoque == NULL) return 0;
    if((ListaEstoque->primeiro) == NULL) return 0;
    
    Elemento *no = ListaEstoque->ultimo;

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

int removeLista(Lista* ListaEstoque, int codigo){
    if(ListaEstoque == NULL) return 0;
    
    Elemento *no = ListaEstoque->primeiro;
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

int consultaListaPosicao(Lista* ListaEstoque, int posicao, TipoProduto *DadosProduto){
    if(ListaEstoque == NULL || posicao <= 0) return 0;

    Elemento *no = ListaEstoque->primeiro;
    int i = 1;

    while(no != NULL && i < posicao){
        no = no->proximo;
        i++;
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

int consultaListaCodigo(Lista* ListaEstoque, int codigo, TipoProduto *DadosProduto){
    if(ListaEstoque == NULL) return 0;
    
    Elemento *no = ListaEstoque->primeiro;
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