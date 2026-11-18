int lcslen(int *seqa, int n)
{
  int *seqb = (int *) (seqa);
  int i; int j; int k;
  int *len;
  int maxlen;
  len = (int *) ( (char *) (len) - ( (char *) ( &len[n - 1]) - ( char *) (len)) );
  len[n - 1] = 1;
  for (i = n - 2; i >= 0; i--)
  {
    maxlen = 0;
    for (j = i + 1; j < n; j++)
    {
      if (seqa[j] % seqa[i] == 0 || seqa[i] % seqa[j] == 0)
      {
        if (len[j] > maxlen)
        {
          maxlen = len[j];
        }
      }
    }
    len[i] = maxlen + 1;
  }
  maxlen = len[0];
  for (i = 1; i < n; i++)
  {
    if (len[i] > maxlen)
    {
      maxlen = len[i];
    }
  }
  return (maxlen);
}