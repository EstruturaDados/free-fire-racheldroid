
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMP 20
#define MAX_NOME 30
#define MAX_TIPO 20

typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int prioridade;
} Componente;

/* ---------- Utilitários ---------- */

// remove '\n' de uma string lida com fgets
void strip_newline(char *s) {
    size_t len = strlen(s);
    if (len == 0) return;
    if (s[len-1] == '\n') s[len-1] = '\0';
}

// lê uma linha com fgets e remove newline; se exceder, limpa stdin
void ler_string(char *buffer, int tamanho) {
    if (fgets(buffer, tamanho, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    // se não tem '\n', limpamos o restante do buffer stdin
    if (strchr(buffer, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    strip_newline(buffer);
}

/* ---------- Exibição ---------- */

// Mostra o menu principal com layout estilo imagem
void mostrar_menu(int total) {
    printf("\n============================================\n");
    printf("        PLANO DE FUGA - CODIGO DA ILHA      \n");
    printf("============================================\n");
    printf("Itens na Mochila: %d/%d\n\n", total, MAX_COMP);
    printf("1. Adicionar Componente\n");
    printf("2. Descartar Componente\n");
    printf("3. Listar Componentes (Inventario)\n");
    printf("4. Organizar Mochila (Ordenar Componentes)\n");
    printf("5. Busca Binaria por Componente-Chave (por nome)\n");
    printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
    printf("--------------------------------------------\n");
    printf("Escolha uma opcao: ");
}

// Exibe o submenu de organizacao (opção 4) conforme solicitado
void mostrar_submenu_organizacao(void) {
    printf("\n--- Estrategia de Organizacao ---\n");
    printf("Como deseja ordenar os componentes:\n");
    printf("1. Por nome (ordem alfabetica)\n");
    printf("2. Por Tipo\n");
    printf("3. Por prioridade de montagem\n");
    printf("0. Cancelar\n");
    printf("Escolha o criterio: ");
}

// Mostra os componentes formatados
void mostrar_componentes(const Componente arr[], int n) {
    printf("\n=== Componentes (%d) ===\n", n);
    printf("%-3s %-28s %-16s %s\n", "No", "Nome", "Tipo", "Prioridade");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < n; ++i) {
        printf("%-3d %-28s %-16s %2d\n", i+1, arr[i].nome, arr[i].tipo, arr[i].prioridade);
    }
    printf("---------------------------------------------------------------\n");
}

/* ---------- Sorts com contagem de comparacoes e tempo ---------- */

/*
 Cada função de ordenação recebe:
 - arr: vetor de componentes
 - n: número de elementos válidos
 - comparacoes: ponteiro para int para armazenar o número de comparações realizadas
 Retorna tempo em segundos (double).
*/

/* Bubble Sort por nome (alfabético) */
double bubbleSortNome(Componente arr[], int n, long *comparacoes) {
    *comparacoes = 0;
    clock_t start = clock();
    for (int i = 0; i < n-1; ++i) {
        int trocou = 0;
        for (int j = 0; j < n-1-i; ++j) {
            (*comparacoes)++;
            if (strcmp(arr[j].nome, arr[j+1].nome) > 0) {
                Componente tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
                trocou = 1;
            }
        }
        if (!trocou) break;
    }
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

/* Insertion Sort por tipo (string) */
double insertionSortTipo(Componente arr[], int n, long *comparacoes) {
    *comparacoes = 0;
    clock_t start = clock();
    for (int i = 1; i < n; ++i) {
        Componente chave = arr[i];
        int j = i - 1;
        // enquanto j >=0 e arr[j].tipo > chave.tipo
        while (j >= 0) {
            (*comparacoes)++;
            if (strcmp(arr[j].tipo, chave.tipo) > 0) {
                arr[j+1] = arr[j];
                j--;
            } else break;
        }
        arr[j+1] = chave;
    }
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

/* Selection Sort por prioridade (int) */
double selectionSortPrioridade(Componente arr[], int n, long *comparacoes) {
    *comparacoes = 0;
    clock_t start = clock();
    for (int i = 0; i < n-1; ++i) {
        int menor_idx = i;
        for (int j = i+1; j < n; ++j) {
            (*comparacoes)++;
            if (arr[j].prioridade < arr[menor_idx].prioridade) {
                menor_idx = j;
            }
        }
        if (menor_idx != i) {
            Componente tmp = arr[i];
            arr[i] = arr[menor_idx];
            arr[menor_idx] = tmp;
        }
    }
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

/* ---------- Busca binária por nome (após ordenar por nome) ---------- */
/* Retorna indice encontrado ou -1. contador de comparações preenchido. */
int buscaBinariaPorNome(const Componente arr[], int n, const char chave[], long *comparacoes) {
    int left = 0, right = n - 1;
    *comparacoes = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        (*comparacoes)++;
        int cmp = strcmp(chave, arr[mid].nome);
        if (cmp == 0) return mid;
        else if (cmp < 0) right = mid - 1;
        else left = mid + 1;
    }
    return -1;
}

/* ---------- Operações básicas de inserção, remoção, busca sequencial ---------- */

/* Inserir novo componente no vetor (retorna 1 se inseriu, 0 se cheio) */
int inserirItemVetor(Componente arr[], int *n) {
    if (*n >= MAX_COMP) {
        printf("Mochila cheia (max %d).\n", MAX_COMP);
        return 0;
    }
    printf("\nInforme o nome do componente: ");
    ler_string(arr[*n].nome, MAX_NOME);
    printf("Informe o tipo do componente: ");
    ler_string(arr[*n].tipo, MAX_TIPO);
    int prioridade = 0;
    do {
        printf("Informe a prioridade (1 a 10): ");
        if (scanf("%d", &prioridade) != 1) {
            limpar_stdin: {
                int c; while ((c = getchar()) != '\n' && c != EOF);
            }
            prioridade = 0;
            printf("Entrada invalida. Tente novamente.\n");
        } else {
            int c; while ((c = getchar()) != '\n' && c != EOF); // limpar newline
            if (prioridade < 1 || prioridade > 10) {
                printf("Prioridade deve ser entre 1 e 10.\n");
            }
        }
    } while (prioridade < 1 || prioridade > 10);
    arr[*n].prioridade = prioridade;
    (*n)++;
    printf("Componente adicionado com sucesso!\n");
    return 1;
}

/* Remover item por nome (retorna 1 se removido, 0 se nao encontrado) */
int removerItemVetor(Componente arr[], int *n) {
    if (*n == 0) { printf("Mochila vazia.\n"); return 0; }
    char nome[MAX_NOME];
    printf("\nInforme o nome do componente a remover: ");
    ler_string(nome, MAX_NOME);
    for (int i = 0; i < *n; ++i) {
        if (strcmp(arr[i].nome, nome) == 0) {
            // desloca à esquerda
            for (int j = i; j < *n - 1; ++j) arr[j] = arr[j+1];
            (*n)--;
            printf("Componente '%s' removido.\n", nome);
            return 1;
        }
    }
    printf("Componente '%s' nao encontrado.\n", nome);
    return 0;
}

/* Busca sequencial por nome (retorna índice ou -1). Conta comparações via ponteiro */
int buscarSequencialVetor(const Componente arr[], int n, const char chave[], long *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n; ++i) {
        (*comparacoes)++;
        if (strcmp(arr[i].nome, chave) == 0) return i;
    }
    return -1;
}

/* ---------- Função principal ---------- */

int main(void) {
    Componente inventario[MAX_COMP];
    int total = 0;
    int opcao;
    int ordenadoPorNome = 0; // flag que indica se o vetor está ordenado por nome

    // variáveis de contagem de comparações (globais lógicas para exibir)
    long comps_sequencial = 0, comps_binaria = 0;
    srand((unsigned int) time(NULL));

    while (1) {
        mostrar_menu(total);
        if (scanf("%d", &opcao) != 1) {
            // limpar stdin e continuar
            int c; while ((c = getchar()) != '\n' && c != EOF);
            printf("Entrada invalida.\n");
            continue;
        }
        int c; while ((c = getchar()) != '\n' && c != EOF); // limpar newline

        if (opcao == 0) {
            printf("Ativando torre de fuga... Saindo.\n");
            break;
        }

        switch (opcao) {
            case 1: { // Adicionar Componente
                if (inserirItemVetor(inventario, &total)) {
                    ordenadoPorNome = 0; // qualquer insercao quebra ordenacao por nome
                }
                break;
            }

            case 2: { // Descartar componente
                if (removerItemVetor(inventario, &total)) {
                    ordenadoPorNome = 0;
                }
                break;
            }

            case 3: { // Listar componentes
                printf("\nStatus da Ordenacao por Nome: %s\n", ordenadoPorNome ? "ORDENADO" : "NAO ORDENADO");
                mostrar_componentes(inventario, total);
                break;
            }

            case 4: { // Organizar Mochila (submenu)
                mostrar_submenu_organizacao();
                int criterio;
                if (scanf("%d", &criterio) != 1) {
                    int cc; while ((cc = getchar()) != '\n' && cc != EOF);
                    printf("Entrada invalida no submenu.\n");
                    break;
                }
                int cc; while ((cc = getchar()) != '\n' && cc != EOF);

                if (criterio == 0) {
                    printf("Cancelado.\n");
                    break;
                } else if (criterio == 1) {
                    long comps = 0;
                    double t = bubbleSortNome(inventario, total, &comps);
                    ordenadoPorNome = 1;
                    printf("\nOrdenacao por NOME concluida. Comparacoes: %ld, Tempo: %.6f s\n", comps, t);
                    mostrar_componentes(inventario, total);
                } else if (criterio == 2) {
                    long comps = 0;
                    double t = insertionSortTipo(inventario, total, &comps);
                    ordenadoPorNome = 0;
                    printf("\nOrdenacao por TIPO concluida. Comparacoes: %ld, Tempo: %.6f s\n", comps, t);
                    mostrar_componentes(inventario, total);
                } else if (criterio == 3) {
                    long comps = 0;
                    double t = selectionSortPrioridade(inventario, total, &comps);
                    ordenadoPorNome = 0;
                    printf("\nOrdenacao por PRIORIDADE concluida. Comparacoes: %ld, Tempo: %.6f s\n", comps, t);
                    mostrar_componentes(inventario, total);
                } else {
                    printf("Opcao invalida no submenu.\n");
                }
                break;
            }

            case 5: { // Busca binária por componente-chave (por nome) - mas só se ordenado por nome
                if (!ordenadoPorNome) {
                    printf("\nBUSCA BINARIA SO FUNCIONA APOS ORDENAR POR NOME.\n");
                    printf("Deseja ordenar por nome agora? (1 = Sim / 0 = Nao): ");
                    int r;
                    if (scanf("%d", &r) != 1) { int cc; while ((cc = getchar()) != '\n' && cc != EOF); break; }
                    int cc; while ((cc = getchar()) != '\n' && cc != EOF);
                    if (r == 1) {
                        long comps = 0;
                        double t = bubbleSortNome(inventario, total, &comps);
                        ordenadoPorNome = 1;
                        printf("Ordenacao por nome feita. Comparacoes: %ld, Tempo: %.6f s\n", comps, t);
                    } else {
                        break;
                    }
                }
                if (total == 0) { printf("Inventario vazio.\n"); break; }
                char chave[MAX_NOME];
                printf("\nDigite o nome a buscar (busca binaria): ");
                ler_string(chave, MAX_NOME);
                clock_t inicio = clock();
                int idx = buscaBinariaPorNome(inventario, total, chave, &comps_binaria);
                double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
                if (idx >= 0) {
                    printf("Componente encontrado no indice %d (comparacoes: %ld, tempo: %.6f s)\n", idx+1, comps_binaria, tempo);
                    printf("  Nome: %s | Tipo: %s | Prioridade: %d\n", inventario[idx].nome, inventario[idx].tipo, inventario[idx].prioridade);
                } else {
                    printf("Componente '%s' nao encontrado (comparacoes: %ld, tempo: %.6f s)\n", chave, comps_binaria, tempo);
                }
                break;
            }

            default:
                printf("Opcao invalida.\n");
                break;
        }
    }

    printf("\nEncerrando programa. Bye.\n");
    return 0;
}