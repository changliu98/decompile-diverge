int func0(int n)
{
  int i, sm = 0;
  for (i = 1; i <= n; i++)
    sm += (2*i-1)*(2*i-1)*(2*i-1)*(2*i-1)*(2*i-1);
  return sm;
}