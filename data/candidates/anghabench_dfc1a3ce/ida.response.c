void __cdecl TH_float2halfbits(float *src, unsigned __int16 *dest)
{
  unsigned int mantissa; // [rsp+0h] [rbp-38h]
  unsigned int mantissaa; // [rsp+0h] [rbp-38h]
  unsigned int exponent; // [rsp+4h] [rbp-34h]
  __int16 exponenta; // [rsp+4h] [rbp-34h]
  int sign; // [rsp+8h] [rbp-30h]
  unsigned int lsb_s1; // [rsp+10h] [rbp-28h]
  char shift; // [rsp+18h] [rbp-20h]
  unsigned int remainder; // [rsp+1Ch] [rbp-1Ch]
  unsigned int u; // [rsp+20h] [rbp-18h]

  u = *(_DWORD *)src & 0x7FFFFFFF;
  if ( u <= 0x7F800000 )
  {
    sign = HIWORD(*(_DWORD *)src) & 0x8000;
    if ( u <= 0x477FEFFF )
    {
      if ( u >= 0x33000001 )
      {
        exponent = (unsigned __int8)(u >> 23);
        mantissa = *(_DWORD *)src & 0x7FFFFF;
        if ( exponent <= 0x70 )
        {
          shift = 126 - exponent;
          exponenta = 0;
          mantissa |= 0x800000u;
        }
        else
        {
          shift = 13;
          exponenta = exponent - 112;
        }
        lsb_s1 = (unsigned int)(1 << shift) >> 1;
        remainder = ((1 << shift) - 1) & mantissa;
        mantissaa = mantissa >> shift;
        if ( remainder > lsb_s1 || remainder == lsb_s1 && (mantissaa & 1) != 0 )
        {
          LOWORD(mantissaa) = mantissaa + 1;
          if ( (mantissaa & 0x3FF) == 0 )
          {
            ++exponenta;
            LOWORD(mantissaa) = 0;
          }
        }
        *dest = mantissaa | (exponenta << 10) | sign;
      }
      else
      {
        *dest = sign;
      }
    }
    else
    {
      *dest = sign | 0x7C00;
    }
  }
  else
  {
    *dest = 0x7FFF;
  }
}