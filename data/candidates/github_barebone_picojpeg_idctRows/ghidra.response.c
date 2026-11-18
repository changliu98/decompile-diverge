/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void idctRows(void)

{
  short sVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  int16 iVar5;
  int16 iVar6;
  int16 iVar7;
  short sVar8;
  short sVar9;
  short sVar10;
  short sVar11;
  short sVar12;
  int16 x42;
  int16 x41;
  int16 x43;
  int16 x40;
  int16 x32;
  int16 x13;
  int16 x12;
  int16 src3;
  int16 src2;
  int16 x31;
  int16 x30;
  int16 src1;
  int16 src0_1;
  int16 x44;
  int16 tmp3;
  int16 tmp2;
  int16 x17;
  int16 x15;
  int16 x24;
  int16 stg26;
  int16 tmp1;
  int16 x6;
  int16 x5;
  int16 src6;
  int16 src5;
  int16 x7;
  int16 x4;
  int16 src7;
  int16 src4;
  int16 src0;
  int16 *pSrc;
  uint8 i;
  
  pSrc = gCoeffBuf;
  for (i = '\0'; i < 8; i = i + '\x01') {
    if ((((((pSrc[1] == 0 && pSrc[2] == 0) && pSrc[3] == 0) && pSrc[4] == 0) && pSrc[5] == 0) &&
        pSrc[6] == 0) && pSrc[7] == 0) {
      iVar5 = *pSrc;
      pSrc[1] = iVar5;
      pSrc[2] = iVar5;
      pSrc[3] = iVar5;
      pSrc[4] = iVar5;
      pSrc[5] = iVar5;
      pSrc[6] = iVar5;
      pSrc[7] = iVar5;
    }
    else {
      sVar1 = pSrc[5] - pSrc[3];
      sVar2 = pSrc[5] + pSrc[3];
      sVar3 = pSrc[1] + pSrc[7];
      sVar4 = pSrc[1] - pSrc[7];
      iVar5 = imul_b5(sVar1 - sVar4);
      iVar6 = imul_b4(sVar4);
      iVar7 = imul_b2(sVar1);
      sVar1 = sVar3 + sVar2;
      sVar4 = (iVar6 - iVar5) - sVar1;
      iVar6 = imul_b1_b3(sVar3 - sVar2);
      sVar2 = iVar6 - sVar4;
      sVar3 = sVar2 + (iVar5 - iVar7);
      sVar8 = *pSrc + pSrc[4];
      sVar9 = *pSrc - pSrc[4];
      sVar10 = pSrc[2] + pSrc[6];
      iVar5 = imul_b1_b3(pSrc[2] - pSrc[6]);
      sVar11 = sVar8 + sVar10;
      sVar8 = sVar8 - sVar10;
      sVar12 = sVar9 + (iVar5 - sVar10);
      sVar9 = sVar9 - (iVar5 - sVar10);
      *pSrc = sVar11 + sVar1;
      pSrc[1] = sVar12 + sVar4;
      pSrc[2] = sVar9 + sVar2;
      pSrc[3] = sVar8 - sVar3;
      pSrc[4] = sVar8 + sVar3;
      pSrc[5] = sVar9 - sVar2;
      pSrc[6] = sVar12 - sVar4;
      pSrc[7] = sVar11 - sVar1;
    }
    pSrc = pSrc + 8;
  }
  return;
}