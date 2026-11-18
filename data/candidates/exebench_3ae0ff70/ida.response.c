void __cdecl mult_big(unsigned int a, unsigned int b, unsigned int *hi, unsigned int *lo)
{
  *hi = HIWORD(b) * HIWORD(a)
      + ((unsigned int)(HIWORD(b) * (unsigned __int16)a) >> 16)
      + ((unsigned int)((unsigned __int16)b * HIWORD(a)) >> 16)
      + (((((unsigned __int16)b * (unsigned int)(unsigned __int16)a) >> 16)
        + (unsigned __int16)(HIWORD(b) * a)
        + (unsigned __int16)(b * HIWORD(a))) >> 16);
  *lo = (unsigned __int16)(b * a)
      + (((((unsigned __int16)b * (unsigned int)(unsigned __int16)a) >> 16)
        + (unsigned __int16)(HIWORD(b) * a)
        + (unsigned __int16)(b * HIWORD(a))) << 16);
}