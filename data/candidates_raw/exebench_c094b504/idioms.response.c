void do_amplify(short *orgPtr, short *destPtr, long xx, long strength)
{
  long temp1;
  while (xx-- > 0)
  {
    temp1 = *orgPtr++ * (strength / 100) + *destPtr;
    if (temp1 > 32767)
      temp1 = 32767;
    else if (temp1 < -32767)
      temp1 = -32767;
    *destPtr++ = (short)temp1;
  }
}