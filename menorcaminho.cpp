/*------------- Estrutura de Dados II --------------
-------------- Entrega Final One-to-all shorthest path ------------
--------------- Gabriel A. Freitas -----------------*/

#include <stdio.h>
#include <stdlib.h>
#include <list> 
#include <vector>
#include <deque> 
#include <iterator> 
using namespace std;

struct node{
	int index;
	vector<struct node*> *adj;
	int visitado;
	int dist;
	int recur;
};
typedef struct node Node;

struct grafo{
	int m;
	vector<Node*> vertices;
};
typedef struct grafo Grafo;


Grafo* criaGrafo(){

	Grafo *g = (Grafo*) malloc (sizeof(Grafo));
	g->m = 0;

	return g; 

}

int existeNode(Grafo *g, int index){

	for(int i = 0; i < g->vertices.size(); i++){
		if(g->vertices[i]->index == index) return 1;
	}

	return 0;

}

Node* addNode(Grafo *g, int index){

	if(!existeNode(g, index)){
		Node *n = (Node*) malloc(sizeof(Node));
		n->index = index;
		n->adj = new vector<Node*>;
		g->vertices.push_back(n);
		return n;
	}

	return NULL;
	
}

Node* buscaNode(Grafo* g, int index){

	int i = 0;
	for(i = 0; i < g->vertices.size(); i++){
		if(g->vertices[i]->index == index) {
			return g->vertices[i];
		}
	}
	return NULL;

}

void removeNode(Grafo *g, int index){

	int i = 0;
	vector<Node*>::iterator it;
	for(it = g->vertices.begin(); it != g->vertices.end(); it++){
		if((*it)->index == index) {
			g->vertices.erase(it);
			break;
		}
	}
	
}

void addArco(Grafo *g, int i, int j){
	
	Node *node_i = buscaNode(g, i);
	Node *node_j = buscaNode(g, j);
	if(node_i == NULL){
		node_i = addNode(g, i);
	}
	if(node_j == NULL){
		node_j = addNode(g, j);
	}
	node_i->adj->push_back(node_j);
	g->m += 1;

}

void addAresta(Grafo *g, int i, int j){
	
	addArco(g, i, j);
	addArco(g, j, i);

}

vector<Node*>* verticesAdj(Grafo *g, int i){
	
	Node* node = buscaNode(g, i);
	if (node != NULL){
		return node->adj;
	}else{
		return NULL;
	}

}

void menorCaminho(Grafo *g, int s){
	int i = 0;
		printf("menor caminho");

	for(i = 0; i<g->vertices.size(); i++){
		g->vertices.at(i)->visitado = 0;
		g->vertices.at(i)->dist = INT_MAX;
	}
	
	deque<Node*> queue;
	Node* aux = buscaNode(g, s);
	
	if(aux==NULL) return;
	queue.push_back(aux);
	
	while(!queue.empty()){
		aux = queue.front();
		queue.pop_front();
		aux->visitado = 1;

		for(i = 0; i < aux->adj->size(); i++){
			if(aux->adj->at(i)->visitado == 0){
				aux->adj->at(i)->dist = aux->dist + 1;
				queue.push_back((aux->adj->at(i)));
			}
		}
	}
}

void distancia(Grafo *g, int i, int j){
	menorCaminho(g, i);
	Node *aux = buscaNode(g, j);
	printf("%d", aux->dist);
}


void imprimirLista(vector<Node*> *lista){

	for(int i = 0; i < lista->size(); i++){
		printf("%d ", lista->at(i)->index);
	}
	printf("\n");

}

void imprimirGrafo(Grafo *g){


	for(int i = 0; i < g->vertices.size(); i++){
		printf("Node %d: ", g->vertices.at(i)->index);
		printf("\n   Adj: ");
		imprimirLista(g->vertices.at(i)->adj);
	}

}

int main(){
	
	Grafo *g = new Grafo();
	int i, j;
	int k = 0;
	while(scanf("%d %d", &i, &j) != EOF){
		addArco(g, i, j);
		printf("%d\n", k++);
	}
	imprimirGrafo(g);
}
