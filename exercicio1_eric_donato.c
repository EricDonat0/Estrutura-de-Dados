#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x = 0, y = 0, z = 0;
    
    int ***matriz;
    
    printf("Digite dimensões X, Y e Z");
    printf("\nDimensão X\n");
    scanf("%d", &x);
    printf("\nDimensão Y\n");
    scanf("%d", &y);
    printf("\nDimensão Z\n");
    scanf("%d", &z);
    printf("====================================");
    
    matriz = (int ***) malloc(x * sizeof(int **));
    
    for (int i = 0; i < x; i++){
        matriz[i] = (int**) malloc(y * sizeof(int*));
    }
    
    for(int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            matriz[i][j] = (int*) malloc (z * sizeof(int));
        }
    }
    
    for(int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            for ( int k = 0; k < z; k++){
                printf("\nElemento matriz[%d]-[%d]-[%d] \n", i,j,k);
                scanf("%d", &matriz[i][j][k]);
            }
        }
    }
    
    printf("\n================================\n");
    for(int i = 0; i < x; i++){
        printf("\nCamada %d\n",i);
        for (int j = 0; j < y; j++){
            for ( int k = 0; k < z; k++){
              printf("%d ", matriz[i][j][k]);
            }
        printf("\n");
        }
    }
    
    for(int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            free(matriz[i][j]);
        }
    }
    
    for (int i = 0; i < x; i++){
        free(matriz[i]);
    }
    
    free(matriz);
    
    return 0;
}