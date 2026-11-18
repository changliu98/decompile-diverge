int __cdecl ok_smul4(int x, int y, int *dest)
{
  *dest = y * x;
  return (unsigned __int64)(y * (__int64)x) >> 32 == 0;
}