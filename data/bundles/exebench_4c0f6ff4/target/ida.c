int __cdecl endGCGdata(char *s, int *addend)
{
  *addend = 0;
  return *s == 62;
}