// Copyright 2020 Unifesp
// Guilherme Neves

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  //  biblioteca necessária para o cálculo CPU time.


// Estrutura para a criação das Arrays a serem ordenadas

typedef int TChave;
typedef struct {
  TChave Chave;
} TItem;

/* Declaração das funções Sort a serem utilizadas */

void Insercao(TItem *A, int n);
void Selecao(TItem *A, int n);
void Bolha(TItem *A, int n);
void heapSort(TItem *A, int n);
void heapConstroi(TItem *A, int n);
void heapRefaz(TItem *A, int esq, int dir);
void mergeSort(TItem *A, int n);
void mergeSort_ordena(TItem *A, TItem *B, int p, int r);
void mergeSort_intercala(TItem *A, TItem *B, int p, int q, int r);
void quickSort(TItem *A, int n);
void quickSort_ordena(TItem *A, int p, int r);
void quickSort_particao_ternaria(TItem *A, int p, int r, int *q, int *t);
void splayTree(TItem *A, int n);

/* Declaração Função para criar as Array solicitadas na P1 */
/* Valores de Type: 1. Aleatória     | 2. Ordenado         */
/*                  3. Inversamente  | 4. Quase Ordenado   */

void CriaArray(TItem Elems[], int n, int type);


/* Implementação Prova 1 - AAED | Análise de Algoritmos e Estruturas de Dados */
/*                    Unifesp - 1º Semestre 2020                              */
/* Análise de desempenho de um algoritmo de ordenação em diferentes cenários. */
/*       Geração dos Arrays: 10, 100, 1.000, 10.000, 100.000, 1.000.000       */
/*         Requisitos: 1. Sem Valores Repetidos | 2. Valores Inteiros         */
/*          (i) Arranjos Ordenados | (ii) Inversamente Ordenados              */
/*           (iii) Quase Ordenados | (iv) Aleátorios                          */

int main(int argc, char *argv[]) {
  int n = atoi(argv[1]);
  int array_type = atoi(argv[2]);
  TItem Itens[n], Itens_Insert[n+1], Itens_Select[n];

  switch (array_type) {
    case 1:
      printf("Tipo Array: Aleatório\n");
      break;
    case 2:
      printf("Tipo Array: Ordenado\n");
      break;
    case 3:
      printf("Tipo Array: Inversamente Ordenado\n");
      break;
    case 4:
      printf("Tipo Array: Quase Ordenado\n");
      break;
    default:
      break;
  }

  CriaArray(Itens, n, array_type);  // Cria Array seguindo args recebidos.

  /* Nesta etapa será criado uma cópia do mesmo Array para todos os sorts. */
  memcpy(&Itens_Select, &Itens, sizeof(Itens));

  /*    Necessário adicionar um elemento na posição [0] no Array Insertion    */
  /* Devido a Utilização da implementação com Sentinela a array tem n+1 elems.*/
  memcpy(&Itens_Insert, &Itens, sizeof(Itens));
  memmove(Itens_Insert, Itens_Insert + n + 1, sizeof(int) * (n+1));
  Itens_Insert[0].Chave = 0;

  /*Implementar outros Sorts*/
  Insercao(Itens_Insert, n);
  Selecao(Itens_Select, n);

}

/* Implementação das Funções Gerais*/


/* Implementação InsertionSort. */
/* Fonte: Análise de Algoritmos e Estruturas de Dados Aula 04/ */
/* Ordenação - Parte 1 */
/* Alterações comentadas para controle clocks CPU, Comparacoes e Movimentacoes*/

void Insercao(TItem *A, int n) {
  int i, j;
  long com = 0, mov = 0;  // Inicializa as variáveis para controle do comp/mov.
  TItem aux;
  clock_t start = clock();  // Captura a contagem inicial de clocks CPU.
  for (i = 2; i <= n; i++) {
    aux = A[i];
    A[0] = aux;
    j = i - 1;
    com++;  // Incrementa a variável de controle de comparação.
    while (aux.Chave < A[j].Chave) {
      A[j + 1] = A[j];
      j--;
      mov++;  // Incrementa a variável de controle de movimentação.
    }
    A[j + 1] = aux;
  }
  clock_t end = clock();  // Captura a contagem final de clocks CPU
  double time_spent = (double)(end - start)/(CLOCKS_PER_SEC);  // Tempo em (s).
  printf("\nINSERTION SORT\n# Total de elementos:%d\nTempo total "
        "para processamento : %f (s) \n"
         "# de movimentacoes : %ld\n# de comparacoes : %ld \n"
         "", n, time_spent, mov, com);
}

/* Implementação SelectionSort. */
/* Fonte: Análise de Algoritmos e Estruturas de Dados Aula 04/ */
/* Ordenação - Parte 1 */

void Selecao(TItem *A, int n) {
  int i, j, Min;
  long com = 0, mov = 0;  // Inicializa as variáveis para controle do comp/mov.
  TItem aux;
  clock_t start = clock();  // Captura a contagem inicial de clocks CPU.
  for (i = 0; i < n - 1; i++) {
    Min = i;
    for (j = i + 1 ; j < n; j++) {
      com++;
      if (A[j].Chave < A[Min].Chave) {
        Min = j;
      }
    }
    if (i != Min) {
      mov++;
      aux = A[Min];
      A[Min] = A[i];
      A[i] = aux;
    }
  }
  clock_t end = clock();  // Captura a contagem final de clocks CPU
  double time_spent = (double)(end - start)/(CLOCKS_PER_SEC);  // Tempo em (s).
  printf("\nSELECTION SORT\n# Total de elementos:%d\nTempo total "
      "para processamento : %f (s) \n"
        "# de movimentacoes : %ld\n# de comparacoes : %ld \n"
        "", n, time_spent, mov, com);
}

/* Implementação BubbleSort. */
/* Fonte: Análise de Algoritmos e Estruturas de Dados Aula 04/ */
/* Ordenação - Parte 1 */

void Bolha(TItem *A, int n) {
  int i, j, troca;
  TItem aux;
  for (i = 0 ; i < n-1 ; i++) {
    troca = 0;
    for (j = 1 ; j < n-i ; j++) {
      if (A[j].Chave < A[j-1].Chave) {
        aux = A[j];
        A[j] = A[j-1];
        A[j-1] = aux;
        troca = 1;
      }
      if (troca == 0) {
        break;
      }
    }
  }
}

/* Implementação HeapSort. */
/* Fonte: Análise de Algoritmos e Estruturas de Dados Aula 04/ */
/* Ordenação - Parte 1 */

void heapSort(TItem *A, int n) {
  TItem aux;
  int m;
  heapConstroi(A, n);
  m = n - 1;
  while (m > 0) {
    aux = A[m];
    A[m] = A[0];
    A[0] = aux;
    m = m - 1;
    heapRefaz(A, 0, m);  // refaz o heap
  }
}

void heapConstroi(TItem *A, int n) {
  int esq;
  esq = (n / 2) - 1;  // esq = primeiro no folha do heap
  while (esq >= 0) {
    heapRefaz(A, esq, n-1);
    esq--;
  }
}

void heapRefaz(TItem *A, int esq, int dir) {
  TItem aux;
  int i, j;
  i = esq;
  j = i * 2 + 1;  // j = primeiro filho de i
  if (j <= dir) {
    aux = A[i];   // aux = no i (pai de j)
    if ((j < dir) && (A[j].Chave < A[j+1].Chave)) {
      j++;  // j recebe o outro filho de i
    }
    if (aux.Chave < A[j].Chave) {
      A[i] = A[j];  // heap precisa ser refeito
      A[j] = aux;
      heapRefaz(A, j, dir);
    }
  }
}

/* Implementação MergeSort. */
/* Fonte: Análise de Algoritmos e Estruturas de Dados Aula 04/ */
/* Ordenação - Parte 2 */

void mergeSort(TItem *A, int n) {
  TItem *B;
  B = (TItem *) malloc(n * sizeof(TItem));
  mergeSort_ordena(A, B, 0, n-1);
  free(B);
}

void mergeSort_ordena(TItem *A, TItem *B, int p, int r) {
  int q;
  if (p < r) {
    q = (p + r) / 2;
    mergeSort_ordena(A, B, p, q);
    mergeSort_ordena(A, B, q + 1, r);
    mergeSort_intercala(A, B, p, q, r);
  }
}

void mergeSort_intercala(TItem *A, TItem *B, int p, int q, int r) {
  int i, j, k;
  if (A[q].Chave > A[q + 1].Chave) {
    for (i = p; i <= q; i++) {
      B[i] = A[i];
    }
    for (j = q + 1; j <= r; j++) {
      B[r + q + 1 - j] = A[j];
    }
    i = p;
    j = r;
    for (k = p; k <= r; k++) {
      if (B[i].Chave <= B[j].Chave) {
        A[k] = B[i];
        i = i + 1;
      } else {
        A[k] = B[j];
        j = j - 1;
      }
    }
  }
}

/* Implementação QuickSort. */
/* Fonte: Análise de Algoritmos e Estruturas de Dados Aula 04/ */
/* Ordenação - Parte 2 */

void quickSort(TItem *A, int n) {
  quickSort_ordena(A, 0, n-1);
}

void quickSort_ordena(TItem *A, int p, int r) {
  int q, t;
  while (p < r) {
    quickSort_particao_ternaria(A, p, r, &q, &t);
    if (q - p < r - t) {
      quickSort_ordena(A, p, q-1);
      p = t + 1;
    } else {
      quickSort_ordena(A, t+1, r);
      r = q - 1;
    }
  }
}

void quickSort_particao_ternaria(TItem *A, int p, int r, int *q, int *t) {
  TItem x, aux;
  int i, j, k;
  x = A[r];
  i = p-1;
  j = p;
  k = r;
  while (j <= k-1) {
    if (A[j].Chave < x.Chave) {
      i = i + 1;
      aux = A[i];
      A[i] = A[j];
      A[j] = aux;
    } else if (A[j].Chave == x.Chave) {
      k = k - 1;
      aux = A[k];
      A[k] = A[j];
      A[j] = aux;
      j = j - 1;
    }
    j = j + 1;
  }
  (*q) = i+1;
  for (j = k; j <= r; j++) {
    i = i + 1;
    aux = A[i];
    A[i] = A[j];
    A[j] = aux;
  }
  (*t) = i;
}

/* Implementação Geração de Array Aleatória. */

void CriaArray(TItem Elems[], int n, int type) {
  switch (type) {
            //  Gerar números aleatórios entre 1 and n sem repetição
    case 1:
      srand((unsigned) time(NULL));
      for (int i=0; i < n; i++) {
          Elems[i].Chave = 1 + rand()%(n);
      }
      break;
      //  Gera um array ordenado de 0 a n
    case 2:
        for (int i = 0; i < n; i++) {
          Elems[i].Chave = i;
        }
        break;
        // Gera um array inversamente ordenado de 0 a n
    case 3:
        for (int i=0 ; i < n; i++) {
          Elems[i].Chave = n-i-1;
        }
        break;
        // Gera um array quase ordenado
    case 4:
        for (int i = 0; i < n; i++) {
          Elems[i].Chave = i;
          if ( i + 1 == n ) {
            int aux;
            aux = Elems[i].Chave;
            Elems[i].Chave = Elems[i-1].Chave;
            Elems[i-1].Chave = aux;
          }
        }
        break;
    default:
        break;
  }
}
