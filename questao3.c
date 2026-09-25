#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int ano;
    int mes;
    int dia;
} Data;

Data parseData(char *s) {
    Data d;
    char *partes = strtok(s, "-");
    d.ano = atoi(partes);

    partes = strtok(NULL, "-");
    d.mes = atoi(partes);

    partes = strtok(NULL, "-");
    d.dia = atoi(partes);

    return d;
}

void formatData(Data d, char *buffer) {
    sprintf(buffer, "%02d/%02d/%04d", d.dia, d.mes, d.ano);
}

typedef struct {
    int id;
    char marca[100];
    char modelo[100];
    int ano;
    char categoria[100];
    char combustivel[5][100];
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

Veiculo *parseVeiculo(char *s) {
    Veiculo *v = (Veiculo *) malloc(sizeof(Veiculo));

    char *partes = strtok(s, ",");
    v->id = atoi(partes);

    partes = strtok(NULL, ",");
    strcpy(v->marca, partes);

    partes = strtok(NULL, ",");
    strcpy(v->modelo, partes);

    partes = strtok(NULL, ",");
    v->ano = atoi(partes);

    partes = strtok(NULL, ",");
    strcpy(v->categoria, partes);

    char combustivelStr[100];
    partes = strtok(NULL, ",");
    strcpy(combustivelStr, partes);

    partes = strtok(NULL, ",");
    v->cilindros = atoi(partes);

    partes = strtok(NULL, ",");
    v->cilindrada = atof(partes);

    partes = strtok(NULL, ",");
    strcpy(v->transmissao, partes);

    partes = strtok(NULL, ",");
    strcpy(v->tracao, partes);

    partes = strtok(NULL, ",");
    v->consumoCidade = atof(partes);

    partes = strtok(NULL, ",");
    v->consumoEstrada = atof(partes);

    partes = strtok(NULL, ",");
    v->co2 = atof(partes);

    partes = strtok(NULL, ",");
    v->turbo = (strcmp(partes, "true") == 0);

    partes = strtok(NULL, ",\n");
    v->dataRegistro = parseData(partes);

    v->quantCombustivel = 0;
    char *token = strtok(combustivelStr, ";");
    while (token != NULL) {
        strcpy(v->combustivel[v->quantCombustivel], token);
        v->quantCombustivel++;
        token = strtok(NULL, ";");
    }

    return v;
}

void formatVeiculo(Veiculo v, char *buffer) {
    char comb[100];
    comb[0] = '\0';
    strcat(comb, "[");
    for (int i = 0; i < v.quantCombustivel; i++) {
        strcat(comb, v.combustivel[i]);
        if (i < v.quantCombustivel - 1) {
            strcat(comb, ",");
        }
    }
    strcat(comb, "]");

    char dataStr[16];
    formatData(v.dataRegistro, dataStr);

    sprintf(buffer,
            "[%d ## %s ## %s ## %d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %.2f ## %.2f ## %.1f ## %s ## %s]",
            v.id, v.marca, v.modelo, v.ano, v.categoria, comb, v.cilindros,
            v.cilindrada, v.transmissao, v.tracao, v.consumoCidade,
            v.consumoEstrada, v.co2, v.turbo ? "true" : "false", dataStr);
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

void swap(Veiculo *v,int a, int b)
{
    Veiculo temp = v[a];
    v[a] = v[b];
    v[b] = temp;
}

void selecao(Veiculo *v, int n){

    for (int i = 0; i < (n - 1); i++)
    {
        int menor = i;
        for (int j = (i + 1); j < n; j++)
        {
            if (v[j].modelo < v[menor].modelo)
            {
                menor = j;
            }
        }
        swap(v, menor, i);
    }
}
int main(){
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