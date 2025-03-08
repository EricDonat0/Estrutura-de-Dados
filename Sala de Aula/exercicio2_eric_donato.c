/******************************************************************************

Implemente em linguiagem C, uma versão recursiva do Bubble Sort.
Não esqueça de testar seu código com vetores gerados de forma
(pseudo) aleatória.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort (int *v, int n){
    int i, j, aux;
    
    for (j = n-1; j>=1; j--){ //Iteração
        for (i = 0; i <= j - 1; i++){ //Iteração
            if (v[i] > v[i+1]){
                aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
            }
        }
    }
}


void bubbleSortRecursivo (int *v, int n){
     int aux;
     if (n == 1){
         return;
     }
     
     for (int i = 0; i <  n - 1; i++){ //Iteração
            if (v[i] > v[i+1]){
                aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
            }
     }
     bubbleSortRecursivo (v, n-1);
}

void main (){
    int tamanho; //Tamanho do vetor
    
    printf("Qual tamanho do seu vetor: "); //tamanho do vetor
    scanf("%d", &tamanho);
    
    int vetor[tamanho]; // Criando um vetor com tamanho N
    
    srand(time(NULL));
    
    printf("============== Vetor Sorteado ==============\n");
    
    for (int i = 0; i < tamanho; i++){ 
        vetor[i] = 1 + (rand() % 10);
        printf("v[%d] : %d\n", i, vetor[i]);
    }
    
    int *v = vetor;
    
    printf("============== Interativo ==============\n");
    bubbleSort(v, tamanho);
    
    for (int i = 0; i < tamanho; i++){ 
        printf("v[%d] : %d\n", i, vetor[i]);
    }
    
    
    printf("============== Vetor Sorteado ==============\n");
    
    for (int i = 0; i < tamanho; i++){ 
        vetor[i] = 1 + (rand() % 10);
        printf("v[%d] : %d\n", i, vetor[i]);
    }
    
    printf("============== Recursivo ==============\n");
    
    bubbleSortRecursivo(v, tamanho);
    
    for (int i = 0; i < tamanho; i++){ 
        printf("v[%d] : %d\n", i, vetor[i]);
    }
}