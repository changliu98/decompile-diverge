void __cdecl bn_mul_comba4(unsigned int *r, unsigned int *a, unsigned int *b)
{
  unsigned int ht_14; // [rsp+0h] [rbp-134h]
  unsigned int ht_14a; // [rsp+0h] [rbp-134h]
  unsigned int lt_14; // [rsp+4h] [rbp-130h]
  unsigned int m1_14; // [rsp+8h] [rbp-12Ch]
  unsigned int m_14; // [rsp+Ch] [rbp-128h]
  unsigned int ht_13; // [rsp+10h] [rbp-124h]
  unsigned int ht_13a; // [rsp+10h] [rbp-124h]
  unsigned int lt_13; // [rsp+14h] [rbp-120h]
  unsigned int m1_13; // [rsp+18h] [rbp-11Ch]
  unsigned int m_13; // [rsp+1Ch] [rbp-118h]
  unsigned int ht_12; // [rsp+20h] [rbp-114h]
  unsigned int ht_12a; // [rsp+20h] [rbp-114h]
  unsigned int lt_12; // [rsp+24h] [rbp-110h]
  unsigned int m1_12; // [rsp+28h] [rbp-10Ch]
  unsigned int m_12; // [rsp+2Ch] [rbp-108h]
  unsigned int ht_11; // [rsp+30h] [rbp-104h]
  unsigned int ht_11a; // [rsp+30h] [rbp-104h]
  unsigned int lt_11; // [rsp+34h] [rbp-100h]
  unsigned int m1_11; // [rsp+38h] [rbp-FCh]
  unsigned int m_11; // [rsp+3Ch] [rbp-F8h]
  unsigned int ht_10; // [rsp+40h] [rbp-F4h]
  unsigned int ht_10a; // [rsp+40h] [rbp-F4h]
  unsigned int lt_10; // [rsp+44h] [rbp-F0h]
  unsigned int m1_10; // [rsp+48h] [rbp-ECh]
  unsigned int m_10; // [rsp+4Ch] [rbp-E8h]
  unsigned int ht_9; // [rsp+50h] [rbp-E4h]
  unsigned int ht_9a; // [rsp+50h] [rbp-E4h]
  unsigned int lt_9; // [rsp+54h] [rbp-E0h]
  unsigned int m1_9; // [rsp+58h] [rbp-DCh]
  unsigned int m_9; // [rsp+5Ch] [rbp-D8h]
  unsigned int ht_8; // [rsp+60h] [rbp-D4h]
  unsigned int ht_8a; // [rsp+60h] [rbp-D4h]
  unsigned int lt_8; // [rsp+64h] [rbp-D0h]
  unsigned int m1_8; // [rsp+68h] [rbp-CCh]
  unsigned int m_8; // [rsp+6Ch] [rbp-C8h]
  unsigned int ht_7; // [rsp+70h] [rbp-C4h]
  unsigned int ht_7a; // [rsp+70h] [rbp-C4h]
  unsigned int lt_7; // [rsp+74h] [rbp-C0h]
  unsigned int m1_7; // [rsp+78h] [rbp-BCh]
  unsigned int m_7; // [rsp+7Ch] [rbp-B8h]
  unsigned int ht_6; // [rsp+80h] [rbp-B4h]
  unsigned int ht_6a; // [rsp+80h] [rbp-B4h]
  unsigned int lt_6; // [rsp+84h] [rbp-B0h]
  unsigned int m1_6; // [rsp+88h] [rbp-ACh]
  unsigned int m_6; // [rsp+8Ch] [rbp-A8h]
  unsigned int ht_5; // [rsp+90h] [rbp-A4h]
  unsigned int ht_5a; // [rsp+90h] [rbp-A4h]
  unsigned int lt_5; // [rsp+94h] [rbp-A0h]
  unsigned int m1_5; // [rsp+98h] [rbp-9Ch]
  unsigned int m_5; // [rsp+9Ch] [rbp-98h]
  unsigned int ht_4; // [rsp+A0h] [rbp-94h]
  unsigned int ht_4a; // [rsp+A0h] [rbp-94h]
  unsigned int lt_4; // [rsp+A4h] [rbp-90h]
  unsigned int m1_4; // [rsp+A8h] [rbp-8Ch]
  unsigned int m_4; // [rsp+ACh] [rbp-88h]
  unsigned int ht_3; // [rsp+B0h] [rbp-84h]
  unsigned int ht_3a; // [rsp+B0h] [rbp-84h]
  unsigned int lt_3; // [rsp+B4h] [rbp-80h]
  unsigned int m1_3; // [rsp+B8h] [rbp-7Ch]
  unsigned int m_3; // [rsp+BCh] [rbp-78h]
  unsigned int ht_2; // [rsp+C0h] [rbp-74h]
  unsigned int ht_2a; // [rsp+C0h] [rbp-74h]
  unsigned int lt_2; // [rsp+C4h] [rbp-70h]
  unsigned int m1_2; // [rsp+C8h] [rbp-6Ch]
  unsigned int m_2; // [rsp+CCh] [rbp-68h]
  unsigned int ht_1; // [rsp+D0h] [rbp-64h]
  unsigned int ht_1a; // [rsp+D0h] [rbp-64h]
  unsigned int lt_1; // [rsp+D4h] [rbp-60h]
  unsigned int m1_1; // [rsp+D8h] [rbp-5Ch]
  unsigned int m_1; // [rsp+DCh] [rbp-58h]
  unsigned int ht_0; // [rsp+E0h] [rbp-54h]
  unsigned int ht_0a; // [rsp+E0h] [rbp-54h]
  unsigned int lt_0; // [rsp+E4h] [rbp-50h]
  unsigned int m1_0; // [rsp+E8h] [rbp-4Ch]
  unsigned int m_0; // [rsp+ECh] [rbp-48h]
  unsigned int ht; // [rsp+F0h] [rbp-44h]
  unsigned int hta; // [rsp+F0h] [rbp-44h]
  unsigned int lt; // [rsp+F4h] [rbp-40h]
  unsigned int m1; // [rsp+F8h] [rbp-3Ch]
  unsigned int m; // [rsp+FCh] [rbp-38h]
  unsigned int c3; // [rsp+100h] [rbp-34h]
  unsigned int c3a; // [rsp+100h] [rbp-34h]
  unsigned int c3b; // [rsp+100h] [rbp-34h]
  unsigned int c3c; // [rsp+100h] [rbp-34h]
  unsigned int c3d; // [rsp+100h] [rbp-34h]
  unsigned int c3e; // [rsp+100h] [rbp-34h]
  unsigned int c3f; // [rsp+100h] [rbp-34h]
  unsigned int c3g; // [rsp+100h] [rbp-34h]
  unsigned int c3h; // [rsp+100h] [rbp-34h]
  unsigned int c3i; // [rsp+100h] [rbp-34h]
  unsigned int c3j; // [rsp+100h] [rbp-34h]
  unsigned int c2; // [rsp+104h] [rbp-30h]
  unsigned int c2a; // [rsp+104h] [rbp-30h]
  unsigned int c2b; // [rsp+104h] [rbp-30h]
  unsigned int c2c; // [rsp+104h] [rbp-30h]
  unsigned int c2d; // [rsp+104h] [rbp-30h]
  unsigned int c2e; // [rsp+104h] [rbp-30h]
  unsigned int c2f; // [rsp+104h] [rbp-30h]
  unsigned int c2g; // [rsp+104h] [rbp-30h]
  unsigned int c2h; // [rsp+104h] [rbp-30h]
  unsigned int c2i; // [rsp+104h] [rbp-30h]
  unsigned int c1; // [rsp+108h] [rbp-2Ch]
  unsigned int c1a; // [rsp+108h] [rbp-2Ch]
  unsigned int c1b; // [rsp+108h] [rbp-2Ch]
  unsigned int c1c; // [rsp+108h] [rbp-2Ch]
  unsigned int c1d; // [rsp+108h] [rbp-2Ch]
  unsigned int c1e; // [rsp+108h] [rbp-2Ch]
  unsigned int c1f; // [rsp+108h] [rbp-2Ch]
  unsigned int c1g; // [rsp+108h] [rbp-2Ch]
  unsigned int c1h; // [rsp+108h] [rbp-2Ch]
  unsigned int c1i; // [rsp+108h] [rbp-2Ch]
  unsigned int c1j; // [rsp+108h] [rbp-2Ch]
  unsigned int c1k; // [rsp+108h] [rbp-2Ch]
  unsigned int t2o; // [rsp+10Ch] [rbp-28h]
  unsigned int t2p; // [rsp+10Ch] [rbp-28h]
  unsigned int t2; // [rsp+10Ch] [rbp-28h]
  unsigned int t2q; // [rsp+10Ch] [rbp-28h]
  unsigned int t2a; // [rsp+10Ch] [rbp-28h]
  unsigned int t2r; // [rsp+10Ch] [rbp-28h]
  unsigned int t2b; // [rsp+10Ch] [rbp-28h]
  unsigned int t2s; // [rsp+10Ch] [rbp-28h]
  unsigned int t2c; // [rsp+10Ch] [rbp-28h]
  unsigned int t2t; // [rsp+10Ch] [rbp-28h]
  unsigned int t2d; // [rsp+10Ch] [rbp-28h]
  unsigned int t2u; // [rsp+10Ch] [rbp-28h]
  unsigned int t2e; // [rsp+10Ch] [rbp-28h]
  unsigned int t2v; // [rsp+10Ch] [rbp-28h]
  unsigned int t2f; // [rsp+10Ch] [rbp-28h]
  unsigned int t2w; // [rsp+10Ch] [rbp-28h]
  unsigned int t2g; // [rsp+10Ch] [rbp-28h]
  unsigned int t2x; // [rsp+10Ch] [rbp-28h]
  unsigned int t2h; // [rsp+10Ch] [rbp-28h]
  unsigned int t2y; // [rsp+10Ch] [rbp-28h]
  unsigned int t2i; // [rsp+10Ch] [rbp-28h]
  unsigned int t2z; // [rsp+10Ch] [rbp-28h]
  unsigned int t2j; // [rsp+10Ch] [rbp-28h]
  unsigned int t2ba; // [rsp+10Ch] [rbp-28h]
  unsigned int t2k; // [rsp+10Ch] [rbp-28h]
  unsigned int t2bb; // [rsp+10Ch] [rbp-28h]
  unsigned int t2l; // [rsp+10Ch] [rbp-28h]
  unsigned int t2bc; // [rsp+10Ch] [rbp-28h]
  unsigned int t2m; // [rsp+10Ch] [rbp-28h]
  unsigned int t2bd; // [rsp+10Ch] [rbp-28h]
  unsigned int t2n; // [rsp+10Ch] [rbp-28h]
  unsigned int t1; // [rsp+110h] [rbp-24h]
  unsigned int t1a; // [rsp+110h] [rbp-24h]
  unsigned int t1b; // [rsp+110h] [rbp-24h]
  unsigned int t1c; // [rsp+110h] [rbp-24h]
  unsigned int t1d; // [rsp+110h] [rbp-24h]
  unsigned int t1e; // [rsp+110h] [rbp-24h]
  unsigned int t1f; // [rsp+110h] [rbp-24h]
  unsigned int t1g; // [rsp+110h] [rbp-24h]
  unsigned int t1h; // [rsp+110h] [rbp-24h]
  unsigned int t1i; // [rsp+110h] [rbp-24h]
  unsigned int t1j; // [rsp+110h] [rbp-24h]
  unsigned int t1k; // [rsp+110h] [rbp-24h]
  unsigned int t1l; // [rsp+110h] [rbp-24h]
  unsigned int t1m; // [rsp+110h] [rbp-24h]
  unsigned int t1n; // [rsp+110h] [rbp-24h]
  unsigned int t1o; // [rsp+110h] [rbp-24h]
  unsigned int bh_0; // [rsp+114h] [rbp-20h]
  unsigned int bh_0a; // [rsp+114h] [rbp-20h]
  unsigned int bh_0b; // [rsp+114h] [rbp-20h]
  unsigned int bh_0c; // [rsp+114h] [rbp-20h]
  unsigned int bh_0d; // [rsp+114h] [rbp-20h]
  unsigned int bh_0e; // [rsp+114h] [rbp-20h]
  unsigned int bh_0f; // [rsp+114h] [rbp-20h]
  unsigned int bh_0g; // [rsp+114h] [rbp-20h]
  unsigned int bh_0h; // [rsp+114h] [rbp-20h]
  unsigned int bh_0i; // [rsp+114h] [rbp-20h]
  unsigned int bh_0j; // [rsp+114h] [rbp-20h]
  unsigned int bh_0k; // [rsp+114h] [rbp-20h]
  unsigned int bh_0l; // [rsp+114h] [rbp-20h]
  unsigned int bh_0m; // [rsp+114h] [rbp-20h]
  unsigned int bh_0n; // [rsp+114h] [rbp-20h]
  unsigned int bh_0o; // [rsp+114h] [rbp-20h]
  unsigned int bl_0; // [rsp+118h] [rbp-1Ch]
  unsigned int bl_0a; // [rsp+118h] [rbp-1Ch]
  unsigned int bl_0b; // [rsp+118h] [rbp-1Ch]
  unsigned int bl_0c; // [rsp+118h] [rbp-1Ch]
  unsigned int bl_0d; // [rsp+118h] [rbp-1Ch]
  unsigned int bl_0e; // [rsp+118h] [rbp-1Ch]
  unsigned int bl_0f; // [rsp+118h] [rbp-1Ch]
  unsigned int bl_0g; // [rsp+118h] [rbp-1Ch]
  unsigned int bl_0h; // [rsp+118h] [rbp-1Ch]
  unsigned int bl_0i; // [rsp+118h] [rbp-1Ch]
  unsigned int bl_0j; // [rsp+118h] [rbp-1Ch]
  unsigned int bl_0k; // [rsp+118h] [rbp-1Ch]
  unsigned int bl_0l; // [rsp+118h] [rbp-1Ch]
  unsigned int bl_0m; // [rsp+118h] [rbp-1Ch]
  unsigned int bl_0n; // [rsp+118h] [rbp-1Ch]
  unsigned int bl_0o; // [rsp+118h] [rbp-1Ch]

  t1 = (unsigned __int16)*a;
  t2o = HIWORD(*a);
  bl_0 = (unsigned __int16)*b;
  bh_0 = HIWORD(*b);
  ht = t2o * bh_0;
  m = t2o * bl_0 + t1 * bh_0;
  if ( m < t2o * bl_0 )
    ht += 0x10000;
  hta = ht + HIWORD(m);
  m1 = (unsigned __int16)m << 16;
  lt = m1 + t1 * bl_0;
  if ( lt < m1 )
    ++hta;
  *r = lt;
  c1 = 0;
  t1a = (unsigned __int16)*a;
  t2p = HIWORD(*a);
  bl_0a = (unsigned __int16)b[1];
  bh_0a = HIWORD(b[1]);
  ht_0 = t2p * bh_0a;
  m_0 = t2p * bl_0a + t1a * bh_0a;
  if ( m_0 < t2p * bl_0a )
    ht_0 += 0x10000;
  ht_0a = ht_0 + HIWORD(m_0);
  m1_0 = (unsigned __int16)m_0 << 16;
  lt_0 = m1_0 + t1a * bl_0a;
  if ( lt_0 < m1_0 )
    ++ht_0a;
  t2 = ht_0a;
  if ( lt_0 + hta < lt_0 )
    t2 = ht_0a + 1;
  c3 = t2;
  t1b = (unsigned __int16)a[1];
  t2q = HIWORD(a[1]);
  bl_0b = (unsigned __int16)*b;
  bh_0b = HIWORD(*b);
  ht_1 = t2q * bh_0b;
  m_1 = t2q * bl_0b + t1b * bh_0b;
  if ( m_1 < t2q * bl_0b )
    ht_1 += 0x10000;
  ht_1a = ht_1 + HIWORD(m_1);
  m1_1 = (unsigned __int16)m_1 << 16;
  lt_1 = m1_1 + t1b * bl_0b;
  if ( lt_1 < m1_1 )
    ++ht_1a;
  t2a = ht_1a;
  c2 = lt_1 + lt_0 + hta;
  if ( c2 < lt_1 )
    t2a = ht_1a + 1;
  c3a = t2a + c3;
  if ( c3a < t2a )
    c1 = 1;
  r[1] = c2;
  c2a = 0;
  t1c = (unsigned __int16)a[2];
  t2r = HIWORD(a[2]);
  bl_0c = (unsigned __int16)*b;
  bh_0c = HIWORD(*b);
  ht_2 = t2r * bh_0c;
  m_2 = t2r * bl_0c + t1c * bh_0c;
  if ( m_2 < t2r * bl_0c )
    ht_2 += 0x10000;
  ht_2a = ht_2 + HIWORD(m_2);
  m1_2 = (unsigned __int16)m_2 << 16;
  lt_2 = m1_2 + t1c * bl_0c;
  if ( lt_2 < m1_2 )
    ++ht_2a;
  t2b = ht_2a;
  c3b = lt_2 + c3a;
  if ( c3b < lt_2 )
    t2b = ht_2a + 1;
  c1a = t2b + c1;
  if ( c1a < t2b )
    c2a = 1;
  t1d = (unsigned __int16)a[1];
  t2s = HIWORD(a[1]);
  bl_0d = (unsigned __int16)b[1];
  bh_0d = HIWORD(b[1]);
  ht_3 = t2s * bh_0d;
  m_3 = t2s * bl_0d + t1d * bh_0d;
  if ( m_3 < t2s * bl_0d )
    ht_3 += 0x10000;
  ht_3a = ht_3 + HIWORD(m_3);
  m1_3 = (unsigned __int16)m_3 << 16;
  lt_3 = m1_3 + t1d * bl_0d;
  if ( lt_3 < m1_3 )
    ++ht_3a;
  t2c = ht_3a;
  c3c = lt_3 + c3b;
  if ( c3c < lt_3 )
    t2c = ht_3a + 1;
  c1b = t2c + c1a;
  if ( c1b < t2c )
    ++c2a;
  t1e = (unsigned __int16)*a;
  t2t = HIWORD(*a);
  bl_0e = (unsigned __int16)b[2];
  bh_0e = HIWORD(b[2]);
  ht_4 = t2t * bh_0e;
  m_4 = t2t * bl_0e + t1e * bh_0e;
  if ( m_4 < t2t * bl_0e )
    ht_4 += 0x10000;
  ht_4a = ht_4 + HIWORD(m_4);
  m1_4 = (unsigned __int16)m_4 << 16;
  lt_4 = m1_4 + t1e * bl_0e;
  if ( lt_4 < m1_4 )
    ++ht_4a;
  t2d = ht_4a;
  c3d = lt_4 + c3c;
  if ( c3d < lt_4 )
    t2d = ht_4a + 1;
  c1c = t2d + c1b;
  if ( c1c < t2d )
    ++c2a;
  r[2] = c3d;
  c3e = 0;
  t1f = (unsigned __int16)*a;
  t2u = HIWORD(*a);
  bl_0f = (unsigned __int16)b[3];
  bh_0f = HIWORD(b[3]);
  ht_5 = t2u * bh_0f;
  m_5 = t2u * bl_0f + t1f * bh_0f;
  if ( m_5 < t2u * bl_0f )
    ht_5 += 0x10000;
  ht_5a = ht_5 + HIWORD(m_5);
  m1_5 = (unsigned __int16)m_5 << 16;
  lt_5 = m1_5 + t1f * bl_0f;
  if ( lt_5 < m1_5 )
    ++ht_5a;
  t2e = ht_5a;
  c1d = lt_5 + c1c;
  if ( c1d < lt_5 )
    t2e = ht_5a + 1;
  c2b = t2e + c2a;
  if ( c2b < t2e )
    c3e = 1;
  t1g = (unsigned __int16)a[1];
  t2v = HIWORD(a[1]);
  bl_0g = (unsigned __int16)b[2];
  bh_0g = HIWORD(b[2]);
  ht_6 = t2v * bh_0g;
  m_6 = t2v * bl_0g + t1g * bh_0g;
  if ( m_6 < t2v * bl_0g )
    ht_6 += 0x10000;
  ht_6a = ht_6 + HIWORD(m_6);
  m1_6 = (unsigned __int16)m_6 << 16;
  lt_6 = m1_6 + t1g * bl_0g;
  if ( lt_6 < m1_6 )
    ++ht_6a;
  t2f = ht_6a;
  c1e = lt_6 + c1d;
  if ( c1e < lt_6 )
    t2f = ht_6a + 1;
  c2c = t2f + c2b;
  if ( c2c < t2f )
    ++c3e;
  t1h = (unsigned __int16)a[2];
  t2w = HIWORD(a[2]);
  bl_0h = (unsigned __int16)b[1];
  bh_0h = HIWORD(b[1]);
  ht_7 = t2w * bh_0h;
  m_7 = t2w * bl_0h + t1h * bh_0h;
  if ( m_7 < t2w * bl_0h )
    ht_7 += 0x10000;
  ht_7a = ht_7 + HIWORD(m_7);
  m1_7 = (unsigned __int16)m_7 << 16;
  lt_7 = m1_7 + t1h * bl_0h;
  if ( lt_7 < m1_7 )
    ++ht_7a;
  t2g = ht_7a;
  c1f = lt_7 + c1e;
  if ( c1f < lt_7 )
    t2g = ht_7a + 1;
  c2d = t2g + c2c;
  if ( c2d < t2g )
    ++c3e;
  t1i = (unsigned __int16)a[3];
  t2x = HIWORD(a[3]);
  bl_0i = (unsigned __int16)*b;
  bh_0i = HIWORD(*b);
  ht_8 = t2x * bh_0i;
  m_8 = t2x * bl_0i + t1i * bh_0i;
  if ( m_8 < t2x * bl_0i )
    ht_8 += 0x10000;
  ht_8a = ht_8 + HIWORD(m_8);
  m1_8 = (unsigned __int16)m_8 << 16;
  lt_8 = m1_8 + t1i * bl_0i;
  if ( lt_8 < m1_8 )
    ++ht_8a;
  t2h = ht_8a;
  c1g = lt_8 + c1f;
  if ( c1g < lt_8 )
    t2h = ht_8a + 1;
  c2e = t2h + c2d;
  if ( c2e < t2h )
    ++c3e;
  r[3] = c1g;
  c1h = 0;
  t1j = (unsigned __int16)a[3];
  t2y = HIWORD(a[3]);
  bl_0j = (unsigned __int16)b[1];
  bh_0j = HIWORD(b[1]);
  ht_9 = t2y * bh_0j;
  m_9 = t2y * bl_0j + t1j * bh_0j;
  if ( m_9 < t2y * bl_0j )
    ht_9 += 0x10000;
  ht_9a = ht_9 + HIWORD(m_9);
  m1_9 = (unsigned __int16)m_9 << 16;
  lt_9 = m1_9 + t1j * bl_0j;
  if ( lt_9 < m1_9 )
    ++ht_9a;
  t2i = ht_9a;
  c2f = lt_9 + c2e;
  if ( c2f < lt_9 )
    t2i = ht_9a + 1;
  c3f = t2i + c3e;
  if ( c3f < t2i )
    c1h = 1;
  t1k = (unsigned __int16)a[2];
  t2z = HIWORD(a[2]);
  bl_0k = (unsigned __int16)b[2];
  bh_0k = HIWORD(b[2]);
  ht_10 = t2z * bh_0k;
  m_10 = t2z * bl_0k + t1k * bh_0k;
  if ( m_10 < t2z * bl_0k )
    ht_10 += 0x10000;
  ht_10a = ht_10 + HIWORD(m_10);
  m1_10 = (unsigned __int16)m_10 << 16;
  lt_10 = m1_10 + t1k * bl_0k;
  if ( lt_10 < m1_10 )
    ++ht_10a;
  t2j = ht_10a;
  c2g = lt_10 + c2f;
  if ( c2g < lt_10 )
    t2j = ht_10a + 1;
  c3g = t2j + c3f;
  if ( c3g < t2j )
    ++c1h;
  t1l = (unsigned __int16)a[1];
  t2ba = HIWORD(a[1]);
  bl_0l = (unsigned __int16)b[3];
  bh_0l = HIWORD(b[3]);
  ht_11 = t2ba * bh_0l;
  m_11 = t2ba * bl_0l + t1l * bh_0l;
  if ( m_11 < t2ba * bl_0l )
    ht_11 += 0x10000;
  ht_11a = ht_11 + HIWORD(m_11);
  m1_11 = (unsigned __int16)m_11 << 16;
  lt_11 = m1_11 + t1l * bl_0l;
  if ( lt_11 < m1_11 )
    ++ht_11a;
  t2k = ht_11a;
  c2h = lt_11 + c2g;
  if ( c2h < lt_11 )
    t2k = ht_11a + 1;
  c3h = t2k + c3g;
  if ( c3h < t2k )
    ++c1h;
  r[4] = c2h;
  c2i = 0;
  t1m = (unsigned __int16)a[2];
  t2bb = HIWORD(a[2]);
  bl_0m = (unsigned __int16)b[3];
  bh_0m = HIWORD(b[3]);
  ht_12 = t2bb * bh_0m;
  m_12 = t2bb * bl_0m + t1m * bh_0m;
  if ( m_12 < t2bb * bl_0m )
    ht_12 += 0x10000;
  ht_12a = ht_12 + HIWORD(m_12);
  m1_12 = (unsigned __int16)m_12 << 16;
  lt_12 = m1_12 + t1m * bl_0m;
  if ( lt_12 < m1_12 )
    ++ht_12a;
  t2l = ht_12a;
  c3i = lt_12 + c3h;
  if ( c3i < lt_12 )
    t2l = ht_12a + 1;
  c1i = t2l + c1h;
  if ( c1i < t2l )
    c2i = 1;
  t1n = (unsigned __int16)a[3];
  t2bc = HIWORD(a[3]);
  bl_0n = (unsigned __int16)b[2];
  bh_0n = HIWORD(b[2]);
  ht_13 = t2bc * bh_0n;
  m_13 = t2bc * bl_0n + t1n * bh_0n;
  if ( m_13 < t2bc * bl_0n )
    ht_13 += 0x10000;
  ht_13a = ht_13 + HIWORD(m_13);
  m1_13 = (unsigned __int16)m_13 << 16;
  lt_13 = m1_13 + t1n * bl_0n;
  if ( lt_13 < m1_13 )
    ++ht_13a;
  t2m = ht_13a;
  c3j = lt_13 + c3i;
  if ( c3j < lt_13 )
    t2m = ht_13a + 1;
  c1j = t2m + c1i;
  if ( c1j < t2m )
    ++c2i;
  r[5] = c3j;
  t1o = (unsigned __int16)a[3];
  t2bd = HIWORD(a[3]);
  bl_0o = (unsigned __int16)b[3];
  bh_0o = HIWORD(b[3]);
  ht_14 = t2bd * bh_0o;
  m_14 = t2bd * bl_0o + t1o * bh_0o;
  if ( m_14 < t2bd * bl_0o )
    ht_14 += 0x10000;
  ht_14a = ht_14 + HIWORD(m_14);
  m1_14 = (unsigned __int16)m_14 << 16;
  lt_14 = m1_14 + t1o * bl_0o;
  if ( lt_14 < m1_14 )
    ++ht_14a;
  t2n = ht_14a;
  c1k = lt_14 + c1j;
  if ( c1k < lt_14 )
    t2n = ht_14a + 1;
  r[6] = c1k;
  r[7] = t2n + c2i;
}