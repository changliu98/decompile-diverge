void __cdecl stb_linear_controller(float *curpos, float target_pos, float acc, float deacc, float dt)
{
  float cp; // [rsp+0h] [rbp-24h]
  float p; // [rsp+4h] [rbp-20h]
  float pa; // [rsp+4h] [rbp-20h]
  float sign; // [rsp+8h] [rbp-1Ch]
  float dta; // [rsp+Ch] [rbp-18h]
  float target_posa; // [rsp+18h] [rbp-Ch]

  target_posa = target_pos;
  dta = dt;
  sign = 1.0;
  cp = *curpos;
  if ( *curpos != target_pos )
  {
    if ( cp > target_pos )
    {
      LODWORD(target_posa) = _mm_cvtsi128_si32((__m128i)LODWORD(target_pos)) ^ 0x80000000;
      LODWORD(cp) = _mm_cvtsi128_si32((__m128i)LODWORD(cp)) ^ 0x80000000;
      sign = -1.0;
    }
    if ( cp < 0.0 )
    {
      p = (float)(deacc * dt) + cp;
      if ( p <= 0.0 )
      {
        dta = 0.0;
      }
      else
      {
        p = 0.0;
        dta = dt - (float)(cp / deacc);
        if ( dta < 0.0 )
          dta = 0.0;
      }
      cp = p;
    }
    pa = (float)(acc * dta) + cp;
    if ( pa > target_posa )
      pa = target_posa;
    *curpos = pa * sign;
  }
}