unsigned long adler32_z(unsigned long adler, char *buf, unsigned long len)
{
  unsigned long a; unsigned long b;
  char *p;
  unsigned long n;
  a = (adler >> 16) & 0xFFFF;
  b = adler & 0xFFFF;
  if (len == 1)
  {
    b += (unsigned char)(*buf);
    if (b >= 65521)
      b -= 65521;
    a += b;
    if (a >= 65521)
      a -= 65521;
    return (a << 16) | b;
  }
  else if (buf == ((void *)0))
  {
    return 1;
  }
  else if (len < 16)
  {
    while (len-- > 0)
    {
      a += (unsigned char)(*buf++);
      b += a;
    }
    if (a >= 65521)
      a -= 65521;
    return (b % 65521) * 65536 + a;
  }
  else
  {
    p = (char *)buf;
    n = len;
    while (n >= 5552)
    {
      n -= 5552;
      do
      {
        a += p[0];
        b += a;
        a += p[1];
        b += a;
        a += p[2];
        b += a;
        a += p[3];
        b += a;
        a += p[4];
        b += a;
        a += p[5];
        b += a;
        a += p[6];
        b += a;
        a += p[7];
        b += a;
        a += p[8];
        b += a;
        a += p[9];
        b += a;
        a += p[10];
        b += a;
        a += p[11];
        b += a;
        a += p[12];
        b += a;
        a += p[13];
        b += a;
        a += p[14];
        b += a;
        a += p[15];
        b += a;
        p += 16;
      }
      while (--n);
      a %= 65521;
      b %= 65521;
    }
    if (n > 0)
    {
      do
      {
        a += p[0];
        b += a;
        a += p[1];
        b += a;
        a += p[2];
        b += a;
        a += p[3];
        b += a;
        a += p[4];
        b += a;
        a += p[5];
        b += a;
        a += p[6];
        b += a;
        a += p[7];
        b += a;
        a += p[8];
        b += a;
        a += p[9];
        b += a;
        a += p[10];
        b += a;
        a += p[11];
        b += a;
        a += p[12];
        b += a;
        a += p[13];
        b += a;
        a += p[14];
        b += a;
        a += p[15];
        b += a;
        p += 16;
      }
      while (--n);
    }
    a %= 65521;
    b %= 65521;
    return (b << 16) | a;
  }
}