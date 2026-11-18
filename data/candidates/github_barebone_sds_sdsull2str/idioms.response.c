int sdsull2str(char *str, unsigned long val)
{
 char *s = str;
 char *p = str;
 char aux;
 do
  *p++ = (val % 10) + '0';
 while (val /= 10);
 int len = p - s;
 *p = '\0';
 p--;
 while (s < p)
 {
  aux = *s;
  *s = *p;
  *p = aux;
  s++;
  p--;
 }
 return len;
}