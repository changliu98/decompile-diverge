char * strcpy(char *dst,char *src)

{
  char *pcVar1;
  size_t i;
  char *src_local;
  char *dst_local;
  
  i = 0;
  do {
    dst[i] = src[i];
    pcVar1 = src + i;
    i = i + 1;
  } while (*pcVar1 != '\0');
  return dst;
}