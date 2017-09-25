#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include "Lista.h"

int objY, objX, personX, personY;

struct estrutura auxiliar;
struct estrutura menorCusto;

double calculaHeuristica(int cordX, int cordY){
    double aux1, aux2, result;
    aux1 = pow((cordX - objX), 2);
    aux2 = pow((cordY - objY), 2);
    result = pow(aux1 + aux2, 0.5);
    return result;
}

void adicionaAlcancaveis(int matriz[20][35], Lista* listaAberta, Lista* listaFechada){
    if(personX + 1 < 20 && matriz[personX + 1][personY] != 'X' && verificaIgual(listaAberta, personX + 1, personY) == 0 && verificaIgual(listaFechada, personX + 1, personY) == 0){
        auxiliar.custoF = calculaHeuristica(personX+1, personY) + matriz[personX][personY];
        auxiliar.posicaoX = personX + 1;
        auxiliar.posicaoY = personY;
        insere_lista_ordenada(listaAberta, auxiliar);
    }

    if(personX - 1 > 0 && matriz[personX - 1][personY] != 'X' && verificaIgual(listaAberta, personX - 1, personY) == 0 && verificaIgual(listaFechada, personX - 1, personY) == 0){
        auxiliar.custoF = calculaHeuristica(personX-1, personY) + matriz[personX][personY];
        auxiliar.posicaoX = personX - 1;
        auxiliar.posicaoY = personY;
        insere_lista_ordenada(listaAberta, auxiliar);
    }

    if(personY + 1 < 35 && matriz[personX][personY + 1] != 'X' && verificaIgual(listaAberta, personX, personY + 1) == 0 && verificaIgual(listaFechada, personX, personY + 1) == 0){
        auxiliar.custoF = calculaHeuristica(personX, personY+1) + matriz[personX][personY];
        auxiliar.posicaoX = personX;
        auxiliar.posicaoY = personY + 1;
        insere_lista_ordenada(listaAberta, auxiliar);
    }

    if(personY - 1 > 0 && matriz[personX][personY - 1] != 'X'  && verificaIgual(listaAberta, personX, personY - 1) == 0 && verificaIgual(listaFechada, personX, personY - 1) == 0){
        auxiliar.custoF = calculaHeuristica(personX, personY - 1) + matriz[personX][personY];
        auxiliar.posicaoX = personX;
        auxiliar.posicaoY = personY - 1;
        insere_lista_ordenada(listaAberta, auxiliar);
    }
}

void imprimeCenario(int matriz[20][35], int i, int j, int auxMapa){
    matriz[personX][personY] = '@';
    for(i = 0; i < 20; i++){
        printf("\n");
        //Necessário verifica qual valor possui na matriz pois no intervalo [0,100]
        //existem diversos valores não utilizados
        for(j = 0; j < 35; j++){
            if(matriz[i][j] == 'X')    //Caso seja uma bloco de parede
                printf("%c", matriz[i][j]);
            else if (matriz[i][j] == 10)   //Terreno ROCHOSO, custo 10
                printf("%c", 'R');
            else if (matriz[i][j] == 4)    //Terreno ARENOSO, custo 4
                printf("%c", 'A');
            else if (matriz[i][j] == 20)
                printf("%c", 'P');      //Terreno PLANALTO, custo 20
            else if (matriz[i][j] == '@'){ //Personagem
                if(i == 0 || i == 19 || j == 0 || j == 34){
                    printf("%c", matriz[i][j]);
                }else{
                    printf("%c", '@');
                    matriz[i][j] = auxMapa;    //Apaga a posição anterior que o personagem já passou
                }
            }else if(matriz[i][j] == 'Z'){ //Objetivo
                printf("%c", matriz[i][j]);
            }else{
                printf(" ");
                //Na primeira impressão da matriz, padroniza todos os pontos
                //que não tem terreno, objetivo ou personagem como custo 1
                matriz[i][j] = 1;
            }
        }
    }
}

void inicializaCenario(int matriz[20][35], int i, int j){
    for(i = 0; i < 20; i++){
        for(j = 0; j < 35; j++){
            if(i == 0 || i == 19 || j == 0 || j == 34){
                matriz[i][j] = 88;
            }else{
                if((i + j) <= 55 && i != 10 && j != 10)
                    matriz[i][j] = rand()%100;
                if(matriz[i][j] == '@')
                    matriz[i][j] = rand()%100;
                if(matriz[i][j] == 'Z')
                    matriz[i][j] = rand()%100;
            }
        }
    }
    while(matriz[personX][personY] == 'X'){
        personX = rand()%20;
        personY = rand()%35;
    }

    while(matriz[objX][objY] == 'X'){
        objX = rand()%20;
        objY = rand()%35;
    }
}

int main(){
    Lista* listaAberta = cria_lista();
    Lista* listaFechada = cria_lista();
    srand(time(NULL));

    int mat[20][35], i = 0, j = 0;
    personX = rand()%20;
    personY = rand()%35;
    objX = rand()%20;
    objY = rand()%35;

    //Adiciona o ponto inicial a lista aberta

    auxiliar.posicaoX = personX;
    auxiliar.posicaoY = personY;
    auxiliar.custoF = calculaHeuristica(personX, personY);
    insere_lista_ordenada(listaAberta, auxiliar);

    inicializaCenario(mat, i, j);

    mat[objX][objY] = 'Z';

    int aux = 0, auxMapa = 1, fim = 0;

    while(!fim && !lista_vazia(listaAberta)){
        system("cls");
        imprimeCenario(mat,i,j,auxMapa);
        Sleep(800);

        //Como o while funciona enquanto a listaAberta não estiver vazia
        //é necessário inserir um ponto antes de iniciar o while
        //o ponto escolhido foi a posição inicial do personagem
        //logo, é necessário retira-ló da lista aberta antes de começar
        //pois antes não precisa ser verificado

        if(aux == 0){
            menorCusto = consulta_lista(listaAberta);
            remove_lista_inicio(listaAberta);
            insere_lista_ordenada(listaFechada, menorCusto);
            aux = 1;
        }
        //Adiciona todos os possíveis estados a partir do ponto atual

        adicionaAlcancaveis(mat, listaAberta, listaFechada);

        //Seleciona o passo de menor custo

        menorCusto = consulta_lista(listaAberta);

        //Retira da lista aberta o passo de menor custo

        remove_lista_inicio(listaAberta);

        //Itens verificados são adicionados a lista fechada,
        //com o objetivo de que não sejam verificados duas vezes

        insere_lista_ordenada(listaFechada, menorCusto);

        //Atualiza a posição do personagem com o novo passo

        personX = menorCusto.posicaoX;
        personY = menorCusto.posicaoY;
        auxMapa = mat[personX][personY];

        //adicionaAlcancaveis(mat, listaAberta, listaFechada);

        //Verifica se o objetivo foi atingido

        if(personX == objX)
            if(personY == objY){
                fim = 1; //Finaliza a busca por novos estados
                system("cls");
                imprimeCenario(mat,i,j,auxMapa);
            }
    }
    printf("\n Objetivo encontrado\n");
    printf("    Pressione qualquer tecla para sair\n" );
    printf("Branch Master \n");
    libera_lista(listaAberta);
    libera_lista(listaFechada);
    getche();
    return 0;
}
