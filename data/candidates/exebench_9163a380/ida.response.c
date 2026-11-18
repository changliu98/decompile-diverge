void __cdecl rmHSVtoRGB(float h, float s, float v, float *r, float *g, float *b)
{
  float v6; // xmm0_4
  float v7; // xmm0_4
  float v8; // xmm0_4
  float ht; // [rsp+0h] [rbp-4Ch]
  unsigned __int64 tb; // [rsp+4h] [rbp-48h]
  float tr; // [rsp+Ch] [rbp-40h]
  unsigned __int64 q; // [rsp+14h] [rbp-38h]
  int i; // [rsp+20h] [rbp-2Ch]

  tr = 0.0;
  tb = 0LL;
  if ( v == 0.0 )
  {
    tr = 0.0;
    tb = 0LL;
  }
  else if ( s == 0.0 )
  {
    tr = v;
    *((float *)&tb + 1) = v;
    *(float *)&tb = v;
  }
  else
  {
    v6 = h * 6.0;
    ht = v6;
    if ( v6 >= 6.0 )
      ht = 0.0;
    i = (int)ht;
    v7 = v * (1.0 - s);
    *((float *)&q + 1) = v7;
    v8 = v * (1.0 - (float)(s * (float)(ht - (float)(int)ht)));
    *(float *)&q = v8;
    if ( (int)ht )
    {
      switch ( i )
      {
        case 1:
          tr = v * (1.0 - (float)(s * (float)(ht - (float)(int)ht)));
          *((float *)&tb + 1) = v;
          LODWORD(tb) = HIDWORD(q);
          break;
        case 2:
          tr = *((float *)&q + 1);
          *((float *)&tb + 1) = v;
          *(float *)&tb = v * (-s * (1.0 - (float)(ht - (float)(int)ht)) + 1.0);
          break;
        case 3:
          tr = *((float *)&q + 1);
          *((float *)&tb + 1) = v * (1.0 - (float)(s * (float)(ht - (float)(int)ht)));
          *(float *)&tb = v;
          break;
        case 4:
          tr = v * (-s * (1.0 - (float)(ht - (float)(int)ht)) + 1.0);
          tb = __PAIR64__(HIDWORD(q), LODWORD(v));
          break;
        case 5:
          tr = v;
          tb = q;
          break;
      }
    }
    else
    {
      tr = v;
      *((float *)&tb + 1) = v * (-s * (1.0 - (float)(ht - (float)(int)ht)) + 1.0);
      LODWORD(tb) = HIDWORD(q);
    }
  }
  *r = tr;
  *g = *((float *)&tb + 1);
  *(_DWORD *)b = tb;
}