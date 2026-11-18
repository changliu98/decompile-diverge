int reverse(char *str)
{
  char *p = str;
  char *q = str;
  while(*q++ != '\0')
    ;
  --q;
  --q;
  while(p < q)
  {
    *p ^= *q;
    *q ^= *p;
    *p ^= *q;
    ++p;
    --q;
  }
  return 0;
}