static int mbtowc(wchar_t *pwc, char *s, size_t n)
{
 int ret;

 if (n > 0 && *s != '\0') {
  *pwc = *s;
  ret = 1;
 } else {
  ret = 0;
 }

 return ret;
}