#include <stdio.h>
#include <stdlib.h>

struct Pilha{
	int valor;
	Pilha *prox;
}typedef Pilha;

Pilha* criarVazia(){
	return NULL;
}

Pilha* criar(int valor){
	Pilha* novo = (Pilha*) malloc(sizeof(Pilha));
	if(novo == NULL){
		exit(-1);
	}
	novo->valor = valor;
	novo->prox = NULL;
	return novo;
}

Pilha* empilhar(Pilha* topo, Pilha* novo){
	novo->prox = topo;
	return novo;
}

Pilha* desempilhar(Pilha* topo){
	Pilha* novoTopo = topo->prox;
	free(topo);
	return novoTopo;
}


void liberarPilha(Pilha* topo){
	Pilha* aux = topo;
	while(topo != NULL){
		printf("%d\n", topo->valor);
		aux = topo;
		topo = topo->prox;
		free(aux);
	}
}

Pilha* removerFila(Pilha* topo){
	Pilha* aux = topo->prox;
	Pilha* ant = topo;
	while(aux != NULL){
		if(aux->prox == NULL){
			ant->prox = NULL;
			free(aux);
			return topo;
		}
		ant = aux;
		aux = aux->prox;
	}	
	return topo;
}

int main(int argc, char** argv){
	Pilha* topo = criarVazia();
		
	topo = empilhar(topo, criar(10));
	topo = empilhar(topo, criar(2));
	topo = empilhar(topo, criar(5));

	removerFila(topo);
	liberarPilha(topo);
	return 0;
}
