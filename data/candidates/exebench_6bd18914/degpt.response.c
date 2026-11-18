void vp8_short_inv_walsh4x4_simd(short *input,short *mb_dqcoeff)

{
  short sVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  short sVar8;
  short *op;
  short *ip;
  int d2;
  int c2;
  int b2;
  int a2;
  int d1;
  int c1;
  int b1;
  int a1;
  int i;
  short output [16];
  short *mb_dqcoeff_local;
  short *input_local;
  
  op = output;
  ip = input;
  for (i = 0; i < 4; i = i + 1) {
    sVar1 = *ip;
    sVar2 = ip[0xc];
    sVar3 = ip[4];
    sVar4 = ip[8];
    sVar5 = ip[4];
    sVar6 = ip[8];
    sVar7 = *ip;
    sVar8 = ip[0xc];
    *op = sVar1 + sVar2 + sVar3 + sVar4;
    op[4] = (sVar5 - sVar6) + (sVar7 - sVar8);
    op[8] = (sVar1 + sVar2) - (sVar3 + sVar4);
    op[0xc] = (sVar7 - sVar8) - (sVar5 - sVar6);
    ip = ip + 1;
    op = op + 1;
  }
  ip = output;
  op = output;
  for (i = 0; i < 4; i = i + 1) {
    sVar1 = *ip;
    sVar2 = ip[3];
    sVar3 = ip[1];
    sVar4 = ip[2];
    sVar5 = ip[1];
    sVar6 = ip[2];
    sVar7 = *ip;
    sVar8 = ip[3];
    *op = (short)((int)sVar1 + (int)sVar2 + (int)sVar3 + (int)sVar4 + 3 >> 3);
    op[1] = (short)(((int)sVar5 - (int)sVar6) + ((int)sVar7 - (int)sVar8) + 3 >> 3);
    op[2] = (short)((((int)sVar1 + (int)sVar2) - ((int)sVar3 + (int)sVar4)) + 3 >> 3);
    op[3] = (short)((((int)sVar7 - (int)sVar8) - ((int)sVar5 - (int)sVar6)) + 3 >> 3);
    ip = ip + 4;
    op = op + 4;
  }
  for (i = 0; i < 0x10; i = i + 1) {
    mb_dqcoeff[i << 4] = output[i];
  }
  return;
}