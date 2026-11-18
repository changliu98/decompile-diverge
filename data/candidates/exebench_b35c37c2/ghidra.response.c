void itox(unsigned_short value,char *s)

{
  char cVar1;
  unsigned_short uVar2;
  unsigned_short v;
  unsigned_short max;
  unsigned_short index;
  char tmp [16];
  char *s_local;
  unsigned_short value_local;
  
  index = 0;
  value_local = value;
  if (value == 0) {
    *s = '0';
    s[1] = '\0';
  }
  else {
    for (; uVar2 = index, value_local != 0; value_local = value_local / 0x10) {
      cVar1 = (char)(value_local % 0x10);
      if (value_local % 0x10 < 10) {
        tmp[index] = cVar1 + '0';
      }
      else {
        tmp[index] = cVar1 + 'W';
      }
      index = index + 1;
    }
    for (; index != 0; index = index - 1) {
      s[(int)((uint)uVar2 - (uint)index)] = tmp[(int)(index - 1)];
    }
    s[uVar2] = '\0';
  }
  return;
}