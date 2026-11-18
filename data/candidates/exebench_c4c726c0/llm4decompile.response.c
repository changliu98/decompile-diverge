void check_long(long *a, long *b, char *ret)
{
  if (b - a == 1)
    *ret = 't';
  else
    *ret = 'f';
}