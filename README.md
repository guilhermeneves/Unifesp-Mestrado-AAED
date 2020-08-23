# Unifesp - Mestrado - Análise de Algoritmos e Estruturas de Dados (AAED)
Proposta de trabalho para disciplina AAED na Unifesp SJC.
Análise de desempenho de algoritmos de ordenação em diferentes cenários.

## Descriçao
A análise do algoritmo será dividida em duas partes. A primeira parte refere-se a análise assintótica
do algoritmo SplaySort. Na segunda, a análise consistirá em comparar o algoritmo com os seguintes competidores:
InsertionSort, SelectionSort, BubbleSort, HeapSort, MergeSort e QuickSort.
## Como gerar os arranjos
Considere arranjos (vetores) com diferentes quantidades de elementos (10, 100, 1.000, 10.000,
100.000, 1.000.000). Considere também arranjos sem valores repetidos. Considere ainda que todos
os elementos dos arranjos correspondem a valores inteiros e, para gerar os arranjos iniciais, utilize:
(i) arranjos ordenados, (ii) inversamente ordenados, (iii) quase ordenados e (iv ) aleatórios.
## O que analisar
A análise assintótica deve ser feita sobre o número de comparações de chaves e o número de
movimentações de registros. Três métricas de desempenho deverão ser consideradas na comparação
com outros algoritmos: (i) número de comparações de chaves, (ii) nímero de movimentações de
registros e (iii) tempo total gasto para ordenação (tempo de processamento e não o tempo de
relógio). 

## Implementação

#### Compilar utilizando GCC 
```sudo gcc -o p1_code Implementacoes.c```

#### Exemplos de Execução

Executa todos os sorts para um Array de 10 posições quase ordenado:

```./p1_code 10 4```

Executa todos os sorts para um Array de 100000 posições aleatórias:

```./p1_code 100000 1```
