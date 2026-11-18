int func0(const int *coin, int m, int n) {
 int i, j;
 int possibilities[n+1][m+1];

 for (i = 0; i <= n; i++) {
  for (j = 0; j <= m; j++) {
   possibilities[i][j] = 0;
  }
 }

 for (i = 1; i <= n; i++) {
  for (j = 1; j <= m; j++) {

   possibilities[i][j] = possibilities[i][j-1];

   if (coin[j-1] <= i && coin[j-1] > 0) {
    possibilities[i][j] += possibilities[(i-coin[j-1])/coin[j-1]][j-1] + 1;
   }
  }
 }

 return possibilities[n][m];
}