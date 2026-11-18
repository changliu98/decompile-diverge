void __cdecl check_long(long *x, long *y, char *ret)
{
  *ret = ((char *)y - (char *)x == 8) ? 116 : 102;
}