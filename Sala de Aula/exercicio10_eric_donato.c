/******************************************************************************

1. (1.0 ponto) Implemente, em linguagem C, uma função iterativa (não recursiva) que recebe um vetor
de inteiros e verifica se ele é a representação de um heap de máximo.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

int pai(int i) {
    return i/2;
}

int esq(int i) {
    return 2*i;
}

int dir(int i) {
    return 2*i+1;
}

void subir(int *heap, int i) {
    int aux;
    int p = pai(i);
    if (p >= 1 && heap[i] > heap[p]) {
        aux = heap[i];
        heap[i] = heap[p];
        heap[p] = aux;
        subir(heap, p);
    }
}

void inserir(int *heap, int *n, int novoItem) {
    *n = *n + 1;
    heap[*n] = novoItem;
    subir(heap, *n);
}

void descer(int *heap, int n, int i) {
    int aux;
    int e = esq(i);
    int d = dir(i);
    int maior = i;
    if (e <= n && heap[e] > heap[maior]) maior = e;
    if (d <= n && heap[d] > heap[maior]) maior = d;
    if (maior != i) {
        aux = heap[i];
        heap[i] = heap[maior];
        heap[maior] = aux;
        descer(heap, n, maior);
    }
}

int removerMaximo(int *heap, int *n) {
    int maximo = heap[1]; // A raiz é sempre o maior elemento no max-heap
    heap[1] = heap[*n];
    *n = *n - 1;
    descer(heap, *n, 1);
    return maximo;
}

void imprimirHeap(int *heap, int n, int i, int b) {
    int j;
    if (i > n) {
        for (j = 0; j < b; j++) printf("-----");
        printf("NULL\n");
        return;
    }
    imprimirHeap(heap, n, dir(i), b + 1);
    for (j = 0; j < b; j++) printf("-----");
    printf("%i\n", heap[i]);
    imprimirHeap(heap, n, esq(i), b + 1);
}

void construirHeapDescendo(int *heap, int n) {
    for (int i = n / 2; i >= 1; i--)
        descer(heap, n, i);
}

void heapSort(int *heap, int n) {
    int aux;
    construirHeapDescendo(heap, n); // Garante estrutura de heap antes de ordenar
    for (int i = n; i > 1; i--) {
        aux = heap[i];
        heap[i] = heap[1];
        heap[1] = aux;
        descer(heap, --n, 1);
    }
}

// Verifica se o vetor representa um heap de máximo
int verificarHeapMaximo(int *heap, int n) {
    for (int i = 1; i <= n / 2; i++) {
        int e = esq(i);
        int d = dir(i);
        if (e <= n && heap[e] > heap[i]) return 0;
        if (d <= n && heap[d] > heap[i]) return 0;
    }
    return 1;
}

int main(void) {
    int heap[MAX];
    int n = 0, i, m;

    // Insere manualmente os elementos no heap
    inserir(heap, &n, 17);
    inserir(heap, &n, 15);
    inserir(heap, &n, 12);
    inserir(heap, &n, 9);
    inserir(heap, &n, 10);
    inserir(heap, &n, 4);
    inserir(heap, &n, 1);
    inserir(heap, &n, 7);
    inserir(heap, &n, 3);
    inserir(heap, &n, 6);

    printf("Heap (vetor):\n");
    for (i = 1; i <= n; i++) printf("heap[%d] = %d\n", i, heap[i]);

    printf("\nHeap (formato de árvore):\n");
    imprimirHeap(heap, n, 1, 0);

    // Verifica se é um heap de máximo
    if (verificarHeapMaximo(heap, n)) {
        printf("\nO vetor representa um heap de máximo.\n");
    } else {
        printf("\nO vetor NÃO representa um heap de máximo.\n");
    }

    // Remove o maior valor da raiz
    printf("\nExtração do maior elemento do heap: %d\n\n", removerMaximo(heap, &n));

    printf("Heap após remoção:\n");
    for (i = 1; i <= n; i++) printf("heap[%d] = %d\n", i, heap[i]);
    printf("\n");
    imprimirHeap(heap, n, 1, 0);

    // Heap Sort
    printf("\nQuantidade de elementos para ordenar: ");
    scanf("%d", &m);

    int vetor[m + 1];
    srand((unsigned)time(NULL));
    for (i = 1; i <= m; i++)
        vetor[i] = 1 + (rand() % 100);

    printf("\nAntes de ordenar:\n");
    for (i = 1; i <= m; i++) printf("vetor[%d] = %d\n", i, vetor[i]);

    heapSort(vetor, m);

    printf("\nDepois de ordenar com Heap Sort:\n");
    for (i = 1; i <= m; i++) printf("vetor[%d] = %d\n", i, vetor[i]);

    return 0;
}
