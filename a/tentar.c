#include <stdio.h>

void swap(int vetor[], int a, int b) {
    int temp = vetor[a];
    vetor[a] = vetor[b];
    vetor[b] = temp;
}

int main() {
    int n = 5;
    // Vetor desordenado para ver as trocas a cada linha
    int vetor[] = {95, 70, 45, 20, 5};

    for (int i = 0; i < n - 1; i++) {
        int menor = i;

        for (int j = i + 1; j < n; j++) {
            if (vetor[j] < vetor[menor]) {
                menor = j;
            }
        }

        // Troca o menor elemento encontrado com a posição i
        swap(vetor, menor, i);

        // Imprime o estado do vetor após esta rodada
        printf("Vetor ordenado: ");
        for (int k = 0; k < n; k++) {
            printf("%d ", vetor[k]);
        }
        printf("\n");
    }

    return 0;
}