int utf8lwrcodepoint(int c)
{
  if (c >= 'A' && c <= 'Z')
    return c + 'a' - 'A';
  if (c >= 0x100 && c <= 0x11f)
    return c + 0x20;
  if (c >= 0x120 && c <= 0x13f)
    return c + 0x20;
  if (c >= 0x0391 && c <= 0x03a9)
    return c + 0x0020;
  if (c >= 0x03b1 && c <= 0x03c9)
    return c + 0x0020;
  if (c >= 0x0410 && c <= 0x042f)
    return c + 0x0020;
  if (c >= 0x04d0 && c <= 0x04ff)
    return c + 0x0050;
  if (c >= 0x0100 && c <= 0x011f)
    return c | 1;
  if (c >= 0x0120 && c <= 0x013f)
    return c | 1;
  if (c >= 0x0140 && c <= 0x014f)
    return c | 1;
  if (c >= 0x0150 && c <= 0x015f)
    return c | 1;
  if (c >= 0x0160 && c <= 0x017f)
    return c | 1;
  if (c >= 0x01d0 && c <= 0x01ff)
    return c | 1;
  if (c >= 0x0210 && c <= 0x021f)
    return c | 1;
  if (c >= 0x0220 && c <= 0x022f)
    return c | 1;
  if (c >= 0x0230 && c <= 0x023f)
    return c | 1;
  if (c >= 0x0400 && c <= 0x041f)
    return c | 1;
  if (c >= 0x0500 && c <= 0x052f)
    return c | 1;
  if (c >= 0x0530 && c <= 0x058f)
    return c | 1;
  if (c == 0x00df)
    return 0x00ff;
  if (c == 0x0392)
    return 0x0393;
  if (c == 0x0396)
    return 0x0397;
  if (c == 0x039a)
    return 0x01d2;
  if (c == 0x039d)
    return 0x039e;
  if (c == 0x039f)
    return 0x03a0;
  if (c == 0x03a3)
    return 0x03a4;
  if (c == 0x03a6)
    return 0x03a7;
  if (c == 0x03a8)
    return 0x03a9;
  if (c == 0x03b1)
    return 0x03b2;
  if (c == 0x03b5)
    return 0x03b6;
  if (c == 0x03b7)
    return 0x03b8;
  if (c == 0x03b9)
    return 0x03ba;
  if (c == 0x03bb)
    return 0x03bc;
  if (c == 0x03bd)
    return 0x03be;
  if (c == 0x03bf)
    return 0x03c0;
  if (c == 0x03c2)
    return 0x03c3;
  if (c == 0x03c4)
    return 0x03c5;
  if (c == 0x03c6)
    return 0x03c7;
  if (c == 0x03c8)
    return 0x03c9;
  if (c == 0x03ca)
    return 0x03cb;
  if (c == 0x03cc)
    return 0x03cd;
  if (c == 0x03ce)
    return 0x03cf;
  if (c == 0x03d1)
    return 0x03d2;
  if (c == 0x03d3)
    return 0x03d4;
  if (c == 0x03d5)
    return 0x03d6;
  if (c == 0x03d7)
    return 0x03d8;
  if (c == 0x03d9)
    return 0x03da;
  if (c == 0x03db)
    return 0x03dc;
  if (c == 0x03dd)
    return 0x03de;
  if (c == 0x03df)
    return 0x03e0;
  if (c == 0x03e1)
    return 0x03e2;
  if (c == 0x03e3)
    return 0x03e4;
  if (c == 0x03e5)
    return 0x03e6;
  if (c == 0x03e7)
    return 0x03e8;
  if (c == 0x03e9)
    return 0x03ea;
  if (c == 0x03eb)
    return 0x03ec;
  if (c == 0x03ed)
    return 0x03ee;
  if (c == 0x03ef)
    return 0x03f0;
  if (c == 0x03f1)
    return 0x03f2;
  if (c == 0x03f3)
    return 0x03f4;
  if (c == 0x03f5)
    return 0x03f6;
  if (c == 0x03f7)
    return 0x03f8;
  if (c == 0x03f9)
    return 0x03fa;
  if (c == 0x03fb)
    return 0x03fc;
  if (c == 0x03fd)
    return 0x03fe;
  if (c == 0x03ff)
    return 0x03e3;
  if (c == 0x0401)
    return 0x0402;
  if (c == 0x0404)
    return 0x0405;
  if (c == 0x0407)
    return 0x0408;
  if (c == 0x040a)
    return 0x040b;
  if (c == 0x040d)
    return 0x040e;
  if (c == 0x0411)
    return 0x0412;
  if (c == 0x0414)
    return 0x0415;
  if (c == 0x0417)
    return 0x0418;
  if (c == 0x041a)
    return 0x041b;
  if (c == 0x041d)
    return 0x041e;
  if (c == 0x0421)
    return 0x042