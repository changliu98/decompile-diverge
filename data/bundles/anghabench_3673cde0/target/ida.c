float __cdecl modff(float x, float *iptr)
{
  int e; // [rsp+0h] [rbp-20h]
  union {float f;uint32_t i;} u; // [rsp+8h] [rbp-18h]
  float v5; // [rsp+1Ch] [rbp-4h]

  e = (unsigned __int8)(LODWORD(x) >> 23) - 127;
  if ( e < 23 )
  {
    if ( e >= 0 )
    {
      if ( ((0x7FFFFF >> e) & LODWORD(x)) != 0 )
      {
        u.i = LODWORD(x) & ~(0x7FFFFF >> e);
        *iptr = u.f;
        return x - u.f;
      }
      else
      {
        *iptr = x;
        LODWORD(v5) = LODWORD(x) & 0x80000000;
      }
    }
    else
    {
      *(_DWORD *)iptr = LODWORD(x) & 0x80000000;
      return x;
    }
  }
  else
  {
    *iptr = x;
    if ( (unsigned __int8)(LODWORD(x) >> 23) == 255 && LODWORD(x) << 9 )
      return x;
    else
      LODWORD(v5) = LODWORD(x) & 0x80000000;
  }
  return v5;
}