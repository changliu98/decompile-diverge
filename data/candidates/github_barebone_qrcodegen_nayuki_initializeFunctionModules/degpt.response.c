void initializeFunctionModules(int version,uint8_t *qrcode)

{
  int iVar1;
  int iVar2;
  int j;
  int i;
  int numAlign;
  uint8_t alignPatPos [7];
  int qrsize;
  uint8_t *qrcode_local;
  int version_local;
  
  iVar1 = version * 4;
  iVar2 = iVar1 + 0x11;
  memset(qrcode,0,(long)((iVar2 * iVar2 + 7) / 8 + 1));
  *qrcode = (uint8_t)iVar2;
  fillRectangle(6,0,1,iVar2,qrcode);
  fillRectangle(0,6,iVar2,1,qrcode);
  fillRectangle(0,0,9,9,qrcode);
  fillRectangle(iVar1 + 9,0,8,9,qrcode);
  fillRectangle(0,iVar1 + 9,9,8,qrcode);
  iVar2 = getAlignmentPatternPositions(version,alignPatPos);
  for (i = 0; i < iVar2; i = i + 1) {
    for (j = 0; j < iVar2; j = j + 1) {
      if ((((i != 0) || (j != 0)) && ((i != 0 || (j != iVar2 + -1)))) &&
         ((i != iVar2 + -1 || (j != 0)))) {
        fillRectangle(alignPatPos[i] - 2,alignPatPos[j] - 2,5,5,qrcode);
      }
    }
  }
  if (6 < version) {
    fillRectangle(iVar1 + 6,0,3,6,qrcode);
    fillRectangle(0,iVar1 + 6,6,3,qrcode);
  }
  return;
}