int __cdecl UnpackImmediate(unsigned int val, int *outByte, int *outShift)
{
  int i; // [rsp+0h] [rbp-1Ch]
  unsigned int vala; // [rsp+14h] [rbp-8h]

  vala = val;
  if ( val )
  {
    for ( i = 0; i < 15; ++i )
    {
      if ( (vala & 3) != 0 && vala < 0x100 )
      {
        *outByte = vala;
        *outShift = i;
        return 1;
      }
      if ( (vala & 3) != 0 )
        return 0;
      vala >>= 2;
    }
    return 0;
  }
  else
  {
    *outByte = 0;
    *outShift = 0;
    return 1;
  }
}