char *url_canonize2(char *dst, const char *src, size_t n,
      unsigned int allow,
      unsigned int m32, unsigned int m64, unsigned int m96)
{
  unsigned char c, h1, h2;
  unsigned int i;
  char *d = dst;

  if (src == dst) {
    for (i = 0; src[i] && i < n; i++) {
      if (src[i] == '%')
 break;
      *d++ = src[i];
    }
  }

  for (; src[i] && i < n; i++) {
    c = (unsigned char) src[i];
    if (c == '%') {
      h1 = (unsigned char) src[i + 1];
      if (!h1) {
 *d = '\0';
 return NULL;
      }
      h2 = (unsigned char) src[i + 2];
      if (!((h1 >= '0' && h1 <= '9') || (h1 >= 'A' && h1 <= 'F') || (h1 >= 'a' && h1 <= 'f')) ||
   !((h2 >= '0' && h2 <= '9') || (h2 >= 'A' && h2 <= 'F') || (h2 >= 'a' && h2 <= 'f'))) {
 *d = '\0';
 return NULL;
      }
      c = (h1 >= 'a' ? h1 - 'a' + 10 : (h1 >= 'A' ? h1 - 'A' + 10 : h1 - '0')) << 4 |
   (h2 >= 'a' ? h2 - 'a' + 10 : (h2 >= 'A' ? h2 - 'A' + 10 : h2 - '0'));
      if (c > 32 && c < 127 &&
   (c < 64 || !(m32 & (1 << (63 - c))) &&
    (c < 96 || !(m64 & (1 << (63 - c))) &&
     (c < 128 || !(m96 & (1 << (63 - c))))))) {
 *d++ = c;
 i += 2;
      } else {
 *d++ = '%';
 *d++ = h1 >= 'a' ? h1 - 'a' + 'A' : h1;
 *d++ = h2 >= 'a' ? h2 - 'a' + 'A' : h2;
 i += 2;
      }
    } else {
      if (!(allow & (1 << (c - 33)))) {
 if (c < 33 || c > 126 ||
     (c < 64 || !(m32 & (1 << (63 - c))) &&
      (c < 96 || !(m64 & (1 << (63 - c))) &&
       (c < 128 || !(m96 & (1 << (63 - c)))))))
   return NULL;
      }
      *d++ = c;
    }
  }
  *d = '\0';
  return d;
}