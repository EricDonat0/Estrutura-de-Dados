/******************************************************************************

5. (1.0 ponto) Implemente, em linguagem C, uma função para o percurso por nível (ou em largura) em
uma árvore binária. (Dica: utilize uma la)

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

// Definição do tipo link como ponteiro para struct node
typedef struct node* link;

// Definição da estrutura node
struct node {
    int chave;
    link esq;
    link dir;
};

// Função para inserir um elemento na árvore binária de busca
link inserir(link raiz, int valor) {
    if (raiz == NULL) {
        link novoNode = (link)malloc(sizeof(struct node));
        novoNode->chave = valor;
        novoNode->esq = NULL;
        novoNode->dir = NULL;
        return novoNode;
    }
    if (valor < raiz->chave)
        raiz->esq = inserir(raiz->esq, valor);
    else
        raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

// Função para buscar uma chave na árvore binária de busca
link buscar(link raiz, int chave) {
    if (raiz == NULL || raiz->chave == chave)
        return raiz;
    if (chave < raiz->chave)
        return buscar(raiz->esq, chave);
    else
        return buscar(raiz->dir, chave);
}

// Função auxiliar para remoção: Caso 1 ou 2
link removerCaso1ou2(link raiz) {
    link q = raiz;
    if (raiz->esq == NULL) {
        q = raiz->dir;
        free(raiz);
        return q;
    } else if (raiz->dir == NULL) {
        q = raiz->esq;
        free(raiz);
        return q;
    }
    return raiz;
}

// Função auxiliar para remoção: Caso 3
link removerCaso3(link raiz) {
    link p = raiz;
    link q = raiz->dir;
    while (q->esq != NULL) {
        p = q;
        q = q->esq;
    }
    raiz->chave = q->chave;
    if (p->esq == q)
        p->esq = removerCaso1ou2(q);
    else
        p->dir = removerCaso1ou2(q);
    return raiz;
}

// Função para remover uma chave na árvore binária de busca
link remover(link raiz, int chave) {
    if (raiz == NULL) return NULL;
    if (chave == raiz->chave)
        if (raiz->esq == NULL || raiz->dir == NULL)
            raiz = removerCaso1ou2(raiz);
        else
            raiz = removerCaso3(raiz);
    else if (chave < raiz->chave)
        raiz->esq = remover(raiz->esq, chave);
    else
        raiz->dir = remover(raiz->dir, chave);
    return raiz;
}

// Funções de percurso
void percursoPreOrdem(link raiz) {
    if (raiz != NULL) {
        printf("%i ", raiz->chave);
        percursoPreOrdem(raiz->esq);
        percursoPreOrdem(raiz->dir);
    }
}

void percursoInOrdem(link raiz) {
    if (raiz != NULL) {
        percursoInOrdem(raiz->esq);
        printf("%i ", raiz->chave);
        percursoInOrdem(raiz->dir);
    }
}

void percursoPosOrdem(link raiz) {
    if (raiz != NULL) {
        percursoPosOrdem(raiz->esq);
        percursoPosOrdem(raiz->dir);
        printf("%i ", raiz->chave);
    }
}

// Visualização
void imprimirPreOrdem(link raiz) {
    printf("(");
    if (raiz != NULL) {
        printf("% i ", raiz->chave);
        imprimirPreOrdem(raiz->esq);
        imprimirPreOrdem(raiz->dir);
    }
    printf(")");
}

void imprimirInOrdem(link p, int b) {
    int i;
    if (p == NULL) {
        for (i = 0; i < b; i++) printf("-----");
        printf("NULL\n");
        return;
    }
    imprimirInOrdem(p->dir, b + 1);
    for (i = 0; i < b; i++) printf("-----");
    printf("%i\n", p->chave);
    imprimirInOrdem(p->esq, b + 1);
}


// Fila para percurso em nível
typedef struct fila {
    link *dados;
    int inicio, fim, tamanho;
} Fila;

Fila* criarFila(int capacidade) {
    Fila* f = malloc(sizeof(Fila));
    f->dados = malloc(sizeof(link) * capacidade);
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = capacidade;
    return f;
}

int filaVazia(Fila* f) {
    return f->inicio == f->fim;
}

void enfileirar(Fila* f, link no) {
    f->dados[f->fim++] = no;
}

link desenfileirar(Fila* f) {
    return f->dados[f->inicio++];
}

void liberarFila(Fila* f) {
    free(f->dados);
    free(f);
}

// Função de percurso por nível (em largura)
void percursoPorNivel(link raiz) {
    if (raiz == NULL) return;
    Fila* fila = criarFila(100); // capacidade fixa (pode ajustar se quiser)
    enfileirar(fila, raiz);
    while (!filaVazia(fila)) {
        link atual = desenfileirar(fila);
        printf("%d ", atual->chave);
        if (atual->esq != NULL)
            enfileirar(fila, atual->esq);
        if (atual->dir != NULL)
            enfileirar(fila, atual->dir);
    }
    liberarFila(fila);
}

int main(void) {
    link Arvore = NULL;
    int chave;

    Arvore = inserir(Arvore, 50);
    Arvore = inserir(Arvore, 40);
    Arvore = inserir(Arvore, 60);
    Arvore = inserir(Arvore, 35);
    Arvore = inserir(Arvore, 45);
    Arvore = inserir(Arvore, 55);
    Arvore = inserir(Arvore, 65);

    printf("Visualização unidimensional:\n");
    imprimirPreOrdem(Arvore);

    printf("\n\nVisualização bidimensional:\n");
    imprimirInOrdem(Arvore, 0);

    printf("\n\nPercurso Pré-Ordem:\n");
    percursoPreOrdem(Arvore);

    printf("\nPercurso In-Ordem:\n");
    percursoInOrdem(Arvore);

    printf("\nPercurso Pós-Ordem:\n");
    percursoPosOrdem(Arvore);

    printf("\nPercurso Por Nível:\n");
    percursoPorNivel(Arvore);

    printf("\n\nInforme o valor que deseja procurar: ");
    scanf("%d", &chave);
    if (buscar(Arvore, chave) != NULL)
        printf("O elemento %d foi encontrado na árvore.\n", chave);
    else
        printf("O elemento %d não foi encontrado na árvore.\n", chave);

    printf("\nInforme o valor que deseja remover: ");
    scanf("%d", &chave);
    Arvore = remover(Arvore, chave);

    printf("\nÁrvore após remoção:\n");
    imprimirInOrdem(Arvore, 0);

    return 0;
}