void __cdecl ComputeReverb16(short *orgPtr, short *destPtr, long xx, long strength)
{
  long temp1;

  while ( xx-- > 0 )
  {
    // Mix the original sample scaled by 'strength' with the destination sample
    temp1 = *orgPtr++ * strength / 100 + *destPtr;

    // Clamp the mixed result to 16-bit signed audio bounds
    if ( temp1 > 0x7FFF )
    {
      temp1 = 0x7FFF;
    }
    else if ( temp1 < -32767 )
    {
      temp1 = -32767;
    }

    // Write back the clamped 16-bit result
    *destPtr++ = (short)temp1;
  }
}