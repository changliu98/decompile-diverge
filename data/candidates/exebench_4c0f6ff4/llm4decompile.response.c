int endGCGdata(char *s, int *addend)
{
  *addend = 0;
  if (*s == '>')
    return 1;
  else
    return 0;
}