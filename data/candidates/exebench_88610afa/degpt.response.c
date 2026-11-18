char * my_strcpy(char *dest,char *src)

{
  int i;
  char *src_local;
  char *dest_local;
  
  i = -1;
  while (i = i + 1, src[i] != '\0') {
    dest[i] = src[i];
  }
  dest[i] = '\0';
  return dest;
}