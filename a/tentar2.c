#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[100];
    int idade;
} Pessoa;

void swap(Pessoa vetor[], int a, int b) {
    Pessoa temp = vetor[a];
    vetor[a] = vetor[b];
    vetor[b] = temp;
}


int main(){
    int n = 4;
    Pessoa pessoa[4] = {{"Carla", 25},
        {"Alice", 20},
        {"Eduardo", 40},
        {"Bruno", 30}
    };
    for(int i = 0 ; i < n-1; i++){
        int menor = i;
    for(int j = (i+1); j < n ; j++ ){
        if(strcmp(pessoa[j].nome,  pessoa[menor].nome) < 0)
            menor = j;
    }    
    swap(pessoa, menor, i);
    printf("Vetor ordenado: ");
        for (int k = 0; k < n; k++) {
            printf("%s%d  ", pessoa[k].nome,pessoa[k].idade);
        }
        printf("\n");
}
    

    return 0;
}