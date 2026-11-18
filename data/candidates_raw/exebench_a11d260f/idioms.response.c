void copy_int(void *dest, void *src)
{
  int *d = (int *) dest;
  int *s = (int *) src;
  *d = *s;
}