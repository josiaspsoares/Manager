#include<stdlib.h>
#include<stdio.h>
#include"ListaEstoque.h"

struct elemento{
    TipoProduto Dados; // Armazena os dados do TAD TipoProduto
    struct elemento *proximo; // Aponta para o próximo elemento da Lista
};
typedef struct elemento Elemento;

Lista* criaLista(){
    Lista* ListaEstoque = (Lista*) malloc(sizeof(Lista));

    if(ListaEstoque != NULL){
        // Verifica se a lista é válida
        *ListaEstoque = NULL;
    }

    return ListaEstoque; // Retorna o endereço alocado
}

void liberaLista(Lista* ListaEstoque){
    if(ListaEstoque != NULL){
        Elemento* no; // Sempre usar uma variável auxiliar para percorrer a lista

        while((*ListaEstoque) != NULL){
            no = *ListaEstoque;
            *ListaEstoque = (*ListaEstoque)->proximo;
            free(no); // Libera cada nó(elemento) da Lista
        }

        free(ListaEstoque); // Libera a Lista
    }
}

int listaVazia(Lista* ListaEstoque){
    if(ListaEstoque == NULL){
        // Verifica se a lista é válida
        return 1; 
    }
    if(*ListaEstoque == NULL){
        // Verifica se a lista possui algum elemento
        return 1;
    }

    return 0; // Se a lista não for vazia, retorna 0
}

int tamanhoLista(Lista* ListaEstoque){

    /* OBS: Os retornos servem para tratar possíveis erros ou sucessos
    que ocorram na execução do programa*/

    if(ListaEstoque == NULL){
        return 0;
    }

    int cont = 0; // Usado para contar o número de Elementos na Lista
    Elemento* no = *ListaEstoque; // O auxiliar nó recebe o início da Lista

    while(no != NULL){ // Percorre até o último elemento da Lista
        cont++;
        no = no->proximo; // O nó atual recebe o próximo nó 
    }

    return cont; // Retorna a quantidade de elementos encontrados
}

int insereListaInicio(Lista* ListaEstoque, TipoProduto DadosProduto){
    if(ListaEstoque == NULL){
        return 0;
    }

    Elemento* no = (Elemento*) malloc(sizeof(Elemento)); // Cria um elemento(nó) auxiliar
    if(no == NULL){
        // Verifica se o nó é válido
        return 0; 
    }

    no->Dados = DadosProduto; // O nó recebe os dados do produto a ser inserido
    no->proximo = (*ListaEstoque); // no->proximo recebe o elemento do início da lista
    *ListaEstoque = no; // O primeiro elemento da lista recebe o nó
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
    no->proximo = NULL; // No último elemento o próximo deve ser Null

    if((*ListaEstoque) == NULL){ // Verifica se a lista está vazia
        *ListaEstoque = no; // O primeiro elemento da lista recebe o nó
    }
    else{
        Elemento *aux = *ListaEstoque; // Cria um elemento auxiliar
        while(aux->proximo != NULL){ // Busca pelo final da Lista
            aux = aux->proximo;
        }
        aux->proximo = no; // Insere o novo nó ao próximo do último da Lista
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
        // Lista Vazia, insere na primeira posição
        no->proximo = (*ListaEstoque);
        *ListaEstoque = no;
        return 1;
    }
    else{
        Elemento *ant, *atual = *ListaEstoque;

        // Insere o produto da Lista em ordem de código e move os outros elementos
        while(atual != NULL && atual->Dados.codigo < DadosProduto.codigo){
            ant = atual;
            atual = atual->proximo;
        }

        if(atual == *ListaEstoque){
            // Verifica se deve inserir na primeira posição
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
    *ListaEstoque = no->proximo; // O ínicio da lista aponta para o segundo elemento
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
        // Verica se é o ínicio da Lista
        *ListaEstoque = no->proximo;
    }
    else{
        // O anterior aponta para o próximo do último elemento que é nulo
        ant->proximo = no->proximo;
    }

    free(no);
    return 1;
}

int removeLista(Lista* ListaEstoque, int codigo){
    // Passa-se o código do produto para a remoção

    if(ListaEstoque == NULL){
        return 0;
    }
    
    Elemento *ant, *no = *ListaEstoque;

    while(no != NULL && no->Dados.codigo != codigo){
        // Percorre a Lista até encontrar o elemento com o mesmo código
        ant = no;
        no = no->proximo;
    }

    if(no == NULL){
        // Se não encontrar o elemento com o código, retorna 0;
        return 0;
    }

    if(no == *ListaEstoque){
        // Verica se é o ínicio da Lista
        *ListaEstoque = no->proximo;
    }
    else{
        // O próximo do anterior rebe o próximo do elemento a ser removido
        ant->proximo = no->proximo;
    }

    free(no);
    return 1;

}

int consultaListaPosicao(Lista* ListaEstoque, int posicao, TipoProduto *DadosProduto){
    if(ListaEstoque == NULL || posicao <= 0){
        // Verifica se a posição é válida
        return 0;
    }

    Elemento *no = *ListaEstoque;
    int i = 1;

    while(no != NULL && i < posicao){
        // Percorre a lista até encontrar a posição desejada
        no = no->proximo;
        i++;
    }

    if(no == NULL){
        // Se não encontrar a posição, retorna 0;
        return 0;
    }
    else{
        // Obtem os dados do produto consultado através de um ponteiro
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
         // Percorre a Lista até encontrar o elemento com o mesmo código informado
        no = no->proximo;
    }

    if(no == NULL){
        // Se não encontrar o elemento com o código, retorna 0;
        return 0;
    }
    else{
         // Obtem os dados do produto consultado através de um ponteiro
        *DadosProduto = no->Dados;
        return 1;
    }
}