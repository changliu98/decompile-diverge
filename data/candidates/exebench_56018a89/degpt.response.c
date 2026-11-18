void util_word_to_dec(char *dst,uint w)

{
  uint uVar1;
  int i;
  int digval;
  char dig_array [11];
  uint w_local;
  char *dst_local;
  
  for (i = 0; i < 10; i = i + 1) {
    dig_array[i] = '0';
  }
  dig_array[10] = '\0';
  i = 9;
  w_local = w;
  while (w_local != 0) {
    uVar1 = w_local % 10;
    w_local = w_local / 10;
    dig_array[i] = (char)uVar1 + '0';
    i = i + -1;
  }
  for (i = 0; dst_local = dst, dig_array[i] == '0' && i < 9; i = i + 1) {
  }
  while (dig_array[i] != '\0') {
    *dst_local = dig_array[i];
    i = i + 1;
    dst_local = dst_local + 1;
  }
  *dst_local = '\0';
  return;
}