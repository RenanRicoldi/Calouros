#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
#define branco 0
#define amarelo 1
#define vermelho 2
#define infinito 200000000

typedef int bool;
typedef int TIPOPESO;

typedef struct adjacencia {
    int vertice;
    TIPOPESO peso;
    struct adjacencia *proximo;
} Adjacencia;

typedef struct vertice {
    Adjacencia *inicio;
    int id;
    double x, y;
} Vertice;

typedef struct grafo {
    int numeroDeVertices;
    int numeroDeArestas;
    Vertice *arranjo;
} Grafo;

Grafo *criaGrafo(int numeroDeVertices) {
    Grafo *g = (Grafo *) malloc(sizeof(Grafo));
    g->numeroDeVertices = numeroDeVertices;
    g->numeroDeArestas = 0;
    g->arranjo = (Vertice *) malloc(numeroDeVertices*sizeof(Vertice));
    
    for(int i = 0; i<numeroDeVertices; i++)
        g->arranjo[i].inicio = NULL;
    return g;
}

Adjacencia *criaAdjacencia(int noFinal, int peso) {
    Adjacencia *lista = (Adjacencia *) malloc(sizeof(Adjacencia));
    
    lista->vertice = noFinal;
    lista->peso = peso;
    lista->proximo = NULL;
    
    return lista;
}

void defineInfo(Grafo* grafo, int noInicial, int noFinal, TIPOPESO peso) {
  Adjacencia *adjacencia = grafo->arranjo[noInicial].inicio;
        while(adjacencia) {
            if(adjacencia->vertice == noFinal){
              adjacencia->peso = peso;
              return;
            }
            adjacencia = adjacencia->proximo;
        }
        printf("Aresta nao encontrada\n");
}

TIPOPESO getInfo(Grafo* grafo, int noInicial, int noFinal) {
  Adjacencia *adjacencia = grafo->arranjo[noInicial].inicio;
        while(adjacencia) {
            if(adjacencia->vertice == noFinal){
              return adjacencia->peso;
            }
            adjacencia = adjacencia->proximo;
        }
        printf("Aresta nao encontrada\n");
        return 0;
}

void removeAresta(Grafo* grafo, int noInicial, int noFinal) {
  Adjacencia *adjacencia = grafo->arranjo[noInicial].inicio;
  Adjacencia *aux;
        while(adjacencia) {
            if(adjacencia->vertice == noFinal){
              grafo->numeroDeArestas--;
              if(grafo->arranjo[noInicial].inicio == adjacencia){
                grafo->arranjo[noInicial].inicio = adjacencia->proximo;
              } else {
                aux->proximo = adjacencia->proximo;
              }              
              free(adjacencia);
              return;
            }
            aux = adjacencia;
            adjacencia = adjacencia->proximo;
            
        }

        printf("Aresta nao encontrada\n");
}

bool insereAresta(Grafo* grafo, int noInicial, int noFinal, TIPOPESO peso) {
    if(!grafo)
        return false;
    if(noFinal < 0 || noFinal >= grafo->numeroDeVertices)
        return false;
    if(noInicial < 0 || noInicial >= grafo->numeroDeVertices)
        return false;

    Adjacencia *novo = criaAdjacencia(noFinal, peso);
    
    novo->proximo = grafo->arranjo[noInicial].inicio;
    grafo->arranjo[noInicial].inicio = novo;

    grafo->numeroDeArestas ++;

    return true;
}

void visitaPorProfundidade(Grafo* grafo, int i, int *cor) {
    cor[i] = amarelo;

    Adjacencia *aresta = grafo->arranjo[i].inicio;
    
    while(aresta) {
        if(cor[aresta->vertice] == branco)
            visitaPorProfundidade(grafo, aresta->vertice, cor);
        
        aresta = aresta->proximo;
    }

    cor[i] = vermelho;
}

void buscaPorProfundidade(Grafo* grafo) {
    int cor[grafo->numeroDeVertices];
    int i;

    for(i = 0; i < grafo->numeroDeVertices; i++) 
        cor[i] = branco;
    
    for(i = 0; i < grafo->numeroDeVertices; i++) {
        if(cor[i] == branco)
            visitaPorProfundidade(grafo, i, cor);
    }
}

void imprime(Grafo* grafo) {
    if (grafo == NULL) {
        printf("Grafo vazio!\n");
        return;
    }

    printf("Vertices: %d. Arestas: %d.\n", grafo->numeroDeVertices, grafo->numeroDeArestas);

    for(int i = 0; i < grafo->numeroDeVertices; i++) {
        printf("v%d: ", i);
        Adjacencia *adjacencia = grafo->arranjo[i].inicio;
        while(adjacencia) {
            printf("v%d(%d) ", adjacencia->vertice, adjacencia->peso);

            adjacencia = adjacencia->proximo;
        }
        printf("\n");
    }
}

void iniciaDijkstra(Grafo* grafo, int* distancia, int* pai, int noInicial) {
    for(int i = 0; i < grafo->numeroDeVertices; i++) {
        distancia[i] = infinito;
        pai[i] = -1;
    }
    distancia[noInicial] = 0;
}

void relaxa(Grafo* grafo, int* distancia, int* pai, int no1, int no2) {
    Adjacencia* aresta = grafo->arranjo[no1].inicio;

    while(aresta && aresta->vertice != no2) 
        aresta = aresta->proximo;

    if(aresta) {
        if(distancia[no2] > distancia[no1] + aresta->peso) {
            distancia[no2] = distancia[no1] + aresta->peso;
            pai[no2] = no1;
        }
    }
}

bool existeAberto(Grafo* grafo, int* aberto) {
    for(int i = 0; i < grafo->numeroDeVertices; i++) {
        if(aberto[i])
            return true;
    }
    
    return false;
}

int menorDistancia(Grafo* grafo, int* aberto, int* distancia) {
    int i, menor;
    
    for(i = 0; i < grafo->numeroDeVertices; i++) {
        if(aberto[i])
            break;
    }
    
    if(i == grafo->numeroDeVertices)
        return -1;
    
    menor = i;

    for(i = i+1; i < grafo->numeroDeVertices; i++) {
        if(aberto[i] && distancia[menor] > distancia[i])
            menor = i;
    }
    return menor;
}

int* dijkstra(Grafo* grafo, int noInicial) {
    int* distancia = (int*) malloc(grafo->numeroDeVertices*sizeof(int));
    int pai[grafo->numeroDeVertices];
    int menor;
    bool aberto[grafo->numeroDeVertices];
    Adjacencia* aresta;
    
    iniciaDijkstra(grafo, distancia, pai, noInicial);

    for(int i = 0; i < grafo->numeroDeVertices; i++) 
        aberto[i] = true;

    while (existeAberto(grafo, aberto))
    {
        menor = menorDistancia(grafo, aberto, distancia);
        aberto[menor] = false;

        aresta = grafo->arranjo[menor].inicio;
        while(aresta) {
            relaxa(grafo, distancia, pai, menor, aresta->vertice);
            aresta = aresta->proximo;
        }
    }

    return distancia;
}

int main() {
    Grafo* grafo = criaGrafo(6);

    insereAresta(grafo, 0, 1, 10);
    insereAresta(grafo, 0, 2, 5);
    insereAresta(grafo, 1, 3, 1);
    insereAresta(grafo, 2, 1, 3);
    insereAresta(grafo, 2, 3, 8);
    insereAresta(grafo, 2, 4, 2);
    insereAresta(grafo, 3, 4, 4);
    insereAresta(grafo, 3, 5, 4);
    insereAresta(grafo, 4, 5, 6);

    // defineInfo(grafo, 0, 1, 1);
    // defineInfo(grafo, 0, 2, 1);
    // defineInfo(grafo, 1, 0, 1);
    // defineInfo(grafo, 1, 3, 1);
    // defineInfo(grafo, 1, 2, 1);
    // defineInfo(grafo, 2, 0, 1);
    // defineInfo(grafo, 2, 1, 1);
    // defineInfo(grafo, 2, 3, 1);
    // defineInfo(grafo, 3, 4, 1);
    // defineInfo(grafo, 3, 2, 1);
    // defineInfo(grafo, 3, 1, 1);
    // defineInfo(grafo, 4, 3, 1);

    // removeAresta(grafo, 0, 1);
    // removeAresta(grafo, 0, 2);
    // removeAresta(grafo, 1, 0);
    // removeAresta(grafo, 1, 3);
    // removeAresta(grafo, 1, 2);
    // removeAresta(grafo, 2, 0);
    // removeAresta(grafo, 2, 1);
    // removeAresta(grafo, 2, 3);
    // removeAresta(grafo, 3, 4);
    // removeAresta(grafo, 3, 2);
    // removeAresta(grafo, 3, 1);
    // removeAresta(grafo, 4, 3);

    buscaPorProfundidade(grafo);
    imprime(grafo);

    int *r = dijkstra(grafo, 0);

    for(int i = 0; i < grafo->numeroDeVertices; i ++) {
        printf("D(v0 -> v%d) = %d\n", i, r[i]);
    }
    return 0;

}
