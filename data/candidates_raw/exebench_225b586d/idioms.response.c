int is_end(char *s, int *addend)
{
  *addend = 0;
  return s[0] == '>';
}