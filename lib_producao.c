#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib_producao.h"

#define MAX_LINE 1024

//Função para tratar a entrada e preparar os dados
void trata_entrada(FILE *entrada, int *n, int *m, double **v, double **p, double **q, double ***c, double **lucro_por_produto) {
    char buffer[MAX_LINE];

    //Leitura de n e m
    if (fgets(buffer, MAX_LINE, entrada)) {
        sscanf(buffer, "%d %d", n, m);
    } else {
        fprintf(stderr, "Erro ao ler arquivo.\n");
        exit(EXIT_FAILURE);
    }

    *v = malloc(*n * sizeof(double));
    *p = malloc(*m * sizeof(double));
    *q = malloc(*m * sizeof(double));
    *c = malloc(*n * sizeof(double *));
    *lucro_por_produto = malloc(*n * sizeof(double));

    for (int i = 0; i < *n; i++) {
        (*c)[i] = malloc(*m * sizeof(double));
    }

    //Leitura dos valores de venda
    if (fgets(buffer, MAX_LINE, entrada)) {
        char *token = strtok(buffer, " ");
        for (int i = 0; i < *n; i++) {
            (*v)[i] = atof(token);
            token = strtok(NULL, " ");
        }
    } else {
        fprintf(stderr, "Erro ao ler valores de venda.\n");
        exit(EXIT_FAILURE);
    }

    //Leitura dos custos e limites de produção
    for (int j = 0; j < *m; j++) {
        if (fgets(buffer, MAX_LINE, entrada)) {
            sscanf(buffer, "%lf %lf", &(*p)[j], &(*q)[j]);
        } else {
            fprintf(stderr, "Erro ao ler custos e limites.\n");
            exit(EXIT_FAILURE);
        }
    }

    //Leitura das proporções de compostos
    for (int i = 0; i < *n; i++) {
        if (fgets(buffer, MAX_LINE, entrada)) {
            char *token = strtok(buffer, " ");
            for (int j = 0; j < *m; j++) {
                (*c)[i][j] = atof(token);
                token = strtok(NULL, " ");
            }
        } else {
            fprintf(stderr, "Erro ao ler proporções de compostos.\n");
            exit(EXIT_FAILURE);
        }
    }

    //Calcula o lucro de cada produto
    for (int i = 0; i < *n; i++){
        (*lucro_por_produto)[i] = (*v)[i];
        for (int j = 0; j < *m; j++){
            (*lucro_por_produto)[i] -= (*p)[j] * (*c)[i][j];
        }
    }
}

//Função para gerar a saída no formato lp_solve
void gerar_lp_solve(int n, int m, double *v, double *p, double *q, double **c, double *lucro_por_produto) {
    //Função objetivo
    printf("max: ");
    for (int i = 0; i < n; i++) {
        printf("%s%.2lfx%d", i > 0 ? " + " : "", lucro_por_produto[i], i + 1);
    }
    printf(";\n");

    //Restrições de limite de compostos
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            printf("%s%.2lfx%d", i > 0 ? " + " : "", c[i][j], i + 1);
        }
        printf(" <= %.2lf;\n", q[j]);
    }

    //Restrições de não negatividade
    for (int i = 0; i < n; i++) {
        printf("x%d >= 0;\n", i + 1);
    }
}

void libera_memoria(double *v, double *p, double *q, double **c, double *lucro_por_produto, int n) {
    if (v != NULL) {
        free(v);
    }
    if (p != NULL) {
        free(p);
    }
    if (q != NULL) {
        free(q);
    }
    if (c != NULL) {
        for (int i = 0; i < n; i++) {
            if (c[i] != NULL) {
                free(c[i]);
            }
        }
        free(c);
    }
}
