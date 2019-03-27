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
	}
}

void posOrdem(Arv* raiz){
	if(raiz!=NULL){		
		posOrdem(raiz->esq);
		posOrdem(raiz->dir);
		printf(" %d ", raiz->val);
	};
}

Arv* buscaBin(Arv* v, int valor){
	if(v == NULL){
		return NULL;
	} 
	else if(v->val > valor){
		return buscaBin(v->esq, valor);
	} 
	else if(v->val < valor){
		return buscaBin(v->dir, valor);
	} 
	else return v;
}

Arv* insereBin(Arv* v, int valor){
	if(v == NULL){
		Arv* novo = (Arv*)malloc(sizeof(Arv));
		novo->val = valor;
		novo->dir = novo->esq = NULL;
		return novo;
	}
	else if(v->val > valor){
		v->esq = insereBin(v->esq, valor);
	}
	else{
		v->dir = insereBin(v->dir, valor);
	}
	return v;
	
}

Arv* removeBin(Arv* v, int valor){
	if(v==NULL){
		return NULL;
	}else if(v->val > valor){
		v->esq = removeBin(v->esq, valor);
	}else if(v->val < valor){
		v->dir = removeBin(v->dir, valor);
	}else{
		//elemento encontrado
		
		if(v->dir == NULL && v->esq == NULL){
			//folha
			free(v);
			return NULL;
			
		}else if(v->dir == NULL){
			//possui filho a esquerda
			Arv* aux = v->esq;
			v->esq = NULL;
			free(v);
			return aux;

		}else if(v->esq == NULL){
			//Possui filho a direita
			Arv* aux = v->dir;
			v->dir = NULL;
			free(v);
			return aux;
		}else{
			
			//Possui dois filhos
			Arv* raiz = v;
			
			int aux = v->val;
			
			//busca filho mais a direita da subarvore esquerda
			Arv* maiorValorDireita = v->esq;
			 
			while(maiorValorDireita->dir != NULL){
				maiorValorDireita = maiorValorDireita->dir;
			} 
			
			//Swap de valores
			raiz->val = maiorValorDireita->val;
			maiorValorDireita->val = aux;
			
			v->esq = removeBin(v->esq, valor);
			
			// return v->esq;  //perda da arvore 
			return v;
		}	
	}	
	return v;
}

int main(){
	Arv* raiz = criaVazia();
	
	raiz = insereBin(raiz, 30); //						30
	raiz = insereBin(raiz, 10); //			10         				40
	raiz = insereBin(raiz, 5);  // 		5		15						50
	raiz = insereBin(raiz, 15); //					20
	raiz = insereBin(raiz, 20); //
	raiz = insereBin(raiz, 40); //
	raiz = insereBin(raiz, 50); //

	inOrdem(raiz);
	
	printf("\n\n");
	removeBin(raiz, 10);
	inOrdem(raiz);
	
	/*
	Arv* a5 = criaArvore(5, criaVazia(), criaVazia());
	Arv* a3 = criaArvore(3, criaVazia(), criaVazia());	
	Arv* a1 = criaArvore(1, criaVazia(), criaVazia());
	Arv* a7 = criaArvore(7, criaVazia(), criaVazia());	
	Arv* a6 = criaArvore(6, a5, a7);
	Arv* a2 = criaArvore(2, a1, a3);	
	raiz = criaArvore(4, a2, a6);
	*/
	
	/*
	printf(" DFS:");
	Arv* retorno = DFS(a1, 5);
	printf("\n\n BFS:");
	retorno = BFS(a1, 5);
	*/
	
	//printf("Pre Ordem: \n");
	//preOrdem(raiz);
	//printf("\nEm Ordem: \n");
	//inOrdem(raiz);
	//printf("\nPos Ordem: \n");
	//posOrdem(raiz);
}
