
void ComputeReverb16( short *orgPtr, short *destPtr, long xx, long strength)
{
 long temp1;
 long valP = 0x7FFFL, valN = -0x7FFFL;

 while( xx-- > 0)
 {
  temp1 = *destPtr + ((strength * (long) *orgPtr++) / 100);

  if( temp1 > valP) temp1 = valP;
  else if( temp1 < valN ) temp1 = valN;

  *destPtr++ = temp1;
 }
}
