int func0(int n, int a, int b, int c)
{
  int i; int j;
  int *mem;
  int *ptr;
  int max;
  int *p = (int *) ( ( ( ( (sizeof(int)) * (n + 10)) + (sizeof(int) - 1)) & (~ (sizeof(int) - 1)) ) );
  mem = p - (n + 10);
  for (i = 0; i < n + 10; i++)
    mem[i] = -1;
  mem[0] = 0;
  for (j = 0; j <= n; j++)
  {
    if (mem[j] != -1)
    {
      if (j + a <= n)
      {
        if (mem[j] + 1 > mem[j + a])
          max = mem[j] + 1;
        else
          max = mem[j + a];
        mem[j + a] = max;
      }
      if (j + b <= n)
      {
        if (mem[j] + 1 > mem[j + b])
          max = mem[j] + 1;
        else
          max = mem[j + b];
        mem[j + b] = max;
      }
      if (j + c <= n)
      {
        if (mem[j] + 1 > mem[j + c])
          max = mem[j] + 1;
        else
          max = mem[j + c];
        mem[j + c] = max;
      }
    }
  }
  return mem[n];
}