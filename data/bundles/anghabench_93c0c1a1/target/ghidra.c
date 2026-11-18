uint32_t hsv2grb(uint16_t hue,uint8_t sat,uint8_t val)

{
  long lVar1;
  uint8_t uVar2;
  uint8_t uVar3;
  uint8_t uVar4;
  ushort uVar5;
  int iVar6;
  uint32_t result;
  uint8_t b;
  uint8_t g;
  uint8_t r;
  uint8_t falling;
  uint8_t rising;
  uint16_t top;
  uint16_t bottom;
  uint16_t H_accent;
  uint8_t val_local;
  uint8_t sat_local;
  uint16_t hue_local;
  
  iVar6 = (sat ^ 0xff) * (uint)val;
  uVar5 = (ushort)((uint)iVar6 >> 8);
  lVar1 = (long)(int)(((uint)(ushort)val - (uint)uVar5) * ((uint)hue % 0x3c)) * 0x88888889;
  uVar2 = (uint8_t)((uint)iVar6 >> 8);
  uVar3 = ((char)(uint)((ulong)lVar1 >> 0x25) - (char)(lVar1 >> 0x3f)) + uVar2;
  lVar1 = (long)(int)(((uint)(ushort)val - (uint)uVar5) * (((hue / 0x3c) * 0x3c - (uint)hue) + 0x3c)
                     ) * 0x88888889;
  uVar4 = ((char)(uint)((ulong)lVar1 >> 0x25) - (char)(lVar1 >> 0x3f)) + uVar2;
  switch((short)(((uint)hue + ((hue >> 3) / 0x2d) * -0x168) / 0x3c)) {
  case 0:
    b = uVar2;
    g = uVar3;
    r = val;
    break;
  case 1:
    b = uVar2;
    g = val;
    r = uVar4;
    break;
  case 2:
    b = uVar3;
    g = val;
    r = uVar2;
    break;
  case 3:
    b = val;
    g = uVar4;
    r = uVar2;
    break;
  case 4:
    b = val;
    g = uVar2;
    r = uVar3;
    break;
  case 5:
    b = uVar4;
    g = uVar2;
    r = val;
  }
  return (uint)g << 0x10 | (uint)r << 8 | (uint)b;
}