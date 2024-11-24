#include <stdio.h>
#include <stdlib.h>
#include "lib_producao.h"

int main() {
    int n, m;
    double *v = NULL, *p = NULL, *q = NULL, **c = NULL, *lucro_por_produto = NULL;

    // Processar entrada
    trata_entrada(stdin, &n, &m, &v, &p, &q, &c, &lucro_por_produto);

    // Gerar saída
    gerar_lp_solve(n, m, v, p, q, c, lucro_por_produto);

    // Liberação de memória
    libera_memoria(v, p, q, c, lucro_por_produto, n);

    return 0;
}

