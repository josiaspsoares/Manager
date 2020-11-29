typedef struct{
    char nome[200];
    char dataValidade[12];
    float valorDeEntrada;
    float valorDeSaida;
    int quantidade;
    int codigo;
}TipoProduto;

struct elementoProduto{
    TipoProduto Dados;
    struct elementoProduto *anterior;
    struct elementoProduto *proximo;
};
typedef struct elementoProduto ElementoProduto;

struct listaProdutos{
    ElementoProduto *primeiro;
    ElementoProduto *ultimo;
    int quantidade;
};

typedef struct listaProdutos ListaProdutos;

ListaProdutos* criaLista();
void liberaLista(ListaProdutos *ListaEstoque);
int tamanhoLista(ListaProdutos *ListaEstoque);
int listaVazia(ListaProdutos *ListaEstoque);
int insereListaInicio(ListaProdutos *ListaEstoque, TipoProduto DadosProduto);
int insereListaFinal(ListaProdutos *ListaEstoque, TipoProduto DadosProduto);
int insereListaOrdenada(ListaProdutos *ListaEstoque, TipoProduto DadosProduto);
int removeListaInicio(ListaProdutos *ListaEstoque);
int removeListaFinal(ListaProdutos *ListaEstoque);
int removeLista(ListaProdutos *ListaEstoque, int codigo);
void removeProdutoEstoque(ListaProdutos *ListaEstoque);
void verificarEstoque(ListaProdutos *ListaEstoque);
void exibirItem(ElementoProduto *auxiliar);
void exibirEstoque(ListaProdutos *ListaEstoque);
void editarEstoque(ListaProdutos *ListaEstoque);
int consultaListaCodigo(ListaProdutos*ListaEstoque, int codigo, TipoProduto *DadosProduto);
void cadastroProduto(TipoProduto* DadosProduto);

