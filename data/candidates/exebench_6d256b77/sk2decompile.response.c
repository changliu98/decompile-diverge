float Intersect(float *matrix, int i, int j, int n) {
  int k;
  float intersect = 0.0;
  float n1 = 0.0;
  float n2 = 0.0;
  for (k = 0; k < n; k++) {
    if (matrix[i * n + k] == 1.0 && matrix[j * n + k] == 1.0) intersect++;
    if (matrix[i * n + k] == 1.0) n1++;
    if (matrix[j * n + k] == 1.0) n2++;
  }
  if (n1 < n2)
    return intersect / n1;
  else
    return intersect / n2;
}