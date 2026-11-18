void stb_qnorm_matrix(struct _STB_MAT *m)
{
  struct _STB_MAT *transposed = ((void *)0);
  struct _STB_MAT *sorted = ((void *)0);
  int i;
  double var;
  double *means;
  int **idx;
  int **ranks;
  int **counts;
  stb_transpose_matrix(m, &transposed);
  idx = (int **)malloc(transposed->rows * sizeof(int *));
  ranks = (int **)malloc(transposed->rows * sizeof(int *));
  counts = (int **)malloc(transposed->rows * sizeof(int *));
  for (i = 0; i < transposed->rows; i++)
    stb_didx(transposed->data[i], &idx[i], &ranks[i], &counts[i], transposed->columns);
  means = (double *)malloc(m->rows * sizeof(double));
  stb_transpose_matrix(transposed, &sorted);
  stb_free_matrix(transposed);
  for (i = 0; i < sorted->rows; i++)
    stb_meanvar(sorted->data[i], sorted->columns, &means[i], &var);
  stb_free_matrix(sorted);
  for (i = 0; i < m->columns; i++)
  {
    int j;
    for (j = 0; j < m->rows; j++)
    {
      int k;
      m->data[idx[i][j]][i] = 0.0;
      for (k = 0; k < counts[i][ranks[i][j]]; k++)
        m->data[idx[i][j]][i] += means[ranks[i][j] + k];
      m->data[idx[i][j]][i] /= (double)counts[i][ranks[i][j]];
    }
  }
  for (i = 0; i < m->columns; i++)
  {
    free(idx[i]);
    free(ranks[i]);
    free(counts[i]);
  }
  free(idx);
  free(ranks);
  free(counts);
  free(means);
}