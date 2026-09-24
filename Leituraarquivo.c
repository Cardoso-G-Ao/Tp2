#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int ano;
    int mes;
    int dia;
} Data;

Data parseData( char* s){
    Data d;
    char* partes = strtok(s,"-");
    d.ano = atoi(partes);

    partes = strtok(NULL,"-");
    d.mes = atoi(partes);
    
    partes = strtok(NULL,"-");
    d.dia = atoi(partes);
    return d;
}

void formatData(Data d , char* buffer){
    buffer[50];
    sprintf(buffer,"%d-%d-%d",d.ano,d.mes,d.dia);
}

typedef struct {
    int id;
    char marca[100];
    char modelo[100];
    int ano;
    char categoria[100];


    char combustivel[3][100];
    int quantCombustivel;


    int cilindros;
    double cilindrada;
    char transmissao[100];
    char tracao[100];
    double consumoCidade;
    double consumoEstrada;
    double co2;
    bool turbo;
    Data dataRegistro;
} Veiculo;

Veiculo*(char* s){
    Veiculo *v = (Veiculo*)malloc(sizeof(Veiculo));
    v->quantCombustivel = 0;

    char* partes = strtok(s,",");
    v->id = atoi(partes);

    partes = strtok(NULL,",");
    strcpy(v->marca,partes);

    partes = strtok(NULL,",");
    strcpy(v->modelo,partes);

    partes = strtok(NULL,",");
    v->ano = atoi(partes);

    partes = strtok(NULL,",");
    strcpy(v->categoria,partes);

    partes = strtok(NULL,",");
    strtok(v->combustivel,partes);//multivalorado

    partes = strtok(NULL,",");
    v->cilindros = atoi(partes);

    partes = strtok(NULL,",");
    v->cilindrada = atof(partes);
   
    partes = strtok(NULL,",");
    strtok(v->trasmissao,partes);

    campo = strtok(NULL, ",");
    v->consumoEstrada = atof(partes);

    campo = strtok(NULL, ",");
    v->emissaoCo2 = atof(partes);

    campo = strtok(NULL, ",");
    v->possuiTurbo = (strcmp(partes, "true") == 0);

    campo = strtok(NULL, ",");
    v->dataRegistro = parseData(partes);



    

}





int main() {
    FILE *arquivo;
    char linha[500];

    arquivo = fopen("veiculos.csv", "r");

    if (arquivo != NULL) {

        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            printf("%s", linha);
        }

        fclose(arquivo);

    } else {
        printf("Erro ao abrir o arquivo!\n");
    }

    return 0;
}