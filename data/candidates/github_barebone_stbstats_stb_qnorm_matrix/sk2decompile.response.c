void stb_qnorm_matrix(stb_matrix *m) {
  int i, j, k, l;
  stb_matrix *mt = NULL;
  stb_transpose_matrix(m, &mt);
  int **didx = (int **)malloc(m->ncol * sizeof(int *));
  int **dlen = (int **)malloc(m->ncol * sizeof(int *));
  int **dpos = (int **)malloc(m->ncol * sizeof(int *));
  for (i = 0; i < mt->nrow; i++) {
    stb_didx(mt->col[i], &dpos[i], &didx[i], &dlen[i], mt->ncol);
  }
  double *mean = (double *)malloc(m->nrow * sizeof(double));
  stb_matrix *mt2 = NULL;
  stb_transpose_matrix(mt, &mt2);
  stb_free_matrix(mt);
  double var;
  for (i = 0; i < mt2->nrow; i++) {
    stb_meanvar(mt2->col[i], mt2->ncol, &mean[i], &var);
  }
  stb_free_matrix(mt2);
  for (i = 0; i < m->ncol; i++) {
    for (j = 0; j < m->nrow; j++) {
      m->col[dpos[i][j]][i] = 0.0;
      for (k = 0; k < dlen[i][didx[i][j]]; k++) {
        m->col[dpos[i][j]][i] += mean[k + didx[i][j]];
      }
      m->col[dpos[i][j]][i] /= dlen[i][didx[i][j]];
    }
  }
  for (l = 0; l < m->ncol; l++) {
    free(dpos[l]);
    free(didx[l]);
    free(dlen[l]);
  }
  free(dpos);
  free(didx);
  free(dlen);
  free(mean);
}