void __cdecl stb_qnorm_matrix(STB_MAT *original)
{
  double *v1; // rax
  double *v2; // rax
  int i_2; // [rsp+4h] [rbp-5Ch]
  int j; // [rsp+8h] [rbp-58h]
  int n; // [rsp+Ch] [rbp-54h]
  int i_1; // [rsp+10h] [rbp-50h]
  int i_0; // [rsp+14h] [rbp-4Ch]
  STB_MAT *sorted; // [rsp+18h] [rbp-48h] BYREF
  double var; // [rsp+20h] [rbp-40h] BYREF
  double *means; // [rsp+28h] [rbp-38h]
  int i; // [rsp+34h] [rbp-2Ch]
  int **idx; // [rsp+38h] [rbp-28h]
  int **counts; // [rsp+40h] [rbp-20h]
  int **ranks; // [rsp+48h] [rbp-18h]
  STB_MAT *transposed; // [rsp+50h] [rbp-10h] BYREF
  STB_MAT *originala; // [rsp+58h] [rbp-8h]

  originala = original;
  transposed = 0LL;
  stb_transpose_matrix(original, &transposed);
  ranks = (int **)malloc(8LL * originala->columns);
  counts = (int **)malloc(8LL * originala->columns);
  idx = (int **)malloc(8LL * originala->columns);
  for ( i = 0; i < transposed->rows; ++i )
    stb_didx(transposed->data[i], &idx[i], &ranks[i], &counts[i], transposed->columns);
  means = (double *)malloc(8LL * originala->rows);
  sorted = 0LL;
  stb_transpose_matrix(transposed, &sorted);
  stb_free_matrix(transposed);
  for ( i_0 = 0; i_0 < sorted->rows; ++i_0 )
    stb_meanvar(sorted->data[i_0], sorted->columns, &means[i_0], &var);
  stb_free_matrix(sorted);
  for ( i_1 = 0; i_1 < originala->columns; ++i_1 )
  {
    for ( n = 0; n < originala->rows; ++n )
    {
      originala->data[idx[i_1][n]][i_1] = 0.0;
      for ( j = 0; j < counts[i_1][ranks[i_1][n]]; ++j )
      {
        v1 = originala->data[idx[i_1][n]];
        v1[i_1] = means[j + ranks[i_1][n]] + v1[i_1];
      }
      v2 = originala->data[idx[i_1][n]];
      v2[i_1] = v2[i_1] / (double)counts[i_1][ranks[i_1][n]];
    }
  }
  for ( i_2 = 0; i_2 < originala->columns; ++i_2 )
  {
    free(idx[i_2]);
    free(ranks[i_2]);
    free(counts[i_2]);
  }
  free(idx);
  free(ranks);
  free(counts);
  free(means);
}