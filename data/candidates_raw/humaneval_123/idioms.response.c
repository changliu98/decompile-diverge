void get_collatz_sequence(int n, int *out, int *size)
{
  int *outp = out;
  int capacity = 10;
  int i;
  int j;
  int temp;
  int insert;
  *size = 1;
  outp[0] = 1;
  while (n != 1)
  {
    if (n % 2 == 0)
    {
      n = n / 2;
    }
    else
    {
      if (*size >= capacity)
      {
        capacity = capacity * 2;
        outp = (int *) realloc(outp, capacity * sizeof(int));
      }
      outp[(*size)++] = n;
      n = n * 3 + 1;
    }
  }
  for (i = 1; i < *size; i++)
  {
    temp = outp[i];
    for (j = i - 1; (insert = (j >= 0 && outp[j] > temp)); j--)
    {
      outp[j + 1] = outp[j];
    }
    outp[j + 1] = temp;
  }
}