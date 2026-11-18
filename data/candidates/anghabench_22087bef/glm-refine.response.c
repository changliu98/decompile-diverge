unsigned __int8 __cdecl linear2ulaw(short sample)
{
  int exponent;
  int sign;
  short abs_sample;

  // Determine the sign bit. If the sample is negative, sign will be 0x80.
  sign = (sample >> 8) & 0x80;
  
  // Calculate the absolute value of the sample
  abs_sample = sign ? -sample : sample;

  // Add the mu-law bias (0x84) to increase dynamic range
  abs_sample += BIAS;

  // Find the exponent using a lookup table based on the high bits
  exponent = linear2ulaw_exp_lut[(unsigned __int8)(abs_sample >> 7)];

  // Construct the final mu-law byte:
  // - Sign bit (0x80 if negative)
  // - Exponent shifted into bits 4-6
  // - Mantissa (4 bits) shifted out of the biased sample
  // Finally, invert all bits (as per the mu-law standard)
  return ~(sign | (exponent << 4) | ((abs_sample >> (exponent + 3)) & 0xF));
}