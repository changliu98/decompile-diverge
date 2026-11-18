char*** func0(int m, int n, int o)
{
 int i, j, k;
 char ***p = (char***)malloc((size_t)o * sizeof(char**));
 for (i = 0; i < o; i++) {
  p[i] = (char**)malloc((size_t)n * sizeof(char*));
  for (j = 0; j < n; j++) {
   p[i][j] = (char*)malloc((size_t)m * sizeof(char));
   for (k = 0; k < m; k++)
    p[i][j][k] = '*';
  }
 }
 return p;
}