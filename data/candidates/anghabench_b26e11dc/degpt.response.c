uint __sw_hweight16(uint w)

{
  uint uVar1;
  uint res;
  uint w_local;
  
  uVar1 = w - (w >> 1 & 0x5555);
  uVar1 = (uVar1 & 0x3333) + (uVar1 >> 2 & 0x3333);
  uVar1 = uVar1 + (uVar1 >> 4) & 0xf0f;
  return uVar1 + (uVar1 >> 8) & 0xff;
}