int func0(char *txt)

{
  byte bVar1;
  int iVar2;
  size_t sVar3;
  ushort **ppuVar4;
  char second_last_char;
  char last_char;
  int len;
  char *txt_local;
  int local_c;
  
  sVar3 = strlen(txt);
  iVar2 = (int)sVar3;
  if (iVar2 == 0) {
    local_c = 0;
  }
  else {
    bVar1 = txt[iVar2 + -1];
    ppuVar4 = __ctype_b_loc();
    if (((*ppuVar4)[(int)(uint)bVar1] & 0x400) == 0) {
      local_c = 0;
    }
    else if (iVar2 == 1) {
      local_c = 1;
    }
    else {
      bVar1 = txt[iVar2 + -2];
      ppuVar4 = __ctype_b_loc();
      if (((*ppuVar4)[(int)(uint)bVar1] & 0x400) == 0) {
        local_c = 1;
      }
      else {
        local_c = 0;
      }
    }
  }
  return local_c;
}