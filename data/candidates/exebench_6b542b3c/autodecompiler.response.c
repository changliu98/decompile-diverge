char *trim(char *s, char *c)
{
 register char *p;
 register char *t;
 char b;

 if (!s) {
  t = s;
  goto end;
 }

 p = index(s, '\0')-1;

 for (;;) {
  b = p < s;
  if (b || !index(c, *p)) {
   break;
  }
  *p = '\0';
  --p;
 }

 t = s;
end:
 return(t);
}