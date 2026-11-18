int enddata(char *buff,int p)

{
  uint uVar1;
  int offset;
  int pageaddr;
  int p_local;
  char *buff_local;
  int local_c;
  
  uVar1 = p & 0x3f;
  if (uVar1 == 0) {
    local_c = 0;
  }
  else {
    buff[(int)((p - uVar1) + 1)] = (char)uVar1 + -1;
    local_c = (p - uVar1) + 0x40;
  }
  return local_c;
}