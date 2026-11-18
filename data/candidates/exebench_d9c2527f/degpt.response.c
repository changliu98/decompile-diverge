char * get_word(char *str,int *len)

{
  bool bVar1;
  int i;
  int *len_local;
  char *str_local;
  
  i = 0;
  str_local = str;
  if (str != (char *)0x0) {
    for (; *str_local == '-'; str_local = str_local + 1) {
    }
    if (('`' < *str_local) && (*str_local < '{')) {
      while( true ) {
        bVar1 = false;
        if ((((i < 0x40) && ((str_local[i] < '0' || (bVar1 = true, '9' < str_local[i])))) &&
            ((str_local[i] < 'a' || (bVar1 = true, 'z' < str_local[i])))) &&
           (bVar1 = true, str_local[i] != '-')) {
          bVar1 = str_local[i] == '_';
        }
        if (!bVar1) break;
        i = i + 1;
      }
    }
  }
  *len = i;
  return str_local;
}