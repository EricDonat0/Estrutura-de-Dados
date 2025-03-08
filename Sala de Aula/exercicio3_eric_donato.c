/******************************************************************************

O código-fonte a seguir implementa, em linguagem C, uma versão recursiva do
algoritmo Bubble Sort.
Escreva a recorrência do algoritmo apresentado e determine sua
soluçãoo assintótica. Ou seja, encontre a complexidade de tempo do
Bubble Sort recursivo.

*******************************************************************************/
#include <stdio.h>

void bubbleSortRecursivo (int *v, int n){
    int i, aux;
    if (n == 1) return;
    
    for (i = 0; i <= n - 2; i++){ // O(n)
        if (v[i] > v[i + 1]){
            aux = v[i];
            v[i] = v[i+1];
            v[i + 1] = aux;
        }
        bubbleSortRecursivo (v, n -1); // O(n)
    }
}

// complexidade: O(n²)
// T(n) = T(n - 1) + n
// T(n - 1) = T(n - 2) + (n - 1)
// T(n - 2) = T(n - 3) + (n - 2)
// ...
// T(2) = T(1) + 2
// ∑ = (n (n + 1)) / 2
// = O(n²)