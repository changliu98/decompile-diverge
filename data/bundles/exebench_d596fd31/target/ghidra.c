size_t itoa(uint value,char *str,uint base)

{
  uint uVar1;
  size_t i;
  int index;
  size_t current;
  char tmp [32];
  char *digits;
  uint base_local;
  char *str_local;
  uint value_local;
  size_t local_10;
  
  if ((base < 2) || (0x24 < base)) {
    local_10 = 0;
  }
  else if (value == 0) {
    *str = '0';
    local_10 = 1;
  }
  else {
    current = 0;
    value_local = value;
    while (value_local != 0) {
      uVar1 = value_local % base;
      value_local = value_local / base;
      tmp[current] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[(int)uVar1];
      current = current + 1;
    }
    for (i = 0; i < current; i = i + 1) {
      str[i] = tmp[(current - i) + -1];
    }
    local_10 = i;
  }
  return local_10;
}