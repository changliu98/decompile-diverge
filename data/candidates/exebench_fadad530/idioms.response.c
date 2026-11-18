void ToIUPAC(char *seq, int is_aseq)
{
  if (is_aseq)
  {
    while (*seq != '\0')
    {
      if (strchr("ACGTUNRYMKSWHBVDacgtunrymkswhbvd", *seq) == ((void *)0) &&
          *seq != ' ' &&
          *seq != '.' &&
          *seq != '_' &&
          *seq != '-' &&
          *seq != '~')
      {
        *seq = 'N';
      }
      seq++;
    }
  }
  else
  {
    while (*seq != '\0')
    {
      if (strchr("ACGTUNRYMKSWHBVDacgtunrymkswhbvd", *seq) == ((void *)0))
      {
        *seq = 'N';
      }
      seq++;
    }
  }
}