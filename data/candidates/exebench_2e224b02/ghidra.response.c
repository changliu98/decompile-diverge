void _prtl16(long num,char *str)

{
  char temp [9];
  int i;
  char *str_local;
  long num_local;
  
  temp[0] = '\0';
  num_local = num;
  for (i = 1; i < 9; i = i + 1) {
    temp[i] = "0123456789abcdef"[num_local & 0xf];
    num_local = num_local >> 4;
  }
  for (i = 8; temp[i] == '0'; i = i + -1) {
  }
  str_local = str;
  if (i == 0) {
    i = 1;
  }
  while (-1 < i) {
    *str_local = temp[i];
    i = i + -1;
    str_local = str_local + 1;
  }
  return;
}