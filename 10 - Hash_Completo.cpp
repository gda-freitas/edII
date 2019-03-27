#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct linha{
	char livre;
	int chave;
	char *valor;
};
typedef struct linha Linha;

struct hash{
	Linha *linhas;
	int tam;
};
typedef struct hash Hash; 

/* -------------------------------------------
     Implemente os protótipos abaixo ! ! !
   ------------------------------------------*/

// Protótipo das funções de dispersão linear e quadrática
int funcDispLinear(Hash * h, int chave, int j){
	int i = chave%20+j;
	if(i>20){	//Se chagou ao fim, vai para inicio
		i = 20;	
	}
	if(j == 20){		//Se deu a volta, retorna erro 
		return -1;
	}
	if(h->linhas[i].livre != 'L'){
		return funcDispLinear(h, chave, j+1);	
	}
	return i;
}

int funcDispQuad(Hash * h, int chave, int k, int ant);

// Protótipo das funções de inserção
bool insereHashLinear(Hash * h, int chave, char * valor){
	int i = chave%20;
	
	if(h->linhas[i].livre != 'L'){
		i = funcDispLinear(h, chave, 1);
		if(i==-1){
			printf("\nFalha na inclusão.\n");
			return false;
		}
	}
	h->linhas[i].valor = valor;
	h->linhas[i].chave = chave;
	h->linhas[i].livre = 'O';
	
	return true;
}
bool insereHashQuad(Hash * h, int chave, char * valor);

// Protótipo das funções de busca
char * buscaHashLinear(Hash * h, int chave);
char * buscaHashQuad(Hash * h, int chave);


// Função de criação de tabela hash
Hash * criaHash(int tam){

	Hash * h = (Hash*) malloc(sizeof(Hash));
	h->linhas = (Linha*) malloc(sizeof(Linha) * tam);
	
	int i;
	for (i = 0; i < tam; i++){
		h->linhas[i].livre = 'L';
	}

	h->tam = tam;

	return h;
	
}


// Função para impressão de tabela hash
void imprimeHash(Hash * h) {
	
	int i;
	for (i = 0; i < h->tam; i++){
		if(h->linhas[i].livre == 'L'){
			printf("[%d] L\n", i);
		}else{
			printf("[%d] %d %s\n",i, h->linhas[i].chave, h->linhas[i].valor);
		}

	}
	
}


int main(){

	Hash * h = criaHash(20); // Tabela com m = 20
	
	insereHashLinear(h,10, "AAA");
	insereHashLinear(h,15, "BBB");
	insereHashLinear(h,10, "CCC");
	insereHashLinear(h,30, "DDD");
	insereHashLinear(h,10, "EEE");
	insereHashLinear(h,35, "FFF");
	insereHashLinear(h,10, "AAA");
	insereHashLinear(h,10, "AAA");
		insereHashLinear(h,10, "AAA");
		insereHashLinear(h,10, "AAA");
		insereHashLinear(h,10, "AAA");
		insereHashLinear(h,10, "AAA");
		insereHashLinear(h,10, "AAA");
		insereHashLinear(h,10, "AAA");
		insereHashLinear(h,10, "AAA");
		insereHashLinear(h,10, "AAA");
		insereHashLinear(h,10, "AAA");
		insereHashLinear(h,10, "AAA");	
		insereHashLinear(h,10, "AAA");
		insereHashLinear(h,10, "AAA");
	
			
	imprimeHash(h);
	return 0;
}
