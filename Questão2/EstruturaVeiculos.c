#include <stdio.h>
#include <stdbool.h>
#include <string.h> 
#include <stdlib.h> 

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    int id;
    char marca[100];
    char modelo[100];
    int ano;
    char categoria[100];
    char combustivel[100][100]; 
    int quantidadeCombustiveis;
    int cilindros;
    double cilindrada;
    char transmissao[100];
    char tracao[100];
    double consumoCidade;
    double consumoEstrada;
    double emissaoCo2;
    bool possuiTurbo;
    Data dataRegistro;
} Veiculo;

Data parseData(char* s) {
    Data data;
    sscanf(s, "%d-%d-%d", &data.ano, &data.mes, &data.dia);
    return data;
}

void formatData(Data d , char* buffer){
  sprintf(buffer, "%02d/%02d/%04d", d.dia, d.mes, d.ano);
}

Veiculo *parseVeiculo(char *s) {
    Veiculo *veiculo = (Veiculo *) malloc(sizeof(Veiculo));

    char *campo = strtok(s, ",");
    veiculo->id = atoi(campo);

    campo = strtok(NULL, ",");
    strcpy(veiculo->marca, campo);

    campo = strtok(NULL, ",");
    strcpy(veiculo->modelo, campo);

    campo = strtok(NULL, ",");
    veiculo->ano = atoi(campo);

    campo = strtok(NULL, ",");
    strcpy(veiculo->categoria, campo);

    char combustivelStr[100];
    campo = strtok(NULL, ",");
    strcpy(combustivelStr, campo);

    campo = strtok(NULL, ",");
    veiculo->cilindros = atoi(campo);

    campo = strtok(NULL, ",");
    veiculo->cilindrada = atof(campo);

    campo = strtok(NULL, ",");
    strcpy(veiculo->transmissao, campo);

    campo = strtok(NULL, ",");
    strcpy(veiculo->tracao, campo);

    campo = strtok(NULL, ",");
    veiculo->consumoCidade = atof(campo);

    campo = strtok(NULL, ",");
    veiculo->consumoEstrada = atof(campo);

    campo = strtok(NULL, ",");
    veiculo->emissaoCo2 = atof(campo);

    campo = strtok(NULL, ",");
    veiculo->possuiTurbo = (strcmp(campo, "true") == 0);

    campo = strtok(NULL, ",\n");
    veiculo->dataRegistro = parseData(campo);

    veiculo->quantidadeCombustiveis = 0;
    char *combustivel = strtok(combustivelStr, ";");

    while (combustivel != NULL) {
        strcpy(veiculo->combustivel[veiculo->quantidadeCombustiveis], combustivel);
        veiculo->quantidadeCombustiveis++;
        combustivel = strtok(NULL, ";");
    }

    return veiculo;
}
void formatVeiculo(Veiculo v, char *buffer) {
    char comb[100];
    comb[0] = '\0';
    strcat(comb, "[");
    for (int i = 0; i < v.quantidadeCombustiveis; i++) {
        strcat(comb, v.combustivel[i]);
        if (i < v.quantidadeCombustiveis - 1) {
            strcat(comb, ";");
        }
    }
    strcat(comb, "]");

    char dataStr[16];
    formatData(v.dataRegistro, dataStr);

    sprintf(buffer,
            "[%d ## %s ## %s ## %d ## %s ## %s ## %d ## %.2f ## %s ## %s ## %.2f ## %.2f ## %.2f ## %s ## %s]",
            v.id, v.marca, v.modelo, v.ano, v.categoria, comb, v.cilindros,
            v.cilindrada, v.transmissao, v.tracao, v.consumoCidade,
            v.consumoEstrada, v.emissaoCo2, v.possuiTurbo ? "true" : "false", dataStr);
}


Veiculo *lerCsv(char *caminhoArquivo, int *n) {
    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", caminhoArquivo);
        *n = 0;
        return NULL;
    }

    char linha[1024];

    int total = 0;
    fgets(linha, 1024, arquivo);
    while (fgets(linha, 1024, arquivo) != NULL) {
        if (strlen(linha) > 1) {
            total++;
        }
    }

    Veiculo *veiculos = (Veiculo *) malloc(total * sizeof(Veiculo));

    rewind(arquivo);
    fgets(linha, 1024, arquivo);

    int i = 0;
    while (fgets(linha, 1024, arquivo) != NULL && i < total) {
        if (strlen(linha) > 1) {
            Veiculo *v = parseVeiculo(linha);
            veiculos[i] = *v;
            free(v);
            i++;
        }
    }

    fclose(arquivo);
    *n = total;
    return veiculos;
}

int buscaSequencial(Veiculo *veiculos, int n, int id) {
    for (int i = 0; i < n; i++) {
        if (veiculos[i].id == id) {
            return i;
        }
    }
    return -1;
}



int main() {
    int n;
    Veiculo *veiculos = lerCsv("veiculos.csv", &n);

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