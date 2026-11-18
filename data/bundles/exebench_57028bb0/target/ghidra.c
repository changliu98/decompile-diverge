char * ft_strcpy(char *dest,char *src)

{
  long lVar1;
  int iVar2;
  int iVar3;
  int src_len;
  int dest_len;
  int i;
  char *src_local;
  char *dest_local;
  char *local_10;
  
  dest_len = 0;
  do {
    iVar2 = dest_len + 1;
    lVar1 = (long)dest_len;
    dest_len = iVar2;
  } while (dest[lVar1] != '\0');
  src_len = 0;
  do {
    iVar3 = src_len + 1;
    lVar1 = (long)src_len;
    src_len = iVar3;
  } while (src[lVar1] != '\0');
  i = -1;
  if (iVar2 < iVar3) {
    local_10 = "";
  }
  else {
    while (i = i + 1, src[i] != '\0') {
      dest[i] = src[i];
    }
    dest[i] = '\0';
    local_10 = dest;
  }
  return local_10;
}