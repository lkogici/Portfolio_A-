#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(){
    srand(time(NULL));
    int mat[20][35], i, j;

    for(i = 0; i < 20; i++){
        for(j = 0; j < 35; j++){
            if(i == 0 || i == 19 || j == 0 || j == 34){
                mat[i][j] = 88;
            }else{
                if((i + j) <= 27)
                    mat[i][j] = rand()%15;
            }
        }
    }
    while(i!=9){
        mat[rand()%20][rand()%35] = 64;
        for(i = 0; i < 20; i++){
            printf("\n");
            for(j = 0; j < 35; j++){
                if(mat[i][j] == 88)
                    printf("%c", mat[i][j]);
                else if (mat[i][j] == 1)
                    printf("%c", 35);
                else if (mat[i][j] == 2)
                    printf("%c", 36);
                else if (mat[i][j] == 64){
                    printf("%c", 64);
                    if(i == 0 || i == 19 || j == 0 || j == 34){
                        mat[i][j] = 88;
                    }else{
                        mat[i][j] = rand()%15;
                    }
                }

                else if (mat[i][j] == 3 || mat[i][j] == 5)
                    printf("X");
                else
                    printf(" ");
            }
        }
        Sleep(1500);
        system("cls");
    }
    return 0;
}
