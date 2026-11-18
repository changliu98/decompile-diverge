void __cdecl bn_sqr_comba8(unsigned int *r, const unsigned int *a)
{
  unsigned __int16 m_34; // [rsp+0h] [rbp-24Ch]
  unsigned int m_34a; // [rsp+0h] [rbp-24Ch]
  unsigned int h_6a; // [rsp+4h] [rbp-248h]
  unsigned int h_6b; // [rsp+4h] [rbp-248h]
  unsigned int h_6; // [rsp+4h] [rbp-248h]
  unsigned int l_6a; // [rsp+8h] [rbp-244h]
  unsigned int l_6; // [rsp+8h] [rbp-244h]
  unsigned int ht_26; // [rsp+Ch] [rbp-240h]
  unsigned int ht_26a; // [rsp+Ch] [rbp-240h]
  unsigned int lt_26; // [rsp+10h] [rbp-23Ch]
  unsigned int m1_26; // [rsp+14h] [rbp-238h]
  unsigned int m_33; // [rsp+18h] [rbp-234h]
  unsigned int ht_25; // [rsp+1Ch] [rbp-230h]
  unsigned int ht_25a; // [rsp+1Ch] [rbp-230h]
  unsigned int lt_25; // [rsp+20h] [rbp-22Ch]
  unsigned int m1_25; // [rsp+24h] [rbp-228h]
  unsigned int m_32; // [rsp+28h] [rbp-224h]
  unsigned __int16 m_31; // [rsp+2Ch] [rbp-220h]
  unsigned int m_31a; // [rsp+2Ch] [rbp-220h]
  unsigned int h_5a; // [rsp+30h] [rbp-21Ch]
  unsigned int h_5b; // [rsp+30h] [rbp-21Ch]
  unsigned int h_5; // [rsp+30h] [rbp-21Ch]
  unsigned int l_5a; // [rsp+34h] [rbp-218h]
  unsigned int l_5; // [rsp+34h] [rbp-218h]
  unsigned int ht_24; // [rsp+38h] [rbp-214h]
  unsigned int ht_24a; // [rsp+38h] [rbp-214h]
  unsigned int lt_24; // [rsp+3Ch] [rbp-210h]
  unsigned int m1_24; // [rsp+40h] [rbp-20Ch]
  unsigned int m_30; // [rsp+44h] [rbp-208h]
  unsigned int ht_23; // [rsp+48h] [rbp-204h]
  unsigned int ht_23a; // [rsp+48h] [rbp-204h]
  unsigned int lt_23; // [rsp+4Ch] [rbp-200h]
  unsigned int m1_23; // [rsp+50h] [rbp-1FCh]
  unsigned int m_29; // [rsp+54h] [rbp-1F8h]
  unsigned int ht_22; // [rsp+58h] [rbp-1F4h]
  unsigned int ht_22a; // [rsp+58h] [rbp-1F4h]
  unsigned int lt_22; // [rsp+5Ch] [rbp-1F0h]
  unsigned int m1_22; // [rsp+60h] [rbp-1ECh]
  unsigned int m_28; // [rsp+64h] [rbp-1E8h]
  unsigned int ht_21; // [rsp+68h] [rbp-1E4h]
  unsigned int ht_21a; // [rsp+68h] [rbp-1E4h]
  unsigned int lt_21; // [rsp+6Ch] [rbp-1E0h]
  unsigned int m1_21; // [rsp+70h] [rbp-1DCh]
  unsigned int m_27; // [rsp+74h] [rbp-1D8h]
  unsigned __int16 m_26; // [rsp+78h] [rbp-1D4h]
  unsigned int m_26a; // [rsp+78h] [rbp-1D4h]
  unsigned int h_4a; // [rsp+7Ch] [rbp-1D0h]
  unsigned int h_4b; // [rsp+7Ch] [rbp-1D0h]
  unsigned int h_4; // [rsp+7Ch] [rbp-1D0h]
  unsigned int l_4a; // [rsp+80h] [rbp-1CCh]
  unsigned int l_4; // [rsp+80h] [rbp-1CCh]
  unsigned int ht_20; // [rsp+84h] [rbp-1C8h]
  unsigned int ht_20a; // [rsp+84h] [rbp-1C8h]
  unsigned int lt_20; // [rsp+88h] [rbp-1C4h]
  unsigned int m1_20; // [rsp+8Ch] [rbp-1C0h]
  unsigned int m_25; // [rsp+90h] [rbp-1BCh]
  unsigned int ht_19; // [rsp+94h] [rbp-1B8h]
  unsigned int ht_19a; // [rsp+94h] [rbp-1B8h]
  unsigned int lt_19; // [rsp+98h] [rbp-1B4h]
  unsigned int m1_19; // [rsp+9Ch] [rbp-1B0h]
  unsigned int m_24; // [rsp+A0h] [rbp-1ACh]
  unsigned int ht_18; // [rsp+A4h] [rbp-1A8h]
  unsigned int ht_18a; // [rsp+A4h] [rbp-1A8h]
  unsigned int lt_18; // [rsp+A8h] [rbp-1A4h]
  unsigned int m1_18; // [rsp+ACh] [rbp-1A0h]
  unsigned int m_23; // [rsp+B0h] [rbp-19Ch]
  unsigned int ht_17; // [rsp+B4h] [rbp-198h]
  unsigned int ht_17a; // [rsp+B4h] [rbp-198h]
  unsigned int lt_17; // [rsp+B8h] [rbp-194h]
  unsigned int m1_17; // [rsp+BCh] [rbp-190h]
  unsigned int m_22; // [rsp+C0h] [rbp-18Ch]
  unsigned int ht_16; // [rsp+C4h] [rbp-188h]
  unsigned int ht_16a; // [rsp+C4h] [rbp-188h]
  unsigned int lt_16; // [rsp+C8h] [rbp-184h]
  unsigned int m1_16; // [rsp+CCh] [rbp-180h]
  unsigned int m_21; // [rsp+D0h] [rbp-17Ch]
  unsigned int ht_15; // [rsp+D4h] [rbp-178h]
  unsigned int ht_15a; // [rsp+D4h] [rbp-178h]
  unsigned int lt_15; // [rsp+D8h] [rbp-174h]
  unsigned int m1_15; // [rsp+DCh] [rbp-170h]
  unsigned int m_20; // [rsp+E0h] [rbp-16Ch]
  unsigned __int16 m_19; // [rsp+E4h] [rbp-168h]
  unsigned int m_19a; // [rsp+E4h] [rbp-168h]
  unsigned int h_3a; // [rsp+E8h] [rbp-164h]
  unsigned int h_3b; // [rsp+E8h] [rbp-164h]
  unsigned int h_3; // [rsp+E8h] [rbp-164h]
  unsigned int l_3a; // [rsp+ECh] [rbp-160h]
  unsigned int l_3; // [rsp+ECh] [rbp-160h]
  unsigned int ht_14; // [rsp+F0h] [rbp-15Ch]
  unsigned int ht_14a; // [rsp+F0h] [rbp-15Ch]
  unsigned int lt_14; // [rsp+F4h] [rbp-158h]
  unsigned int m1_14; // [rsp+F8h] [rbp-154h]
  unsigned int m_18; // [rsp+FCh] [rbp-150h]
  unsigned int ht_13; // [rsp+100h] [rbp-14Ch]
  unsigned int ht_13a; // [rsp+100h] [rbp-14Ch]
  unsigned int lt_13; // [rsp+104h] [rbp-148h]
  unsigned int m1_13; // [rsp+108h] [rbp-144h]
  unsigned int m_17; // [rsp+10Ch] [rbp-140h]
  unsigned int ht_12; // [rsp+110h] [rbp-13Ch]
  unsigned int ht_12a; // [rsp+110h] [rbp-13Ch]
  unsigned int lt_12; // [rsp+114h] [rbp-138h]
  unsigned int m1_12; // [rsp+118h] [rbp-134h]
  unsigned int m_16; // [rsp+11Ch] [rbp-130h]
  unsigned int ht_11; // [rsp+120h] [rbp-12Ch]
  unsigned int ht_11a; // [rsp+120h] [rbp-12Ch]
  unsigned int lt_11; // [rsp+124h] [rbp-128h]
  unsigned int m1_11; // [rsp+128h] [rbp-124h]
  unsigned int m_15; // [rsp+12Ch] [rbp-120h]
  unsigned int ht_10; // [rsp+130h] [rbp-11Ch]
  unsigned int ht_10a; // [rsp+130h] [rbp-11Ch]
  unsigned int lt_10; // [rsp+134h] [rbp-118h]
  unsigned int m1_10; // [rsp+138h] [rbp-114h]
  unsigned int m_14; // [rsp+13Ch] [rbp-110h]
  unsigned int ht_9; // [rsp+140h] [rbp-10Ch]
  unsigned int ht_9a; // [rsp+140h] [rbp-10Ch]
  unsigned int lt_9; // [rsp+144h] [rbp-108h]
  unsigned int m1_9; // [rsp+148h] [rbp-104h]
  unsigned int m_13; // [rsp+14Ch] [rbp-100h]
  unsigned int ht_8; // [rsp+150h] [rbp-FCh]
  unsigned int ht_8a; // [rsp+150h] [rbp-FCh]
  unsigned int lt_8; // [rsp+154h] [rbp-F8h]
  unsigned int m1_8; // [rsp+158h] [rbp-F4h]
  unsigned int m_12; // [rsp+15Ch] [rbp-F0h]
  unsigned __int16 m_11; // [rsp+160h] [rbp-ECh]
  unsigned int m_11a; // [rsp+160h] [rbp-ECh]
  unsigned int h_2a; // [rsp+164h] [rbp-E8h]
  unsigned int h_2b; // [rsp+164h] [rbp-E8h]
  unsigned int h_2; // [rsp+164h] [rbp-E8h]
  unsigned int l_2a; // [rsp+168h] [rbp-E4h]
  unsigned int l_2; // [rsp+168h] [rbp-E4h]
  unsigned int ht_7; // [rsp+16Ch] [rbp-E0h]
  unsigned int ht_7a; // [rsp+16Ch] [rbp-E0h]
  unsigned int lt_7; // [rsp+170h] [rbp-DCh]
  unsigned int m1_7; // [rsp+174h] [rbp-D8h]
  unsigned int m_10; // [rsp+178h] [rbp-D4h]
  unsigned int ht_6; // [rsp+17Ch] [rbp-D0h]
  unsigned int ht_6a; // [rsp+17Ch] [rbp-D0h]
  unsigned int lt_6; // [rsp+180h] [rbp-CCh]
  unsigned int m1_6; // [rsp+184h] [rbp-C8h]
  unsigned int m_9; // [rsp+188h] [rbp-C4h]
  unsigned int ht_5; // [rsp+18Ch] [rbp-C0h]
  unsigned int ht_5a; // [rsp+18Ch] [rbp-C0h]
  unsigned int lt_5; // [rsp+190h] [rbp-BCh]
  unsigned int m1_5; // [rsp+194h] [rbp-B8h]
  unsigned int m_8; // [rsp+198h] [rbp-B4h]
  unsigned int ht_4; // [rsp+19Ch] [rbp-B0h]
  unsigned int ht_4a; // [rsp+19Ch] [rbp-B0h]
  unsigned int lt_4; // [rsp+1A0h] [rbp-ACh]
  unsigned int m1_4; // [rsp+1A4h] [rbp-A8h]
  unsigned int m_7; // [rsp+1A8h] [rbp-A4h]
  unsigned int ht_3; // [rsp+1ACh] [rbp-A0h]
  unsigned int ht_3a; // [rsp+1ACh] [rbp-A0h]
  unsigned int lt_3; // [rsp+1B0h] [rbp-9Ch]
  unsigned int m1_3; // [rsp+1B4h] [rbp-98h]
  unsigned int m_6; // [rsp+1B8h] [rbp-94h]
  unsigned __int16 m_5; // [rsp+1BCh] [rbp-90h]
  unsigned int m_5a; // [rsp+1BCh] [rbp-90h]
  unsigned int h_1a; // [rsp+1C0h] [rbp-8Ch]
  unsigned int h_1b; // [rsp+1C0h] [rbp-8Ch]
  unsigned int h_1; // [rsp+1C0h] [rbp-8Ch]
  unsigned int l_1a; // [rsp+1C4h] [rbp-88h]
  unsigned int l_1; // [rsp+1C4h] [rbp-88h]
  unsigned int ht_2; // [rsp+1C8h] [rbp-84h]
  unsigned int ht_2a; // [rsp+1C8h] [rbp-84h]
  unsigned int lt_2; // [rsp+1CCh] [rbp-80h]
  unsigned int m1_2; // [rsp+1D0h] [rbp-7Ch]
  unsigned int m_4; // [rsp+1D4h] [rbp-78h]
  unsigned int ht_1; // [rsp+1D8h] [rbp-74h]
  unsigned int ht_1a; // [rsp+1D8h] [rbp-74h]
  unsigned int lt_1; // [rsp+1DCh] [rbp-70h]
  unsigned int m1_1; // [rsp+1E0h] [rbp-6Ch]
  unsigned int m_3; // [rsp+1E4h] [rbp-68h]
  unsigned int ht_0; // [rsp+1E8h] [rbp-64h]
  unsigned int ht_0a; // [rsp+1E8h] [rbp-64h]
  unsigned int lt_0; // [rsp+1ECh] [rbp-60h]
  unsigned int m1_0; // [rsp+1F0h] [rbp-5Ch]
  unsigned int m_2; // [rsp+1F4h] [rbp-58h]
  unsigned __int16 m_1; // [rsp+1F8h] [rbp-54h]
  unsigned int m_1a; // [rsp+1F8h] [rbp-54h]
  unsigned int h_0a; // [rsp+1FCh] [rbp-50h]
  unsigned int h_0b; // [rsp+1FCh] [rbp-50h]
  unsigned int h_0; // [rsp+1FCh] [rbp-50h]
  unsigned int l_0a; // [rsp+200h] [rbp-4Ch]
  unsigned int l_0; // [rsp+200h] [rbp-4Ch]
  unsigned int ht; // [rsp+204h] [rbp-48h]
  unsigned int hta; // [rsp+204h] [rbp-48h]
  unsigned int lt; // [rsp+208h] [rbp-44h]
  unsigned int m1; // [rsp+20Ch] [rbp-40h]
  unsigned int m_0; // [rsp+210h] [rbp-3Ch]
  unsigned __int16 m; // [rsp+214h] [rbp-38h]
  unsigned int ma; // [rsp+214h] [rbp-38h]
  unsigned int ha; // [rsp+218h] [rbp-34h]
  unsigned int h; // [rsp+218h] [rbp-34h]
  unsigned int la; // [rsp+21Ch] [rbp-30h]
  unsigned int l; // [rsp+21Ch] [rbp-30h]
  unsigned int c3; // [rsp+220h] [rbp-2Ch]
  unsigned int c3a; // [rsp+220h] [rbp-2Ch]
  unsigned int c3b; // [rsp+220h] [rbp-2Ch]
  unsigned int c3c; // [rsp+220h] [rbp-2Ch]
  unsigned int c3d; // [rsp+220h] [rbp-2Ch]
  unsigned int c3e; // [rsp+220h] [rbp-2Ch]
  unsigned int c3f; // [rsp+220h] [rbp-2Ch]
  unsigned int c3g; // [rsp+220h] [rbp-2Ch]
  unsigned int c3h; // [rsp+220h] [rbp-2Ch]
  unsigned int c3i; // [rsp+220h] [rbp-2Ch]
  unsigned int c3j; // [rsp+220h] [rbp-2Ch]
  unsigned int c3k; // [rsp+220h] [rbp-2Ch]
  unsigned int c3l; // [rsp+220h] [rbp-2Ch]
  unsigned int c3m; // [rsp+220h] [rbp-2Ch]
  unsigned int c3n; // [rsp+220h] [rbp-2Ch]
  unsigned int c3o; // [rsp+220h] [rbp-2Ch]
  unsigned int c3p; // [rsp+220h] [rbp-2Ch]
  unsigned int c3q; // [rsp+220h] [rbp-2Ch]
  unsigned int c3r; // [rsp+220h] [rbp-2Ch]
  unsigned int c3s; // [rsp+220h] [rbp-2Ch]
  unsigned int c3t; // [rsp+220h] [rbp-2Ch]
  unsigned int c3u; // [rsp+220h] [rbp-2Ch]
  unsigned int c3v; // [rsp+220h] [rbp-2Ch]
  unsigned int c3w; // [rsp+220h] [rbp-2Ch]
  unsigned int c3x; // [rsp+220h] [rbp-2Ch]
  unsigned int c3y; // [rsp+220h] [rbp-2Ch]
  unsigned int c3z; // [rsp+220h] [rbp-2Ch]
  unsigned int c3ba; // [rsp+220h] [rbp-2Ch]
  unsigned int c2; // [rsp+224h] [rbp-28h]
  unsigned int c2a; // [rsp+224h] [rbp-28h]
  unsigned int c2b; // [rsp+224h] [rbp-28h]
  unsigned int c2c; // [rsp+224h] [rbp-28h]
  unsigned int c2d; // [rsp+224h] [rbp-28h]
  unsigned int c2e; // [rsp+224h] [rbp-28h]
  unsigned int c2f; // [rsp+224h] [rbp-28h]
  unsigned int c2g; // [rsp+224h] [rbp-28h]
  unsigned int c2h; // [rsp+224h] [rbp-28h]
  unsigned int c2i; // [rsp+224h] [rbp-28h]
  unsigned int c2j; // [rsp+224h] [rbp-28h]
  unsigned int c2k; // [rsp+224h] [rbp-28h]
  unsigned int c2l; // [rsp+224h] [rbp-28h]
  unsigned int c2m; // [rsp+224h] [rbp-28h]
  unsigned int c2n; // [rsp+224h] [rbp-28h]
  unsigned int c2o; // [rsp+224h] [rbp-28h]
  unsigned int c2p; // [rsp+224h] [rbp-28h]
  unsigned int c2q; // [rsp+224h] [rbp-28h]
  unsigned int c2r; // [rsp+224h] [rbp-28h]
  unsigned int c2s; // [rsp+224h] [rbp-28h]
  unsigned int c2t; // [rsp+224h] [rbp-28h]
  unsigned int c2u; // [rsp+224h] [rbp-28h]
  unsigned int c2v; // [rsp+224h] [rbp-28h]
  unsigned int c2w; // [rsp+224h] [rbp-28h]
  unsigned int c2x; // [rsp+224h] [rbp-28h]
  unsigned int c2y; // [rsp+224h] [rbp-28h]
  unsigned int c2z; // [rsp+224h] [rbp-28h]
  unsigned int c1; // [rsp+228h] [rbp-24h]
  unsigned int c1a; // [rsp+228h] [rbp-24h]
  unsigned int c1b; // [rsp+228h] [rbp-24h]
  unsigned int c1c; // [rsp+228h] [rbp-24h]
  unsigned int c1d; // [rsp+228h] [rbp-24h]
  unsigned int c1e; // [rsp+228h] [rbp-24h]
  unsigned int c1f; // [rsp+228h] [rbp-24h]
  unsigned int c1g; // [rsp+228h] [rbp-24h]
  unsigned int c1h; // [rsp+228h] [rbp-24h]
  unsigned int c1i; // [rsp+228h] [rbp-24h]
  unsigned int c1j; // [rsp+228h] [rbp-24h]
  unsigned int c1k; // [rsp+228h] [rbp-24h]
  unsigned int c1l; // [rsp+228h] [rbp-24h]
  unsigned int c1m; // [rsp+228h] [rbp-24h]
  unsigned int c1n; // [rsp+228h] [rbp-24h]
  unsigned int c1o; // [rsp+228h] [rbp-24h]
  unsigned int c1p; // [rsp+228h] [rbp-24h]
  unsigned int c1q; // [rsp+228h] [rbp-24h]
  unsigned int c1r; // [rsp+228h] [rbp-24h]
  unsigned int c1s; // [rsp+228h] [rbp-24h]
  unsigned int c1t; // [rsp+228h] [rbp-24h]
  unsigned int c1u; // [rsp+228h] [rbp-24h]
  unsigned int c1v; // [rsp+228h] [rbp-24h]
  unsigned int c1w; // [rsp+228h] [rbp-24h]
  unsigned int c1x; // [rsp+228h] [rbp-24h]
  unsigned int c1y; // [rsp+228h] [rbp-24h]
  unsigned int c1z; // [rsp+228h] [rbp-24h]
  unsigned int t2bi; // [rsp+22Ch] [rbp-20h]
  unsigned int t2; // [rsp+22Ch] [rbp-20h]
  unsigned int t2a; // [rsp+22Ch] [rbp-20h]
  unsigned int t2bj; // [rsp+22Ch] [rbp-20h]
  unsigned int t2b; // [rsp+22Ch] [rbp-20h]
  unsigned int t2bk; // [rsp+22Ch] [rbp-20h]
  unsigned int t2c; // [rsp+22Ch] [rbp-20h]
  unsigned int t2bl; // [rsp+22Ch] [rbp-20h]
  unsigned int t2d; // [rsp+22Ch] [rbp-20h]
  unsigned int t2e; // [rsp+22Ch] [rbp-20h]
  unsigned int t2bm; // [rsp+22Ch] [rbp-20h]
  unsigned int t2f; // [rsp+22Ch] [rbp-20h]
  unsigned int t2bn; // [rsp+22Ch] [rbp-20h]
  unsigned int t2g; // [rsp+22Ch] [rbp-20h]
  unsigned int t2bo; // [rsp+22Ch] [rbp-20h]
  unsigned int t2h; // [rsp+22Ch] [rbp-20h]
  unsigned int t2bp; // [rsp+22Ch] [rbp-20h]
  unsigned int t2i; // [rsp+22Ch] [rbp-20h]
  unsigned int t2bq; // [rsp+22Ch] [rbp-20h]
  unsigned int t2j; // [rsp+22Ch] [rbp-20h]
  unsigned int t2k; // [rsp+22Ch] [rbp-20h]
  unsigned int t2br; // [rsp+22Ch] [rbp-20h]
  unsigned int t2l; // [rsp+22Ch] [rbp-20h]
  unsigned int t2bs; // [rsp+22Ch] [rbp-20h]
  unsigned int t2m; // [rsp+22Ch] [rbp-20h]
  unsigned int t2bt; // [rsp+22Ch] [rbp-20h]
  unsigned int t2n; // [rsp+22Ch] [rbp-20h]
  unsigned int t2bu; // [rsp+22Ch] [rbp-20h]
  unsigned int t2o; // [rsp+22Ch] [rbp-20h]
  unsigned int t2bv; // [rsp+22Ch] [rbp-20h]
  unsigned int t2p; // [rsp+22Ch] [rbp-20h]
  unsigned int t2bw; // [rsp+22Ch] [rbp-20h]
  unsigned int t2q; // [rsp+22Ch] [rbp-20h]
  unsigned int t2bx; // [rsp+22Ch] [rbp-20h]
  unsigned int t2r; // [rsp+22Ch] [rbp-20h]
  unsigned int t2s; // [rsp+22Ch] [rbp-20h]
  unsigned int t2by; // [rsp+22Ch] [rbp-20h]
  unsigned int t2t; // [rsp+22Ch] [rbp-20h]
  unsigned int t2bz; // [rsp+22Ch] [rbp-20h]
  unsigned int t2u; // [rsp+22Ch] [rbp-20h]
  unsigned int t2ca; // [rsp+22Ch] [rbp-20h]
  unsigned int t2v; // [rsp+22Ch] [rbp-20h]
  unsigned int t2cb; // [rsp+22Ch] [rbp-20h]
  unsigned int t2w; // [rsp+22Ch] [rbp-20h]
  unsigned int t2cc; // [rsp+22Ch] [rbp-20h]
  unsigned int t2x; // [rsp+22Ch] [rbp-20h]
  unsigned int t2cd; // [rsp+22Ch] [rbp-20h]
  unsigned int t2y; // [rsp+22Ch] [rbp-20h]
  unsigned int t2z; // [rsp+22Ch] [rbp-20h]
  unsigned int t2ce; // [rsp+22Ch] [rbp-20h]
  unsigned int t2ba; // [rsp+22Ch] [rbp-20h]
  unsigned int t2cf; // [rsp+22Ch] [rbp-20h]
  unsigned int t2bb; // [rsp+22Ch] [rbp-20h]
  unsigned int t2cg; // [rsp+22Ch] [rbp-20h]
  unsigned int t2bc; // [rsp+22Ch] [rbp-20h]
  unsigned int t2ch; // [rsp+22Ch] [rbp-20h]
  unsigned int t2bd; // [rsp+22Ch] [rbp-20h]
  unsigned int t2be; // [rsp+22Ch] [rbp-20h]
  unsigned int t2ci; // [rsp+22Ch] [rbp-20h]
  unsigned int t2bf; // [rsp+22Ch] [rbp-20h]
  unsigned int t2cj; // [rsp+22Ch] [rbp-20h]
  unsigned int t2bg; // [rsp+22Ch] [rbp-20h]
  unsigned int t2bh; // [rsp+22Ch] [rbp-20h]
  unsigned int t1; // [rsp+230h] [rbp-1Ch]
  unsigned int t1a; // [rsp+230h] [rbp-1Ch]
  unsigned int t1b; // [rsp+230h] [rbp-1Ch]
  unsigned int t1c; // [rsp+230h] [rbp-1Ch]
  unsigned int t1d; // [rsp+230h] [rbp-1Ch]
  unsigned int t1e; // [rsp+230h] [rbp-1Ch]
  unsigned int t1f; // [rsp+230h] [rbp-1Ch]
  unsigned int t1g; // [rsp+230h] [rbp-1Ch]
  unsigned int t1h; // [rsp+230h] [rbp-1Ch]
  unsigned int t1i; // [rsp+230h] [rbp-1Ch]
  unsigned int t1j; // [rsp+230h] [rbp-1Ch]
  unsigned int t1k; // [rsp+230h] [rbp-1Ch]
  unsigned int t1l; // [rsp+230h] [rbp-1Ch]
  unsigned int t1m; // [rsp+230h] [rbp-1Ch]
  unsigned int t1n; // [rsp+230h] [rbp-1Ch]
  unsigned int t1o; // [rsp+230h] [rbp-1Ch]
  unsigned int t1p; // [rsp+230h] [rbp-1Ch]
  unsigned int t1q; // [rsp+230h] [rbp-1Ch]
  unsigned int t1r; // [rsp+230h] [rbp-1Ch]
  unsigned int t1s; // [rsp+230h] [rbp-1Ch]
  unsigned int t1t; // [rsp+230h] [rbp-1Ch]
  unsigned int t1u; // [rsp+230h] [rbp-1Ch]
  unsigned int t1v; // [rsp+230h] [rbp-1Ch]
  unsigned int t1w; // [rsp+230h] [rbp-1Ch]
  unsigned int t1x; // [rsp+230h] [rbp-1Ch]
  unsigned int t1y; // [rsp+230h] [rbp-1Ch]
  unsigned int t1z; // [rsp+230h] [rbp-1Ch]
  unsigned int t1ba; // [rsp+230h] [rbp-1Ch]
  unsigned int bh_0; // [rsp+234h] [rbp-18h]
  unsigned int bh_0a; // [rsp+234h] [rbp-18h]
  unsigned int bh_0b; // [rsp+234h] [rbp-18h]
  unsigned int bh_0c; // [rsp+234h] [rbp-18h]
  unsigned int bh_0d; // [rsp+234h] [rbp-18h]
  unsigned int bh_0e; // [rsp+234h] [rbp-18h]
  unsigned int bh_0f; // [rsp+234h] [rbp-18h]
  unsigned int bh_0g; // [rsp+234h] [rbp-18h]
  unsigned int bh_0h; // [rsp+234h] [rbp-18h]
  unsigned int bh_0i; // [rsp+234h] [rbp-18h]
  unsigned int bh_0j; // [rsp+234h] [rbp-18h]
  unsigned int bh_0k; // [rsp+234h] [rbp-18h]
  unsigned int bh_0l; // [rsp+234h] [rbp-18h]
  unsigned int bh_0m; // [rsp+234h] [rbp-18h]
  unsigned int bh_0n; // [rsp+234h] [rbp-18h]
  unsigned int bh_0o; // [rsp+234h] [rbp-18h]
  unsigned int bh_0p; // [rsp+234h] [rbp-18h]
  unsigned int bh_0q; // [rsp+234h] [rbp-18h]
  unsigned int bh_0r; // [rsp+234h] [rbp-18h]
  unsigned int bh_0s; // [rsp+234h] [rbp-18h]
  unsigned int bh_0t; // [rsp+234h] [rbp-18h]
  unsigned int bh_0u; // [rsp+234h] [rbp-18h]
  unsigned int bh_0v; // [rsp+234h] [rbp-18h]
  unsigned int bh_0w; // [rsp+234h] [rbp-18h]
  unsigned int bh_0x; // [rsp+234h] [rbp-18h]
  unsigned int bh_0y; // [rsp+234h] [rbp-18h]
  unsigned int bh_0z; // [rsp+234h] [rbp-18h]
  unsigned int bh_0ba; // [rsp+234h] [rbp-18h]
  unsigned int bl_0; // [rsp+238h] [rbp-14h]
  unsigned int bl_0a; // [rsp+238h] [rbp-14h]
  unsigned int bl_0b; // [rsp+238h] [rbp-14h]
  unsigned int bl_0c; // [rsp+238h] [rbp-14h]
  unsigned int bl_0d; // [rsp+238h] [rbp-14h]
  unsigned int bl_0e; // [rsp+238h] [rbp-14h]
  unsigned int bl_0f; // [rsp+238h] [rbp-14h]
  unsigned int bl_0g; // [rsp+238h] [rbp-14h]
  unsigned int bl_0h; // [rsp+238h] [rbp-14h]
  unsigned int bl_0i; // [rsp+238h] [rbp-14h]
  unsigned int bl_0j; // [rsp+238h] [rbp-14h]
  unsigned int bl_0k; // [rsp+238h] [rbp-14h]
  unsigned int bl_0l; // [rsp+238h] [rbp-14h]
  unsigned int bl_0m; // [rsp+238h] [rbp-14h]
  unsigned int bl_0n; // [rsp+238h] [rbp-14h]
  unsigned int bl_0o; // [rsp+238h] [rbp-14h]
  unsigned int bl_0p; // [rsp+238h] [rbp-14h]
  unsigned int bl_0q; // [rsp+238h] [rbp-14h]
  unsigned int bl_0r; // [rsp+238h] [rbp-14h]
  unsigned int bl_0s; // [rsp+238h] [rbp-14h]
  unsigned int bl_0t; // [rsp+238h] [rbp-14h]
  unsigned int bl_0u; // [rsp+238h] [rbp-14h]
  unsigned int bl_0v; // [rsp+238h] [rbp-14h]
  unsigned int bl_0w; // [rsp+238h] [rbp-14h]
  unsigned int bl_0x; // [rsp+238h] [rbp-14h]
  unsigned int bl_0y; // [rsp+238h] [rbp-14h]
  unsigned int bl_0z; // [rsp+238h] [rbp-14h]
  unsigned int bl_0ba; // [rsp+238h] [rbp-14h]

  la = (unsigned __int16)*a;
  ha = HIWORD(*a);
  m = ha * la;
  h = ((__int64)((ha * la) & 0xFFFF8000) >> 15) + ha * ha;
  ma = m << 17;
  l = ma + la * la;
  if ( l < ma )
    ++h;
  *r = l;
  c1 = 0;
  t1 = (unsigned __int16)a[1];
  t2bi = HIWORD(a[1]);
  bl_0 = (unsigned __int16)*a;
  bh_0 = HIWORD(*a);
  ht = t2bi * bh_0;
  m_0 = t2bi * bl_0 + t1 * bh_0;
  if ( m_0 < t2bi * bl_0 )
    ht += 0x10000;
  hta = ht + HIWORD(m_0);
  m1 = (unsigned __int16)m_0 << 16;
  lt = m1 + t1 * bl_0;
  if ( lt < m1 )
    ++hta;
  if ( (hta & 0x80000000) != 0 )
    c1 = 1;
  t2 = 2 * hta;
  if ( (lt & 0x80000000) != 0 )
    ++t2;
  c2 = 2 * lt + h;
  if ( c2 < 2 * lt && !++t2 )
    ++c1;
  c3 = t2;
  r[1] = c2;
  c2a = 0;
  h_0a = a[1];
  l_0a = (unsigned __int16)h_0a;
  h_0b = HIWORD(h_0a);
  m_1 = h_0b * l_0a;
  h_0 = ((__int64)((h_0b * l_0a) & 0xFFFF8000) >> 15) + h_0b * h_0b;
  m_1a = m_1 << 17;
  l_0 = m_1a + l_0a * l_0a;
  if ( l_0 < m_1a )
    ++h_0;
  t2a = h_0;
  c3a = l_0 + c3;
  if ( c3a < l_0 )
    t2a = h_0 + 1;
  c1a = t2a + c1;
  if ( c1a < t2a )
    c2a = 1;
  t1a = (unsigned __int16)a[2];
  t2bj = HIWORD(a[2]);
  bl_0a = (unsigned __int16)*a;
  bh_0a = HIWORD(*a);
  ht_0 = t2bj * bh_0a;
  m_2 = t2bj * bl_0a + t1a * bh_0a;
  if ( m_2 < t2bj * bl_0a )
    ht_0 += 0x10000;
  ht_0a = ht_0 + HIWORD(m_2);
  m1_0 = (unsigned __int16)m_2 << 16;
  lt_0 = m1_0 + t1a * bl_0a;
  if ( lt_0 < m1_0 )
    ++ht_0a;
  if ( (ht_0a & 0x80000000) != 0 )
    ++c2a;
  t2b = 2 * ht_0a;
  if ( (lt_0 & 0x80000000) != 0 )
    ++t2b;
  c3b = 2 * lt_0 + c3a;
  if ( c3b < 2 * lt_0 && !++t2b )
    ++c2a;
  c1b = t2b + c1a;
  if ( c1b < t2b )
    ++c2a;
  r[2] = c3b;
  c3c = 0;
  t1b = (unsigned __int16)a[3];
  t2bk = HIWORD(a[3]);
  bl_0b = (unsigned __int16)*a;
  bh_0b = HIWORD(*a);
  ht_1 = t2bk * bh_0b;
  m_3 = t2bk * bl_0b + t1b * bh_0b;
  if ( m_3 < t2bk * bl_0b )
    ht_1 += 0x10000;
  ht_1a = ht_1 + HIWORD(m_3);
  m1_1 = (unsigned __int16)m_3 << 16;
  lt_1 = m1_1 + t1b * bl_0b;
  if ( lt_1 < m1_1 )
    ++ht_1a;
  if ( (ht_1a & 0x80000000) != 0 )
    c3c = 1;
  t2c = 2 * ht_1a;
  if ( (lt_1 & 0x80000000) != 0 )
    ++t2c;
  c1c = 2 * lt_1 + c1b;
  if ( c1c < 2 * lt_1 && !++t2c )
    ++c3c;
  c2b = t2c + c2a;
  if ( c2b < t2c )
    ++c3c;
  t1c = (unsigned __int16)a[2];
  t2bl = HIWORD(a[2]);
  bl_0c = (unsigned __int16)a[1];
  bh_0c = HIWORD(a[1]);
  ht_2 = t2bl * bh_0c;
  m_4 = t2bl * bl_0c + t1c * bh_0c;
  if ( m_4 < t2bl * bl_0c )
    ht_2 += 0x10000;
  ht_2a = ht_2 + HIWORD(m_4);
  m1_2 = (unsigned __int16)m_4 << 16;
  lt_2 = m1_2 + t1c * bl_0c;
  if ( lt_2 < m1_2 )
    ++ht_2a;
  if ( (ht_2a & 0x80000000) != 0 )
    ++c3c;
  t2d = 2 * ht_2a;
  if ( (lt_2 & 0x80000000) != 0 )
    ++t2d;
  c1d = 2 * lt_2 + c1c;
  if ( c1d < 2 * lt_2 && !++t2d )
    ++c3c;
  c2c = t2d + c2b;
  if ( c2c < t2d )
    ++c3c;
  r[3] = c1d;
  c1e = 0;
  h_1a = a[2];
  l_1a = (unsigned __int16)h_1a;
  h_1b = HIWORD(h_1a);
  m_5 = h_1b * l_1a;
  h_1 = ((__int64)((h_1b * l_1a) & 0xFFFF8000) >> 15) + h_1b * h_1b;
  m_5a = m_5 << 17;
  l_1 = m_5a + l_1a * l_1a;
  if ( l_1 < m_5a )
    ++h_1;
  t2e = h_1;
  c2d = l_1 + c2c;
  if ( c2d < l_1 )
    t2e = h_1 + 1;
  c3d = t2e + c3c;
  if ( c3d < t2e )
    c1e = 1;
  t1d = (unsigned __int16)a[3];
  t2bm = HIWORD(a[3]);
  bl_0d = (unsigned __int16)a[1];
  bh_0d = HIWORD(a[1]);
  ht_3 = t2bm * bh_0d;
  m_6 = t2bm * bl_0d + t1d * bh_0d;
  if ( m_6 < t2bm * bl_0d )
    ht_3 += 0x10000;
  ht_3a = ht_3 + HIWORD(m_6);
  m1_3 = (unsigned __int16)m_6 << 16;
  lt_3 = m1_3 + t1d * bl_0d;
  if ( lt_3 < m1_3 )
    ++ht_3a;
  if ( (ht_3a & 0x80000000) != 0 )
    ++c1e;
  t2f = 2 * ht_3a;
  if ( (lt_3 & 0x80000000) != 0 )
    ++t2f;
  c2e = 2 * lt_3 + c2d;
  if ( c2e < 2 * lt_3 && !++t2f )
    ++c1e;
  c3e = t2f + c3d;
  if ( c3e < t2f )
    ++c1e;
  t1e = (unsigned __int16)a[4];
  t2bn = HIWORD(a[4]);
  bl_0e = (unsigned __int16)*a;
  bh_0e = HIWORD(*a);
  ht_4 = t2bn * bh_0e;
  m_7 = t2bn * bl_0e + t1e * bh_0e;
  if ( m_7 < t2bn * bl_0e )
    ht_4 += 0x10000;
  ht_4a = ht_4 + HIWORD(m_7);
  m1_4 = (unsigned __int16)m_7 << 16;
  lt_4 = m1_4 + t1e * bl_0e;
  if ( lt_4 < m1_4 )
    ++ht_4a;
  if ( (ht_4a & 0x80000000) != 0 )
    ++c1e;
  t2g = 2 * ht_4a;
  if ( (lt_4 & 0x80000000) != 0 )
    ++t2g;
  c2f = 2 * lt_4 + c2e;
  if ( c2f < 2 * lt_4 && !++t2g )
    ++c1e;
  c3f = t2g + c3e;
  if ( c3f < t2g )
    ++c1e;
  r[4] = c2f;
  c2g = 0;
  t1f = (unsigned __int16)a[5];
  t2bo = HIWORD(a[5]);
  bl_0f = (unsigned __int16)*a;
  bh_0f = HIWORD(*a);
  ht_5 = t2bo * bh_0f;
  m_8 = t2bo * bl_0f + t1f * bh_0f;
  if ( m_8 < t2bo * bl_0f )
    ht_5 += 0x10000;
  ht_5a = ht_5 + HIWORD(m_8);
  m1_5 = (unsigned __int16)m_8 << 16;
  lt_5 = m1_5 + t1f * bl_0f;
  if ( lt_5 < m1_5 )
    ++ht_5a;
  if ( (ht_5a & 0x80000000) != 0 )
    c2g = 1;
  t2h = 2 * ht_5a;
  if ( (lt_5 & 0x80000000) != 0 )
    ++t2h;
  c3g = 2 * lt_5 + c3f;
  if ( c3g < 2 * lt_5 && !++t2h )
    ++c2g;
  c1f = t2h + c1e;
  if ( c1f < t2h )
    ++c2g;
  t1g = (unsigned __int16)a[4];
  t2bp = HIWORD(a[4]);
  bl_0g = (unsigned __int16)a[1];
  bh_0g = HIWORD(a[1]);
  ht_6 = t2bp * bh_0g;
  m_9 = t2bp * bl_0g + t1g * bh_0g;
  if ( m_9 < t2bp * bl_0g )
    ht_6 += 0x10000;
  ht_6a = ht_6 + HIWORD(m_9);
  m1_6 = (unsigned __int16)m_9 << 16;
  lt_6 = m1_6 + t1g * bl_0g;
  if ( lt_6 < m1_6 )
    ++ht_6a;
  if ( (ht_6a & 0x80000000) != 0 )
    ++c2g;
  t2i = 2 * ht_6a;
  if ( (lt_6 & 0x80000000) != 0 )
    ++t2i;
  c3h = 2 * lt_6 + c3g;
  if ( c3h < 2 * lt_6 && !++t2i )
    ++c2g;
  c1g = t2i + c1f;
  if ( c1g < t2i )
    ++c2g;
  t1h = (unsigned __int16)a[3];
  t2bq = HIWORD(a[3]);
  bl_0h = (unsigned __int16)a[2];
  bh_0h = HIWORD(a[2]);
  ht_7 = t2bq * bh_0h;
  m_10 = t2bq * bl_0h + t1h * bh_0h;
  if ( m_10 < t2bq * bl_0h )
    ht_7 += 0x10000;
  ht_7a = ht_7 + HIWORD(m_10);
  m1_7 = (unsigned __int16)m_10 << 16;
  lt_7 = m1_7 + t1h * bl_0h;
  if ( lt_7 < m1_7 )
    ++ht_7a;
  if ( (ht_7a & 0x80000000) != 0 )
    ++c2g;
  t2j = 2 * ht_7a;
  if ( (lt_7 & 0x80000000) != 0 )
    ++t2j;
  c3i = 2 * lt_7 + c3h;
  if ( c3i < 2 * lt_7 && !++t2j )
    ++c2g;
  c1h = t2j + c1g;
  if ( c1h < t2j )
    ++c2g;
  r[5] = c3i;
  c3j = 0;
  h_2a = a[3];
  l_2a = (unsigned __int16)h_2a;
  h_2b = HIWORD(h_2a);
  m_11 = h_2b * l_2a;
  h_2 = ((__int64)((h_2b * l_2a) & 0xFFFF8000) >> 15) + h_2b * h_2b;
  m_11a = m_11 << 17;
  l_2 = m_11a + l_2a * l_2a;
  if ( l_2 < m_11a )
    ++h_2;
  t2k = h_2;
  c1i = l_2 + c1h;
  if ( c1i < l_2 )
    t2k = h_2 + 1;
  c2h = t2k + c2g;
  if ( c2h < t2k )
    c3j = 1;
  t1i = (unsigned __int16)a[4];
  t2br = HIWORD(a[4]);
  bl_0i = (unsigned __int16)a[2];
  bh_0i = HIWORD(a[2]);
  ht_8 = t2br * bh_0i;
  m_12 = t2br * bl_0i + t1i * bh_0i;
  if ( m_12 < t2br * bl_0i )
    ht_8 += 0x10000;
  ht_8a = ht_8 + HIWORD(m_12);
  m1_8 = (unsigned __int16)m_12 << 16;
  lt_8 = m1_8 + t1i * bl_0i;
  if ( lt_8 < m1_8 )
    ++ht_8a;
  if ( (ht_8a & 0x80000000) != 0 )
    ++c3j;
  t2l = 2 * ht_8a;
  if ( (lt_8 & 0x80000000) != 0 )
    ++t2l;
  c1j = 2 * lt_8 + c1i;
  if ( c1j < 2 * lt_8 && !++t2l )
    ++c3j;
  c2i = t2l + c2h;
  if ( c2i < t2l )
    ++c3j;
  t1j = (unsigned __int16)a[5];
  t2bs = HIWORD(a[5]);
  bl_0j = (unsigned __int16)a[1];
  bh_0j = HIWORD(a[1]);
  ht_9 = t2bs * bh_0j;
  m_13 = t2bs * bl_0j + t1j * bh_0j;
  if ( m_13 < t2bs * bl_0j )
    ht_9 += 0x10000;
  ht_9a = ht_9 + HIWORD(m_13);
  m1_9 = (unsigned __int16)m_13 << 16;
  lt_9 = m1_9 + t1j * bl_0j;
  if ( lt_9 < m1_9 )
    ++ht_9a;
  if ( (ht_9a & 0x80000000) != 0 )
    ++c3j;
  t2m = 2 * ht_9a;
  if ( (lt_9 & 0x80000000) != 0 )
    ++t2m;
  c1k = 2 * lt_9 + c1j;
  if ( c1k < 2 * lt_9 && !++t2m )
    ++c3j;
  c2j = t2m + c2i;
  if ( c2j < t2m )
    ++c3j;
  t1k = (unsigned __int16)a[6];
  t2bt = HIWORD(a[6]);
  bl_0k = (unsigned __int16)*a;
  bh_0k = HIWORD(*a);
  ht_10 = t2bt * bh_0k;
  m_14 = t2bt * bl_0k + t1k * bh_0k;
  if ( m_14 < t2bt * bl_0k )
    ht_10 += 0x10000;
  ht_10a = ht_10 + HIWORD(m_14);
  m1_10 = (unsigned __int16)m_14 << 16;
  lt_10 = m1_10 + t1k * bl_0k;
  if ( lt_10 < m1_10 )
    ++ht_10a;
  if ( (ht_10a & 0x80000000) != 0 )
    ++c3j;
  t2n = 2 * ht_10a;
  if ( (lt_10 & 0x80000000) != 0 )
    ++t2n;
  c1l = 2 * lt_10 + c1k;
  if ( c1l < 2 * lt_10 && !++t2n )
    ++c3j;
  c2k = t2n + c2j;
  if ( c2k < t2n )
    ++c3j;
  r[6] = c1l;
  c1m = 0;
  t1l = (unsigned __int16)a[7];
  t2bu = HIWORD(a[7]);
  bl_0l = (unsigned __int16)*a;
  bh_0l = HIWORD(*a);
  ht_11 = t2bu * bh_0l;
  m_15 = t2bu * bl_0l + t1l * bh_0l;
  if ( m_15 < t2bu * bl_0l )
    ht_11 += 0x10000;
  ht_11a = ht_11 + HIWORD(m_15);
  m1_11 = (unsigned __int16)m_15 << 16;
  lt_11 = m1_11 + t1l * bl_0l;
  if ( lt_11 < m1_11 )
    ++ht_11a;
  if ( (ht_11a & 0x80000000) != 0 )
    c1m = 1;
  t2o = 2 * ht_11a;
  if ( (lt_11 & 0x80000000) != 0 )
    ++t2o;
  c2l = 2 * lt_11 + c2k;
  if ( c2l < 2 * lt_11 && !++t2o )
    ++c1m;
  c3k = t2o + c3j;
  if ( c3k < t2o )
    ++c1m;
  t1m = (unsigned __int16)a[6];
  t2bv = HIWORD(a[6]);
  bl_0m = (unsigned __int16)a[1];
  bh_0m = HIWORD(a[1]);
  ht_12 = t2bv * bh_0m;
  m_16 = t2bv * bl_0m + t1m * bh_0m;
  if ( m_16 < t2bv * bl_0m )
    ht_12 += 0x10000;
  ht_12a = ht_12 + HIWORD(m_16);
  m1_12 = (unsigned __int16)m_16 << 16;
  lt_12 = m1_12 + t1m * bl_0m;
  if ( lt_12 < m1_12 )
    ++ht_12a;
  if ( (ht_12a & 0x80000000) != 0 )
    ++c1m;
  t2p = 2 * ht_12a;
  if ( (lt_12 & 0x80000000) != 0 )
    ++t2p;
  c2m = 2 * lt_12 + c2l;
  if ( c2m < 2 * lt_12 && !++t2p )
    ++c1m;
  c3l = t2p + c3k;
  if ( c3l < t2p )
    ++c1m;
  t1n = (unsigned __int16)a[5];
  t2bw = HIWORD(a[5]);
  bl_0n = (unsigned __int16)a[2];
  bh_0n = HIWORD(a[2]);
  ht_13 = t2bw * bh_0n;
  m_17 = t2bw * bl_0n + t1n * bh_0n;
  if ( m_17 < t2bw * bl_0n )
    ht_13 += 0x10000;
  ht_13a = ht_13 + HIWORD(m_17);
  m1_13 = (unsigned __int16)m_17 << 16;
  lt_13 = m1_13 + t1n * bl_0n;
  if ( lt_13 < m1_13 )
    ++ht_13a;
  if ( (ht_13a & 0x80000000) != 0 )
    ++c1m;
  t2q = 2 * ht_13a;
  if ( (lt_13 & 0x80000000) != 0 )
    ++t2q;
  c2n = 2 * lt_13 + c2m;
  if ( c2n < 2 * lt_13 && !++t2q )
    ++c1m;
  c3m = t2q + c3l;
  if ( c3m < t2q )
    ++c1m;
  t1o = (unsigned __int16)a[4];
  t2bx = HIWORD(a[4]);
  bl_0o = (unsigned __int16)a[3];
  bh_0o = HIWORD(a[3]);
  ht_14 = t2bx * bh_0o;
  m_18 = t2bx * bl_0o + t1o * bh_0o;
  if ( m_18 < t2bx * bl_0o )
    ht_14 += 0x10000;
  ht_14a = ht_14 + HIWORD(m_18);
  m1_14 = (unsigned __int16)m_18 << 16;
  lt_14 = m1_14 + t1o * bl_0o;
  if ( lt_14 < m1_14 )
    ++ht_14a;
  if ( (ht_14a & 0x80000000) != 0 )
    ++c1m;
  t2r = 2 * ht_14a;
  if ( (lt_14 & 0x80000000) != 0 )
    ++t2r;
  c2o = 2 * lt_14 + c2n;
  if ( c2o < 2 * lt_14 && !++t2r )
    ++c1m;
  c3n = t2r + c3m;
  if ( c3n < t2r )
    ++c1m;
  r[7] = c2o;
  c2p = 0;
  h_3a = a[4];
  l_3a = (unsigned __int16)h_3a;
  h_3b = HIWORD(h_3a);
  m_19 = h_3b * l_3a;
  h_3 = ((__int64)((h_3b * l_3a) & 0xFFFF8000) >> 15) + h_3b * h_3b;
  m_19a = m_19 << 17;
  l_3 = m_19a + l_3a * l_3a;
  if ( l_3 < m_19a )
    ++h_3;
  t2s = h_3;
  c3o = l_3 + c3n;
  if ( c3o < l_3 )
    t2s = h_3 + 1;
  c1n = t2s + c1m;
  if ( c1n < t2s )
    c2p = 1;
  t1p = (unsigned __int16)a[5];
  t2by = HIWORD(a[5]);
  bl_0p = (unsigned __int16)a[3];
  bh_0p = HIWORD(a[3]);
  ht_15 = t2by * bh_0p;
  m_20 = t2by * bl_0p + t1p * bh_0p;
  if ( m_20 < t2by * bl_0p )
    ht_15 += 0x10000;
  ht_15a = ht_15 + HIWORD(m_20);
  m1_15 = (unsigned __int16)m_20 << 16;
  lt_15 = m1_15 + t1p * bl_0p;
  if ( lt_15 < m1_15 )
    ++ht_15a;
  if ( (ht_15a & 0x80000000) != 0 )
    ++c2p;
  t2t = 2 * ht_15a;
  if ( (lt_15 & 0x80000000) != 0 )
    ++t2t;
  c3p = 2 * lt_15 + c3o;
  if ( c3p < 2 * lt_15 && !++t2t )
    ++c2p;
  c1o = t2t + c1n;
  if ( c1o < t2t )
    ++c2p;
  t1q = (unsigned __int16)a[6];
  t2bz = HIWORD(a[6]);
  bl_0q = (unsigned __int16)a[2];
  bh_0q = HIWORD(a[2]);
  ht_16 = t2bz * bh_0q;
  m_21 = t2bz * bl_0q + t1q * bh_0q;
  if ( m_21 < t2bz * bl_0q )
    ht_16 += 0x10000;
  ht_16a = ht_16 + HIWORD(m_21);
  m1_16 = (unsigned __int16)m_21 << 16;
  lt_16 = m1_16 + t1q * bl_0q;
  if ( lt_16 < m1_16 )
    ++ht_16a;
  if ( (ht_16a & 0x80000000) != 0 )
    ++c2p;
  t2u = 2 * ht_16a;
  if ( (lt_16 & 0x80000000) != 0 )
    ++t2u;
  c3q = 2 * lt_16 + c3p;
  if ( c3q < 2 * lt_16 && !++t2u )
    ++c2p;
  c1p = t2u + c1o;
  if ( c1p < t2u )
    ++c2p;
  t1r = (unsigned __int16)a[7];
  t2ca = HIWORD(a[7]);
  bl_0r = (unsigned __int16)a[1];
  bh_0r = HIWORD(a[1]);
  ht_17 = t2ca * bh_0r;
  m_22 = t2ca * bl_0r + t1r * bh_0r;
  if ( m_22 < t2ca * bl_0r )
    ht_17 += 0x10000;
  ht_17a = ht_17 + HIWORD(m_22);
  m1_17 = (unsigned __int16)m_22 << 16;
  lt_17 = m1_17 + t1r * bl_0r;
  if ( lt_17 < m1_17 )
    ++ht_17a;
  if ( (ht_17a & 0x80000000) != 0 )
    ++c2p;
  t2v = 2 * ht_17a;
  if ( (lt_17 & 0x80000000) != 0 )
    ++t2v;
  c3r = 2 * lt_17 + c3q;
  if ( c3r < 2 * lt_17 && !++t2v )
    ++c2p;
  c1q = t2v + c1p;
  if ( c1q < t2v )
    ++c2p;
  r[8] = c3r;
  c3s = 0;
  t1s = (unsigned __int16)a[7];
  t2cb = HIWORD(a[7]);
  bl_0s = (unsigned __int16)a[2];
  bh_0s = HIWORD(a[2]);
  ht_18 = t2cb * bh_0s;
  m_23 = t2cb * bl_0s + t1s * bh_0s;
  if ( m_23 < t2cb * bl_0s )
    ht_18 += 0x10000;
  ht_18a = ht_18 + HIWORD(m_23);
  m1_18 = (unsigned __int16)m_23 << 16;
  lt_18 = m1_18 + t1s * bl_0s;
  if ( lt_18 < m1_18 )
    ++ht_18a;
  if ( (ht_18a & 0x80000000) != 0 )
    c3s = 1;
  t2w = 2 * ht_18a;
  if ( (lt_18 & 0x80000000) != 0 )
    ++t2w;
  c1r = 2 * lt_18 + c1q;
  if ( c1r < 2 * lt_18 && !++t2w )
    ++c3s;
  c2q = t2w + c2p;
  if ( c2q < t2w )
    ++c3s;
  t1t = (unsigned __int16)a[6];
  t2cc = HIWORD(a[6]);
  bl_0t = (unsigned __int16)a[3];
  bh_0t = HIWORD(a[3]);
  ht_19 = t2cc * bh_0t;
  m_24 = t2cc * bl_0t + t1t * bh_0t;
  if ( m_24 < t2cc * bl_0t )
    ht_19 += 0x10000;
  ht_19a = ht_19 + HIWORD(m_24);
  m1_19 = (unsigned __int16)m_24 << 16;
  lt_19 = m1_19 + t1t * bl_0t;
  if ( lt_19 < m1_19 )
    ++ht_19a;
  if ( (ht_19a & 0x80000000) != 0 )
    ++c3s;
  t2x = 2 * ht_19a;
  if ( (lt_19 & 0x80000000) != 0 )
    ++t2x;
  c1s = 2 * lt_19 + c1r;
  if ( c1s < 2 * lt_19 && !++t2x )
    ++c3s;
  c2r = t2x + c2q;
  if ( c2r < t2x )
    ++c3s;
  t1u = (unsigned __int16)a[5];
  t2cd = HIWORD(a[5]);
  bl_0u = (unsigned __int16)a[4];
  bh_0u = HIWORD(a[4]);
  ht_20 = t2cd * bh_0u;
  m_25 = t2cd * bl_0u + t1u * bh_0u;
  if ( m_25 < t2cd * bl_0u )
    ht_20 += 0x10000;
  ht_20a = ht_20 + HIWORD(m_25);
  m1_20 = (unsigned __int16)m_25 << 16;
  lt_20 = m1_20 + t1u * bl_0u;
  if ( lt_20 < m1_20 )
    ++ht_20a;
  if ( (ht_20a & 0x80000000) != 0 )
    ++c3s;
  t2y = 2 * ht_20a;
  if ( (lt_20 & 0x80000000) != 0 )
    ++t2y;
  c1t = 2 * lt_20 + c1s;
  if ( c1t < 2 * lt_20 && !++t2y )
    ++c3s;
  c2s = t2y + c2r;
  if ( c2s < t2y )
    ++c3s;
  r[9] = c1t;
  c1u = 0;
  h_4a = a[5];
  l_4a = (unsigned __int16)h_4a;
  h_4b = HIWORD(h_4a);
  m_26 = h_4b * l_4a;
  h_4 = ((__int64)((h_4b * l_4a) & 0xFFFF8000) >> 15) + h_4b * h_4b;
  m_26a = m_26 << 17;
  l_4 = m_26a + l_4a * l_4a;
  if ( l_4 < m_26a )
    ++h_4;
  t2z = h_4;
  c2t = l_4 + c2s;
  if ( c2t < l_4 )
    t2z = h_4 + 1;
  c3t = t2z + c3s;
  if ( c3t < t2z )
    c1u = 1;
  t1v = (unsigned __int16)a[6];
  t2ce = HIWORD(a[6]);
  bl_0v = (unsigned __int16)a[4];
  bh_0v = HIWORD(a[4]);
  ht_21 = t2ce * bh_0v;
  m_27 = t2ce * bl_0v + t1v * bh_0v;
  if ( m_27 < t2ce * bl_0v )
    ht_21 += 0x10000;
  ht_21a = ht_21 + HIWORD(m_27);
  m1_21 = (unsigned __int16)m_27 << 16;
  lt_21 = m1_21 + t1v * bl_0v;
  if ( lt_21 < m1_21 )
    ++ht_21a;
  if ( (ht_21a & 0x80000000) != 0 )
    ++c1u;
  t2ba = 2 * ht_21a;
  if ( (lt_21 & 0x80000000) != 0 )
    ++t2ba;
  c2u = 2 * lt_21 + c2t;
  if ( c2u < 2 * lt_21 && !++t2ba )
    ++c1u;
  c3u = t2ba + c3t;
  if ( c3u < t2ba )
    ++c1u;
  t1w = (unsigned __int16)a[7];
  t2cf = HIWORD(a[7]);
  bl_0w = (unsigned __int16)a[3];
  bh_0w = HIWORD(a[3]);
  ht_22 = t2cf * bh_0w;
  m_28 = t2cf * bl_0w + t1w * bh_0w;
  if ( m_28 < t2cf * bl_0w )
    ht_22 += 0x10000;
  ht_22a = ht_22 + HIWORD(m_28);
  m1_22 = (unsigned __int16)m_28 << 16;
  lt_22 = m1_22 + t1w * bl_0w;
  if ( lt_22 < m1_22 )
    ++ht_22a;
  if ( (ht_22a & 0x80000000) != 0 )
    ++c1u;
  t2bb = 2 * ht_22a;
  if ( (lt_22 & 0x80000000) != 0 )
    ++t2bb;
  c2v = 2 * lt_22 + c2u;
  if ( c2v < 2 * lt_22 && !++t2bb )
    ++c1u;
  c3v = t2bb + c3u;
  if ( c3v < t2bb )
    ++c1u;
  r[10] = c2v;
  c2w = 0;
  t1x = (unsigned __int16)a[7];
  t2cg = HIWORD(a[7]);
  bl_0x = (unsigned __int16)a[4];
  bh_0x = HIWORD(a[4]);
  ht_23 = t2cg * bh_0x;
  m_29 = t2cg * bl_0x + t1x * bh_0x;
  if ( m_29 < t2cg * bl_0x )
    ht_23 += 0x10000;
  ht_23a = ht_23 + HIWORD(m_29);
  m1_23 = (unsigned __int16)m_29 << 16;
  lt_23 = m1_23 + t1x * bl_0x;
  if ( lt_23 < m1_23 )
    ++ht_23a;
  if ( (ht_23a & 0x80000000) != 0 )
    c2w = 1;
  t2bc = 2 * ht_23a;
  if ( (lt_23 & 0x80000000) != 0 )
    ++t2bc;
  c3w = 2 * lt_23 + c3v;
  if ( c3w < 2 * lt_23 && !++t2bc )
    ++c2w;
  c1v = t2bc + c1u;
  if ( c1v < t2bc )
    ++c2w;
  t1y = (unsigned __int16)a[6];
  t2ch = HIWORD(a[6]);
  bl_0y = (unsigned __int16)a[5];
  bh_0y = HIWORD(a[5]);
  ht_24 = t2ch * bh_0y;
  m_30 = t2ch * bl_0y + t1y * bh_0y;
  if ( m_30 < t2ch * bl_0y )
    ht_24 += 0x10000;
  ht_24a = ht_24 + HIWORD(m_30);
  m1_24 = (unsigned __int16)m_30 << 16;
  lt_24 = m1_24 + t1y * bl_0y;
  if ( lt_24 < m1_24 )
    ++ht_24a;
  if ( (ht_24a & 0x80000000) != 0 )
    ++c2w;
  t2bd = 2 * ht_24a;
  if ( (lt_24 & 0x80000000) != 0 )
    ++t2bd;
  c3x = 2 * lt_24 + c3w;
  if ( c3x < 2 * lt_24 && !++t2bd )
    ++c2w;
  c1w = t2bd + c1v;
  if ( c1w < t2bd )
    ++c2w;
  r[11] = c3x;
  c3y = 0;
  h_5a = a[6];
  l_5a = (unsigned __int16)h_5a;
  h_5b = HIWORD(h_5a);
  m_31 = h_5b * l_5a;
  h_5 = ((__int64)((h_5b * l_5a) & 0xFFFF8000) >> 15) + h_5b * h_5b;
  m_31a = m_31 << 17;
  l_5 = m_31a + l_5a * l_5a;
  if ( l_5 < m_31a )
    ++h_5;
  t2be = h_5;
  c1x = l_5 + c1w;
  if ( c1x < l_5 )
    t2be = h_5 + 1;
  c2x = t2be + c2w;
  if ( c2x < t2be )
    c3y = 1;
  t1z = (unsigned __int16)a[7];
  t2ci = HIWORD(a[7]);
  bl_0z = (unsigned __int16)a[5];
  bh_0z = HIWORD(a[5]);
  ht_25 = t2ci * bh_0z;
  m_32 = t2ci * bl_0z + t1z * bh_0z;
  if ( m_32 < t2ci * bl_0z )
    ht_25 += 0x10000;
  ht_25a = ht_25 + HIWORD(m_32);
  m1_25 = (unsigned __int16)m_32 << 16;
  lt_25 = m1_25 + t1z * bl_0z;
  if ( lt_25 < m1_25 )
    ++ht_25a;
  if ( (ht_25a & 0x80000000) != 0 )
    ++c3y;
  t2bf = 2 * ht_25a;
  if ( (lt_25 & 0x80000000) != 0 )
    ++t2bf;
  c1y = 2 * lt_25 + c1x;
  if ( c1y < 2 * lt_25 && !++t2bf )
    ++c3y;
  c2y = t2bf + c2x;
  if ( c2y < t2bf )
    ++c3y;
  r[12] = c1y;
  c1z = 0;
  t1ba = (unsigned __int16)a[7];
  t2cj = HIWORD(a[7]);
  bl_0ba = (unsigned __int16)a[6];
  bh_0ba = HIWORD(a[6]);
  ht_26 = t2cj * bh_0ba;
  m_33 = t2cj * bl_0ba + t1ba * bh_0ba;
  if ( m_33 < t2cj * bl_0ba )
    ht_26 += 0x10000;
  ht_26a = ht_26 + HIWORD(m_33);
  m1_26 = (unsigned __int16)m_33 << 16;
  lt_26 = m1_26 + t1ba * bl_0ba;
  if ( lt_26 < m1_26 )
    ++ht_26a;
  if ( (ht_26a & 0x80000000) != 0 )
    c1z = 1;
  t2bg = 2 * ht_26a;
  if ( (lt_26 & 0x80000000) != 0 )
    ++t2bg;
  c2z = 2 * lt_26 + c2y;
  if ( c2z < 2 * lt_26 && !++t2bg )
    ++c1z;
  c3z = t2bg + c3y;
  if ( c3z < t2bg )
    ++c1z;
  r[13] = c2z;
  h_6a = a[7];
  l_6a = (unsigned __int16)h_6a;
  h_6b = HIWORD(h_6a);
  m_34 = h_6b * l_6a;
  h_6 = ((__int64)((h_6b * l_6a) & 0xFFFF8000) >> 15) + h_6b * h_6b;
  m_34a = m_34 << 17;
  l_6 = m_34a + l_6a * l_6a;
  if ( l_6 < m_34a )
    ++h_6;
  t2bh = h_6;
  c3ba = l_6 + c3z;
  if ( c3ba < l_6 )
    t2bh = h_6 + 1;
  r[14] = c3ba;
  r[15] = t2bh + c1z;
}