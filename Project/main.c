#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

int objY = 10, objX = 10;

double calculaHeuristica(int cordX, int cordY){
    double aux1, aux2, result;
    aux1 = pow((cordX - objX), 2);
    aux2 = pow((cordY - objY), 2);
    result = pow(aux1 + aux2, 0.5);
    return result;
}

int main(){
    srand(time(NULL));
    int mat[20][35], i, j;

    for(i = 0; i < 20; i++){
        for(j = 0; j < 35; j++){
            if(i == 0 || i == 19 || j == 0 || j == 34){
                mat[i][j] = 88;
            }else{
                if((i + j) <= 20 && i != 10 && j != 10)
                    mat[i][j] = rand()%100;
                    if(mat[i][j] == 64)
                        mat[i][j] = rand()%100;
                    if(mat[i][j] == 90)
                        mat[i][j] = rand()%100;
            }
        }
    }

    mat[objX][objY] = 90;

    while(i!=9){
        mat[rand()%20][rand()%35] = 64;
        for(i = 0; i < 20; i++){
            printf("\n");
            for(j = 0; j < 35; j++){
                if(mat[i][j] == 88)
                    printf("%c", mat[i][j]);
                else if (mat[i][j] == 10)
                    printf("%c", 82);
                else if (mat[i][j] == 4)
                    printf("%c", 65);
                else if (mat[i][j] == 20)
                    printf("%c", 80);
                else if (mat[i][j] == 64){
                    if(i == 0 || i == 19 || j == 0 || j == 34){
                        mat[i][j] = 88;
                        printf("%c", mat[i][j]);
                    }else{
                        if(mat[i][j] != 1){
                            printf("%c", 64);
                            mat[i][j] = 33;
                        }
                    }
                }else if(mat[i][j] == 90){
                    printf("%c", mat[i][j]);
                }else
                    printf(" ");
            }
        }
        Sleep(1500);
        system("cls");
    }
    return 0;
}
