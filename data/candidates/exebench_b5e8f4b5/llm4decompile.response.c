char *convert_set_base(char *s, int *base)
{
 *base = 10;
 if (s && *s == '0') {
  ++s;
  if (*s == 'x' || *s == 'X') {
   *base = 16;
   ++s;
  }
 }
 return s;
}