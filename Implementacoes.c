// Copyright 2020 Unifesp - AAED - 1º Semestre
// Guilherme Neves

#include <stdio.h>
#include <stdlib.h>
#include <time.h>  // biblioteca necessária para o cálculo CPU time.
#include "Definicoes.h"  // declaração de funções, estruturas e variáveis

/* Implementação Prova 1 - AAED | Análise de Algoritmos e Estruturas de Dados */
/*                    Unifesp - 1º Semestre 2020                              */
/* Análise de desempenho de um algoritmo de ordenação em diferentes cenários. */
/*       Geração dos Arrays: 10, 100, 1.000, 10.000, 100.000, 1.000.000       */
/*         Requisitos: 1. Sem Valores Repetidos | 2. Valores Inteiros         */
/*          (i) Arranjos Ordenados | (ii) Inversamente Ordenados              */
/*           (iii) Quase Ordenados | (iv) Aleátorios                          */
/*            Compilação:  gcc -o p1_code Implementacoes.c                    */
/*    Exemplo para rodar o programa Arranjos Aleatorios: ./p1_code 100 1      */

int main(int argc, char *argv[]) {
  int n = atoi(argv[1]);  // Recebe número de elementos
  int array_type = atoi(argv[2]);  // Recebe tipo da ordenação

  // Aloca n posições para TItem
  TItem *Itens = malloc((n) * sizeof(TItem));
  // Aloca n + 1 para Titem. Necessário para InsertionSort (Sentinela)
  TItem *Itens_Not_Ordered = malloc((n+1) * sizeof(TItem));

  //  Mostra na saída do programa o Tipo de Array Selecionado.
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

  /*   Nesta etapa será criado uma cópia do mesmo Array para todos os sorts.  */
  /*      Devido ao limite tamanho do array é utilizado alocação dinâmica     */
  /*                       Início Chamada Funções Sort                        */
  CriaArray(Itens, n, array_type);  // Cria Array seguindo args recebidos.

  /*   ####################################################################   */
  /*                              Selection Sort                              */
  /*   ####################################################################   */

  Copia_TItemA_Para_TItemB(Itens, Itens_Not_Ordered, n, 0);
  Selecao(Itens_Not_Ordered, n);

  /*   ####################################################################   */
  /*                              Insertion Sort                              */
  /*   ####################################################################   */
  /*    Necessário adicionar um elemento na posição [0] no Array Insertion    */
  /* Devido a Utilização da implementação com Sentinela a array tem n+1 elems.*/
  /*   Último parametro da fnução Copia_TItemA_Para_TItemB ajusta n para n+1  */

  Copia_TItemA_Para_TItemB(Itens, Itens_Not_Ordered, n, 1);
  Insercao(Itens_Not_Ordered, n);

  /*   ####################################################################  */
  /*                               Bubble Sort                               */
  /*   ####################################################################  */

  Copia_TItemA_Para_TItemB(Itens, Itens_Not_Ordered, n, 0);
  Bolha(Itens_Not_Ordered, n);

  /*   ####################################################################  */
  /*                                Heap Sort                                */
  /*   ####################################################################  */

  Copia_TItemA_Para_TItemB(Itens, Itens_Not_Ordered, n, 0);
  heapSort(Itens_Not_Ordered, n);

  /*   ####################################################################  */
  /*                                Merge Sort                               */
  /*   ####################################################################  */

  Copia_TItemA_Para_TItemB(Itens, Itens_Not_Ordered, n, 0);
  mergeSort(Itens_Not_Ordered, n);

  /*   ####################################################################  */
  /*                                Quick Sort                               */
  /*   ####################################################################  */

  Copia_TItemA_Para_TItemB(Itens, Itens_Not_Ordered, n, 0);
  quickSort(Itens_Not_Ordered, n);

  /*   ####################################################################  */
  /*                                Splay Sort                               */
  /*   ####################################################################  */
  /* Necessário a inicialização da SplayTree, conforme 1 passo do SplaySort  */
  /*   É passado o endereço desta struct SplayTree criada para a função      */

  Copia_TItemA_Para_TItemB(Itens, Itens_Not_Ordered, n, 0);
  SplayTree *node;
  node = NULL;
  splaySort(&node, n, Itens_Not_Ordered);
}

/* Implementação das Funções Gerais*/

/* Implementação InsertionSort. */
/* Fonte: Análise de Algoritmos e Estruturas de Dados Aula 04/ */
/* Ordenação - Parte 1 */
/* Alterações comentadas para controle clocks CPU, Comparacoes e Movimentacoes*/

void Insercao(TItem *A, int n) {
  int i, j;
  long long com = 0, mov = 0;  // Inicializa as variáveis para controle do comp/mov.
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
         "# de movimentacoes : %lld\n# de comparacoes : %lld"
         "", n, time_spent, mov, com);
}

/* Implementação SelectionSort. */
/* Fonte: Análise de Algoritmos e Estruturas de Dados Aula 04/ */
/* Ordenação - Parte 1 */

void Selecao(TItem *A, int n) {
  int i, j, Min;
  long long com = 0, mov = 0;  // Inicializa as variáveis controle do comp/mov.
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
        "# de movimentacoes : %lld\n# de comparacoes : %lld"
        "", n, time_spent, mov, com);
}

/* Implementação BubbleSort. */
/* Fonte: Análise de Algoritmos e Estruturas de Dados Aula 04/ */
/* Ordenação - Parte 1 */

void Bolha(TItem *A, int n) {
  int i, j, troca;
  long long com = 0, mov = 0;  // Inicializa as variáveis para controle do comp/mov.
  TItem aux;
  clock_t start = clock();  // Captura a contagem inicial de clocks CPU.
  for (i = 0 ; i < n-1 ; i++) {
    troca = 0;
    for (j = 1 ; j < n-i ; j++) {
      com++;
      if (A[j].Chave < A[j-1].Chave) {
        aux = A[j];
        A[j] = A[j-1];
        A[j-1] = aux;
        troca = 1;
        mov++;
      }
    }
    if (troca == 0) {
      break;
    }
  }
  clock_t end = clock();  // Captura a contagem final de clocks CPU
  double time_spent = (double)(end - start)/(CLOCKS_PER_SEC);  // Tempo em (s).
  printf("\nBUBBLE SORT\n# Total de elementos:%d\nTempo total "
      "para processamento : %f (s) \n"
        "# de movimentacoes : %lld\n# de comparacoes : %lld"
        "", n, time_spent, mov, com);
}

/* Implementação HeapSort. */
/* Fonte: Análise de Algoritmos e Estruturas de Dados Aula 04/ */
/* Ordenação - Parte 1 */

void heapSort(TItem *A, int n) {
  TItem aux;
  int m;
  clock_t start = clock();  // Captura a contagem inicial de clocks CPU.
  heapConstroi(A, n);
  m = n - 1;
  while (m > 0) {
    aux = A[m];
    A[m] = A[0];
    A[0] = aux;
    m = m - 1;
    heapRefaz(A, 0, m);  // refaz o heap
  }
  clock_t end = clock();  // Captura a contagem final de clocks CPU
  double time_spent = (double)(end - start)/(CLOCKS_PER_SEC);  // Tempo em (s).
  printf("\nHEAP SORT\n# Total de elementos:%d\nTempo total "
      "para processamento : %f (s) \n"
        "# de movimentacoes : %lld\n# de comparacoes : %lld"
        "", n, time_spent, mov_heap, com_heap);
}

void heapConstroi(TItem *A, int n) {
  int esq;
  esq = (n / 2) - 1;  // esq = primeiro no folha do heap
  while (esq >= 0) {
    heapRefaz(A, esq, n-1);
    esq--;
  }
}

//  Rearranja elementos para satisfazer a condição de Heap
void heapRefaz(TItem *A, int esq, int dir) {
  TItem aux;
  int i, j;
  i = esq;
  j = i * 2 + 1;  // j = primeiro filho de i
  if (j <= dir) {
    aux = A[i];   // aux = no i (pai de j)
    com_heap++;
    if ((j < dir) && (A[j].Chave < A[j+1].Chave)) {
      j++;  // j recebe o outro filho de i
    }
    com_heap++;
    if (aux.Chave < A[j].Chave) {
      A[i] = A[j];  // heap precisa ser refeito
      A[j] = aux;
      mov_heap++;
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

  clock_t start = clock();  // Captura a contagem inicial de clocks CPU.
  mergeSort_ordena(A, B, 0, n-1);
  clock_t end = clock();  // Captura a contagem final de clocks CPU

  double time_spent = (double)(end - start)/(CLOCKS_PER_SEC);  // Tempo em (s).
  printf("\nMERGE SORT\n# Total de elementos:%d\nTempo total "
      "para processamento : %f (s) \n"
        "# de movimentacoes : %lld\n# de comparacoes : %lld"
        "", n, time_spent, mov_merge, com_merge);
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
      com_merge++;
      if (B[i].Chave <= B[j].Chave) {
        A[k] = B[i];
        i = i + 1;
        mov_merge++;
      } else {
        A[k] = B[j];
        j = j - 1;
        mov_merge++;
      }
    }
  }
}

/* Implementação QuickSort. */
/* Fonte: Análise de Algoritmos e Estruturas de Dados Aula 04/ */
/* Ordenação - Parte 2 */

void quickSort(TItem *A, int n) {
  clock_t start = clock();  // Captura a contagem inicial de clocks CPU.
  quickSort_ordena(A, 0, n-1);
  clock_t end = clock();  // Captura a contagem final de clocks CPU

  double time_spent = (double)(end - start)/(CLOCKS_PER_SEC);  // Tempo em (s).
  printf("\nQUICK SORT\n# Total de elementos:%d\nTempo total "
      "para processamento : %f (s) \n"
      "# de movimentacoes : %lld\n# de comparacoes : %lld"
      "", n, time_spent, mov_quick, com_quick);
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
    com_quick++;
    if (A[j].Chave < x.Chave) {
      i = i + 1;
      aux = A[i];
      A[i] = A[j];
      A[j] = aux;
      mov_quick++;
    } else if (A[j].Chave == x.Chave) {
      k = k - 1;
      aux = A[k];
      A[k] = A[j];
      A[j] = aux;
      j = j - 1;
      mov_quick++;
    }
    j = j + 1;
  }
  (*q) = i+1;
  for (j = k; j <= r; j++) {
    i = i + 1;
    aux = A[i];
    A[i] = A[j];
    A[j] = aux;
    mov_quick++;
  }
  (*t) = i;
}

/* Implementação SplaySort. */
/* Fonte: Adaptação de https://github.com/Arc676/WikiSort */

// Função de rotação a esquerda convencional de árvore binária
void leftRotate(SplayTree *node) {
  SplayTree *tmp;
  tmp = node->right;
  if (tmp != NULL) {
    node->right = tmp->left;
    if (tmp->left != NULL) {
      tmp->left->parent = node;
    }
    tmp->parent = node->parent;
  }
  if (node->parent == NULL) {
    node->parent = tmp;
    mov_splay++;
  } else if (node == node->parent->left) {
      node->parent->left = tmp;
      mov_splay++;
  } else {
      node->parent->right = tmp;
      mov_splay++;
  }
  if (tmp != NULL) {
    tmp->left = node;
  }
  node->parent = tmp;
}

// Função de rotação a direita convencional de árvore binária

void rightRotate(SplayTree *node) {
  SplayTree *tmp;
  tmp = node->left;
  if (tmp != NULL) {
    node->left = tmp->right;
    if (tmp->right != NULL) {
      tmp->right->parent = node;
    }
    tmp->parent = node->parent;
  }
  if (node->parent == NULL) {
    node->parent = tmp;
    mov_splay++;
  } else if ( node == node->parent->left ) {
    node->parent->left = tmp;
    mov_splay++;
  } else {
    node->parent->right = tmp;
    mov_splay++;
  }
  if (tmp != NULL) {
    tmp->right = node;
  }
  node->parent = tmp;
}

// Função para encontrar a raíz da árvore.
// Necessária para cada chamada de SplayTreeInsert.

SplayTree* getRoot(SplayTree **node) {
    while ((*node)->parent != NULL) {
      (*node) = (*node)->parent;
    }
  return (*node);
}

// Função principal do SplaySort
// Avalia o nó passado para a função e determina o tipo de movimentação
// sendo estas: ZIG | ZIG-ZIG | ZIG-ZAG

void splayCreate(SplayTree *x) {
  while (x->parent != NULL) {  // Enquanto não estiver na raíz
    com_splay++; // Contabiliza 1 comparação 
    // Avalia se é aplicável ZIG, podendo ser a esquerda ou direita.
    if (x->parent->parent == NULL) {
      com_splay++;
      if (x->parent->left == x) {
        rightRotate(x->parent);
      } else if (x->parent->right == x) {
        leftRotate(x->parent);
      }
    // Avalia se é aplicável ZIG-ZIG, podendo ser a esquerda ou direita.
    } else if (x->parent->left == x && x->parent->parent->left == x->parent) {
      rightRotate(x->parent->parent);
      rightRotate(x->parent);
    } else if (x->parent->right == x && x->parent->parent->right == x->parent) {
      leftRotate(x->parent->parent);
      leftRotate(x->parent);
    // Avalia se é aplicável ZIG-ZAG, podendo ser a esquerda ou direita.
    } else if (x->parent->left == x && x->parent->parent->right == x->parent) {
      rightRotate(x->parent);  // We rotate to the right
      leftRotate(x->parent);  // Then we rotate to the left
    } else if (x->parent->right == x && x->parent->parent->left == x->parent) {
      leftRotate(x->parent);  // We rotate to the left
      rightRotate(x->parent);  // Then we rotate to the right
    }
  }
}

// Função Anterior ao Splay, é encontrado o nó para encaixar este elemento
// Mesmo passo de uma árvore binária de busca convencional

void splayTreeInsert(SplayTree **splayTree, SplayTree *parent,
                     SplayTree *value) {
  if (!(*splayTree)) {
    *splayTree = value;
    (*splayTree)->parent = parent;
    (*splayTree)->left = NULL;
    (*splayTree)->right = NULL;
    // We create the splay Tree
    splayCreate(*splayTree);
    return;
  } else {
    com_splay++;  // Captura comparações para encontrar o nó do elemento.
    if (value->key < (*splayTree)->key) {
      splayTreeInsert(&(*splayTree)->left, (*splayTree), value);
    } else {
      if (value->key > (*splayTree)->key) {
        splayTreeInsert(&(*splayTree)->right, (*splayTree), value);
      } else {
        if (value->key == (*splayTree)->key) {
          splayTreeInsert(&(*splayTree)->right, (*splayTree), value);
        }
      }
    }
  }
}

// A função inorderSplayTree percorre a SplayTree após a inserção de todos 
// os elementos TItem na SplayTree de forma in-order traversal.
// é nesta fase (e ultima) que são armazenados em TItem os dados ordenados
// Ponto importante: Nessa recursão para arrays ordenados ou inversamente
// há um ponto de melhoria de utilizar método iterativo, pois foi necessário
// para estes dois tipos de arranjos comentar a linha left para rodar ordenado
// e vice-versa. devido ao apontamento para NULL.

void inorderSplayTree(SplayTree *splayTree, TItem *A) {
  if (splayTree == NULL) {
    return;
  } else {
      inorderSplayTree(splayTree->left, A);
      A[index_splay].Chave = splayTree->key;
      index_splay++;
      inorderSplayTree(splayTree->right, A);
  }
}

// Função Geral

void splaySort(SplayTree **splayTree, int size, TItem *A) {
  // 1. Inicializa a árvore
  // 2. Insere os elementos na SplayTree
  // 3. Roda a SplayTree in-order
  int i;
  SplayTree *aux;
  aux = NULL;
  clock_t start = clock();  // Captura a contagem inicial de clocks CPU.
  for (i = 0; i < size; i++) {
    aux = (SplayTree *)malloc(sizeof(SplayTree));
    aux->key = A[i].Chave;
    splayTreeInsert(splayTree, NULL, aux);
    // Garante que a função insert será chamada sempre a partir da raíz
    *splayTree = getRoot(splayTree);
  }
  inorderSplayTree(*splayTree, A);
  clock_t end = clock();  // Captura a contagem final de clocks CPU
  double time_spent = (double)(end - start)/(CLOCKS_PER_SEC);  // Tempo em (s).
  //free(aux);
  printf("\nSPLAY SORT\n# Total de elementos:%d\nTempo total "
      "para processamento : %f (s) \n"
      "# de movimentacoes : %lld\n# de comparacoes : %lld\n"
      "", size, time_spent, mov_splay, com_splay);
}

/*   ###################################     */
/* Implementação Geração de Array Aleatória. */
/*   ###################################     */

void CriaArray(TItem Elems[], int n, int type) {
  switch (type) {
            //  Gerar números aleatórios entre 0 and n-1 sem repetição
    case 1:
      for (int i=0; i < n; i++) {
        Elems[i].Chave = 1+i;
      }
      for (int i = 0; i < n; i++) {    // Embaralha Array.
        int temp = Elems[i].Chave;
        int randomIndex = rand() % (n);
        Elems[i].Chave = Elems[randomIndex].Chave;
        Elems[randomIndex].Chave = temp;
      }
      break;
      //  Gera um array ordenado de 0 a n-1
    case 2:
        for (int i = 0; i < n; i++) {
          Elems[i].Chave = i;
        }
        break;
        // Gera um array inversamente ordenado de 0 a n-1
    case 3:
        for (int i=0 ; i < n; i++) {
          Elems[i].Chave = n-i-1;
        }
        break;
        // Gera um array quase ordenado, troca n-1 com n-2
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

/*   ###################################     */
/*      Implementação Cópia de TItem.        */
/*   ###################################     */

void Copia_TItemA_Para_TItemB(TItem ElemsA[], TItem ElemsB[], int n, int k) {
  int aux;
  for (int i=0; i < n; i++) {
      ElemsB[i+k].Chave = ElemsA[i].Chave;
  }
  if (k == 1) {
    ElemsB[0].Chave = 0;
  }
}
