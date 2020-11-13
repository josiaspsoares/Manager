#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"ListaVendas.h"

ListaVendas* criaListaVendas(){
    ListaVendas* ListaVendasManager = (ListaVendas*) malloc(sizeof(ListaVendas));

    if(ListaVendasManager != NULL){
        ListaVendasManager->primeiro = NULL;
        ListaVendasManager->ultimo = NULL;
        ListaVendasManager->quantidade = 0;
        ListaVendasManager->codigoAtual = 1;
    }

    return ListaVendasManager;
}

void liberaListaVendas(ListaVendas* ListaVendasManager){
    if(ListaVendasManager != NULL){
        ElementoVenda* no;

        while(ListaVendasManager->primeiro != NULL){
            no = ListaVendasManager->primeiro;
            ListaVendasManager->primeiro = ListaVendasManager->primeiro->proximo;
            free(no);
        }

        free(ListaVendasManager);
    }
}

int listaVendasVazia(ListaVendas* ListaVendasManager){
    if(ListaVendasManager == NULL) return 1;
    if(ListaVendasManager->primeiro == NULL) return 1;
    return 0;
}

int tamanhoListaVendas(ListaVendas* ListaVendasManager){
    if(ListaVendasManager == NULL) return 0;
    return ListaVendasManager->quantidade;
}

int insereListaVendasInicio(ListaVendas* ListaVendasManager, TipoVenda DadosVenda){
    if(ListaVendasManager == NULL) return 0;
    
    ElementoVenda* no = (ElementoVenda*) malloc(sizeof(ElementoVenda));
    if(no == NULL) return 0; 
    no->Dados = DadosVenda;

    if(listaVendasVazia(ListaVendasManager)){ 	
		ListaVendasManager->primeiro = no;
		ListaVendasManager->ultimo = no;
	}
	else{		
		no->proximo = ListaVendasManager->primeiro;
		ListaVendasManager->primeiro->anterior = no;
		ListaVendasManager->primeiro = no;
	}
     
    ListaVendasManager->quantidade++;
    return 1;
}

int removeListaVendasInicio(ListaVendas* ListaVendasManager){
    if(ListaVendasManager == NULL) return 0;
    if((ListaVendasManager->primeiro) == NULL) return 0;
    
    ElementoVenda *no = ListaVendasManager->primeiro;
    ListaVendasManager->primeiro = no->proximo;	

	if(no->proximo != NULL){
        no->proximo->anterior = NULL;	
        ListaVendasManager->quantidade--;
    }

    free(no);
    return 1;		
}

int removeListaVendasFinal(ListaVendas* ListaVendasManager){
    if(ListaVendasManager == NULL) return 0;
    if((ListaVendasManager->primeiro) == NULL) return 0;
    
    ElementoVenda *no = ListaVendasManager->ultimo;

    if(no == ListaVendasManager->primeiro){
        free(no);
        return removeListaVendasInicio(ListaVendasManager);
    }
    else{
        ListaVendasManager->ultimo->anterior->proximo = NULL;
        ListaVendasManager->ultimo = ListaVendasManager->ultimo->anterior;
        ListaVendasManager->quantidade--;
        free(no);
        return 1;
    }
}

int removeListaVendas(ListaVendas* ListaVendasManager, int codigo){
    if(ListaVendasManager == NULL) return 0;
    
    ElementoVenda *no = ListaVendasManager->primeiro;
    while(no != NULL && no->Dados.codigo != codigo){
        no = no->proximo;
    }

    if(no == NULL) return 0;
    if(no == ListaVendasManager->primeiro){
        free(no);
        return removeListaVendasInicio(ListaVendasManager);
    }
    else if(no == ListaVendasManager->ultimo){
        free(no);
        return removeListaVendasFinal(ListaVendasManager);
    }
    else{
        no->anterior->proximo = no->proximo;
        no->proximo->anterior = no->anterior;
        ListaVendasManager->quantidade--;
        free(no);
        return 1;
    }
}