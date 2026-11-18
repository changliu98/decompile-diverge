int ellipsis(char *str,int len)

{
  bool bVar1;
  char *pcVar2;
  bool bVar3;
  char *ptr;
  int inGBK;
  int i;
  int len_local;
  char *str_local;
  int local_c;
  
  bVar1 = false;
  if ((len < 0) || (str == (char *)0x0)) {
    local_c = 0;
  }
  else if (len < 3) {
    str[len] = '\0';
    local_c = 1;
  }
  else {
    i = len + -3;
    for (ptr = str; *ptr != '\0' && i != 0; ptr = ptr + 1) {
      if (bVar1) {
        bVar1 = false;
      }
      else if (((int)*ptr & 0x80U) != 0) {
        bVar1 = true;
      }
      i = i + -1;
    }
    i = 3;
    pcVar2 = ptr;
    do {
      ptr = pcVar2;
      bVar3 = false;
      if (*ptr != '\0') {
        i = i + -1;
        bVar3 = i != 0;
      }
      pcVar2 = ptr + 1;
    } while (bVar3);
    if ((ptr[1] != '\0') && (i == 0)) {
      str[len] = '\0';
      *ptr = '.';
      ptr[-1] = '.';
      if ((!bVar1) && (((int)ptr[-2] & 0x80U) != 0)) {
        ptr[-2] = '.';
      }
    }
    local_c = 1;
  }
  return local_c;
}