/******************************************************************************

LISTA SEM CABEÇA
Implemente, em linguagem C, funções recursivas para imprimir uma lista ligada,
sem e com cabeça.

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
    novoNode->item = novoItem; // Atribui o valor ao item do nÃ³ criado
    novoNode->next = *lista; // Aponta para o antigo primeiro nÃ³
    *lista = novoNode; // Atualiza o ponteiro da lista para o novo nÃ³
}

struct node *buscar(struct node *lista, int chave) {
    struct node *p = lista; // Ponteiro auxiliar para percorrer a lista

    // Percorre a lista enquanto nÃ£o chegar ao final e nÃ£o encontrar o elemento
    while (p != NULL && p->item != chave)
        p = p->next; // AvanÃ§a para o prÃ³ximo nÃ³

    return p; // Retorna o ponteiro para o nÃ³ encontrado ou NULL se nÃ£o achou
}

struct node *remover(struct node *lista, int chave) {
    struct node *p = lista; // Ponteiro p inicia no primeiro nÃ³ da lista
    struct node *q = NULL;  // Ponteiro q para rastrear o nÃ³ anterior de p

    // Percorre a lista procurando o nÃ³ com o valor chave
    while (p != NULL && p->item != chave) {
        q = p;      // Armazena o nÃ³ atual p em q (nÃ³ anterior ao nÃ³ p)
        p = p->next; // AvanÃ§a para o prÃ³ximo nÃ³
    }

    // Se o elemento nÃ£o foi encontrado, a lista permanece inalterada
    if (p == NULL)
        return lista; // Retorna a lista original, sem remoÃ§Ã£o

    // Se o nÃ³ a ser removido for o primeiro da lista
    if (q == NULL)
        lista = p->next; // O prÃ³ximo nÃ³ de p torna-se o novo inÃ­cio da lista
    else
        q->next = p->next; // Ajusta o ponteiro next do nÃ³ q para p->next

    free(p); // Libera a memÃ³ria do nÃ³ removido
    return lista;
}

void imprimir(struct node *lista) {
    struct node *p = lista; // Ponteiro auxiliar para percorrer a lista
    printf("Lista: ");
    while (p != NULL) { // Itera sobre todos os nÃ³s da lista
        if (p->next != NULL)
            printf("%d -> ", p->item); // Exibe o item seguido de "->"
        else
            printf("%d", p->item); // Exibe o Ãºltimo item sem "->"
        p = p->next; // AvanÃ§a para o prÃ³ximo nÃ³
    }
}

void imprimirRecursivo(struct node *lista) {
    struct node *p = lista; // Ponteiro auxiliar para percorrer a lista
    
    if (p==NULL) return;
    
        if (p->next != NULL)
            printf("%d -> ", p->item); // Exibe o item seguido de "->"
        else
            printf("%d", p->item); // Exibe o Ãºltimo item sem "->"
        imprimirRecursivo(p->next); // AvanÃ§a para o prÃ³ximo nÃ³
}

int main(void) {
    int i, n;
    struct node *Lista = NULL; // Inicializar a lista vazia
    int chave; // VariÃ¡vel para armazenar o valor a ser removido
    
    printf("Quantidade de nÃ³s da lista: ");
    scanf("%d", &n);
    printf("\n");
    
    // Inserir n elementos (pseudo)aleatÃ³rios na lista
    srand((unsigned)time(NULL));

    for (i = 0; i < n; i++) 
        inserir(&Lista, 1 + (rand()%100));
    
    // Exibir os elementos da lista antes da remoÃ§Ã£o
    printf("Lista antes da remoÃ§Ã£o:\n");
    imprimirRecursivo(Lista);
    
    // Solicitar ao usuÃ¡rio um valor para remover na lista
    printf("\n\nDigite o valor do elemento que deseja remover: ");
    scanf("%d", &chave);
    
    Lista = remover(Lista, chave);
    
    // Exibir os elementos da lista depois da remoÃ§Ã£o
    printf("\nLista depois da remoÃ§Ã£o:\n");
    imprimirRecursivo(Lista);
       
    return 0;
}