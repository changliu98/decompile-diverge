void permute(int *mat)
{
  int i; int j; int temp;
  int *max; int *min;
  max = mat;
  min = mat;
  for (i = 0; i < 5; i++)
    for (j = i; j < 5; j++)
      if (*max < mat[i * 5 + j])
        max = &mat[i * 5 + j];
      if (*min > mat[i * 5 + j])
        min = &mat[i * 5 + j];
  temp = mat[12];
  mat[12] = *max;
  *max = temp;
  *min = *min;
  max = &mat[1];
  for (i = 0; i < 5; i++)
    for (j = 0; j < 5; j++)
      if ((i != 0 || j != 0) && *max > mat[i * 5 + j])
        max = &mat[i * 5 + j];
  temp = *max;
  *max = mat[4];
  mat[4] = temp;
  max = &mat[1];
  for (i = 0; i < 5; i++)
    for (j = 0; j < 5; j++)
      if ((i != 0 || j != 0) && (i != 0 || j != 4) && *max > mat[i * 5 + j])
        max = &mat[i * 5 + j];
  temp = *max;
  *max = mat[20];
  mat[20] = temp;
  max = &mat[1];
  for (i = 0; i < 5; i++)
    for (j = 0; j < 5; j++)
      if ((i != 0 || j != 0) && (i != 0 || j != 4) && (i != 4 || j != 0) && *max > mat[i * 5 + j])
        max = &mat[i * 5 + j];
  temp = *max;
  *max = mat[24];
  mat[24] = temp;
}