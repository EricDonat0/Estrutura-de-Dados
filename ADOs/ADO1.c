/******************************************************************************

Implemente, em linguagem C, um programa que utilize ponteiro de ponteiro para manipular um vetor de palavras (strings).
Seu programa deve: (a) Pedir ao usuário que informe a
quantidade de palavras que deseja inserir; (b) Alocar dinamicamente um vetor de ponteiros para
char, para armazenar as palavras, com no máximo 100 caracteres cada; (c) Solicitar ao usuário que
insira as palavras, alocando dinamicamente memória para cada uma delas; (d) Codicar uma função
chamada converterParaMaiusculo, que recebe um ponteiro de ponteiro e a quantidade de palavras,
convertendo todas para maiúsculas (CAIXA ALTA); (e) Exibir as palavras informadas pelo usuário
antes e depois da conversão; (f ) Liberar (desalocar) toda a memória alocada dinamicamente ao nal
do programa.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_CHAR 100 // Define o tamanho máximo de cada palavra

// Função que converte todas as palavras para maiúsculas
void converterParaMaiusculo(char **palavras, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        for (int j = 0; palavras[i][j] != '\0'; j++) {
            palavras[i][j] = toupper(palavras[i][j]);
        }
    }
}

int main() {
    int quantidade;
    printf("Digite a quantidade de palavras: ");
    scanf("%d", &quantidade);
    getchar(); // Limpa o buffer do teclado após o scanf

    // Aloca memória para o vetor de ponteiros que armazenará as palavras
    char **palavras = (char **)malloc(quantidade * sizeof(char *));
    if (palavras == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Leitura das palavras fornecidas pelo usuário
    for (int i = 0; i < quantidade; i++) {
        // Aloca memória para cada palavra
        palavras[i] = (char *)malloc(MAX_CHAR * sizeof(char));
        if (palavras[i] == NULL) {
            printf("Erro ao alocar memória para a palavra %d.\n", i + 1);
            return 1;
        }
        printf("Digite a palavra %d: ", i + 1);
        fgets(palavras[i], MAX_CHAR, stdin);
        palavras[i][strcspn(palavras[i], "\n")] = 0; // Remove a quebra de linha
    }

    // Exibe as palavras antes da conversão para maiúsculas
    printf("\nPalavras antes da conversão:\n");
    for (int i = 0; i < quantidade; i++) {
        printf("%s\n", palavras[i]);
    }

    // Chama a função para converter as palavras para maiúsculas
    converterParaMaiusculo(palavras, quantidade);

    // Exibe as palavras após a conversão para maiúsculas
    printf("\nPalavras depois da conversão:\n");
    for (int i = 0; i < quantidade; i++) {
        printf("%s\n", palavras[i]);
    }

    // Libera a memória alocada dinamicamente
    for (int i = 0; i < quantidade; i++) {
        free(palavras[i]); // Libera cada palavra individualmente
    }
    free(palavras); // Libera o vetor de ponteiros

    return 0;
}