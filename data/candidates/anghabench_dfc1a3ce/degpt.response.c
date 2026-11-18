void TH_float2halfbits(float *src,unsigned_short *dest)

{
  float fVar1;
  ushort uVar2;
  float fVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint mantissa;
  uint exponent;
  uint sign;
  uint lsb_m1;
  uint lsb_s1;
  uint lsb;
  uint shift;
  uint remainder;
  uint u;
  uint x;
  unsigned_short *dest_local;
  float *src_local;
  
  fVar1 = *src;
  fVar3 = ABS(fVar1);
  if ((uint)fVar3 < 0x7f800001) {
    uVar2 = (ushort)((uint)fVar1 >> 0x10) & 0x8000;
    if ((uint)fVar3 < 0x477ff000) {
      if ((uint)fVar3 < 0x33000001) {
        *dest = uVar2;
      }
      else {
        uVar4 = (uint)fVar3 >> 0x17;
        mantissa = (uint)fVar1 & 0x7fffff;
        if (uVar4 < 0x71) {
          shift._0_1_ = 0x7e - (char)uVar4;
          exponent = 0;
          mantissa = mantissa | 0x800000;
        }
        else {
          shift._0_1_ = 0xd;
          exponent = uVar4 - 0x70;
        }
        uVar4 = 1 << ((byte)shift & 0x1f);
        uVar5 = uVar4 >> 1;
        uVar4 = mantissa & uVar4 - 1;
        uVar6 = mantissa >> ((byte)shift & 0x1f);
        mantissa._0_2_ = (ushort)uVar6;
        if (((uVar5 < uVar4) || ((uVar4 == uVar5 && ((uVar6 & 1) != 0)))) &&
           (mantissa._0_2_ = (ushort)(uVar6 + 1), (uVar6 + 1 & 0x3ff) == 0)) {
          exponent = exponent + 1;
          mantissa._0_2_ = 0;
        }
        *dest = uVar2 | (ushort)(exponent << 10) | (ushort)mantissa;
      }
    }
    else {
      *dest = uVar2 | 0x7c00;
    }
  }
  else {
    *dest = 0x7fff;
  }
  return;
}