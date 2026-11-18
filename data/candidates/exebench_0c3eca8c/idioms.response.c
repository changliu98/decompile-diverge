void expand(char *compacted, char *expanded)
{
  int i; int j;
  if (compacted[0] >= '0' && compacted[0] <= '9' && compacted[2] >= '0' && compacted[2] <= '9' && compacted[0] <= compacted[2])
  {
    for (i = compacted[0], j = 0; i <= compacted[2]; i++)
    {
      expanded[j] = i;
      j++;
    }
    expanded[j] = '\0';
  }
  else if (compacted[0] >= 'A' && compacted[0] <= 'Z' && compacted[2] >= 'A' && compacted[2] <= 'Z' && compacted[0] <= compacted[2])
  {
    for (i = compacted[0], j = 0; i <= compacted[2]; i++)
    {
      expanded[j] = i;
      j++;
    }
    expanded[j] = '\0';
  }
  else if (compacted[0] >= 'a' && compacted[0] <= 'z' && compacted[2] >= 'a' && compacted[2] <= 'z' && compacted[0] <= compacted[2])
  {
    for (i = compacted[0], j = 0; i <= compacted[2]; i++)
    {
      expanded[j] = i;
      j++;
    }
    expanded[j] = '\0';
  }
  return;
}