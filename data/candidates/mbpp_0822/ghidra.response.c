_Bool func0(char *p)

{
  _Bool _Var1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  size_t sVar6;
  ushort **ppuVar7;
  int i;
  _Bool hasSpecial;
  _Bool hasDigit;
  _Bool hasUpper;
  _Bool hasLower;
  int len;
  char *p_local;
  _Bool local_9;
  
  sVar6 = strlen(p);
  iVar5 = (int)sVar6;
  bVar2 = false;
  bVar3 = false;
  bVar4 = false;
  _Var1 = false;
  if ((iVar5 < 6) || (0xc < iVar5)) {
    local_9 = false;
  }
  else {
    for (i = 0; i < iVar5; i = i + 1) {
      ppuVar7 = __ctype_b_loc();
      if (((*ppuVar7)[(int)p[i]] & 0x200) == 0) {
        ppuVar7 = __ctype_b_loc();
        if (((*ppuVar7)[(int)p[i]] & 0x100) == 0) {
          ppuVar7 = __ctype_b_loc();
          if (((*ppuVar7)[(int)p[i]] & 0x800) == 0) {
            if (((p[i] == '$') || (p[i] == '#')) || (p[i] == '@')) {
              _Var1 = true;
            }
            else {
              ppuVar7 = __ctype_b_loc();
              if (((*ppuVar7)[(int)p[i]] & 0x2000) != 0) {
                return false;
              }
            }
          }
          else {
            bVar4 = true;
          }
        }
        else {
          bVar3 = true;
        }
      }
      else {
        bVar2 = true;
      }
    }
    local_9 = false;
    if (((bVar2) && (local_9 = false, bVar3)) && (local_9 = false, bVar4)) {
      local_9 = _Var1;
    }
  }
  return local_9;
}