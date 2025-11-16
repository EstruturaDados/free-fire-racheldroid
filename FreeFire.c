#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.
#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\nMochila cheia! Maximo de 10 itens.\n");
        return;
    }

    printf("\n--- Adicionar Item ---\n");

    printf("Nome do item: ");
    scanf("%29s", mochila[*total].nome);

    printf("Tipo (arma, municao, cura, ferramenta): ");
    scanf("%19s", mochila[*total].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);

    (*total)++;

    printf("\nItem adicionado com sucesso!\n");
}


// ================================
// Função para remover item por nome
// ================================
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("\nNenhum item na mochila para remover.\n");
        return;
    }

    char nomeBusca[30];
    int encontrado = -1;

    printf("\n--- Remover Item ---\n");
    printf("Digite o nome do item: ");
    scanf("%29s", nomeBusca);

    // Busca sequencial
    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\nItem nao encontrado.\n");
        return;
    }

    // Remoção deslocando elementos
    for (int i = encontrado; i < *total - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*total)--;

    printf("\nItem removido com sucesso!\n");
}


// ================================
// Função de listagem dos itens
// ================================
void listarItens(Item mochila[], int total) {
    printf("\n=========== ITENS NA MOCHILA ===========\n");

    if (total == 0) {
        printf("Mochila vazia.\n");
        printf("=========================================\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("%d. %s  | Tipo: %s | Qtd: %d\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }

    printf("=========================================\n");
}


// ================================
// Função para buscar item por nome
// ================================
void buscarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("\nMochila vazia.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- Buscar Item ---\n");
    printf("Digite o nome do item: ");
    scanf("%29s", nomeBusca);

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }

    printf("\nItem nao encontrado.\n");
}


// ================================
// PROGRAMA PRINCIPAL
// ================================
int main() {

    Item mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao;

    do {
        printf("\n=========================================\n");
        printf("   MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("=========================================\n");
        printf("Itens na Mochila: %d/10\n\n", totalItens);

        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("4. Buscar Item\n");
        printf("0. Sair\n");
        printf("-----------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                break;
            case 2:
                removerItem(mochila, &totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                break;
            case 4:
                buscarItem(mochila, totalItens);
                break;
            case 0:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("\nOpcao invalida.\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
