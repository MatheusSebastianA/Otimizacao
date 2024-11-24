#ifndef lib_producao
#define lib_producao

void trata_entrada(FILE *entrada, int *n, int *m, double **v, double **p, double **q, double ***c, double **lucro_por_produto);
 
void gerar_lp_solve(int n, int m, double *v, double *p, double *q, double **c, double *lucro_por_produto);

void libera_memoria(double *v, double *p, double *q, double **c, double *lucro_por_produto, int n);

#endif /* lib_producao */