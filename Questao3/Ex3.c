#include <stdio.h>
#define SEM_MAIN
#include "../Questao2/EstruturaVeiculos.c"

void Swap(Veiculo vetorV[], int i, int j){
    Veiculo temp = vetorV[i];
    vetorV[i] = vetorV[j];
    vetorV[j] = temp;
}


void BuscaSelecao(Veiculo *vetorV,int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int menor = i;
        for (int j = (i + 1); j < n; j++)
        {
            if (strcmp(vetorV[j].modelo, vetorV[menor].modelo) < 0){
            menor = j;
            }   
        }
        if (menor != i) {
            Swap(vetorV, i, menor);
        }
    }
}


int main() {
    int n;
    Veiculo *veiculos = lerCsv("../Questão2/veiculos.csv", &n);

    BuscaSelecao(veiculos, n);

    int id;
    char buffer[1024];

    while (scanf("%d", &id) == 1) {
        if (id == -1) {
            break;
        }
        int pos = buscaSequencial(veiculos, n, id);
        if (pos != -1) {
            formatVeiculo(veiculos[pos], buffer);
            printf("%s\n", buffer);
        }
    }

    free(veiculos);
    return 0;
}
