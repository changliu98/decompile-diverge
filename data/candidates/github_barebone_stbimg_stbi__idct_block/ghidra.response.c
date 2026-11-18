void stbi__idct_block(stbi_uc *out,int out_stride,short *data)

{
  stbi_uc sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int x3_1;
  int x2_1;
  int x1_1;
  int x0_1;
  int p5_1;
  int p4_1;
  int p3_1;
  int p2_1;
  int p1_1;
  int t3_1;
  int t2_1;
  int t1_1;
  int t0_1;
  int x3;
  int x2;
  int x1;
  int x0;
  int p5;
  int p4;
  int p3;
  int p2;
  int p1;
  int t3;
  int t2;
  int t1;
  int t0;
  int dcterm;
  short *d;
  stbi_uc *o;
  int *v;
  int val [64];
  int i;
  short *data_local;
  int out_stride_local;
  stbi_uc *out_local;
  
  v = val;
  d = data;
  for (i = 0; i < 8; i = i + 1) {
    if ((((d[8] == 0) && (d[0x10] == 0)) && (d[0x18] == 0)) &&
       (((d[0x20] == 0 && (d[0x28] == 0)) && ((d[0x30] == 0 && (d[0x38] == 0)))))) {
      iVar2 = (int)*d << 2;
      v[0x38] = iVar2;
      v[0x30] = iVar2;
      v[0x28] = iVar2;
      v[0x20] = iVar2;
      v[0x18] = iVar2;
      v[0x10] = iVar2;
      v[8] = iVar2;
      *v = iVar2;
    }
    else {
      iVar3 = ((int)d[0x10] + (int)d[0x30]) * 0x8a9;
      iVar2 = iVar3 + d[0x30] * -0x1d8f;
      iVar3 = iVar3 + d[0x10] * 0xc3f;
      iVar4 = ((int)*d + (int)d[0x20]) * 0x1000;
      iVar5 = ((int)*d - (int)d[0x20]) * 0x1000;
      iVar6 = (int)d[0x38];
      iVar7 = (int)d[0x28];
      iVar8 = (int)d[0x18];
      iVar9 = (int)d[8];
      iVar10 = (iVar6 + iVar8 + iVar7 + iVar9) * 0x12d0;
      iVar11 = iVar10 + (iVar6 + iVar9) * -0xe65;
      iVar10 = iVar10 + (iVar7 + iVar8) * -0x2901;
      iVar12 = (iVar6 + iVar8) * -0x1f62;
      iVar13 = (iVar7 + iVar9) * -0x63d;
      iVar9 = iVar11 + iVar13 + iVar9 * 0x1805;
      iVar8 = iVar10 + iVar12 + iVar8 * 0x312a;
      iVar7 = iVar10 + iVar13 + iVar7 * 0x20da;
      iVar6 = iVar11 + iVar12 + iVar6 * 0x4c7;
      iVar11 = iVar4 + iVar3 + 0x200;
      iVar10 = iVar5 + iVar2 + 0x200;
      iVar2 = (iVar5 - iVar2) + 0x200;
      iVar3 = (iVar4 - iVar3) + 0x200;
      *v = iVar11 + iVar9 >> 10;
      v[0x38] = iVar11 - iVar9 >> 10;
      v[8] = iVar10 + iVar8 >> 10;
      v[0x30] = iVar10 - iVar8 >> 10;
      v[0x10] = iVar2 + iVar7 >> 10;
      v[0x28] = iVar2 - iVar7 >> 10;
      v[0x18] = iVar3 + iVar6 >> 10;
      v[0x20] = iVar3 - iVar6 >> 10;
    }
    d = d + 1;
    v = v + 1;
  }
  v = val;
  o = out;
  for (i = 0; i < 8; i = i + 1) {
    iVar7 = (v[2] + v[6]) * 0x8a9;
    iVar6 = iVar7 + v[6] * -0x1d8f;
    iVar7 = iVar7 + v[2] * 0xc3f;
    iVar8 = (*v + v[4]) * 0x1000;
    iVar9 = (*v - v[4]) * 0x1000;
    iVar2 = v[7];
    iVar3 = v[5];
    iVar4 = v[3];
    iVar5 = v[1];
    iVar10 = (iVar2 + iVar4 + iVar3 + iVar5) * 0x12d0;
    iVar11 = iVar10 + (iVar2 + iVar5) * -0xe65;
    iVar10 = iVar10 + (iVar3 + iVar4) * -0x2901;
    iVar12 = (iVar2 + iVar4) * -0x1f62;
    iVar13 = (iVar3 + iVar5) * -0x63d;
    iVar5 = iVar11 + iVar13 + iVar5 * 0x1805;
    iVar4 = iVar10 + iVar12 + iVar4 * 0x312a;
    iVar3 = iVar10 + iVar13 + iVar3 * 0x20da;
    iVar2 = iVar11 + iVar12 + iVar2 * 0x4c7;
    iVar11 = iVar8 + iVar7 + 0x1010000;
    iVar10 = iVar9 + iVar6 + 0x1010000;
    iVar6 = (iVar9 - iVar6) + 0x1010000;
    iVar7 = (iVar8 - iVar7) + 0x1010000;
    sVar1 = stbi__clamp(iVar11 + iVar5 >> 0x11);
    *o = sVar1;
    sVar1 = stbi__clamp(iVar11 - iVar5 >> 0x11);
    o[7] = sVar1;
    sVar1 = stbi__clamp(iVar10 + iVar4 >> 0x11);
    o[1] = sVar1;
    sVar1 = stbi__clamp(iVar10 - iVar4 >> 0x11);
    o[6] = sVar1;
    sVar1 = stbi__clamp(iVar6 + iVar3 >> 0x11);
    o[2] = sVar1;
    sVar1 = stbi__clamp(iVar6 - iVar3 >> 0x11);
    o[5] = sVar1;
    sVar1 = stbi__clamp(iVar7 + iVar2 >> 0x11);
    o[3] = sVar1;
    sVar1 = stbi__clamp(iVar7 - iVar2 >> 0x11);
    o[4] = sVar1;
    v = v + 8;
    o = o + out_stride;
  }
  return;
}