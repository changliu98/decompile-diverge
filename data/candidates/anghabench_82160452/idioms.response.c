int sdsll2str(char *str, long val)
{
 char *s = str;
 char *t = str;
 char aux;
 if (val < 0)
  val = -val;
 long v = val;
 do
 {
  *t++ = (val % 10) + '0';
  val /= 10;
 } while (val);
 if (val < 0)
  *t++ = '-';
 int len = t - s;
 *t = '\0';
 t--;
 while (s < t)
 {
  aux = *s;
  *s = *t;
  *t = aux;
  s++;
  t--;
 }
 return len;
}