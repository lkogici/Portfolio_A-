#include <stdio.h>
#include <stdlib.h>
#include "Lista.h" //inclui os Prot�tipos

//Defini��o do tipo lista
struct elemento{
    struct estrutura dados;
    struct elemento *prox;
};

typedef struct elemento Elemento;

Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li){
    if(li != NULL){
        Elemento* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int insere_lista_ordenada(Lista* li, struct estrutura al){
    if(li == NULL)
        return 0;
    Elemento *no = (Elemento*) malloc(sizeof(Elemento));
    if(no == NULL)
        return 0;
    no->dados = al;
    if((*li) == NULL){//lista vazia: insere in�cio
        no->prox = NULL;
        *li = no;
        return 1;
    }
    else{
        Elemento *ant, *atual = *li;
        while(atual != NULL && atual->dados.custoF < al.custoF){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){//insere in�cio
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}

int remove_lista_inicio(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elemento *no = *li;
    *li = no->prox;
    free(no);
    return 1;
}

int tamanho_lista(Lista* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Elemento* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li){
    return 0;
}

int lista_vazia(Lista* li){
    if(li == NULL)
        return 1;
    if(*li == NULL)
        return 1;
    return 0;
}

struct estrutura consulta_lista(Lista* li){
    return (*li)->dados;
}

int verificaIgual(Lista* li, int x, int y)
{
    if(li == NULL)
        return 0;
    Elemento* no = *li;
    int aux = 0;
    while(no != NULL){
        if(no->dados.posicaoX == x && no->dados.posicaoY == y)
            aux = 1;
        no = no->prox;
    }
    return aux;
}

void imprimeLista(Lista* li){
    Elemento *no = *li;
    while(no != NULL){
        printf("\n");
        printf("Posicao do elemento: %d x %d \n", no->dados.posicaoX, no->dados.posicaoY);
        printf("Custo F: %.2f \n", no->dados.custoF);
        printf("\n");
        no = no->prox;
    }
}
