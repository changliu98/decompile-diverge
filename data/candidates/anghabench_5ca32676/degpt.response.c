void wht4x4(int16_t *coef)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  int e1_1;
  int d1_1;
  int c1_1;
  int b1_1;
  int a1_1;
  int e1;
  int d1;
  int c1;
  int b1;
  int a1;
  int i;
  int16_t *coef_local;
  
  for (i = 0; i < 4; i = i + 1) {
    iVar3 = (int)coef[i + 4] + (int)coef[i];
    iVar4 = (int)coef[i + 0xc] - (int)coef[i + 8];
    sVar1 = (short)(iVar3 - iVar4 >> 1);
    sVar2 = sVar1 - coef[i + 4];
    sVar1 = sVar1 - coef[i + 8];
    coef[i] = (short)iVar3 - sVar1;
    coef[i + 4] = sVar1;
    coef[i + 8] = sVar2 + (short)iVar4;
    coef[i + 0xc] = sVar2;
  }
  for (i = 0; i < 4; i = i + 1) {
    iVar3 = (int)coef[i * 4 + 1] + (int)coef[i << 2];
    iVar4 = (int)coef[i * 4 + 3] - (int)coef[i * 4 + 2];
    sVar1 = (short)(iVar3 - iVar4 >> 1);
    sVar2 = sVar1 - coef[i * 4 + 1];
    sVar1 = sVar1 - coef[i * 4 + 2];
    coef[i << 2] = ((short)iVar3 - sVar1) * 2;
    coef[i * 4 + 1] = sVar1 * 2;
    coef[i * 4 + 2] = (sVar2 + (short)iVar4) * 2;
    coef[i * 4 + 3] = sVar2 * 2;
  }
  return;
}