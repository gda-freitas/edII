#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <stack>

using namespace std;

typedef struct arv{
	int val;
	struct arv* esq;
	struct arv* dir;
	//int altura; /valor para manter controle de balanço a cada nodo
}Arv;

Arv* criaVazia(){
	return NULL;
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

void preOrder(Arv* raiz){
	if(raiz!=NULL){
		printf(" %d ", raiz->val);
		preOrder(raiz->esq);
		preOrder(raiz->dir);
	};
}

void inOrder(Arv* raiz){
	if(raiz!=NULL){		
		inOrder(raiz->esq);
		printf(" %d ", raiz->val);
		inOrder(raiz->dir);
	}
}

void posOrder(Arv* raiz){
	if(raiz!=NULL){		
		posOrder(raiz->esq);
		posOrder(raiz->dir);
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
		//novo->altura = 0; 
		return novo;
	}
	else if(v->val > valor){
		v->esq = insereBin(v->esq, valor);
	}
	else{
		v->dir = insereBin(v->dir, valor);
	}
	//v->altura++;
	
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
			//aux->altura--;
			return aux;

		}else if(v->esq == NULL){
			//Possui filho a direita
			Arv* aux = v->dir;
			v->dir = NULL;
			free(v);
			//aux->altura--;
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
			
			//v->altura--;
			return v;
		}	
	}	
	//v->altura--;
	return v;
}

/*
void rotaDireita(Arv* v){ recebe o nodo Pai do nodo a ser rocationado
	Arx* aux = v->esq;
	v->esq = v->esq->dir;  Filho da direita da sub-árvore da esquerda passa a ser filho da esquerda da raiz
	v->esq->dir = v;	Filho da esquerda vira a nova raiz
}

void rotaEsquerda(Arv* v){  
	Arx* aux = v->dir;   
	v->dir = v->dir->esq;
	v->dir->esq = v;		
}
 
void balancear(Arv* v){  recebe a raiz da arvore e checa a cada nodo o valor de FB
	int fb = 0;
	if(v->esq->altura - v->esq->altura > 1 && v->esq->esq->altura - v->esq->dir->altura >0){
		rotaDireita(v);
	}
	else if(v->esq->altura - v->esq->altura < -1 && v->esq->esq->altura - v->esq->dir->altura <0){
		rotaEsquerda(v);
	}
	balancear(v->esq);
	banacear(v->dir);
}

*/

int main(){
	Arv* raiz = criaVazia();
	
	raiz = insereBin(raiz, 30); //						30
	raiz = insereBin(raiz, 10); //			10         				40
	raiz = insereBin(raiz, 5);  // 		5		15						50
	raiz = insereBin(raiz, 15); //					20
	raiz = insereBin(raiz, 20); //
	raiz = insereBin(raiz, 40); //
	raiz = insereBin(raiz, 50); //

	inOrder(raiz);
	
	printf("\n\n");
	removeBin(raiz, 10);
	inOrder(raiz);
	
	/*
	printf(" DFS:");
	Arv* retorno = DFS(a1, 5);
	printf("\n\n BFS:");
	retorno = BFS(a1, 5);
	*/
	
	//printf("Pre Ordem: \n");
	//preOrder(raiz);
	//printf("\nEm Ordem: \n");
	//inOrder(raiz);
	//printf("\nPos Ordem: \n");
	//posOrder(raiz);
}
