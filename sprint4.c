#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_NOME 50

typedef struct {
    int    id;
    char   nome[MAX_NOME];
    int    idade;
    int    prioridade_clinica; // 1 a 5
} Paciente;

//Geração dos dados

// Prefixos e Sufixos para os nomes
static const char *prefixos[] = {
    "Ana","Bruno","Carlos","Diana","Eduardo",
    "Fernanda","Gabriel","Helena","Igor","Julia",
    "Lucas","Maria","Nicolas","Olivia","Pedro",
    "Quezia","Rafael","Sabrina","Thiago","Ursula"
};
static const char *sobrenomes[] = {
    "Silva","Santos","Oliveira","Souza","Lima",
    "Pereira","Costa","Ferreira","Rodrigues","Almeida",
    "Nascimento","Carvalho","Gomes","Martins","Araújo"
};

void gerar_pacientes(Paciente *lista, int n) {
    int np = 20, ns = 15;
    for (int i = 0; i < n; i++) {
        lista[i].id              = i + 1;
        lista[i].idade           = rand() % 60 + 18;          /* 18–77 */
        lista[i].prioridade_clinica = rand() % 5  + 1;        /* 1–5  */
        snprintf(lista[i].nome, MAX_NOME, "%s %s",
                 prefixos[rand() % np],
                 sobrenomes[rand() % ns]);
    }
}

//Exibir

void exibir(const Paciente *lista, int n, const char *titulo) {
    printf("\n=== %s (primeiros %d registros) ===\n", titulo, n);
    printf("%-5s %-22s %-6s %-18s\n",
           "ID", "Nome", "Idade", "Prioridade Clinica");
    printf("%-5s %-22s %-6s %-18s\n",
           "----", "---------------------", "------", "-----------------");
    for (int i = 0; i < n; i++) {
        printf("%-5d %-22s %-6d %d\n",
               lista[i].id,
               lista[i].nome,
               lista[i].idade,
               lista[i].prioridade_clinica);
    }
}

//Copiar

void copiar(const Paciente *src, Paciente *dst, int n) {
    memcpy(dst, src, n * sizeof(Paciente));
}

//Selection Sort

void selection_sort(Paciente *lista, int n) {
    for (int i = 0; i < n - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (lista[j].prioridade_clinica > lista[max_idx].prioridade_clinica)
                max_idx = j;
        }
        if (max_idx != i) {
            Paciente tmp   = lista[i];
            lista[i]       = lista[max_idx];
            lista[max_idx] = tmp;
        }
    }
}

//Merge Sort

void merge(Paciente *lista, int esq, int meio, int dir) {
    int n1 = meio - esq + 1;
    int n2 = dir  - meio;

    Paciente *L = (Paciente *)malloc(n1 * sizeof(Paciente));
    Paciente *R = (Paciente *)malloc(n2 * sizeof(Paciente));

    for (int i = 0; i < n1; i++) L[i] = lista[esq  + i];
    for (int j = 0; j < n2; j++) R[j] = lista[meio + 1 + j];

    int i = 0, j = 0, k = esq;
    while (i < n1 && j < n2) {
        // Ordenação decrescente: maior prioridade primeiro
        if (L[i].prioridade_clinica >= R[j].prioridade_clinica)
            lista[k++] = L[i++];
        else
            lista[k++] = R[j++];
    }
    while (i < n1) lista[k++] = L[i++];
    while (j < n2) lista[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort_rec(Paciente *lista, int esq, int dir) {
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2;
        merge_sort_rec(lista, esq, meio);
        merge_sort_rec(lista, meio + 1, dir);
        merge(lista, esq, meio, dir);
    }
}

void merge_sort(Paciente *lista, int n) {
    merge_sort_rec(lista, 0, n - 1);
}

//Executa um teste completo para N pacientes

void executar_teste(int n) {
    printf("\n\n");
    printf("##############################################\n");
    printf("#   TESTE COM %d PACIENTES                   \n", n);
    printf("##############################################\n");

    //Aloca e gera dados
    Paciente *original   = (Paciente *)malloc(n * sizeof(Paciente));
    Paciente *para_sel   = (Paciente *)malloc(n * sizeof(Paciente));
    Paciente *para_merge = (Paciente *)malloc(n * sizeof(Paciente));

    gerar_pacientes(original, n);

    //Exibe 10 primeiros
    exibir(original, 10, "ANTES DA ORDENACAO");

    //Selection Sort
    copiar(original, para_sel, n);
    clock_t ini_sel = clock();
    selection_sort(para_sel, n);
    clock_t fim_sel = clock();
    double tempo_sel = (double)(fim_sel - ini_sel) / CLOCKS_PER_SEC;

    //Merge Sort
    copiar(original, para_merge, n);
    clock_t ini_merge = clock();
    merge_sort(para_merge, n);
    clock_t fim_merge = clock();
    double tempo_merge = (double)(fim_merge - ini_merge) / CLOCKS_PER_SEC;

    //Exibe os 10 primeiros de cada
    exibir(para_sel,   10, "APOS SELECTION SORT (maior prioridade primeiro)");
    exibir(para_merge, 10, "APOS MERGE SORT    (maior prioridade primeiro)");

    //Tempos
    printf("\n--- Tempos de Execucao (%d pacientes) ---\n", n);
    printf("Selection Sort : %.8f segundos\n", tempo_sel);
    printf("Merge Sort     : %.8f segundos\n", tempo_merge);

    free(original);
    free(para_sel);
    free(para_merge);
}

// Main

int main(void) {
    srand(42); // semente fixa para reprodutibilidade

    printf("================================================\n");
    printf("  Plataforma Blua – Care Plus                   \n");
    printf("  Sprint 4: Ordenacao de Pacientes              \n");
    printf("  Criterio: prioridade_clinica (5 = critica)    \n");
    printf("================================================\n");

    executar_teste(100);
    executar_teste(300);

    printf("\n\n=== FIM DA EXECUCAO ===\n");
    return 0;
}