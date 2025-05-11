/******************************************************************************

5. (1.0 ponto) Implemente, em linguagem C, uma função recursiva que remova um
determinado elementode uma árvore AVL,caso ele exista. A remoção pode ser
baseada no algoritmo de remoção em uma árvore binária de busca, com as devidas
adaptações para manter o balanceamento da árvore AVL após a exclusão

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct node* link;

struct node { 
    int chave; 
    link esq;
    link dir;
    int h;
};

int altura(link raiz) {
    return (raiz == NULL) ? -1 : raiz->h;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

link rotacaoDireita(link p) {
    link u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    p->h = max(altura(p->esq), altura(p->dir)) + 1;
    u->h = max(altura(u->esq), p->h) + 1;
    return u;
}

link rotacaoEsquerda(link p) {
    link z = p->dir;
    p->dir = z->esq;
    z->esq = p;
    p->h = max(altura(p->esq), altura(p->dir)) + 1;
    z->h = max(p->h, altura(z->dir)) + 1;
    return z;
}

link rotacaoEsquerdaDireita(link p) {
    p->esq = rotacaoEsquerda(p->esq);
    return rotacaoDireita(p);
}

link rotacaoDireitaEsquerda(link p) {
    p->dir = rotacaoDireita(p->dir);
    return rotacaoEsquerda(p);
}

link inserirAVL(link raiz, int valor) {
    if (raiz == NULL) {
        link novoNode = (link)malloc(sizeof(struct node));
        novoNode->chave = valor;
        novoNode->esq = NULL;
        novoNode->dir = NULL;
        novoNode->h = 0;
        return novoNode;
    } 
    if (valor < raiz->chave)
        raiz->esq = inserirAVL(raiz->esq, valor);
    else
        raiz->dir = inserirAVL(raiz->dir, valor);
    
    raiz->h = max(altura(raiz->esq), altura(raiz->dir)) + 1;
    
    int fb = altura(raiz->esq) - altura(raiz->dir);

    if (fb == 2) {
        if (valor < raiz->esq->chave)
            return rotacaoDireita(raiz);
        else
            return rotacaoEsquerdaDireita(raiz);
    }
    else if (fb == -2) {
        if (valor > raiz->dir->chave)
            return rotacaoEsquerda(raiz);
        else
            return rotacaoDireitaEsquerda(raiz);
    }

    return raiz;
}

link encontrarMinimo(link raiz) {
    while (raiz->esq != NULL)
        raiz = raiz->esq;
    return raiz;
}

link removerAVL(link raiz, int valor) {
    if (raiz == NULL)
        return NULL;

    if (valor < raiz->chave) {
        raiz->esq = removerAVL(raiz->esq, valor);
    } else if (valor > raiz->chave) {
        raiz->dir = removerAVL(raiz->dir, valor);
    } else {
        if (raiz->esq == NULL || raiz->dir == NULL) {
            link temp = raiz->esq ? raiz->esq : raiz->dir;
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }
            free(temp);
        } else {
            link temp = encontrarMinimo(raiz->dir);
            raiz->chave = temp->chave;
            raiz->dir = removerAVL(raiz->dir, temp->chave);
        }
    }

    if (raiz == NULL)
        return NULL;

    raiz->h = max(altura(raiz->esq), altura(raiz->dir)) + 1;

    int fb = altura(raiz->esq) - altura(raiz->dir);

    if (fb == 2) {
        int fbesq = altura(raiz->esq->esq) - altura(raiz->esq->dir);
        if (fbesq >= 0)
            return rotacaoDireita(raiz);
        else
            return rotacaoEsquerdaDireita(raiz);
    }
    if (fb == -2) {
        int fbdir = altura(raiz->dir->esq) - altura(raiz->dir->dir);
        if (fbdir <= 0)
            return rotacaoEsquerda(raiz);
        else
            return rotacaoDireitaEsquerda(raiz);
    }

    return raiz;
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

int main(void) {
    link Arvore = NULL;

    Arvore = inserirAVL(Arvore, 1);
    Arvore = inserirAVL(Arvore, 2);
    Arvore = inserirAVL(Arvore, 3);
    Arvore = inserirAVL(Arvore, 4);
    Arvore = inserirAVL(Arvore, 5);
    Arvore = inserirAVL(Arvore, 6);
    Arvore = inserirAVL(Arvore, 7);

    printf("Árvore antes da remoção:\n");
    imprimirInOrdem(Arvore, 0);

    printf("\nRemovendo o elemento 4:\n");
    Arvore = removerAVL(Arvore, 4);

    printf("\nÁrvore após a remoção:\n");
    imprimirInOrdem(Arvore, 0);

    return 0;
}