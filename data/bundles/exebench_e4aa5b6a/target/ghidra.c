int util_read_dec(char *str,int *result)

{
  int iVar1;
  bool bVar2;
  long tmp2;
  int i;
  int tmp;
  int neg;
  int *result_local;
  char *str_local;
  
  *result = 0;
  bVar2 = *str == '-';
  str_local = str;
  if (bVar2) {
    str_local = str + 1;
  }
  i = (int)bVar2;
  tmp2 = 0;
  while ((((*str_local != '\0' && (iVar1 = *str_local + -0x30, -1 < iVar1)) && (iVar1 < 10)) &&
         (tmp2 = (long)iVar1 + tmp2 * 10, tmp2 < 0x80000000))) {
    str_local = str_local + 1;
    i = i + 1;
    *result = (int)tmp2;
  }
  if (bVar2) {
    if (i == 1) {
      return 0;
    }
    *result = -*result;
  }
  return i;
}