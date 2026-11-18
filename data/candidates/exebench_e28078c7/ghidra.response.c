uint parse_int(char *str,int *num)

{
  char cVar1;
  char null;
  int t;
  int length;
  int digit;
  int minus_fl;
  int i;
  int *num_local;
  char *str_local;
  
  t = 1;
  *num = 0;
  cVar1 = *str;
  i = (int)(cVar1 == '-');
  for (length = 1; str[length] != '\0'; length = length + 1) {
    t = t * 10;
  }
  while( true ) {
    if (str[i] == '\0') {
      if (cVar1 == '-') {
        *num = -*num;
      }
      return 1;
    }
    if (9 < (int)str[i] - 0x30U) break;
    if (0 < i) {
      t = t / 10;
    }
    *num = t * ((int)str[i] - 0x30U) + *num;
    i = i + 1;
  }
  return 0;
}