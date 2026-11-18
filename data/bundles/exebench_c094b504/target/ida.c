void __cdecl ComputeReverb16(short *orgPtr, short *destPtr, long xx, long strength)
{
  __int64 v4; // rax
  short *v5; // rcx
  short *v6; // rax
  long temp1; // [rsp+18h] [rbp-28h]

  while ( 1 )
  {
    v4 = xx--;
    if ( v4 <= 0 )
      break;
    v5 = orgPtr++;
    temp1 = *v5 * strength / 100 + *destPtr;
    if ( temp1 <= 0x7FFF )
    {
      if ( temp1 < -32767 )
        LOWORD(temp1) = -32767;
    }
    else
    {
      LOWORD(temp1) = 0x7FFF;
    }
    v6 = destPtr++;
    *v6 = temp1;
  }
}