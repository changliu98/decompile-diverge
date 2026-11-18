unsigned __int8 __cdecl linear2ulaw(short sample)
{
  int exponent; // [rsp+6h] [rbp-Ch]
  int sign; // [rsp+Ah] [rbp-8h]
  short samplea; // [rsp+10h] [rbp-2h]
  short sampleb; // [rsp+10h] [rbp-2h]

  samplea = sample;
  sign = (sample >> 8) & 0x80;
  if ( sign )
    samplea = -sample;
  sampleb = BIAS + samplea;
  exponent = linear2ulaw_exp_lut[(unsigned __int8)(sampleb >> 7)];
  return ~((sampleb >> (exponent + 3)) & 0xF | (16 * exponent) | sign);
}