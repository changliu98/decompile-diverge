char * ft_strcpy(char *dest,char *src)

{
  int i;
  char *src_local;
  char *dest_local;
  
  for (i = 0; src[i] != '\0'; i = i + 1) {
    dest[i] = src[i];
  }
  dest[i] = '\0';
  return dest;
}