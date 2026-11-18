char *url_canonize2(char *dst, const char *src, size_t n,
      unsigned int syn33,
      unsigned int m32, unsigned int m64, unsigned int m96)
{
  unsigned char c;
  unsigned char h1, h2;
  unsigned char l1, l2;
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
    c = (unsigned char)src[i];
    if (c == '%') {
      h1 = (unsigned char)src[i + 1];
      h2 = (unsigned char)src[i + 2];
      if (!(((h1) >= '0' && (h1) <= '9') || ((h1) >= 'A' && (h1) <= 'F') || ((h1) >= 'a' && (h1) <= 'f')) || !(((h2) >= '0' && (h2) <= '9') || ((h2) >= 'A' && (h2) <= 'F') || ((h2) >= 'a' && (h2) <= 'f')))
 return NULL;
      l1 = (h1 >= 'a') ? 'a' : ((h1 >= 'A') ? 'A' : 0);
      l2 = (h2 >= 'a') ? 'a' : ((h2 >= 'A') ? 'A' : 0);
      c = (h1 - l1) * 16 | (h2 - l2);
      if (c > 32 && c < 127 &&
   (c < 64 ||
    (c < 96 ? (m32 & (1 << (63 - c))) : (c < 128 ? (m64 & (1 << (63 - c))) : (m96 & (1 << (63 - c)))))) {
 *d++ = c;
 i += 2;
      } else {
 if (h1 >= 'a')
   h1 -= 0x20;
 if (h2 >= 'a')
   h2 -= 0x20;
 *d++ = '%';
 *d++ = h1;
 *d++ = h2;
 i += 2;
      }
    } else {
      if (!(syn33 & (1 << (c - 33)))) {
 if (c < 33 || c > 126)
   return NULL;
 if (c < 64 ||
     (c < 96 ? (m32 & (1 << (63 - c))) : (c < 128 ? (m64 & (1 << (63 - c))) : (m96 & (1 << (63 - c)))))
   return NULL;
      }
      *d++ = c;
    }
  }
  *d = '\0';
  return d;
}