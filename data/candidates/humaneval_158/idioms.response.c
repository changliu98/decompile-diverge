char *func0(char **words, int count)
{
  int i;
  int j;
  int unique_count;
  int maxu;
  char *max;
  char unique[256];
  char **wordsa = words;
  int counta = count;
  max = "";
  maxu = 0;
  for (i = 0; i < counta; i++)
  {
    memset(unique, '\0', sizeof(unique));
    unique_count = 0;
    for (j = 0; wordsa[i][j] != '\0'; j++)
    {
      if (strchr(unique, wordsa[i][j]) == ((void *)0))
      {
        int len = strlen(unique);
        unique[len] = wordsa[i][j];
        unique[len + 1] = '\0';
        unique_count++;
      }
    }
    if (unique_count > maxu || (unique_count == maxu && strcmp(wordsa[i], max) < 0))
    {
      max = wordsa[i];
      maxu = unique_count;
    }
  }
  return max;
}