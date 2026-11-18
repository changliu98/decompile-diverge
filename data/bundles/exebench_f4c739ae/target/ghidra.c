double randum(long *seed)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  double res;
  long newseed2;
  long newseed1;
  long newseed0;
  long seed2;
  long seed1;
  long seed0;
  long mult1;
  long mult0;
  long sum;
  long *seed_local;
  
  uVar1 = (*seed & 0xfffU) * 0x60d;
  uVar2 = uVar1 & 0xfff;
  uVar3 = *seed >> 0xc & 0xfff;
  uVar1 = uVar3 * 0x60d + (*seed & 0xfffU) * 0x196 + ((long)uVar1 >> 0xc);
  uVar4 = uVar1 & 0xfff;
  uVar1 = (*seed >> 0x18 & 0xffU) * 0x60d + uVar3 * 0x196 + ((long)uVar1 >> 0xc) & 0xff;
  *seed = uVar1 << 0x18 | uVar4 << 0xc | uVar2;
  return DAT_00102008 *
         (((double)uVar2 * DAT_00102010 + (double)uVar4) * DAT_00102010 + (double)uVar1);
}