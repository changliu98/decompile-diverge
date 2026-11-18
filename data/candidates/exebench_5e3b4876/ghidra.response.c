uint scan_8long(char *s,unsigned_long *u)

{
  ulong uVar1;
  unsigned_long c;
  unsigned_long result;
  uint pos;
  unsigned_long *u_local;
  char *s_local;
  
  pos = 0;
  result = 0;
  while (uVar1 = (ulong)((int)s[pos] - 0x30U & 0xff), uVar1 < 8) {
    result = result * 8 + uVar1;
    pos = pos + 1;
  }
  *u = result;
  return pos;
}