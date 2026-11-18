int iset(int i, int *ip)
{
  *ip = i & ~1;
  return i;
}