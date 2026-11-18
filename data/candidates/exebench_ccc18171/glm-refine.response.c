int __cdecl ok_smul4(int x, int y, int *dest)
{
  *dest = x * y;
  return ((long long)x * y) >> 32 == 0;
}