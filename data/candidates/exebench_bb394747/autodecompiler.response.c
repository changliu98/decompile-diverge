int get_hashmask (int x)
{
  int res = 1;
  while (1)
    {
      if (res >= x)
        {
          x = res;
          break;
        }
      res *= 2;
    }
  return x - 1;
}