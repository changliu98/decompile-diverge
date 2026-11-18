int get_hashmask(int *size)
{
  int tsize = 1;
  while (tsize < *size)
    tsize *= 2;
  *size = tsize;
  return tsize - 1;
}