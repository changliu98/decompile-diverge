void __cdecl check_long(long *x, long *y, char *ret)
{
  char v3; // al

  v3 = 102;
  if ( (char *)y - (char *)x == 8 )
    v3 = 116;
  *ret = v3;
}