void __cdecl check_int(int *x, int *y, char *ret)
{
  char v3; // al

  v3 = 102;
  if ( (char *)y - (char *)x == 4 )
    v3 = 116;
  *ret = v3;
}