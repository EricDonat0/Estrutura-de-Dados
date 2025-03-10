/******************************************************************************

LISTA COM CABEÇA
Implemente, em linguagem C, funções recursivas para imprimir uma lista ligada,
sem e com cabeça.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// DefiniÃ§Ã£o do tipo link como ponteiro para struct node
typedef struct node *link;

// DefiniÃ§Ã£o da estrutura node
struct node {
    int item;
    link next; // Ponteiro para o prÃ³ximo nÃ³
};

// FunÃ§Ã£o para inserir um item na lista com cabeÃ§a
void inserir(link *lista, int novoItem) {
    link novoNode = (link)malloc(sizeof(struct node));
    novoNode->item = novoItem; // Atribui o valor ao item do nÃ³ criado
    novoNode->next = (*lista)->next; // Aponta para o antigo primeiro nÃ³
    (*lista)->next = novoNode; // Atualiza o ponteiro da lista para o novo nÃ³
}

// FunÃ§Ã£o para buscar um item na lista com cabeÃ§a
link buscar(link lista, int chave) {
    link p = lista->next; // Ponteiro auxiliar comeÃ§a no primeiro nÃ³ real (depois da cabeÃ§a)

    // Percorre a lista enquanto nÃ£o chegar ao final e nÃ£o encontrar o elemento
    while (p != NULL && p->item != chave)
        p = p->next; // AvanÃ§a para o prÃ³ximo nÃ³

    return p; // Retorna o ponteiro para o nÃ³ encontrado ou NULL se nÃ£o achou
}

// FunÃ§Ã£o para remover um item na lista com cabeÃ§a
link remover(link lista, int chave) {
    link p = lista->next; // Ponteiro p inicia no primeiro nÃ³ real (depois da cabeÃ§a)
    link q = lista;  // Ponteiro q Ã© o nÃ³ anterior (cabeÃ§a) de p

    // Percorre a lista procurando o nÃ³ com o valor chave
    while (p != NULL && p->item != chave) {
        q = p;      // Armazena o nÃ³ atual p em q (nÃ³ anterior ao nÃ³ p)
        p = p->next; // AvanÃ§a para o prÃ³ximo nÃ³
    }

    // Se o elemento nÃ£o foi encontrado, a lista permanece inalterada
    if (p == NULL)
        return lista; // Retorna a lista original, sem remoÃ§Ã£o

    // Remove p da lista, ajustando o ponteiro do nÃ³ anterior
    q->next = p->next; 

    free(p); // Libera a memÃ³ria do nÃ³ removido
    return lista;
}

// FunÃ§Ã£o para imprimir a lista com cabeÃ§a
void imprimir(link lista) {
    link p = lista->next; // ComeÃ§a no primeiro nÃ³ real (depois da cabeÃ§a)
    printf("Lista: ");
    while (p != NULL) { // Itera sobre todos os nÃ³s da lista
        if (p->next != NULL)
            printf("%d -> ", p->item); // Exibe o item seguido de "->"
        else
            printf("%d", p->item); // Exibe o Ãºltimo item sem "->"
        p = p->next; // AvanÃ§a para o prÃ³ximo nÃ³
    }
}

void imprimirRecursivo(link lista) {
    struct node *p = lista->next; // Ponteiro auxiliar para percorrer a lista
    
    if (p==NULL) return;
    
        if (p->next != NULL)
            printf("%d -> ", p->item); // Exibe o item seguido de "->"
        else
            printf("%d", p->item); // Exibe o Ãºltimo item sem "->"
        imprimirRecursivo(p); // AvanÃ§a para o prÃ³ximo nÃ³
}

int main(void) {
    int i, n;
    link Lista = (link)malloc(sizeof(struct node)); // Cria a cabeÃ§a da lista
    Lista->next = NULL; // Inicializar a lista com cabeÃ§a vazia
    int chave; // VariÃ¡vel para armazenar o valor a ser buscado/removido
    
    printf("Quantidade de nÃ³s da lista: ");
    scanf("%d", &n);
    printf("\n");
    
    // Inserir n elementos (pseudo)aleatÃ³rios na lista
    srand((unsigned)time(NULL));

    for (i = 0; i < n; i++) 
        inserir(&Lista, 1 + (rand()%100));
    
    // Exibir os elementos da lista
    imprimirRecursivo(Lista);
    
    // Solicitar ao usuÃ¡rio um valor para buscar na lista
    printf("\n\nDigite o valor do elemento que deseja buscar: ");
    scanf("%d", &chave);
    
    // Buscar o elemento na lista ligada
    if (buscar(Lista, chave) != NULL)
       printf("\nO elemento %d foi encontrado na lista!", chave);
    else 
       printf("\nO elemento %d nÃ£o foi encontrado na lista!", chave);
    
    // Solicitar ao usuÃ¡rio um valor para remover na lista
    printf("\n\nDigite o valor do elemento que deseja remover: ");
    scanf("%d", &chave);
    
    Lista = remover(Lista, chave);
    
    // Exibir os elementos da lista depois da remoÃ§Ã£o
    printf("\nLista depois da remoÃ§Ã£o:\n");
    imprimirRecursivo(Lista);
       
    return 0;
}