char *to_unix_path(char *dst, char *src)
{
 char *dst_start = dst;

 if (dst != ((void *) 0) && src != ((void *) 0)) {
  while (1) {
   if (*src == '\0') {
    *dst = *src;
    break;
   }
   else if (*src == '\\') {
    *dst++ = '/';
    src++;
   }
   else {
    *dst++ = *src++;
   }
  }
 }

 return dst_start;
}