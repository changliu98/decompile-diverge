int tt_unesc(char *s,char esc)
{
  char *p,*q;
  int n;

  p=q=s; n=0;
  while(*p!=esc && *p!='\0') p++;
  if(*p=='\0') return 0;
  while(*p!='\0')
  {
    if(*p==esc)
    {
      p++; n++;
    }
    *q++=*p++;
  }
  return n;
}