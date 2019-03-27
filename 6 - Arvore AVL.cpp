#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <stack>

using namespace std;

typedef struct arv{
	int val;
	struct arv* esq;
	struct arv* dir;
	int altura; 
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

int atualizarAltura(Arv* v){
 	if(v==NULL){
 		return 0;
	}
	else if(v->esq==NULL && v->dir==NULL){
		v->altura = 1;
		return 1;
	}
	else{
		int altEsq = atualizarAltura(v->esq);
		int altDir = atualizarAltura(v->dir);
		if(altDir > altEsq){
			v->altura = altDir + 1;
			return v->altura;
		}
		else if(altDir < altEsq){
			v->altura = altEsq + 1;
			return v->altura;
		}
	}	
 }

void rotaDireita(Arv** v){  
	Arv* aux = (*v)->esq; 
	Arv* original = *v;
	*v = aux;  
	original->esq = aux->dir;
	aux->dir = original;		
}

void rotaEsquerda(Arv** v){  
	Arv* aux = (*v)->dir; 
	Arv* original = *v;
	*v = aux;  
	original->dir = aux->esq;
	aux->esq = original;		
}
 
int calcFB(Arv* esq, Arv* dir){
	int altEsq = 0;
	int altDir = 0;
	if(esq != NULL){
		altEsq = esq->altura;
	}	
	if(dir != NULL){
		altDir = dir->altura;
	}
	return (altEsq-altDir);
}

void balancear(Arv** v){
	Arv* raiz = *v;
	if(calcFB(raiz->esq, raiz->dir) > 1){
		if(calcFB(raiz->esq->esq, raiz->esq->dir) > 0){
			printf(" Caso 1, rotacao direita externa \n");
			rotaDireita(v);
		}else{
			printf(" Caso 3, rotacao esquerda interna e direita externa \n");
			rotaEsquerda(&((*v)->esq));
			rotaDireita(v);
		}		
	}
	else if(calcFB(raiz->esq, raiz->dir) < -1) {
		if(calcFB(raiz->dir->esq, raiz->dir->dir) < 0){
			printf(" Caso 2, rotacao esquerda externa \n");
			rotaEsquerda(v);
		}else{
			printf(" Caso 4. rotacao direita interna e esquerda externa \n");
			rotaDireita(&((*v)->dir));
			rotaEsquerda(v);
		}		
	}
	atualizarAltura(*v);
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

Arv* insereBin(Arv* original, Arv* v, int valor){
	if(v == NULL){
		Arv* novo = (Arv*)malloc(sizeof(Arv));
		novo->val = valor;
		novo->dir = novo->esq = NULL;
		novo->altura = 0; 
		atualizarAltura(original);
		return novo;
	}
	else if(v->val > valor){
		v->esq = insereBin(original, v->esq, valor);
	}
	else{
		v->dir = insereBin(original, v->dir, valor);
	}
	
	balancear(&v);
	return v;	
}

Arv* removeBin(Arv* original, Arv* v, int valor){
	if(v==NULL){
		return NULL;
	}else if(v->val > valor){
		v->esq = removeBin(original, v->esq, valor);
	}else if(v->val < valor){
		v->dir = removeBin(original, v->dir, valor);
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
			
			v->esq = removeBin(original, v->esq, valor);
		
			return v;
		}	
	}	
	atualizarAltura(original);
	balancear(&v);
	return v;
}


int main(){
	Arv* raiz1 = criaVazia();
	
	raiz1 = insereBin(raiz1, raiz1, 12); 
	raiz1 = insereBin(raiz1, raiz1, 10);	
	raiz1 = insereBin(raiz1, raiz1, 6);		
	printf(" Arvore: 12, 10, 6\n Saida:");
	preOrder(raiz1);	
	printf("\n\n");
	
	Arv* raiz2 = criaVazia();	
	raiz2 = insereBin(raiz2, raiz2, 6); 
	raiz2 = insereBin(raiz2, raiz2, 10);	
	raiz2 = insereBin(raiz2, raiz2, 12);
	printf(" Arvore: 6, 10, 12\n Saida:");
	preOrder(raiz2);
	printf("\n\n");

	Arv* raiz3 = criaVazia();	
	raiz3 = insereBin(raiz3, raiz3, 7);//					7
	raiz3 = insereBin(raiz3, raiz3, 2);//			2				9
	raiz3 = insereBin(raiz3, raiz3, 9);//	1				5	
	raiz3 = insereBin(raiz3, raiz3, 1);//				3
	raiz3 = insereBin(raiz3, raiz3, 5);	
	raiz3 = insereBin(raiz3, raiz3, 3);	
	printf(" Arvore: 7, 2, 9, 1, 5, 3\n Saida:");
	preOrder(raiz3);
	printf("\n\n");

	Arv* raiz4 = criaVazia();	
	raiz4 = insereBin(raiz4, raiz4, 6);//				6
	raiz4 = insereBin(raiz4, raiz4, 4);//		4					10
	raiz4 = insereBin(raiz4, raiz4, 10);//					8				12
	raiz4 = insereBin(raiz4, raiz4, 8);//						9
	raiz4 = insereBin(raiz4, raiz4, 12);	
	raiz4 = insereBin(raiz4, raiz4, 9);	
	printf(" Arvore: 6, 4, 10, 8, 12, 9\n Saida:");
	preOrder(raiz4);

	printf("\n\n Exclusao dos elementos 3,1,2 da arv3\n");
	raiz3 = removeBin(raiz3, raiz3, 3);
	raiz3 = removeBin(raiz3, raiz3, 1);
	raiz3 = removeBin(raiz3, raiz3, 2);

	preOrder(raiz3);

	printf("\n\n\t *Arvores apresentadas em Ordem de Inclusao\n\t **Saidas em Pre-Order");
}
