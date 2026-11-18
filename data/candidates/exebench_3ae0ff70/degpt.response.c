void mult_big(uint a,uint b,uint *hi,uint *lo)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint c1_b;
  uint c1_a;
  uint c2;
  uint c1;
  uint c0;
  uint blo;
  uint bhi;
  uint alo;
  uint ahi;
  uint *lo_local;
  uint *hi_local;
  uint b_local;
  uint a_local;
  
  uVar1 = (a & 0xffff) * (b & 0xffff);
  uVar2 = (a >> 0x10) * (b & 0xffff);
  uVar3 = (a & 0xffff) * (b >> 0x10);
  uVar4 = (uVar2 & 0xffff) + (uVar3 & 0xffff) + (uVar1 >> 0x10);
  *hi = (uVar4 >> 0x10) + (uVar2 >> 0x10) + (uVar3 >> 0x10) + (a >> 0x10) * (b >> 0x10);
  *lo = uVar4 * 0x10000 + (uVar1 & 0xffff);
  return;
}