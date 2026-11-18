int lcs(char *str)
{
  int len = strlen(str);
  int table[-1][-1];
  int i; int j; int k;
  for (i = 0; i < len; i++)
    table[i][i] = 1;
  for (k = 2; k <= len; k++)
  {
    for (i = 0; i < len - k + 1; i++)
    {
      j = i + k - 1;
      if (str[i] == str[j] && k == 2)
        table[i][j] = 2;
      else if (str[i] == str[j])
        table[i][j] = table[i + 1][j] + 2;
      else
      {
        if (table[i][j - 1] > table[i + 1][j])
          table[i][j] = table[i][j - 1];
        else
          table[i][j] = table[i + 1][j];
      }
    }
  }
  return table[0][len - 1];
}