#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
    buffer[100];
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

Veiculo* parseVeiculo(char* s){
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

    char *token = strtok(s, ";");
    while(token != NULL){
        strcpy(v->combustivel[v->quantCombustivel], token);
        v->quantCombustivel++;
    }

    partes = strtok(NULL,",");
    v->cilindros = atoi(partes);

    partes = strtok(NULL,",");
    v->cilindrada = atof(partes);

    partes = strtok(NULL,",");
    strtok(v->transmissao,partes);

    partes = strtok(NULL, ",");
    v->consumoEstrada = atof(partes);

    partes = strtok(NULL, ",");
    v->co2 = atof(partes);

    partes = strtok(NULL, ",");
    v->turbo = (strcmp(partes, "true") == 0);

    partes = strtok(NULL, ",");
    v->dataRegistro = parseData(partes);



    return v;
}



void formatVeiculo(Veiculo v , char* buffer){
buffer[100];
sprintf(buffer,"%d,%s,%s,%d,%s,%s,%d,%d,%f,%s,%s,%f,%f,%f,%s,%02d-%02d-%02d",
        v.id,
        v.marca,
        v.modelo,
        v.ano,
        v.categoria,
        v.combustivel,
        v.quantCombustivel,
        v.cilindros,
        v.cilindrada,
        v.transmissao,
        v.tracao,
        v.consumoCidade,
        v.consumoEstrada,
        v.co2,
        v.turbo ? true: false,
        v.dataRegistro.dia,
        v.dataRegistro.mes,
        v.dataRegistro.ano);
}

Veiculo** lerCsv(char* caminhoArquivo , int* n ){
    FILE *arquivo;
    char linhas[500];
    int quant = 0 ;
    Veiculo **v = (Veiculo**)malloc(510 * sizeof(Veiculo*));
    arquivo = fopen(caminhoArquivo,"r");
    if(arquivo == NULL){
        printf("erro");
    }
    else{
        while(fgets(linhas, sizeof(linhas), stdin) != NULL){
            if(linhas[0] != '\0'){
            v[quant] = parseVeiculo(linhas);
            quant++;    
            }
        }
    }
    *n = quant;
    return v;
}


int main() {
    int *yes;
    Veiculo **v = lerCsv("veiculos.csv",yes);

    

    while(id != -1){
        if(id = v.id){

        }
    }
    
    
    

    return 0;
}