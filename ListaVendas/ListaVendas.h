#include"../ListaEstoque/ListaEstoque.h"

typedef struct{
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
    int segundo;
}Time;

// struct tmp {
//     int tm_sec;   // Indica os segundos de 0 a 59
//     int tm_min;   // Indica os minutos de 0 a 59
//     int tm_hour;  // Indica as horas de 0 a 24
//     int tm_mday;  // Indica os dias do mês de 1 a 31
//     int tm_mon;   // Indica os meses do ano de 0 a 11
//     int tm_year;  // Indica o ano a partir de 1900
//     int tm_wday;  // Indica o dia da semana de 0 (domingo) até 6 (sábado)
//     int tm_yday;  // Indica o dia do ano de 1 a 365
//     int tm_isdst; // Indica o horário de verão se for diferente de zero
// };

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
