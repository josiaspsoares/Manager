#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include"ListaVendas.h"

ListaVendas* criaListaVendas(){
    ListaVendas* ListaVendasManager = (ListaVendas*) malloc(sizeof(ListaVendas));

    if(ListaVendasManager != NULL){
        ListaVendasManager->primeiro = NULL;
        ListaVendasManager->ultimo = NULL;
        ListaVendasManager->valorInicialCaixa = 0.0;
        ListaVendasManager->valorFinalCaixa = 0.0;
        ListaVendasManager->lucroFinal = 0.0;
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

void preencherData(TipoVenda *venda){
	struct tm *data_hora_atual;
	time_t segundos;

	time(&segundos);
	data_hora_atual = (struct tm*) localtime(&segundos);

	venda->DataHora->dia=data_hora_atual->tm_mday;

    venda->DataHora->mes=data_hora_atual->tm_mon+1;

	venda->DataHora->ano=data_hora_atual->tm_year+1900;

	venda->DataHora->hora=data_hora_atual->tm_hour;//hora
	venda->DataHora->minuto=data_hora_atual->tm_min;//minuto
	venda->DataHora->segundo=data_hora_atual->tm_sec;//segundo

    return;
}


void realizarVenda(ListaProdutos *lista, ListaVendas *listaVendido){
    ElementoProduto *produtoAuxiliar;
    int opcao,controle=0, respostas=0;//variavel respostas que responde todas as perguntas
    float valorEntregadoCliente;
    ElementoProduto *produtoVendido;
    TipoVenda DadosVenda;
    DadosVenda.DataHora = (Time*) calloc(1, sizeof(Time));
    struct tm dataAtual;

    preencherData(&DadosVenda);
    system("pause");

    if (lista->quantidade==0){
        printf("\n\nNão há produtos cadastrados.\n");

        return;

    }

    produtoAuxiliar=lista->primeiro;
    printf("<<REALIZAR VENDA>> \n\n");

    while (produtoAuxiliar!=NULL){
        printf("%d) %s\n", produtoAuxiliar->Dados.codigo, produtoAuxiliar->Dados.nome);

        produtoAuxiliar=produtoAuxiliar->proximo;
    }

    printf("Digite o código do produto que vendeu: ");

    scanf ("%d", &respostas);


    produtoAuxiliar=lista->primeiro;

    while (produtoAuxiliar!=NULL){ // Procura o produto com o código dito.
        if (produtoAuxiliar->Dados.codigo==respostas){
            produtoVendido=produtoAuxiliar;
            controle=1;
            break;
        }
        produtoAuxiliar=produtoAuxiliar->proximo;
    }

    if (controle==0){// variavel controle controla se entrou ou não na função que encontra os codigos iguais
        printf("Não há produtos com o código!");
        return;
    }

    printf("Produto ( %s ) que custa R$%.2f\nVenda de quantas unidades?  ",produtoVendido->Dados.nome,  produtoVendido->Dados.valorDeSaida);

    scanf ("%d", &respostas);

    if (produtoVendido->Dados.quantidade>=respostas){
        printf("Nome do vendedor:  ");
        fflush(stdin);
        gets(DadosVenda.vendedor);

        printf("\n\n");

        printf("Qual o método de pagamento?\n1) Cartão\n2)Dinheiro\n\n : ");
        do{
            scanf ("%d", &opcao);
        }while(opcao!=1 && opcao!=2);

        system("cls");
        printf("Processando venda...\n\n");

        switch(opcao){//DIVIDE CARTAO OU DINHEIRO, POIS SAO TRATAMENTOS DIFERENTES
            case 1:
                strcpy(DadosVenda.metodoPagamento, "Cartão");
                DadosVenda.troco=0;
                break;
            case 2:
                printf("Quanto o cliente entregou (Ficará um loop até o cliente entregar um valor maior ou igual a %.2f ):\n\b ", (respostas*produtoVendido->Dados.valorDeSaida));
                do{
                    scanf ("%f", &valorEntregadoCliente);
                }while(valorEntregadoCliente<(respostas*produtoVendido->Dados.valorDeSaida));//controla pro valor entregue ser maior

                strcpy(DadosVenda.metodoPagamento, "Dinheiro");
                DadosVenda.troco=valorEntregadoCliente-(respostas*produtoVendido->Dados.valorDeSaida);
                printf("TROCO = %.2f ", DadosVenda.troco);
            break;
        }


        //processando todos os dados da venda
        DadosVenda.valorPago=(respostas*produtoVendido->Dados.valorDeSaida);
        produtoVendido->Dados.quantidade=produtoVendido->Dados.quantidade-respostas;
        DadosVenda.codigo=listaVendido->quantidade;
        DadosVenda.lucroVenda=(respostas*produtoVendido->Dados.valorDeSaida)-(respostas*produtoVendido->Dados.valorDeEntrada);
        DadosVenda.totalVenda=respostas*produtoVendido->Dados.valorDeSaida;

        printf("\n\nvendedor %s, meto %s, total %.2f, luc %.2f, valor pg %.2f, troco %.2f\n\n", DadosVenda.vendedor,DadosVenda.metodoPagamento,DadosVenda.totalVenda,
               DadosVenda.lucroVenda, DadosVenda.valorPago,DadosVenda.troco);
        printf("\n\n%d/%d/%d, %d:%d", DadosVenda.DataHora->dia, DadosVenda.DataHora->mes,DadosVenda.DataHora->ano,DadosVenda.DataHora->hora,DadosVenda.DataHora->minuto, DadosVenda.DataHora->segundo );
        insereListaVendasInicio(listaVendido,DadosVenda);
        listaVendido->valorFinalCaixa += DadosVenda.totalVenda;
        listaVendido->lucroFinal += DadosVenda.lucroVenda;
    }
    else{
        printf("\n\nNão há esse estoque para venda.\n\n");
        return;
    }
}

int fechamentoDeCaixa(ListaVendas* ListaVendasManager){
	int i;
	
    FILE *pont_arq;
    pont_arq = fopen("RelatorioVendas.txt", "w");

	printf(" Valor inicial do caixa: ");
	scanf("%f", &ListaVendasManager->valorInicialCaixa);
	
    ElementoVenda *VendaAuxiliar = ListaVendasManager->primeiro;
    
    fprintf(pont_arq, "     *** RELATÓRIO DE VENDAS ***\n\n");
    fprintf(pont_arq, "%-3s   %-10s   %-5s    %-10s    %-5s\n", "COD", "VENDEDOR", "VALOR", "PAGAMENTO", "DATA");

	for(i=0; i < ListaVendasManager->quantidade; i++){
        fprintf(pont_arq, "%3d - %-10s - %5.2f - %-10s - ", VendaAuxiliar->Dados.codigo, VendaAuxiliar->Dados.vendedor, VendaAuxiliar->Dados.valorPago, VendaAuxiliar->Dados.metodoPagamento);
        fprintf(pont_arq,"%d/%d/%d, %d:%d\n", VendaAuxiliar->Dados.DataHora->dia, VendaAuxiliar->Dados.DataHora->mes,VendaAuxiliar->Dados.DataHora->ano,VendaAuxiliar->Dados.DataHora->hora,VendaAuxiliar->Dados.DataHora->minuto, VendaAuxiliar->Dados.DataHora->segundo );
        VendaAuxiliar = VendaAuxiliar->proximo;
    }
	
	printf("----------------------------\n");
	printf(" Caixa Inicial: %.2f\n", ListaVendasManager->valorInicialCaixa);
    fprintf(pont_arq, "\n\n > Caixa Inicial: %.2f\n", ListaVendasManager->valorInicialCaixa);
	printf(" Caixa Final: %.2f\n", ListaVendasManager->valorFinalCaixa);
    fprintf(pont_arq, " > Caixa Final: %.2f\n", ListaVendasManager->valorFinalCaixa);
    printf(" Lucro Total: %.2f\n", ListaVendasManager->lucroFinal);
    fprintf(pont_arq, " > Lucro Total: %.2f\n", ListaVendasManager->lucroFinal);
	printf(" Quantidade de vendas: %d", ListaVendasManager->quantidade);
    fprintf(pont_arq, " > Quantidade de vendas: %d", ListaVendasManager->quantidade);
	printf("----------------------------\n");

    fclose(pont_arq);
    return 0;
}

