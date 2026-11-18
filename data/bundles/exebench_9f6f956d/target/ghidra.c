int ckstrncpy(char *dest,char *src,int len)

{
  int i;
  int len_local;
  char *src_local;
  char *dest_local;
  int local_c;
  
  if (((len < 1) || (src == (char *)0x0)) || (dest == (char *)0x0)) {
    if (dest != (char *)0x0) {
      *dest = '\0';
    }
    local_c = 0;
  }
  else {
    for (i = 0; src[i] != '\0' && i < len + -1; i = i + 1) {
      dest[i] = src[i];
    }
    dest[i] = '\0';
    local_c = i;
  }
  return local_c;
}