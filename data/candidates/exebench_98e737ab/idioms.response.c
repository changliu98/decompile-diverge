void uint_to_double(void *dest, void *src)
{
  int *d = (int *) dest;
  int *s = (int *) src;
  *d = (int) *s;
}