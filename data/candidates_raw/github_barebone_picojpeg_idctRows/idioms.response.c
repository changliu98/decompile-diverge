void sbc_filter()
{
  unsigned char i;
  short *p = gCoeffBuf;
  for ( i = 0; i < 8; i++ )
  {
    if ( p[7] | p[6] | p[5] | p[4] | p[3] | p[2] | p[1] )
    {
      short a = p[5];
      short b = p[3];
      short c = p[1];
      short d = p[7];
      short e = sbc_add( a - b - (c - d) );
      short f = sbc_sub( c - d ) - e;
      short g = e - sbc_sub( a - b );
      short h = f - (a + b + c + d);
      short i1 = p[4];
      short j = i1 + p[0];
      short k = p[0] - i1;
      short l = p[2];
      short m = p[6];
      short n = sbc_sub( l - m ) - (l + m);
      p[0] = j + l + m + a + b + c + d;
      p[1] = h + n + k;
      p[2] = g + k - n;
      p[3] = j - (l + m) - (f + g);
      p[4] = f + g + j - (l + m);
      p[5] = k - n - g;
      p[6] = n + k - h;
      p[7] = m + l + j - (a + b + c + d);
    }
    else
    {
      short a = p[0];
      p[1] = a;
      p[2] = a;
      p[3] = a;
      p[4] = a;
      p[5] = a;
      p[6] = a;
      p[7] = a;
    }
    p += 8;
  }
}