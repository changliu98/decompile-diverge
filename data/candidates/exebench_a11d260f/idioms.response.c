void int_to_float(void *dest, void *src)
{
  int *d = (int *) dest;
  int *s = (int *) src;
  *d = *s;
}