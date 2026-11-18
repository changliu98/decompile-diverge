uint __sw_hweight32(uint w)

{
  uint uVar1;
  uint res;
  uint w_local;
  
  uVar1 = w - (w >> 1 & 0x55555555);
  uVar1 = (uVar1 & 0x33333333) + (uVar1 >> 2 & 0x33333333);
  uVar1 = uVar1 + (uVar1 >> 4) & 0xf0f0f0f;
  uVar1 = uVar1 + (uVar1 >> 8);
  return uVar1 + (uVar1 >> 0x10) & 0xff;
}