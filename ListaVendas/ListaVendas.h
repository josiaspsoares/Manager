#include"../ListaEstoque/ListaEstoque.h"

typedef struct{
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
    int segundo;
}Time;

typedef struct{
    int codigo;
    char vendedor[100];
    Time *DataHora;
    //ListaProdutos *Carrinho;
    char metodoPagamento[50];
    float totalVenda;
    float lucroVenda;
    float valorPago;
    float troco;
}TipoVenda;

struct elementoVenda{
    TipoVenda Dados;
    struct elementoVenda *anterior;
    struct elementoVenda *proximo;
};
typedef struct elementoVenda ElementoVenda;

struct listaVendas{
    ElementoVenda *primeiro;
    ElementoVenda *ultimo;
    float valorInicialCaixa;
    float valorFinalCaixa;
    float lucroFinal;
    int quantidade;
    int codigoAtual;
};
typedef struct listaVendas ListaVendas;

ListaVendas* criaListaVendas();
void liberaListaVendas(ListaVendas* ListaVendasManager);
int tamanhoListaVendas(ListaVendas* ListaVendasManager);
int listaVendasVazia(ListaVendas* ListaVendasManager);
int insereListaVendasInicio(ListaVendas* ListaVendasManager, TipoVenda DadosVenda);
int removeListaVendasInicio(ListaVendas* ListaVendasManager);
int removeListaVendasFinal(ListaVendas* ListaVendasManager);
int removeListaVendas(ListaVendas* ListaVendasManager, int codigo);
void preencherData(TipoVenda *venda);
void realizarVenda(ListaProdutos *lista, ListaVendas *listaVendido);
int fechamentoDeCaixa(ListaVendas* ListaVendasManager);
