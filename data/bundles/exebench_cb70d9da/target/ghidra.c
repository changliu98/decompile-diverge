void BTIC2D_TransDCT_Vert(int *iblk,int *oblk)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int ib1p6n2n5;
  int ib0p7n3n4;
  int ib3n4;
  int ib2n5;
  int ib1n6;
  int ib0n7;
  int ib3p4;
  int ib2p5;
  int ib1p6;
  int ib0p7;
  int ob7;
  int ob6;
  int ob5;
  int ob4;
  int ob3;
  int ob2;
  int ob1;
  int ob0;
  int ib7;
  int ib6;
  int ib5;
  int ib4;
  int ib3;
  int ib2;
  int ib1;
  int ib0;
  int *oblk_local;
  int *iblk_local;
  
  iVar1 = *iblk + iblk[0x38];
  iVar2 = iblk[8] + iblk[0x30];
  iVar3 = iblk[0x10] + iblk[0x28];
  iVar4 = iblk[0x18] + iblk[0x20];
  iVar5 = *iblk - iblk[0x38];
  iVar6 = iblk[8] - iblk[0x30];
  iVar7 = iblk[0x10] - iblk[0x28];
  iVar8 = iblk[0x18] - iblk[0x20];
  *oblk = (iVar1 + iVar2 + iVar3 + iVar4) * 0x5b + 0x8000 >> 0x10;
  oblk[8] = iVar5 * 0x7e + iVar6 * 0x6a + iVar7 * 0x47 + iVar8 * 0x19 + 0x8000 >> 0x10;
  oblk[0x10] = (iVar1 - iVar4) * 0x76 + (iVar2 - iVar3) * 0x31 + 0x8000 >> 0x10;
  oblk[0x18] = iVar5 * 0x6a + iVar6 * -0x19 + iVar7 * -0x7e + iVar8 * -0x47 + 0x8000 >> 0x10;
  oblk[0x20] = (((iVar1 - iVar2) - iVar3) + iVar4) * 0x5b + 0x8000 >> 0x10;
  oblk[0x28] = iVar5 * 0x47 + iVar6 * -0x7e + iVar7 * 0x19 + iVar8 * 0x6a + 0x8000 >> 0x10;
  oblk[0x30] = (iVar1 - iVar4) * 0x31 + (iVar2 - iVar3) * -0x76 + 0x8000 >> 0x10;
  oblk[0x38] = iVar5 * 0x19 + iVar6 * -0x47 + iVar7 * 0x6a + iVar8 * -0x7e + 0x8000 >> 0x10;
  return;
}