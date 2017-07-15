#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
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

    if(personX - 1 >= 0 && matriz[personX - 1][personY] != 'X' && verificaIgual(listaAberta, personX - 1, personY) == 0 && verificaIgual(listaFechada, personX - 1, personY) == 0){
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

    if(personY - 1 >= 0 && matriz[personX][personY - 1] != 'X'  && verificaIgual(listaAberta, personX, personY - 1) == 0 && verificaIgual(listaFechada, personX, personY - 1) == 0){
        auxiliar.custoF = calculaHeuristica(personX, personY - 1) + matriz[personX][personY];
        auxiliar.posicaoX = personX;
        auxiliar.posicaoY = personY - 1;
        insere_lista_ordenada(listaAberta, auxiliar);
    }
}

int main(){
    Lista* listaAberta = cria_lista();
    Lista* listaFechada = cria_lista();
    srand(time(NULL));

    int mat[20][35], i, j;
    personX = rand()%20;
    personY = rand()%35;
    objX = rand()%20;
    objY = rand()%35;
    //Adiciona o ponto inicial a lista aberta
    auxiliar.posicaoX = personX;
    auxiliar.posicaoY = personY;
    auxiliar.custoF = calculaHeuristica(personX, personY);
    insere_lista_ordenada(listaAberta, auxiliar);

    for(i = 0; i < 20; i++){
        for(j = 0; j < 35; j++){
            if(i == 0 || i == 19 || j == 0 || j == 34){
                mat[i][j] = 88;
            }else{
                if((i + j) <= 55 && i != 10 && j != 10)
                    mat[i][j] = rand()%100;
                if(mat[i][j] == 64)
                    mat[i][j] = rand()%100;
                if(mat[i][j] == 90)
                    mat[i][j] = rand()%100;
            }
        }
    }


    /*for(i = 0; i < 20; i++){
        for(j = 0; j < 35; j++){
            mat[i][j] = 88;
        }
    }
    mat[17][32] = 1;
    mat[16][32] = 1;
    mat[15][32] = 1;
    mat[14][32] = 1;
    mat[18][32] = 1;
    mat[18][31] = 1;
    mat[18][30] = 1;
    mat[18][29] = 1;
    mat[18][28] = 1;
    */

    mat[objX][objY] = 'Z';
    int aux = 0;

    while((personX != objX && personY != objY) && !lista_vazia(listaAberta)){
        system("cls");
        mat[personX][personY] = '@';
        for(i = 0; i < 20; i++){
            printf("\n");
            for(j = 0; j < 35; j++){
                if(mat[i][j] == 'X')
                    printf("%c", mat[i][j]);
                else if (mat[i][j] == 10)
                    printf("%c", 'R');
                else if (mat[i][j] == 4)
                    printf("%c", 'A');
                else if (mat[i][j] == 20)
                    printf("%c", 'P');
                else if (mat[i][j] == 64){
                    if(i == 0 || i == 19 || j == 0 || j == 34){
                        mat[i][j] = 'X';
                        printf("%c", mat[i][j]);
                    }else{
                        if(mat[i][j] != 1){
                            printf("%c", 64);
                            mat[i][j] = 33;
                        }
                    }
                }else if(mat[i][j] == 'Z'){
                    printf("%c", mat[i][j]);
                }else{
                    printf(" ");
                    mat[i][j] = 1;
                }
            }
        }
        printf("\n");
        Sleep(500);
        if(aux == 0){
            menorCusto = consulta_lista(listaAberta);
            remove_lista_inicio(listaAberta);
            insere_lista_ordenada(listaFechada, menorCusto);
            aux = 1;
        }
        adicionaAlcancaveis(mat, listaAberta, listaFechada);
        menorCusto = consulta_lista(listaAberta);
        remove_lista_inicio(listaAberta);
        insere_lista_ordenada(listaFechada, menorCusto);
        personX = menorCusto.posicaoX;
        personY = menorCusto.posicaoY;
        adicionaAlcancaveis(mat, listaAberta, listaFechada);
    }
    printf("Tamanho %d \n", tamanho_lista(listaAberta));
    printf("Posicao personagem %d x %d \n", personX, personY);
    printf("Posicao objetivo %d x %d \n", objX, objY);
    libera_lista(listaAberta);
    libera_lista(listaFechada);
    return 0;
}
