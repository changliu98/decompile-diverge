void find_ibm(int char1,int char2,int *outchar1,int *outchar2)

{
  int iVar1;
  uint uVar2;
  int tmp2;
  int tmp1;
  int rno;
  int *outchar2_local;
  int *outchar1_local;
  int char2_local;
  int char1_local;
  
  uVar2 = 0;
  if (((char1 + -0xa1) * 0x9d + char2) - 0x3fU != (uint)(0x7e < char2)) {
    uVar2 = 0x22;
  }
  iVar1 = 0;
  if (0x198 < uVar2) {
    iVar1 = 0x5d;
  }
  uVar2 = iVar1 + uVar2;
  iVar1 = uVar2 + (uVar2 % 0xbc) * -0xbc;
  tmp2 = iVar1 + 0x3f;
  if (0x7e < tmp2) {
    tmp2 = iVar1 + 0x40;
  }
  *outchar1 = uVar2 % 0xbc + 0x89;
  *outchar1 = tmp2;
  return;
}