float __cdecl RGB(float H, float M1, float M2)
{
  float v3; // xmm0_4
  float v4; // xmm0_4
  float Ha; // [rsp+8h] [rbp-8h]

  Ha = H;
  if ( H >= 0.0 )
  {
    if ( H > 360.0 )
    {
      v4 = H - 360.0;
      Ha = v4;
    }
  }
  else
  {
    v3 = H + 360.0;
    Ha = v3;
  }
  if ( Ha >= 60.0 )
  {
    if ( Ha >= 180.0 )
    {
      if ( Ha >= 240.0 )
        return M1;
      else
        return M1 + (float)((float)(M2 - M1) * (float)(240.0 - Ha)) / 60.0;
    }
    else
    {
      return M2;
    }
  }
  else
  {
    return M1 + (float)((float)(M2 - M1) * Ha) / 60.0;
  }
}