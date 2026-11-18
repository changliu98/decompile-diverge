void stb_qnorm_matrix(STB_MAT *original)

{
  int i_3;
  int j;
  int n;
  int i_2;
  int i_1;
  STB_MAT *sorted;
  double var;
  double *means;
  int i;
  int **idx;
  int **counts;
  int **ranks;
  STB_MAT *transposed;
  STB_MAT *original_local;
  
  transposed = (STB_MAT *)0x0;
  original_local = original;
  stb_transpose_matrix(original,&transposed);
  ranks = malloc((long)original_local->columns << 3);
  counts = malloc((long)original_local->columns << 3);
  idx = malloc((long)original_local->columns << 3);
  for (i = 0; i < transposed->rows; i = i + 1) {
    stb_didx(transposed->data[i],idx + i,ranks + i,counts + i,transposed->columns);
  }
  means = malloc((long)original_local->rows << 3);
  sorted = (STB_MAT *)0x0;
  stb_transpose_matrix(transposed,&sorted);
  stb_free_matrix(transposed);
  for (i_1 = 0; i_1 < sorted->rows; i_1 = i_1 + 1) {
    stb_meanvar(sorted->data[i_1],sorted->columns,means + i_1,&var);
  }
  stb_free_matrix(sorted);
  for (i_2 = 0; i_2 < original_local->columns; i_2 = i_2 + 1) {
    for (n = 0; n < original_local->rows; n = n + 1) {
      original_local->data[idx[i_2][n]][i_2] = 0.0;
      for (j = 0; j < counts[i_2][ranks[i_2][n]]; j = j + 1) {
        original_local->data[idx[i_2][n]][i_2] =
             means[ranks[i_2][n] + j] + original_local->data[idx[i_2][n]][i_2];
      }
      original_local->data[idx[i_2][n]][i_2] =
           original_local->data[idx[i_2][n]][i_2] / (double)counts[i_2][ranks[i_2][n]];
    }
  }
  for (i_3 = 0; i_3 < original_local->columns; i_3 = i_3 + 1) {
    free(idx[i_3]);
    free(ranks[i_3]);
    free(counts[i_3]);
  }
  free(idx);
  free(ranks);
  free(counts);
  free(means);
  return;
}