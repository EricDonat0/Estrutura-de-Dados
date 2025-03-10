/******************************************************************************

4. (1.0 ponto) Implemente, em linguagem C, um algoritmo recursivo para encontrar o valor máximo em
um vetor de inteiros, dividindo o vetor em dois subvetores de tamanho aproximadamente n/2 cada.


*******************************************************************************/
#include <stdio.h>

// Função auxiliar para retornar o maior entre dois números
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Função recursiva para encontrar o valor máximo em um vetor
int findMax(int arr[], int left, int right) {
    // Caso base: se houver apenas um elemento, ele é o máximo
    if (left == right) {
        return arr[left];
    }
    
    // Calcula o ponto médio do vetor
    int mid = (left + right) / 2;
    
    // Divide o vetor em duas partes e encontra o máximo em cada parte
    int maxLeft = findMax(arr, left, mid);
    int maxRight = findMax(arr, mid + 1, right);
    
    // Retorna o maior valor entre os dois subvetores
    return max(maxLeft, maxRight);
}

int main() {
    // Define um vetor de exemplo
    int arr[] = {1, 9, 3, 7, 5, 11, 2, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    // Chama a função recursiva para encontrar o valor máximo
    int maxValue = findMax(arr, 0, n - 1);
    
    // Exibe o valor máximo encontrado
    printf("O valor máximo no vetor é: %d\n", maxValue);
    
    return 0;
}