int replace(char *str, char what, char to)
{
  char *p1;
  p1 = str;
  while( (p1 = strchr(p1, what)) != NULL )
    {
      *p1 = to;
      p1++;
    }
  return 0;
}