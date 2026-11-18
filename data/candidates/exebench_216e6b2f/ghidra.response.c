char * my_strcpy(char *dest,char *src)

{
  int lp;
  char *src_local;
  char *dest_local;
  
  for (lp = 0; src[lp] != '\0'; lp = lp + 1) {
    dest[lp] = src[lp];
  }
  dest[lp] = '\0';
  return dest;
}