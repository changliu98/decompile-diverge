void __cdecl squeeze(char *s1, char *s2)
{
  int i, j, k;
  int contains;

  i = 0;
  k = 0;
  while (s1[i])
  {
    contains = 0;
    for (j = 0; s2[j]; ++j)
    {
      if (s1[i] == s2[j])
        contains = 1;
    }
    
    if (!contains)
    {
      s1[k++] = s1[i];
    }
    ++i;
  }
  s1[k] = '\0';
}