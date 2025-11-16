#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// ===============================
// STRUCT DO ITEM
// ===============================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ===============================
// CABEÇALHO BONITO IGUAL AO PRINT
// ===============================
void exibirMenu(int total) {
    printf("=====================================\n");
    printf("   MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
    printf("=====================================\n");
    printf("Itens na Mochila: %d/10\n\n", total);

    printf("1. Adicionar Item (Loot)\n");
    printf("2. Remover Item\n");
    printf("3. Listar Itens na Mochila\n");
    printf("4. Buscar Item por Nome\n");
    printf("0. Sair\n");
    printf("-------------------------------------\n");
    printf("Escolha uma opcao: ");
}

// ===============================
// INSERIR ITEM
// ===============================
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\nA mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\nDigite o nome do item: ");
    scanf(" %29[^\n]", novo.nome);

    printf("Digite o tipo (Arma, Municao, Cura...): ");
    scanf(" %19[^\n]", novo.tipo);

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[*total] = novo;
    (*total)++;

    printf("\nItem adicionado com sucesso!\n");
}

// ===============================
// REMOVER ITEM
// ===============================
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("\nA mochila está vazia, nada para remover.\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item a remover: ");
    scanf(" %29[^\n]", nome);

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            // deslocar itens
            for (int j = i; j < *total - 1; j++)
                mochila[j] = mochila[j + 1];

            (*total)--;
            printf("\nItem removido com sucesso!\n");
            return;
        }
    }

    printf("\nItem não encontrado!\n");
}

// ===============================
// LISTAR ITENS
// ===============================
void listarItens(Item mochila[], int total) {
    if (total == 0) {
        printf("\nA mochila está vazia.\n");
        return;
    }

    printf("\n==== ITENS NA MOCHILA ====\n");
    for (int i = 0; i < total; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("===========================\n");
}

// ===============================
// BUSCA SEQUENCIAL
// ===============================
void buscarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("\nA mochila está vazia.\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item para buscar: ");
    scanf(" %29[^\n]", nome);

    int comparacoes = 0;

    for (int i = 0; i < total; i++) {
        comparacoes++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("Comparações realizadas: %d\n", comparacoes);
            return;
        }
    }

    printf("\nItem não encontrado.\n");
    printf("Comparações realizadas: %d\n", comparacoes);
}

// ===============================
// PROGRAMA PRINCIPAL
// ===============================
int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        exibirMenu(total);
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirItem(mochila, &total); break;
            case 2: removerItem(mochila, &total); break;
            case 3: listarItens(mochila, total); break;
            case 4: buscarItem(mochila, total); break;
            case 0: printf("\nSaindo...\n"); break;
            default: printf("\nOpcao invalida!\n"); break;
        }

        printf("\n");
    } while (opcao != 0);

    return 0;
}
