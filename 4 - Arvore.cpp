#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <stack>

using namespace std;

typedef struct arv{
	int val;
	struct arv* esq;
	struct arv* dir;
}Arv;

Arv* criaVazia(){
	return NULL;
}

Arv* criaArvore(int valor, Arv* esq, Arv* dir){
	Arv* arvore =  (Arv*)malloc(sizeof(Arv));
	if(arvore == NULL){
		printf("Erro na alocacao de memoria.");
		exit(EXIT_FAILURE);
	}
	arvore->val = valor;
	arvore->esq = esq;
	arvore->dir = dir;
	
	return arvore;	
}

Arv* DFS(Arv* raiz, int valor){
	stack<Arv*> stackArv;
	Arv* aux = criaVazia();
	
	stackArv.push(raiz);

	while(!stackArv.empty()){
		aux = stackArv.top();
		stackArv.pop();
		
		printf("\n %d", aux->val);
		if(aux->val == valor){
			return aux;
		}
		else{
			if(aux->esq != NULL){
				stackArv.push(aux->esq);
			} 
			if(aux->dir!=NULL){
				stackArv.push(aux->dir);
			}
		}		
	}	
	
	return NULL;
}

Arv* BFS(Arv* raiz, int valor){
	queue<Arv*> queueArv;
	Arv* aux = criaVazia();
	
	queueArv.push(raiz);
	while(!queueArv.empty()){
		aux = queueArv.front();		
		queueArv.pop();
		
		printf("\n %d", aux->val);
		if(aux->val == valor){
			return aux;
		}
		else{
			if(aux->esq != NULL){
				queueArv.push(aux->esq);
			} 
			if(aux->dir!=NULL){
				queueArv.push(aux->dir);
			}
		}		
	}	
	
	return NULL;
}

void preOrdem(Arv* raiz){
	if(raiz!=NULL){
		printf(" %d ", raiz->val);
		preOrdem(raiz->esq);
		preOrdem(raiz->dir);
	};
}

void inOrdem(Arv* raiz){
	if(raiz!=NULL){		
		inOrdem(raiz->esq);
		printf(" %d ", raiz->val);
		inOrdem(raiz->dir);
	};
}

void posOrdem(Arv* raiz){
	if(raiz!=NULL){		
		posOrdem(raiz->esq);
		posOrdem(raiz->dir);
		printf(" %d ", raiz->val);
	};
}

int main(){
	Arv* raiz = criaVazia();	
	
	Arv* a4 = criaArvore(4, criaVazia(), criaVazia());
	Arv* a5 = criaArvore(5, criaVazia(), criaVazia());
	Arv* a6 = criaArvore(6, criaVazia(), criaVazia());
	Arv* a7 = criaArvore(7, criaVazia(), criaVazia());	
	Arv* a2 = criaArvore(2, a4, a5);	
	Arv* a3 = criaArvore(3, a6, a7);	
	raiz = criaArvore(1, a2, a3);	
	
	/*
	printf(" DFS:");
	Arv* retorno = DFS(a1, 5);
	printf("\n\n BFS:");
	retorno = BFS(a1, 5);
	*/
	
	printf("Pre Ordem: \n");
	preOrdem(raiz);
	printf("\nEm Ordem: \n");
	inOrdem(raiz);
	printf("\nPos Ordem: \n");
	posOrdem(raiz);
}
