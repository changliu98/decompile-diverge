uLong __cdecl adler32_z(uLong adler, const Bytef *buf, z_size_t len)
{
  const Bytef *v4; // rax
  const Bytef *v6; // rax
  unsigned int n; // [rsp+0h] [rbp-2Ch]
  unsigned __int64 sum2; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2a; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2b; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2c; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2d; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2e; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2f; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2g; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2h; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2i; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2j; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2k; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2l; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2m; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2n; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2o; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2p; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2q; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2r; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2s; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2t; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2u; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2v; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2w; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2x; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2y; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2z; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2ba; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2bb; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2bc; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2bd; // [rsp+4h] [rbp-28h]
  unsigned __int64 sum2be; // [rsp+4h] [rbp-28h]
  z_size_t lena; // [rsp+Ch] [rbp-20h]
  const Bytef *bufa; // [rsp+14h] [rbp-18h]
  uLong adlera; // [rsp+1Ch] [rbp-10h]
  uLong adlerb; // [rsp+1Ch] [rbp-10h]
  uLong adlerc; // [rsp+1Ch] [rbp-10h]
  uLong adlerd; // [rsp+1Ch] [rbp-10h]
  uLong adlere; // [rsp+1Ch] [rbp-10h]
  uLong adlerf; // [rsp+1Ch] [rbp-10h]
  uLong adlerg; // [rsp+1Ch] [rbp-10h]
  uLong adlerh; // [rsp+1Ch] [rbp-10h]
  uLong adleri; // [rsp+1Ch] [rbp-10h]
  uLong adlerj; // [rsp+1Ch] [rbp-10h]
  uLong adlerk; // [rsp+1Ch] [rbp-10h]
  uLong adlerl; // [rsp+1Ch] [rbp-10h]
  uLong adlerm; // [rsp+1Ch] [rbp-10h]
  uLong adlern; // [rsp+1Ch] [rbp-10h]
  uLong adlero; // [rsp+1Ch] [rbp-10h]
  uLong adlerp; // [rsp+1Ch] [rbp-10h]
  uLong adlerq; // [rsp+1Ch] [rbp-10h]
  uLong adlerr; // [rsp+1Ch] [rbp-10h]
  uLong adlers; // [rsp+1Ch] [rbp-10h]
  uLong adlert; // [rsp+1Ch] [rbp-10h]
  uLong adleru; // [rsp+1Ch] [rbp-10h]
  uLong adlerv; // [rsp+1Ch] [rbp-10h]
  uLong adlerw; // [rsp+1Ch] [rbp-10h]
  uLong adlerx; // [rsp+1Ch] [rbp-10h]
  uLong adlery; // [rsp+1Ch] [rbp-10h]
  uLong adlerz; // [rsp+1Ch] [rbp-10h]
  uLong adlerba; // [rsp+1Ch] [rbp-10h]
  uLong adlerbb; // [rsp+1Ch] [rbp-10h]
  uLong adlerbc; // [rsp+1Ch] [rbp-10h]
  uLong adlerbd; // [rsp+1Ch] [rbp-10h]
  uLong adlerbe; // [rsp+1Ch] [rbp-10h]
  uLong adlerbf; // [rsp+1Ch] [rbp-10h]

  bufa = buf;
  lena = len;
  sum2 = WORD1(adler);
  adlera = (unsigned __int16)adler;
  if ( len == 1 )
  {
    adlerb = (unsigned __int16)adler + (unsigned __int64)*buf;
    if ( adlerb >= 0xFFF1 )
      adlerb -= 65521LL;
    sum2a = WORD1(adler) + adlerb;
    if ( sum2a >= 0xFFF1 )
      sum2a -= 65521LL;
    return (sum2a << 16) | adlerb;
  }
  else if ( buf )
  {
    if ( len >= 0x10 )
    {
      while ( lena >= 0x15B0 )
      {
        lena -= 5552LL;
        n = 347;
        do
        {
          adlerc = adlera + *bufa;
          sum2b = sum2 + adlerc;
          adlerd = adlerc + bufa[1];
          sum2c = sum2b + adlerd;
          adlere = adlerd + bufa[2];
          sum2d = sum2c + adlere;
          adlerf = adlere + bufa[3];
          sum2e = sum2d + adlerf;
          adlerg = adlerf + bufa[4];
          sum2f = sum2e + adlerg;
          adlerh = adlerg + bufa[5];
          sum2g = sum2f + adlerh;
          adleri = adlerh + bufa[6];
          sum2h = sum2g + adleri;
          adlerj = adleri + bufa[7];
          sum2i = sum2h + adlerj;
          adlerk = adlerj + bufa[8];
          sum2j = sum2i + adlerk;
          adlerl = adlerk + bufa[9];
          sum2k = sum2j + adlerl;
          adlerm = adlerl + bufa[10];
          sum2l = sum2k + adlerm;
          adlern = adlerm + bufa[11];
          sum2m = sum2l + adlern;
          adlero = adlern + bufa[12];
          sum2n = sum2m + adlero;
          adlerp = adlero + bufa[13];
          sum2o = sum2n + adlerp;
          adlerq = adlerp + bufa[14];
          sum2p = sum2o + adlerq;
          adlera = adlerq + bufa[15];
          sum2 = sum2p + adlera;
          bufa += 16;
          --n;
        }
        while ( n );
        adlera %= 0xFFF1uLL;
        sum2 %= 0xFFF1uLL;
      }
      if ( lena )
      {
        while ( lena >= 0x10 )
        {
          lena -= 16LL;
          adlerr = adlera + *bufa;
          sum2q = sum2 + adlerr;
          adlers = adlerr + bufa[1];
          sum2r = sum2q + adlers;
          adlert = adlers + bufa[2];
          sum2s = sum2r + adlert;
          adleru = adlert + bufa[3];
          sum2t = sum2s + adleru;
          adlerv = adleru + bufa[4];
          sum2u = sum2t + adlerv;
          adlerw = adlerv + bufa[5];
          sum2v = sum2u + adlerw;
          adlerx = adlerw + bufa[6];
          sum2w = sum2v + adlerx;
          adlery = adlerx + bufa[7];
          sum2x = sum2w + adlery;
          adlerz = adlery + bufa[8];
          sum2y = sum2x + adlerz;
          adlerba = adlerz + bufa[9];
          sum2z = sum2y + adlerba;
          adlerbb = adlerba + bufa[10];
          sum2ba = sum2z + adlerbb;
          adlerbc = adlerbb + bufa[11];
          sum2bb = sum2ba + adlerbc;
          adlerbd = adlerbc + bufa[12];
          sum2bc = sum2bb + adlerbd;
          adlerbe = adlerbd + bufa[13];
          sum2bd = sum2bc + adlerbe;
          adlerbf = adlerbe + bufa[14];
          sum2be = sum2bd + adlerbf;
          adlera = adlerbf + bufa[15];
          sum2 = sum2be + adlera;
          bufa += 16;
        }
        while ( lena-- )
        {
          v6 = bufa++;
          adlera += *v6;
          sum2 += adlera;
        }
        adlera %= 0xFFF1uLL;
        sum2 %= 0xFFF1uLL;
      }
      return (sum2 << 16) | adlera;
    }
    else
    {
      while ( lena-- )
      {
        v4 = bufa++;
        adlera += *v4;
        sum2 += adlera;
      }
      if ( adlera >= 0xFFF1 )
        adlera -= 65521LL;
      return ((sum2 % 0xFFF1) << 16) | adlera;
    }
  }
  else
  {
    return 1LL;
  }
}