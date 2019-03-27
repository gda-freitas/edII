#include <stdio.h>
#include <stdlib.h>
#include <list> 
#include <iterator> 
using namespace std;

struct grafo{
	int n;
	int m;
	int **adj;
}typedef Grafo;

Grafo* criaGrafo(int n){
	int i = 0, j = 0;
	Grafo* g = (Grafo*) malloc(sizeof(Grafo));

	g->adj = (int**) malloc ((n+1)*sizeof(int));
	
	for(i=0; i<n; i++){
		g->adj[i] =(int*) malloc((n+1)*sizeof(int));
	}
	
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			g->adj[i][j] = 0;
		}
	}
	
	g->n = 0;
	g->m = 0;
	
	return g;
}

void addAresta(Grafo *g, int i, int j){
	if(i<g->n && j<g->n){
		
		if(g->adj[i][j]==0){
			g->adj[i][j] = 1;
			g->adj[j][i] = 1;
			g->m += 2;
		}
	}
}

void removeAresta(Grafo *g, int i, int j){
	if(i<g->n && j<g->n){
		
		if(g->adj[i][j]==1){
			g->adj[i][j] = 0;
			g->adj[j][i] = 0;
			g->m -= 2;
		}
	}
}

list<int>* verticesAdj(Grafo *g, int i){
	list<int> *adj = new list<int>;
	
	int j = 0;
	if(i<g->n){
		for(j = 0; j< g->n; j++){
			if(g->adj[i][j] == 1){
				adj->push_back(j);
			}
		}
		return adj;
		
	}else{
		return NULL;
	}
}

int numVertices(Grafo *g){
	return g->n;
}

int numArestas(Grafo *g){
	return g->m;
}

void imprimirLista(list<int> *lista){
	list<int>::iterator it;
	
	for(it = lista->begin(); it != lista->end(); it++){
		printf("%d ", *it);
	}
	
} 

int main(){
	int tam = 347, i=0, j=0;
	Grafo *grafo = criaGrafo(tam);
	
	while(!EOF){
		scanf("%d %d\n", &i, &j);
		addAresta(grafo, i, j);
	}
	
	printf("Número e arestas: %d", numArestas(grafo));
	printf("OOOOOOOOOOOOOOOOOOOIIIIIIIIIIII");

}
