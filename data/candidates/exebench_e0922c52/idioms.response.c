void outfname(char *name)
{
  char *p = name;
  while(*p != '\0')
    p++;
  *(--p) = 's';
  return;
}