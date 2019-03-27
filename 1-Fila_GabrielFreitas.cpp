/*--------- Estrutura de Dados II ---------
------------ Entrega 1 - Fila ------------
----------- Gabriel A. Freitas ----------*/

#include <stdio.h>
#include <stdlib.h>

struct fila{
	int valor;
	struct fila* prox;
};
typedef struct fila Fila;

Fila* criaVazia(){  //Retorna um ponteiro NULL para inicializar a struct Fila.
	return NULL;
}

int ehVazia(Fila *inicioFila){	//Verifica se ha elementos na fila.
	if(inicioFila == NULL){
		return -1;
	}
	return 1;
}

Fila* criar(int val){	//Cria e retorna um novo elemento.
	Fila* novoItem = (Fila*)malloc(sizeof(Fila));
	if(novoItem == NULL){
		printf("\nFalha na alocacao de memoria.");
		exit(-1);
	}
	novoItem->valor = val;	
	novoItem->prox = NULL;
	return novoItem;
}

Fila* enfileirar(Fila* inicioFila, Fila* novo){	//Adiciona um elemento ao inicio da Fila.
	novo->prox = inicioFila; 
	return novo;
}

Fila* desenfileirar(Fila* inicioFila){	//Retira o ultimo elemento da Fila.
	if(ehVazia(inicioFila) == -1){
		printf("Fila Vazia. \n");
		exit(1);
	}	
	Fila* ant = inicioFila;
	Fila* aux = inicioFila->prox;
	if(aux == NULL){
		free(aux);
		return NULL;
	}
	while(aux->prox!=NULL){
		ant = aux;
		aux = aux->prox;
	}
	ant->prox = NULL;
	free(aux);
	return inicioFila;
}



void imprimir(Fila* inicioFila){	//Imprime todos os elementos da Fila.
	printf("\n---FILA---\n");
	if(ehVazia(inicioFila) == -1){
		printf("Fila Vazia. \n");
		return;
	}
	
	Fila* ant = inicioFila;
	Fila* aux = inicioFila->prox;
		
	while(aux!=NULL){
		printf("%d -> ", ant->valor);
		ant = aux;
		aux = aux->prox;
	}
	printf("%d \n", ant->valor);
}

int main(void){
	Fila* inicioFila = criaVazia();
		
	imprimir(inicioFila);
	
	inicioFila = enfileirar(inicioFila, criar(10));
	imprimir(inicioFila);
	inicioFila = enfileirar(inicioFila, criar(5));
	imprimir(inicioFila);
	inicioFila = enfileirar(inicioFila, criar(2));
	imprimir(inicioFila);
	
	inicioFila = enfileirar(inicioFila, criar(20));
	imprimir(inicioFila);
	inicioFila = desenfileirar(inicioFila);
	
	imprimir(inicioFila);
	inicioFila = desenfileirar(inicioFila);
	imprimir(inicioFila);
	inicioFila = desenfileirar(inicioFila);
	imprimir(inicioFila);
	inicioFila = desenfileirar(inicioFila);
	
	imprimir(inicioFila);
	
	return 0;
}
