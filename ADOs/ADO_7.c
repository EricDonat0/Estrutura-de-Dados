/******************************************************************************

2. (1.0 ponto) Implemente, em linguagem C, uma la, usando vetor/arranjo circular, que utilize uma
função furaFila que insere um elemento na primeira posição da la. A única restrição é que este
procedimento deve ser O(1), ou seja, não pode movimentar os outros elementos da la. Note que
neste caso, estaremos desrespeitando o conceito de FILA (o primeiro a entrar é o primeiro a sair).

*******************************************************************************/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

typedef struct node* link;

struct node { 
    int item; 
    link next;
};

typedef struct {
  link inicio;
  link final;
} FILA;

void inicializar(FILA *f) {
  f->inicio = NULL;
  f->final = NULL;
}

void enfileirar(FILA *f, int x) {
  link novoNode = (link) malloc(sizeof(struct node));
  novoNode->item = x;
  novoNode->next = NULL;
  if (f->inicio == NULL)
    f->inicio = novoNode;
  else
    f->final->next = novoNode;
  f->final = novoNode;
}

void desenfileirar(FILA *f, int *i) {
  if (f->inicio == NULL)
    printf("Fila Vazia!\n");
  else {
    *i = f->inicio->item;
    link tmp = f->inicio;
    f->inicio = f->inicio->next;
    if (f->inicio == NULL)
      f->final = NULL;
    free(tmp);
  }
}

void furaFila(FILA *f, int x) {
  link novoNode = (link) malloc(sizeof(struct node));
  novoNode->item = x;
  novoNode->next = f->inicio;
  f->inicio = novoNode;

  if (f->final == NULL)
    f->final = novoNode;
}

void imprimir(FILA f) {
  link p = f.inicio;
  printf("Fila: \" ");
  while (p != NULL) {
    printf("%d ", p->item);
    p = p->next;
  }
  printf("\"\n");
}

int main(void) {
  int i, n, c;
  FILA f;
  inicializar(&f);

  printf("Quantidade de elementos: ");
  scanf("%d", &n);
  printf("\n");

  srand((unsigned)time(NULL));
  for (i = 0; i < n; i++) 
      enfileirar(&f, 1 + (rand() % 100));
  
  imprimir(f);

  desenfileirar(&f, &c);
  printf("Elemento removido do início: %d\n", c);
  imprimir(f);

  // Testando o furaFila
  furaFila(&f, 999);
  printf("Após furar a fila com o valor 999:\n");
  imprimir(f);

  return 0;
}