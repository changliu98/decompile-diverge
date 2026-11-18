char *itoa(unsigned long v, char *string, int r, int is_neg)
{
  char buf[-1];
  char *start = string;
  char *p = buf;
  do
  {
    *p++ = a0123456789abcd[(v % r) & 15];
  } while (v /= r);
  if (is_neg)
    *p++ = '-';
  do
  {
    *string++ = *(--p);
  } while (buf != p);
  *string = '\0';
  return start;
}