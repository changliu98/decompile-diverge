char * my_strncpy(char *dest,char *src,int n)

{
  int i;
  int n_local;
  char *src_local;
  char *dest_local;
  
  i = -1;
  while (i = i + 1, src[i] != '\0' && i < n) {
    dest[i] = src[i];
  }
  dest[i] = '\0';
  return dest;
}