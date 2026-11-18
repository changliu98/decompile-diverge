int _chartorune(unsigned_short *rune,char *str)

{
  ushort uVar1;
  ushort uVar2;
  long l;
  int c2;
  int c1;
  int c;
  char *str_local;
  unsigned_short *rune_local;
  
  uVar1 = (ushort)(byte)*str;
  if (uVar1 < 0x80) {
    *rune = (ushort)(byte)*str;
    return 1;
  }
  uVar2 = (byte)str[1] ^ 0x80;
  if ((uVar2 & 0xc0) == 0) {
    if (uVar1 < 0xe0) {
      if ((0xbf < uVar1) && (uVar2 = (uVar1 & 0x1f) << 6 | uVar2, 0x7f < uVar2)) {
        *rune = uVar2;
        return 2;
      }
    }
    else if ((((((byte)str[2] ^ 0x80) & 0xc0) == 0) && (uVar1 < 0xf0)) &&
            (uVar1 = ((uVar1 & 0xf) << 6 | uVar2) << 6 | (byte)str[2] ^ 0x80, 0x7ff < uVar1)) {
      *rune = uVar1;
      return 3;
    }
  }
  *rune = 0x80;
  return 1;
}