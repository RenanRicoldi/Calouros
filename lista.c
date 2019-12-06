#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    struct no *prox;
    int info;
} No;

typedef struct lista {
    struct no *inicio;
} Lista;

Lista* criaLista(){
    Lista *lista = (Lista*)malloc(sizeof(Lista));
    lista->inicio = NULL;
    return lista;
}

void criaNo(Lista* lista, int info){
    No *no = (No*)malloc(sizeof(No));
    no->info = info;
    no->prox = NULL;

    if (lista->inicio == NULL){        
        lista->inicio = no;
    }
    else
    {
        No* aux = lista->inicio;
        while(1){
            if(aux->prox == NULL){
                aux->prox = no;
                break;
            }
            else{
                aux = aux->prox;
            }
        }
    }   
}

void imprimeLista(Lista *lista){
    No* no = lista->inicio;

    while(no != NULL){
        printf("no = %d\n", no->info);
        no = no->prox;
    }
}

void excluir(Lista *lista, int info){
    No* no = lista->inicio;
    No* aux;

    while(info != no->info) {
        aux = no;
        no = no->prox;
        if(no == NULL)
        {
            printf("Nenhum elemento com a informacao inserida foi encontrado na lista\n");
            return;
        }
    }
    
    if(no != lista->inicio) {
        aux->prox = no->prox;
        free(no);
    } else {
        if(lista->inicio->prox == NULL) {
            lista->inicio = NULL;
            free(no);
        } else {
            lista->inicio = lista->inicio->prox;
            free(no);
        }
    }

    return;
}

int main() {
    Lista *lista = criaLista();
    int comando = 2;

    while(comando != 0)
    {
        printf("Digite o numero a ser inserido: ");
        scanf("%d", &comando);
        criaNo(lista, comando);
    }
    comando = 1;
    
    while(comando != 0)
    {
        printf("Digite o numero a ser excluido: ");
        scanf("%d", &comando);
        excluir(lista, comando);
    }

    imprimeLista(lista);
}
