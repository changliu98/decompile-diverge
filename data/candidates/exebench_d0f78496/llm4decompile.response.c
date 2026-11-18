char *read_int(char *s, int nr, int *d)
{
 int i, n=0;
 for (i=nr; i-- && *s>='0' && *s<='9'; s++)
  n = n*10 + *s - '0';
 *d = n;
 return s;
}