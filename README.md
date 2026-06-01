# 🏥 Plataforma Blua – Care Plus
## Sprint 4 · Ordenação e Busca de Pacientes

> Implementação e comparação empírica de **Selection Sort** e **Merge Sort** aplicados a registros de pacientes ordenados por prioridade clínica — parte do desafio técnico da plataforma Blua em parceria com a Care Plus.

---

## 📋 Sobre o Projeto

A Care Plus opera a plataforma **Blua** com foco em cuidado proativo de saúde. Para garantir que pacientes em estado crítico sejam atendidos primeiro, a lista de pacientes precisa estar sempre ordenada pelo atributo `prioridade_clinica` (escala de 1 a 5, onde **5 = estado crítico**).

Este projeto implementa dois algoritmos de ordenação do zero em **linguagem C**, mede seu desempenho com conjuntos de 100 e 300 pacientes simulados e compara os resultados para orientar a escolha do algoritmo mais adequado ao cenário real.

---

## 🗂️ Estrutura do Repositório

```
├── blua_ordenacao.c   # Código-fonte principal em C
└── README.md
```

---

## ⚙️ Como Executar

### OnlineGDB (recomendado para avaliação)

1. Acesse [onlinegdb.com](https://onlinegdb.com)
2. Selecione a linguagem **C**
3. Cole o conteúdo de `blua_ordenacao.c`
4. Clique em **Run**

### Localmente (GCC)

```bash
gcc -O0 -o blua_ordenacao blua_ordenacao.c
./blua_ordenacao
```

---

## 🧩 Estrutura de Dados

Cada paciente é representado pela seguinte struct:

```c
typedef struct {
    int  id;
    char nome[50];
    int  idade;
    int  prioridade_clinica; // 1 (baixa) a 5 (crítica)
} Paciente;
```

Os dados são gerados pelo próprio código via `rand()`:

```c
lista[i].idade            = rand() % 60 + 18;  // 18 a 77 anos
lista[i].prioridade_clinica = rand() % 5 + 1;  // 1 a 5
```

---

## 🔢 Algoritmos Implementados

### Selection Sort

A cada iteração, varre o subarray restante em busca do paciente com **maior** prioridade e o posiciona no início da parte não ordenada.

```c
for (int i = 0; i < n - 1; i++) {
    int max_idx = i;
    for (int j = i + 1; j < n; j++)
        if (lista[j].prioridade_clinica > lista[max_idx].prioridade_clinica)
            max_idx = j;
    // troca lista[i] ↔ lista[max_idx]
}
```

| Propriedade | Valor |
|---|---|
| Complexidade de tempo | O(n²) |
| Complexidade de espaço | O(1) — in-place |
| Estável | Não |

### Merge Sort

Divide recursivamente a lista ao meio e mescla as sublistas em ordem decrescente de prioridade.

```c
// Mesclagem: maior prioridade primeiro
if (L[i].prioridade_clinica >= R[j].prioridade_clinica)
    lista[k++] = L[i++];
else
    lista[k++] = R[j++];
```

| Propriedade | Valor |
|---|---|
| Complexidade de tempo | O(n log n) |
| Complexidade de espaço | O(n) — vetores auxiliares |
| Estável | Sim |

---

## 📊 Resultados de Desempenho

Medição via `clock()` da biblioteca `<time.h>`, semente fixa `srand(42)`, compilação sem otimizações (`-O0`):

| Tamanho (n) | Selection Sort | Merge Sort | Razão SS / MS |
|---|---|---|---|
| 100 pacientes | 0.00001400 s | 0.00002100 s | 0.67× |
| 300 pacientes | 0.00011900 s | 0.00004900 s | **2.43×** |

> Em 300 registros, o Selection Sort consome **2,4× mais tempo** que o Merge Sort — tendência que se intensifica à medida que n cresce.

### Saída esperada (trecho)

```
##############################################
#   TESTE COM 300 PACIENTES
##############################################

=== ANTES DA ORDENACAO (primeiros 10 registros) ===
ID    Nome                   Idade  Prioridade Clinica
1     Ana Lima               44     4
2     Ana Carvalho           58     3
...

=== APOS MERGE SORT (maior prioridade primeiro) ===
ID    Nome                   Idade  Prioridade Clinica
5     Sabrina Nascimento     69     5
7     Olivia Silva           61     5
...

--- Tempos de Execucao (300 pacientes) ---
Selection Sort : 0.00011900 segundos
Merge Sort     : 0.00004900 segundos
```

---

## 🏁 Conclusão

Para a plataforma Blua, o **Merge Sort é o algoritmo recomendado**. Seu custo O(n log n) escala bem com o crescimento da base de pacientes, é determinístico e garante que pacientes críticos (prioridade 5) estejam sempre no topo da fila — o que em saúde significa atendimento mais rápido para quem mais precisa.

O **Selection Sort** tem valor pedagógico e pode ser útil para listas muito pequenas (até ~50 registros), onde sua simplicidade supera a necessidade de performance.

---

## 🛠️ Tecnologias

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![GCC](https://img.shields.io/badge/GCC-A42E2B?style=for-the-badge&logo=gnu&logoColor=white)

- Linguagem: **C (C99)**
- Compilador: **GCC**
- Plataforma de execução: **OnlineGDB**
- Bibliotecas: `stdio.h` · `stdlib.h` · `string.h` · `time.h`

---

## 📄 Licença

Projeto acadêmico desenvolvido para o Sprint 4 da disciplina de Algoritmos e Estruturas de Dados — **Care Plus / Plataforma Blua**.
