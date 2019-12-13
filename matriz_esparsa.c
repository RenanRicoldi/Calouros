#include <stdio.h>
#include <stdlib.h>


//É um elemento da lista encadeada
typedef struct no {
    float valor;
    int coluna;
    struct no *proximo;
} No;

//A matriz possui um vetor (arranjo) de listas encadeadas representando cada elemento daquela linha
typedef struct {
    No** arranjo_de_listas;
    int numero_de_linhas;
    int numero_de_colunas;
} Matriz;

//Recebe uma matriz não inicializada e retorna uma matriz com as listas apontando para NULL
Matriz* iniciar_matriz(Matriz* matriz, int numero_de_linhas, int numero_de_colunas) {
    matriz = malloc(sizeof(Matriz));
    int i;

    matriz->numero_de_linhas = numero_de_linhas;
    matriz->numero_de_colunas = numero_de_colunas;
    matriz->arranjo_de_listas = (No**) malloc(numero_de_linhas*sizeof(No));
    
    for(i = 0; i < numero_de_linhas; i++)
        matriz->arranjo_de_listas[i] = NULL;

    return matriz;
}

//Recebe a posição de inserção e o valor de inserção
void inserir_valor_na_matriz(Matriz* matriz, int linha, int coluna, float valor) {
    if(linha < 0 || coluna < 0 || linha >= matriz->numero_de_linhas || coluna >= matriz->numero_de_colunas) //Verificação da posição de inserção
        return;
    
    No* anterior = NULL;
    No* atual = matriz->arranjo_de_listas[linha];

    while(atual != NULL && atual->coluna < coluna) {
        anterior = atual;
        atual = atual->proximo;
    }

    if(atual != NULL && atual->coluna == coluna) {      //Se já existe um elemento nessa linha e coluna altera o valor dele
        if(valor == 0) {
            if(anterior == NULL)
                matriz->arranjo_de_listas[linha] = atual->proximo;
            else
                anterior->proximo = atual->proximo;
            
            free(atual);
        }
        else
        {
            atual->valor = valor;
        }
    } else {                                            //Senão cria um novo elemento
        No* no = (No*) malloc(sizeof(No));
        no->coluna = coluna;
        no->valor = valor;
        no->proximo = atual;
        if(anterior == NULL)
            matriz->arranjo_de_listas[linha] = no;
        else
            anterior->proximo = no;
    }
}

//retorna o valor da posição informada
float buscar_valor_na_matriz(Matriz* matriz, int linha, int coluna) {
    if(linha < 0 || coluna < 0 || linha >= matriz->numero_de_linhas || coluna >= matriz->numero_de_colunas) //Verificação da posição de inserção
        return -1.0;

    No* no = matriz->arranjo_de_listas[linha];

    while(no != NULL && no->coluna < coluna)
        no = no->proximo;

    if(no != NULL && no->coluna == coluna)
        return no->valor;

    return 0;
}

int main() {
    int linhas = 3;
    int colunas = 3;
    int i, j;

    Matriz* matriz = iniciar_matriz(matriz, linhas, colunas);

    inserir_valor_na_matriz(matriz, 0, 1, 4.3);
    inserir_valor_na_matriz(matriz, 1, 0, 4.3);
    inserir_valor_na_matriz(matriz, 1, 1, 4.3);
    inserir_valor_na_matriz(matriz, 1, 2, 4.3);
    inserir_valor_na_matriz(matriz, 2, 1, 4.3);

    for(i = 0; i < linhas; i++) {
        for(j = 0; j < colunas; j++) {
            printf("%.1f ", buscar_valor_na_matriz(matriz, i, j));
        }
        printf("\n");
    }

    return 0;
}