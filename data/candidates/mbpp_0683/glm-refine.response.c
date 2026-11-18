bool __cdecl func0(int n)
{
  int i, j;

  for (i = 1; i * i <= n; ++i)
  {
    for (j = 1; j * j <= n; ++j)
    {
      if (i * i + j * j == n)
        return true;
    }
  }
  return false;
}