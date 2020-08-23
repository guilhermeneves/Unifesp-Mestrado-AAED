// Copyright 2020 Unifesp
// Guilherme Neves

#ifndef DEFINICOES_H_
#define DEFINICOES_H_

// Estrutura para SplayTree

typedef struct splayTree SplayTree;
struct splayTree {
  SplayTree* left;
  int key;
  SplayTree* right;
  SplayTree* parent;
} *root;

// Estrutura para a criação das Arrays a serem ordenadas

typedef int TChave;
typedef struct {
  TChave Chave;
} TItem;

// Index para preencher o array durante o in-order traversal no SplaySort
int index_splay = 0;

void leftRotate(SplayTree *node);
void rightRotate(SplayTree *node);

SplayTree* getRoot(SplayTree **node);
void splayTreeInsert(SplayTree **splayTree, SplayTree *parent,
                     SplayTree *value);
void splayCreate(SplayTree *x);
void inorderSplayTree(SplayTree *splayTree, TItem *A);
void splaySort(SplayTree **splayTree, int size, TItem *A);

// Variáveis para controle de comparações e movimentações de funções recursivas

long long com_heap = 0, mov_heap = 0;    //  Controle HeapSort
long long com_merge = 0, mov_merge = 0;  //  Controle MergeSort
long long com_quick = 0, mov_quick = 0;  //  Controle QuickSort
long long com_splay = 0, mov_splay = 0;  //  Controle SplaySort

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

/* Função Auxiliar para Copia completa da Estrutura TItem       */
/*      Sem a necessidade de apontamento na memória.            */
/* Necessária para o reaproveitamento dos dados para novo sort. */

void Copia_TItemA_Para_TItemB(TItem ElemsA[], TItem ElemsB[], int n, int k);

#endif  // DEFINICOES_H_

