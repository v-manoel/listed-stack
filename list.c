/*Algoritmo de lista dinamica encadeada, com pilha dinamica para elementos iguais*/

#include <stdlib.h>
#include <stdio.h>

typedef struct celula{
	int nColuna;
	struct celula *proxColuna;
	struct celula *proxLinha;
}celula;

void insertCelula (celula **marcador, int nColuna);
int deleteCelula (celula **marcador, int nColuna);
void printTabela (celula **marcador);

int main(void){
	celula *marcador = NULL;
    int nColuna;
    char opcao = 'e';

	do{
		printf("\n\n=====\tEscolha uma opcao:\t=====\n\ni - Para inserir;\n\nr- Para retirar;\n\ne - Para sair;\n\nl - Para listar;\n\n:");
		scanf(" %c",&opcao);
		system("cls");
		if(opcao == 'i'){
			printf("Digite o dado a ser inserido:\t");
			scanf("%d",&nColuna);
			insertCelula(&marcador, nColuna);
		}
		else if(opcao == 'r'){
            printf("Digite o dado a ser retirado:\t");
			scanf("%d",&nColuna);
            printf("[%d] - Coluna Retirado", deleteCelula(&marcador, nColuna));

		}
		else if(opcao == 'l')
			printTabela(&marcador);
	}while(opcao != 'e');
}

void insertCelula (celula **marcador, int nColuna){
	//Ponteiros atual e anterior são necessários para encontrar a posicao de inserção do dado
	celula *currentCelula, *previousCelula, *novaCelula;

	//Alocacao e verificacao de exito da alocaçao de memória para nova estrutura
	novaCelula = (celula*)malloc(sizeof(celula));
	if(!novaCelula){
		printf("0xE001 - Erro no processor de alocacao de memória");
		exit(1);
	}

	novaCelula->nColuna = nColuna;
	novaCelula->proxLinha = NULL;

	//Caso já tenha sido feita a primeira inserção na lista
	if(*marcador){
        currentCelula = *marcador;
        previousCelula = NULL;
		while(currentCelula && (currentCelula->nColuna < novaCelula->nColuna)){
			previousCelula = currentCelula;
			currentCelula = currentCelula->proxColuna;
		}

		//Caso o valor inserido for menor que o primeiro valor da lista
		if(currentCelula == *marcador && (currentCelula->nColuna > novaCelula->nColuna)){
			novaCelula->proxColuna = *marcador;
			*marcador = novaCelula;
		}
		//Caso todos os valores da lista forem  menores que o valor inserido
		else if(!currentCelula){
			previousCelula->proxColuna = novaCelula;
			novaCelula->proxColuna = NULL;
		}
		//Caso o valor inserido esteja entre o menor e maior valor da lista
		else if(currentCelula->nColuna > novaCelula->nColuna){
			previousCelula->proxColuna = novaCelula;
			novaCelula->proxColuna = currentCelula;
		}
		//Caso o valor inserido já esteja na lista
		else{
			while(currentCelula->proxLinha)
				currentCelula = currentCelula->proxLinha;
			currentCelula->proxLinha = novaCelula;
			novaCelula->proxLinha = NULL;
			novaCelula->proxColuna = NULL;
		}
	}
	//Caso seja a primeira inserção da lista
	else{
		novaCelula->proxColuna = NULL;
		*marcador = novaCelula;
	}

	return;
}

int deleteCelula (celula **marcador, int nColuna){
	//Caso não exista colunas na lista
	if(!(*marcador)){
		printf("0xE002 - Nao existem celulas na lista ");
		return 0;
	}
	celula *currentCelula, *previousCelula;
	currentCelula = *marcador;
	while(currentCelula && (currentCelula->nColuna != nColuna)){
		previousCelula = currentCelula;
		currentCelula = currentCelula->proxColuna;
	}
	//Caso a coluna não esteja contido na lista
	if(!currentCelula){
		printf("0xE003 -A celula nao esta contido na lista ");
		return 0;
	}
	int nColunaDeletada = currentCelula->nColuna;

	//Caso existam celulas replicadas
	if(currentCelula->proxLinha){
        celula *currentLinha,*previousLinha;
		currentLinha = currentCelula->proxLinha;
		currentCelula->proxLinha = NULL;
		while(currentLinha){
			previousLinha = currentLinha;
			currentLinha = currentLinha->proxLinha;
			free(previousLinha);
		}
	}
	//Caso exista apenas uma celula na lista
	if (!((*marcador)->nColuna))
        *marcador = NULL;

	//Caso seja necessario mover o marcador do inicio da lista
	else if((*marcador)->nColuna == nColuna)
		*marcador = currentCelula->proxColuna;

	//Caso o valor removido seja o ultimo da lista
	else if(!currentCelula->proxColuna)
		previousCelula->proxColuna = NULL;

	//Caso o valor removido esteja entre o menor e o maior valor da lista
	else
		previousCelula->proxColuna = currentCelula->proxColuna;

	free(currentCelula);
	return (nColunaDeletada);
}

void printTabela (celula **marcador){
     if(!(*marcador)){
        printf("0xE002 - Nao existem celulas na lista");
        return;
     }
     celula *tabelaAux = *marcador;
     celula *linhaAux = *marcador;
     while(tabelaAux){
            while(linhaAux){
                printf("%d  ", linhaAux->nColuna);
                linhaAux = linhaAux->proxLinha;
            }
        printf("\n");
        tabelaAux = tabelaAux->proxColuna;
        linhaAux = tabelaAux;
     }
}
