int ok_smul4 (int x, int y, int *dest)
{
  int tmp = (int) ((long long) x * (long long) y);
  *dest = tmp;
  return *dest == tmp;
}