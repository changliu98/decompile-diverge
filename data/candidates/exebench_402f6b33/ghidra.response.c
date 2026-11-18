void itoa(int num,char *str,int base)

{
  char *digits;
  char tmp [16];
  int sign;
  int i;
  int base_local;
  char *str_local;
  int num_local;
  
  num_local = num;
  if (num < 0) {
    num_local = -num;
  }
  i = 0;
  if (num_local == 0) {
    i = 1;
    tmp[0] = '0';
  }
  else {
    for (; num_local != 0; num_local = num_local / base) {
      tmp[i] = "0123456789ABCDEF"[num_local % base];
      i = i + 1;
    }
  }
  str_local = str;
  if (num < 0) {
    tmp[i] = '-';
    i = i + 1;
  }
  while (i != 0) {
    *str_local = tmp[i + -1];
    i = i + -1;
    str_local = str_local + 1;
  }
  *str_local = '\0';
  return;
}