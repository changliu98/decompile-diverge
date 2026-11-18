int lps(char *seq)
{
  int i, j;
  int n = strlen(seq);
  int L[n+1][n+1];

  for (i = 0; i <= n; i++)
    for (j = 0; j <= n; j++)
      L[i][j] = 0;

  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++)
      if (seq[i-1] == seq[j-1] && i != j)
        L[i][j] = L[i-1][j-1] + 1;
      else
        L[i][j] = ((L[i-1][j] > L[i][j-1]) ? (L[i-1][j]) : (L[i][j-1]));

  return L[n][n];
}