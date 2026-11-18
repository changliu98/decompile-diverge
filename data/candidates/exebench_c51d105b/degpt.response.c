void png_64bit_product(long v1,long v2,unsigned_long *hi_product,unsigned_long *lo_product)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  ulong uVar5;
  ulong uVar6;
  long y;
  long x;
  long hi;
  long lo;
  int d;
  int c;
  int b;
  int a;
  unsigned_long *lo_product_local;
  unsigned_long *hi_product_local;
  long v2_local;
  long v1_local;
  
  uVar1 = (uint)((ulong)v1 >> 0x10) & 0xffff;
  uVar2 = (uint)v1 & 0xffff;
  uVar3 = (uint)((ulong)v2 >> 0x10) & 0xffff;
  uVar4 = (uint)v2 & 0xffff;
  uVar5 = (ulong)(int)(uVar2 * uVar4);
  uVar6 = ((long)uVar5 >> 0x10 & 0xffffU) + (long)(int)(uVar1 * uVar4 + uVar3 * uVar2);
  *hi_product = (long)(int)(uVar1 * uVar3) + ((long)uVar6 >> 0x10 & 0xffffU);
  *lo_product = uVar5 & 0xffff | (uVar6 & 0xffff) << 0x10;
  return;
}