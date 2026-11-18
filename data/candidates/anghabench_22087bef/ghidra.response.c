uchar linear2ulaw(short sample)

{
  ushort uVar1;
  uchar ulawbyte;
  int mantissa;
  int exponent;
  int sign;
  short sample_local;
  
  uVar1 = sample >> 8 & 0x80;
  sample_local = sample;
  if (uVar1 != 0) {
    sample_local = -sample;
  }
  return ((byte)uVar1 |
          (byte)(linear2ulaw::exp_lut[(int)((int)(short)(sample_local + BIAS) >> 7 & 0xff)] << 4) |
         (byte)((int)(short)(sample_local + BIAS) >>
               ((char)linear2ulaw::exp_lut[(int)((int)(short)(sample_local + BIAS) >> 7 & 0xff)] +
                3U & 0x1f)) & 0xf) ^ 0xff;
}