void *decrement_value(void *val)
{
  int *i = (int *)val;
  if (i)
    --*i;
  return ((void *)0);
}