void ltostr(uint uiValue,char *pString)

{
  uint uVar1;
  uint value;
  int i;
  char *pString_local;
  uint uiValue_local;
  
  *pString = '\0';
  pString[8] = '\0';
  uiValue_local = uiValue;
  for (i = 0; i < 8; i = i + 1) {
    uVar1 = (uiValue_local & 0xf) + 0x30;
    value._0_1_ = (char)uVar1;
    if (0x39 < uVar1) {
      value._0_1_ = (char)(uiValue_local & 0xf) + '7';
    }
    pString[7 - i] = (char)value;
    uiValue_local = uiValue_local >> 4;
  }
  return;
}