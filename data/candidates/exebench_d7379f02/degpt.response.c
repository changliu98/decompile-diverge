void itoa(unsigned_short value,char *s)

{
  unsigned_short uVar1;
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
    for (; uVar1 = index, value_local != 0; value_local = value_local / 10) {
      tmp[index] = (char)((ulong)value_local % 10) + '0';
      index = index + 1;
    }
    for (; index != 0; index = index - 1) {
      s[(int)((uint)uVar1 - (uint)index)] = tmp[(int)(index - 1)];
    }
    s[uVar1] = '\0';
  }
  return;
}