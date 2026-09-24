#include <stdio.h>

int main() {
    FILE *arquivo;
    char nome[50];

  
    printf("Digite um nome: ");
    scanf("%49s", nome); 

  
    arquivo = fopen("exemplo.txt", "w");

    
    if (arquivo != NULL) {
        
        fprintf(arquivo, "%s\n", nome); 
        
        fclose(arquivo); 
        printf("Nome gravado com sucesso no arquivo!\n");
    } else {
        printf("Erro ao criar/abrir o arquivo!\n");
    }

    return 0;
}