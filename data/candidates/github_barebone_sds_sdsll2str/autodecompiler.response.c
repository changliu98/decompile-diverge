static size_t sdsll2str(char *dest, long long src)
{
 size_t len;
 unsigned long long u;
 char *p;
 char c;

 if (src < 0) {
  if (src != ((long long)((unsigned long long)(~0) >> 1))) {
   u = (unsigned long long)(-src);
  } else {
   u = (unsigned long long)((unsigned long long)(~0) >> 1);
  }
 } else {
  u = (unsigned long long)src;
 }

 p = dest;
 do {
  *p++ = '0' + (u % 10);
  u /= 10;
 } while (u);

 if (src < 0) {
  *p++ = '-';
 }

 len = p - dest;
 *p = '\0';
 p--;

 while (dest < p) {
  c = *dest;
  *dest = *p;
  *p = c;
  dest++;
  p--;
 }

 return len;
}