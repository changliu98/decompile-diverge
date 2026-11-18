
char* strcpy(char* dest, const char* src) {
 char* pdest = dest;
 const char* psrc = src;
 while (*psrc != 0)
  *pdest++ = *psrc++;
 *pdest = '\0';
 return dest;
}
