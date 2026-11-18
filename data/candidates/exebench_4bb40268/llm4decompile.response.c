void check_int(void *x, void *y, char *ret)
{
  int *xx = (int *)x;
  int *yy = (int *)y;

  if (yy - xx == 1)
    *ret = 't';
  else
    *ret = 'f';
}