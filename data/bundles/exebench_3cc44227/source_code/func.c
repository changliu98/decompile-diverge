
const char *js_itoa(char *out, unsigned int a)
{
 char buf[32], *s = out;
 unsigned int i = 0;
 while (a) {
  buf[i++] = (a % 10) + '0';
  a /= 10;
 }
 if (i == 0)
  buf[i++] = '0';
 while (i > 0)
  *s++ = buf[--i];
 *s = 0;
 return out;
}
