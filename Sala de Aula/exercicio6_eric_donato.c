/******************************************************************************

Digamos que nosso alfabeto contém apenas as letras a, b e c.
Considere o seguinte conjunto de palavras (strings):
c, aca, bcb, abcba, bacab, aacaa, bbcbb, … Qualquer string
desse conjunto tem a forma WcM, sendo W uma sequência de
letras que só contém a e b, e M é o inverso de W (ou seja, M é
W lido de trás para frente). Implemente, em linguagem C, um
programa que utiliza uma pilha dinâmica para decidir se uma
string x pertence ou não ao conjunto, ou seja, decidir se x é da
forma WcM.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição do tipo link como ponteiro para struct node
typedef struct node* link;

// Definição da estrutura node
struct node {
    char item;
    link next; // Ponteiro para o próximo nó
};

// Estrutura chamada PILHA para representar a pilha
typedef struct {
    link topo; // Ponteiro para o topo da pilha
} PILHA;

// Função para inicializar a pilha vazia
void inicializar(PILHA *p) {
    p->topo = NULL; // Indica que a pilha está vazia
}

// Função para empilhar (push) um elemento na pilha
void empilhar(PILHA *p, char x) {
    link novoNode = (link)malloc(sizeof(struct node)); // Aloca novo nó
    novoNode->item = x; // Armazena x no novo nó
    novoNode->next = p->topo; // O novo nó aponta para o topo da pilha
    p->topo = novoNode; // O topo da pilha aponta para o novo nó
}

// Função para desempilhar (pop) um elemento da pilha
void desempilhar(PILHA *p, char *t) {
    if (p->topo == NULL) // Verifica se a pilha está vazia
        printf("Pilha Vazia!\n");
    else { // A pilha tem pelo menos um elemento
        *t = p->topo->item; // Faz uma cópia do elemento no topo
        link tmp = p->topo; // Guarda o endereço do topo
        p->topo = p->topo->next; // Atualiza o topo para o próximo
        free(tmp);
    }
}

// Função para imprimir os elementos da pilha
void imprimir(PILHA p) {
    link q = p.topo;
    printf("Pilha:\n");
    while (q != NULL) { // Percorre a pilha do topo até a base
        printf(" %c\n", q->item); // Exibe os elementos na ordem de desempilhamento
        q = q->next;
    }
}

// Função para verificar se a string tem o formato WcM
int verificarString(const char *str) {
    PILHA p;
    inicializar(&p); // Inicializa a pilha
    int n = strlen(str);
    int i = 0;

    // Passo 1: Empilhar W (sequência de 'a' e 'b' antes de 'c')
    while (i < n && (str[i] == 'a' || str[i] == 'b')) {
        empilhar(&p, str[i]);
        i++;
    }

    // Passo 2: Verificar o caractere 'c' no meio
    if (i < n && str[i] == 'c') {
        i++;  // Avança para o próximo caractere após 'c'
    } else {
        return 0;  // Se não encontrar 'c', retorna falso
    }

    // Passo 3: Verificar se o restante da string é o inverso de W
    while (i < n) {
        char topoPilha;
        desempilhar(&p, &topoPilha);
        if (topoPilha != str[i]) {
            return 0;  // Se não corresponder ao inverso, retorna falso
        }
        i++;
    }

    // Se a pilha estiver vazia, a string pertence ao conjunto
    return p.topo == NULL;
}

int main(void) {
    char str[100];
    
    // Solicita ao usuário a string a ser verificada
    printf("Digite uma string: ");
    fgets(str, sizeof(str), stdin);
    
    // Remove o caractere de nova linha (\n) caso exista
    str[strcspn(str, "\n")] = 0;

    // Verifica se a string está no formato WcM
    if (verificarString(str)) {
        printf("A string pertence ao conjunto.\n");
    } else {
        printf("A string não pertence ao conjunto.\n");
    }

    return 0;
}