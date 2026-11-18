void get_type(void *x, void *y, char *type)
{
  *type = 'f';
  if (y - x == sizeof(double))
    *type = 't';
}