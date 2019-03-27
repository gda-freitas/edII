#include <stdio.h>
#include <stdlib.h>

struct lista{
	int valor;
	lista* prox;
};
typedef struct lista Lista;

Lista* criarVazia(){
	return NULL;
}

bool ehVazia(Lista* l){
	if(l == NULL)
		return true;
	else
		return false;
}

Lista* criarLista(int val){
	Lista* l = (Lista*) malloc(sizeof(Lista));
	if(ehVazia(l)){
		printf("Erro na alocacao.");
		exit(EXIT_FAILURE);
	}
	l->prox = NULL;
	l->valor = val;
	return l;
}

Lista* incluirInicio(Lista* lista, Lista* elemento){
	elemento->prox = lista;
	return elemento;
}

Lista* incluirFim(Lista* lista, Lista* elemento){
	if(ehVazia(lista)){
		return elemento;
	}
	Lista* aux = lista;	
	while(!ehVazia(aux->prox)){
		aux = aux->prox;
	}
	aux->prox = elemento;
	return lista;
}

void imprimirLista(Lista* lista){
	Lista* aux = lista;
	if(ehVazia(lista)){
		printf("Lista Vazia.\n");
		return;
	}
	while(!ehVazia(aux)){
		printf("%d ", aux->valor);
		aux = aux->prox;
	}
	printf("\n");
}

Lista* incluirOrdenado(Lista* lista, Lista* elemento){	
	Lista* aux;
	if(ehVazia(lista)){		
		return elemento;
	}
	else if(lista > elemento){
		elemento->prox = lista;
	}
	aux = lista;	
	while(!ehVazia(aux->prox) && aux->prox->valor < elemento->valor){
		aux = aux->prox;
	}
	elemento->prox = aux->prox;
	aux->prox = elemento;
	
	return lista;
}

int main(void){
	Lista* lista = criarVazia();
	imprimirLista(lista);
	lista = incluirOrdenado(lista, criarLista(2));

	lista = incluirOrdenado(lista, criarLista(10));
	lista = incluirOrdenado(lista, criarLista(5));
	
	lista = incluirOrdenado(lista, criarLista(20));

	lista = incluirOrdenado(lista, criarLista(15));
	imprimirLista(lista);
}
