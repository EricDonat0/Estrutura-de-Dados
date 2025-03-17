/******************************************************************************

Implemente uma lista simplesmente ligada/encadeada circular com
cabeça (head node ou dummy node), com as operações de inserção,
busca e remoção.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node *link;

struct node {
    int item;
    link next;
};

void inserir(link *lista, int novoItem) {
    link novoNode = (link)malloc(sizeof(struct node));
    novoNode->item = novoItem;

            novoNode->next = (*lista)->next;
            (*lista)->next = novoNode;
}

link buscar(link lista, int chave) {
    if (lista->next == lista) 
        return NULL;

    link p = lista->next;

    do {
        if (p->item == chave)
            return p;
        p = p->next;
    } while (p != lista);

    return NULL;
}

link remover(link lista, int chave) {
    link p = lista->next;
    link q = lista;
    
    if (lista->next == lista)
        return NULL;

    do {
        if (p->item == chave) break;
        q = p;
        p = p->next;
    } while (p != lista);

    if (p == lista && p->item != chave) 
        return lista;

        q->next = p->next;
    
    free(p);
    return lista;
}

void imprimir(link lista) {
    link p = lista->next;
    printf("Lista: ");
    
    if (p == lista) 
        return;
    
    do {
        if (p->next != lista)  
            printf("%d -> ", p->item);
        else
            printf("%d", p->item);
        p = p->next;
    } while (p != lista);
}

int main(void) {
    int i, n;
    link Lista = (link)malloc(sizeof(struct node)); // Cria a cabeÃ§a da lista
    Lista->next = Lista;
    int chave;
    
    printf("Quantidade de nÃ³s da lista: ");
    scanf("%d", &n);
    printf("\n");
    
    srand((unsigned)time(NULL));

    for (i = 0; i < n; i++) 
        inserir(&Lista, 1 + (rand()%100));
    
    imprimir(Lista);
    
    printf("\n\nDigite o valor do elemento que deseja buscar: ");
    scanf("%d", &chave);
    
    if (buscar(Lista, chave) != NULL)
       printf("\nO elemento %d foi encontrado na lista!", chave);
    else 
       printf("\nO elemento %d nÃ£o foi encontrado na lista!", chave);
    
    printf("\n\nDigite o valor do elemento que deseja remover: ");
    scanf("%d", &chave);
    
    Lista = remover(Lista, chave);
    
    printf("\nLista depois da remoÃ§Ã£o:\n");
    imprimir(Lista);
       
    return 0;
}