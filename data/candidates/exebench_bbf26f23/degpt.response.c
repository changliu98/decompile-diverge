char * strcpy(char *dest,char *src)

{
  uint size;
  char *src_local;
  char *dest_local;
  
  for (size = 0; src[size] != '\0'; size = size + 1) {
    dest[size] = src[size];
  }
  dest[size] = '\0';
  return dest;
}