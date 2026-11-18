void stb_qnorm_matrix(STB_MAT *original)
{
   int i,j,k,n;
   STB_MAT *transposed = NULL;
   stb_transpose_matrix(original, &transposed);


   int **idx = (int **) malloc(original->columns * sizeof(int *));
   int **counts = (int **) malloc(original->columns * sizeof(int *));
   int **ranks = (int **) malloc(original->columns * sizeof(int *));
   for (i=0; i < transposed->rows; ++i)
      stb_didx(transposed->data[i], &idx[i], &ranks[i], &counts[i], transposed->columns);


   double *means = (double *) malloc(original->rows * sizeof(double));
   double var;
   STB_MAT *sorted = NULL;
   stb_transpose_matrix(transposed, &sorted);
   stb_free_matrix(transposed);
   for (i=0; i < sorted->rows; ++i)
      stb_meanvar(sorted->data[i], sorted->columns, &means[i], &var);
   stb_free_matrix(sorted);


   for (j=0; j < original->columns; ++j) {
      for (n=0; n < original->rows; ++n) {
         original->data[idx[j][n]][j] = 0;
         for (k=0; k < counts[j][ranks[j][n]]; ++k)
            original->data[idx[j][n]][j] += means[ranks[j][n]+k];
         original->data[idx[j][n]][j] /= (double) counts[j][ranks[j][n]];
      }
   }


   for (i=0; i < original->columns; ++i) {
      free(idx[i]);
      free(ranks[i]);
      free(counts[i]);
   }
   free(idx);
   free(ranks);
   free(counts);
   free(means);
}