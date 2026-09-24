#include <stdio.h>

int main(){
    FILE *arquivo;
    char linha[100];
    arquivo = fopen("exemplo.txt", "r");

    if(arquivo != NULL){
      fgets(linha, sizeof(linha), arquivo);
      printf("Linha lida: %s", linha);
    }
    fclose(arquivo);

    return 0;
}