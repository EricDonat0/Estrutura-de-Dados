/******************************************************************************

3. (1.0 ponto) Implemente, em linguagem C, uma função que encontre o nó com o conteúdo de valor
mínimo em uma lista simplesmente encadeada/ligada sem cabeça de valores inteiros. Faça duas
versões: uma iterativa e uma recursiva.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
    int item;
    struct node *next;
};

void inserir(struct node **lista, int novoItem) {
    struct node *novoNode = (struct node *)malloc(sizeof(struct node));
    novoNode->item = novoItem;
    novoNode->next = *lista;
    *lista = novoNode;
}

struct node *buscar(struct node *lista, int chave) {
    struct node *p = lista;
    while (p != NULL && p->item != chave)
        p = p->next;
    return p;
}

struct node *remover(struct node *lista, int chave) {
    struct node *p = lista;
    struct node *q = NULL;
    while (p != NULL && p->item != chave) {
        q = p;
        p = p->next;
    }
    if (p == NULL)
        return lista;
    if (q == NULL)
        lista = p->next;
    else
        q->next = p->next;
    free(p);
    return lista;
}

void imprimir(struct node *lista) {
    struct node *p = lista;
    printf("Lista: ");
    while (p != NULL) {
        if (p->next != NULL)
            printf("%d -> ", p->item);
        else
            printf("%d", p->item);
        p = p->next;
    }
    printf("\n");
}

// Função iterativa para encontrar o menor valor na lista
struct node* findMinIterative(struct node* head) {
    if (head == NULL) return NULL;
    struct node* minNode = head;
    struct node* current = head->next;
    while (current != NULL) {
        if (current->item < minNode->item) {
            minNode = current;
        }
        current = current->next;
    }
    return minNode;
}

// Função recursiva para encontrar o menor valor na lista
struct node* findMinRecursive(struct node* head) {
    if (head == NULL || head->next == NULL) return head;
    struct node* minNode = findMinRecursive(head->next);
    return (head->item < minNode->item) ? head : minNode;
}

int main(void) {
    int i, n;
    struct node *Lista = NULL;
    int chave;
    
    printf("Quantidade de nós da lista: ");
    scanf("%d", &n);
    printf("\n");
    
    srand((unsigned)time(NULL));
    for (i = 0; i < n; i++) 
        inserir(&Lista, 1 + (rand() % 100));
    
    printf("Lista antes da remoção:\n");
    imprimir(Lista);
    
    printf("\nDigite o valor do elemento que deseja remover: ");
    scanf("%d", &chave);
    Lista = remover(Lista, chave);
    
    printf("\nLista depois da remoção:\n");
    imprimir(Lista);
    
    // Encontrando o menor valor na lista
    struct node *minNodeIterative = findMinIterative(Lista);
    struct node *minNodeRecursive = findMinRecursive(Lista);
    
    if (minNodeIterative)
        printf("\nMenor valor (Iterativo): %d\n", minNodeIterative->item);
    if (minNodeRecursive)
        printf("Menor valor (Recursivo): %d\n", minNodeRecursive->item);
    
    return 0;
}
