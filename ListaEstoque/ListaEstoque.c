#include<stdlib.h>
#include<stdio.h>
#include"ListaEstoque.h"

struct elemento{
    TipoProduto Dados; // Armazena os dados do TAD TipoProduto
    struct elemento *proximo; // Aponta para o pr�ximo elemento da Lista
};
typedef struct elemento Elemento;

Lista* criaLista(){
    Lista* ListaEstoque = (Lista*) malloc(sizeof(Lista));

    if(ListaEstoque != NULL){
        // Verifica se a lista � v�lida
        *ListaEstoque = NULL;
    }

    return ListaEstoque; // Retorna o endere�o alocado
}

void liberaLista(Lista* ListaEstoque){
    if(ListaEstoque != NULL){
        Elemento* no; // Sempre usar uma vari�vel auxiliar para percorrer a lista

        while((*ListaEstoque) != NULL){
            no = *ListaEstoque;
            *ListaEstoque = (*ListaEstoque)->proximo;
            free(no); // Libera cada n�(elemento) da Lista
        }

        free(ListaEstoque); // Libera a Lista
    }
}

int listaVazia(Lista* ListaEstoque){
    if(ListaEstoque == NULL){
        // Verifica se a lista � v�lida
        return 1; 
    }
    if(*ListaEstoque == NULL){
        // Verifica se a lista possui algum elemento
        return 1;
    }

    return 0; // Se a lista n�o for vazia, retorna 0
}

int tamanhoLista(Lista* ListaEstoque){

    /* OBS: Os retornos servem para tratar poss�veis erros ou sucessos
    que ocorram na execu��o do programa*/

    if(ListaEstoque == NULL){
        return 0;
    }

    int cont = 0; // Usado para contar o n�mero de Elementos na Lista
    Elemento* no = *ListaEstoque; // O auxiliar n� recebe o in�cio da Lista

    while(no != NULL){ // Percorre at� o �ltimo elemento da Lista
        cont++;
        no = no->proximo; // O n� atual recebe o pr�ximo n� 
    }

    return cont; // Retorna a quantidade de elementos encontrados
}

int insereListaInicio(Lista* ListaEstoque, TipoProduto DadosProduto){
    if(ListaEstoque == NULL){
        return 0;
    }

    Elemento* no = (Elemento*) malloc(sizeof(Elemento)); // Cria um elemento(n�) auxiliar
    if(no == NULL){
        // Verifica se o n� � v�lido
        return 0; 
    }

    no->Dados = DadosProduto; // O n� recebe os dados do produto a ser inserido
    no->proximo = (*ListaEstoque); // no->proximo recebe o elemento do in�cio da lista
    *ListaEstoque = no; // O primeiro elemento da lista recebe o n�
    return 1;
}

int insereListaFinal(Lista* ListaEstoque, TipoProduto DadosProduto){
    if(ListaEstoque == NULL){
        return 0;
    }

    Elemento* no = (Elemento*) malloc(sizeof(Elemento));
    if(no == NULL){
        return 0;
    }

    no->Dados = DadosProduto;
    no->proximo = NULL; // No �ltimo elemento o pr�ximo deve ser Null

    if((*ListaEstoque) == NULL){ // Verifica se a lista est� vazia
        *ListaEstoque = no; // O primeiro elemento da lista recebe o n�
    }
    else{
        Elemento *aux = *ListaEstoque; // Cria um elemento auxiliar
        while(aux->proximo != NULL){ // Busca pelo final da Lista
            aux = aux->proximo;
        }
        aux->proximo = no; // Insere o novo n� ao pr�ximo do �ltimo da Lista
    }

    return 1;
}

int insereListaOrdenada(Lista* ListaEstoque, TipoProduto DadosProduto){
    if(ListaEstoque == NULL){
        return 0;
    }

    Elemento* no = (Elemento*) malloc(sizeof(Elemento));
    if(no == NULL){
        return 0;
    }

    no->Dados = DadosProduto;
    if(listaVazia(ListaEstoque)){
        // Lista Vazia, insere na primeira posi��o
        no->proximo = (*ListaEstoque);
        *ListaEstoque = no;
        return 1;
    }
    else{
        Elemento *ant, *atual = *ListaEstoque;

        // Insere o produto da Lista em ordem de c�digo e move os outros elementos
        while(atual != NULL && atual->Dados.codigo < DadosProduto.codigo){
            ant = atual;
            atual = atual->proximo;
        }

        if(atual == *ListaEstoque){
            // Verifica se deve inserir na primeira posi��o
            no->proximo = (*ListaEstoque);
            *ListaEstoque = no;
        }
        else{
            no->proximo = ant->proximo;
            ant->proximo = no;
        }
        
        return 1;
    }

}

int removeListaInicio(Lista* ListaEstoque){
    if(ListaEstoque == NULL){
        return 0;
    }
    if((*ListaEstoque) == NULL){
        return 0;
    }

    Elemento *no = *ListaEstoque;
    *ListaEstoque = no->proximo; // O �nicio da lista aponta para o segundo elemento
    free(no); // Libera o elemento removido
    return 1;
}

int removeListaFinal(Lista* ListaEstoque){
    if(ListaEstoque == NULL){
        return 0;
    }
    if((*ListaEstoque) == NULL){
        return 0;
    }

    Elemento *ant, *no = *ListaEstoque;
    while(no->proximo != NULL){
        // Busca o final da Lista
        ant = no;
        no = no->proximo;
    }

    if(no == (*ListaEstoque)){
        // Verica se � o �nicio da Lista
        *ListaEstoque = no->proximo;
    }
    else{
        // O anterior aponta para o pr�ximo do �ltimo elemento que � nulo
        ant->proximo = no->proximo;
    }

    free(no);
    return 1;
}

int removeLista(Lista* ListaEstoque, int codigo){
    // Passa-se o c�digo do produto para a remo��o

    if(ListaEstoque == NULL){
        return 0;
    }
    
    Elemento *ant, *no = *ListaEstoque;

    while(no != NULL && no->Dados.codigo != codigo){
        // Percorre a Lista at� encontrar o elemento com o mesmo c�digo
        ant = no;
        no = no->proximo;
    }

    if(no == NULL){
        // Se n�o encontrar o elemento com o c�digo, retorna 0;
        return 0;
    }

    if(no == *ListaEstoque){
        // Verica se � o �nicio da Lista
        *ListaEstoque = no->proximo;
    }
    else{
        // O pr�ximo do anterior rebe o pr�ximo do elemento a ser removido
        ant->proximo = no->proximo;
    }

    free(no);
    return 1;

}

int consultaListaPosicao(Lista* ListaEstoque, int posicao, TipoProduto *DadosProduto){
    if(ListaEstoque == NULL || posicao <= 0){
        // Verifica se a posi��o � v�lida
        return 0;
    }

    Elemento *no = *ListaEstoque;
    int i = 1;

    while(no != NULL && i < posicao){
        // Percorre a lista at� encontrar a posi��o desejada
        no = no->proximo;
        i++;
    }

    if(no == NULL){
        // Se n�o encontrar a posi��o, retorna 0;
        return 0;
    }
    else{
        // Obtem os dados do produto consultado atrav�s de um ponteiro
        *DadosProduto = no->Dados;
        return 1;
    }
}

int consultaListaCodigo(Lista* ListaEstoque, int codigo, TipoProduto *DadosProduto){
    if(ListaEstoque == NULL){
        return 0;
    }

    Elemento *no = *ListaEstoque;
    while(no != NULL && no->Dados.codigo != codigo){
         // Percorre a Lista at� encontrar o elemento com o mesmo c�digo informado
        no = no->proximo;
    }

    if(no == NULL){
        // Se n�o encontrar o elemento com o c�digo, retorna 0;
        return 0;
    }
    else{
         // Obtem os dados do produto consultado atrav�s de um ponteiro
        *DadosProduto = no->Dados;
        return 1;
    }
}