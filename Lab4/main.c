/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
 ICMC/USP

 * Autor	: Guilherme Alves Campos
 * Nº USP	: 8522320

 * Disciplina : SCC0216 - Modelagem Computacional em Grafos 
 * Professor  :  Ricardo Campello
 * Descriçao  : Workaholic 
_._._._._._._._._._._._._._._._._._._._._.*/

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


int cost;
int hotel;

GRAPH *makeGraph (int vertex, int edges);
int *getFriends (int nFriends);
int choose (GRAPH *mapa, int *amigos, int nAmigos, int cidade, int *iMin);
void printIntVector (int *v, int n);

int main (int argc, char *argv[]) {
    int nCidades;
    int nCaminhos;
    int *menorCaminho = NULL;
    int nMenor;

    int nAmigos;
    int *amigos = NULL;
    int mAmigo;

    int cidade;
    int tCusto;
    int op;

    GRAPH *mapa = NULL;

    /*Recebendo entradas iniciais*/
    scanf("%d", &nCidades);
    scanf ("%d %d", &cost, &hotel);
    scanf("%d", &nCaminhos);

    /*Modelando o problema em um grafo*/
    mapa = makeGraph (nCidades, nCaminhos);

    /*Salvando amigos*/
    scanf ("%d", &nAmigos);
    amigos = getFriends (nAmigos);

    scanf("%d %d", &op,  &cidade);
    
    tCusto = choose(mapa, amigos, nAmigos, cidade, &mAmigo);
    menorCaminho = getMenorCaminho (mapa, amigos[mAmigo], cidade, &nMenor);
   
    switch (op) {
        
        case 1: printf("%.3d\n", tCusto);
                break;
        case 2: printIntVector(menorCaminho, nMenor);
                printf("\n");
                break;
        case 3: if (mAmigo == -1) printf("Atende ");
                else printf("Repassa ");
                printf("%.3d\n", tCusto);
                break;
    
        default: break;
    }

	return 0;
}

void printIntVector (int *v, int n) {
    int i;
    for (i = n-1; i >= 0; i--) printf ("%d ", v[i]);
}

int choose (GRAPH *mapa, int *amigos, int nAmigos, int cidade, int *iMin) {
    int i;
    int x;

    int min = INT_MAX;
    int jMin;


    for (i = 0; i < nAmigos; i++) {
        x = getMin (mapa, amigos[i], cidade);
        //printf("min: %d\n", x);

        if (x < min) {
            min = x;
            (*iMin) = i;
        }
    }

    jMin = getMin (mapa, 1, cidade);
    //printf("jMin: %d\nmin: %d\n", jMin, min);

    jMin += hotel;
    min += cost;
    
    (*iMin) = jMin <= min ? 10 : (*iMin); 
    return jMin <= min ? jMin : min;  

}

int *getFriends (int nFriends) {
    int i;
    int *friends = (int *) malloc (nFriends * sizeof(int)); 

    for (i = 0; i < nFriends; i++) {
        scanf ("%d", &friends[i]);
    }

    return friends;

}

GRAPH *makeGraph (int vertex, int edges) {
    GRAPH *grafo = NULL;
    int cidade1, cidade2;
    int valor;
    int i, j;

    grafo = createGraph();

    //Cidade 0 ser'a uma cidade fantasma, sem ligaçao com as demais
    for (i = 0; i < vertex + 1; i++) {
        insertVertex(grafo, i);    
    }


    for (i = 0; i < edges; i++) {
        scanf ("%d %d %d", &cidade1, &cidade2, &valor);
        insertEdge (grafo, cidade1, cidade2, valor);
    }

    return grafo;
}