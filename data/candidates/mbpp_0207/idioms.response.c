int func0(char *s)
{
  int i; int j;
  int n = strlen(s);
  int lcs[-1][-1];
  for (i = 0; i <= n; i++)
    for (j = 0; j <= n; j++)
      lcs[i][j] = 0;
  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++)
      if (s[i - 1] == s[j - 1] && i != j)
        lcs[i][j] = lcs[i - 1][j - 1] + 1;
      else
        lcs[i][j] = lcs[i - 1][j] > lcs[i][j - 1] ? lcs[i - 1][j] : lcs[i][j - 1];
  return lcs[n][n];
}