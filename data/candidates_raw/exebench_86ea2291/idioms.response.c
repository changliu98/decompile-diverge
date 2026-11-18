void *val_dtor(void *val)
{
  int *i = (int *)val;
  if (i)
    --*i;
  return ((void *)0);
}