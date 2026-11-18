unsigned char linear2ulaw(short sample)
{
 int sign, exponent, mantissa;
 unsigned char ulawbyte;


 sign = (sample >> 8) & 0x80;
 if (sign != 0)
 {
  sample = 0 - sample;
 }
 sample = sample + BIAS;

 exponent = linear2ulaw_exp_lut[(sample >> 7) & 0xFF];
 mantissa = (sample >> (exponent + 3)) & 0x0F;
 ulawbyte = ~(sign | (exponent << 4) | mantissa);

 return ulawbyte;
}