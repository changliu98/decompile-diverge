char * func0(char *str1)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  size_t sVar5;
  ushort **ppuVar6;
  int lastIdx;
  int i;
  int length;
  int is_valid;
  int has_digit;
  int has_lower;
  int has_upper;
  char *str1_local;
  
  bVar1 = false;
  bVar2 = false;
  bVar3 = false;
  sVar5 = strlen(str1);
  iVar4 = (int)sVar5;
  for (i = 0; i < iVar4; i = i + 1) {
    ppuVar6 = __ctype_b_loc();
    if (((*ppuVar6)[(int)str1[i]] & 0x100) != 0) {
      bVar1 = true;
    }
    ppuVar6 = __ctype_b_loc();
    if (((*ppuVar6)[(int)str1[i]] & 0x200) != 0) {
      bVar2 = true;
    }
    ppuVar6 = __ctype_b_loc();
    if (((*ppuVar6)[(int)str1[i]] & 0x800) != 0) {
      bVar3 = true;
    }
  }
  func0::result[0] = '\0';
  if (!bVar1) {
    strcat(func0::result,"String must have 1 upper case character,");
  }
  if (!bVar2) {
    strcat(func0::result,"String must have 1 lower case character,");
  }
  if (!bVar3) {
    strcat(func0::result,"String must have 1 number,");
  }
  if (iVar4 < 8) {
    strcat(func0::result,"String length should be atleast 8,");
  }
  if ((((bVar1) && (bVar2)) && (bVar3)) && (7 < iVar4)) {
    strcpy(func0::result,"Valid string.");
  }
  else {
    sVar5 = strlen(func0::result);
    iVar4 = (int)sVar5 + -1;
    if (func0::result[iVar4] == ',') {
      func0::result[iVar4] = '\0';
    }
  }
  return func0::result;
}