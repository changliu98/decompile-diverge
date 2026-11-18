int endGCGdata(char *ch, int *addend)
{
  *addend = 0;
  if(*ch == '>')
    return 1;
  return 0;
}