char * strcpy(char *dest,char *src)

{
  char *psrc;
  char *pdest;
  char *src_local;
  char *dest_local;
  
  psrc = src;
  pdest = dest;
  while (*psrc != '\0') {
    *pdest = *psrc;
    psrc = psrc + 1;
    pdest = pdest + 1;
  }
  *pdest = '\0';
  return dest;
}