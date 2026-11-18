static uchar utf8lwrcodepoint(uchar c) {
  uchar r = c;
  if ((c >= 0x41 && c <= 0x5a) || (c >= 0xc0 && c <= 0xd6) ||
      (c >= 0xd8 && c <= 0xde) || (c >= 0xe13 && c <= 0xe29) ||
      (c >= 0xe31 && c <= 0xe39) || (c >= 0x410 && c <= 0x42f)) {
    r = c + 0x20;
  } else if (c >= 0x400 && c <= 0x40f) {
    r = c + 0x50;
  } else if ((c >= 0x100 && c <= 0x13f) || (c >= 0x142 && c <= 0x147) ||
             (c >= 0x17a && c <= 0x1bf) || (c >= 0x1c6 && c <= 0x1c9) ||
             (c >= 0x220 && c <= 0x225) || (c >= 0x258 && c <= 0x26f) ||
             (c >= 0x272 && c <= 0x29f) || (c >= 0x2a2 && c <= 0x2af) ||
             (c >= 0x2ba && c <= 0x2bf) || (c >= 0x3c0 && c <= 0x3ff) ||
             (c >= 0x480 && c <= 0x4ff) || (c >= 0x540 && c <= 0x5ff)) {
    r = c | 0x01;
  } else if ((c >= 0x149 && c <= 0x14e) || (c >= 0x1cd && c <= 0x1ce) ||
             (c >= 0x1f5 && c <= 0x1f8) || (c >= 0x1fb && c <= 0x1fc) ||
             (c >= 0x227 && c <= 0x228) || (c >= 0x259 && c <= 0x25f)) {
    r = (c + 1) & ~0x01;
  } else if (c == 0x178) {
    r = 0xff;
  } else if (c == 0x191) {
    r = 0x192;
  } else if (c == 0x197) {
    r = 0x198;
  } else if (c == 0x19e) {
    r = 0x25f;
  } else if (c == 0x1a1) {
    r = 0x1a2;
  } else if (c == 0x1ac) {
    r = 0x1ad;
  } else if (c == 0x1b7) {
    r = 0x1b8;
  } else if (c == 0x1bb) {
    r = 0x1bc;
  } else if (c == 0x1c5) {
    r = 0x402;
  } else if (c == 0x1c6) {
    r = 0x1c7;
  } else if (c == 0x1c9) {
    r = 0x403;
  } else if (c == 0x1ca) {
    r = 0x1cb;
  } else if (c == 0x1cd) {
    r = 0x1ce;
  } else if (c == 0x1d2) {
    r = 0x1d4;
  } else if (c == 0x1d7) {
    r = 0x1d9;
  } else if (c == 0x1da) {
    r = 0x1db;
  } else if (c == 0x1dc) {
    r = 0x1dd;
  } else if (c == 0x3a0) {
    r = 0x3a1;
  } else if (c == 0x3a2) {
    r = 0x3a3;
  } else if (c == 0x3a6) {
    r = 0x3a7;
  } else if (c == 0x3b5) {
    r = 0x3b7;
  } else if (c == 0x3b8) {
    r = 0x3b9;
  } else if (c == 0x3ba) {
    r = 0x3bb;
  } else if (c == 0x3c1) {
    r = 0x3c2;
  } else if (c == 0x3c3) {
    r = 0x3c4;
  } else if (c == 0x3c5) {
    r = 0x3c6;
  } else if (c == 0x3c7) {
    r = 0x3c8;
  } else if (c == 0x3c9) {
    r = 0x3ca;
  } else if (c == 0x3d0) {
    r = 0x3d1;
  } else if (c == 0x3d6) {
    r = 0x3d7;
  } else if (c == 0x3d9) {
    r = 0x3da;
  } else if (c == 0x3db) {
    r = 0x3dc;
  } else if (c == 0x3dd) {
    r = 0x3de;
  } else if (c == 0x3e0) {
    r = 0x3e1;
  } else if (c == 0x3e2) {
    r = 0x3e3;
  } else if (c == 0x3e3) {
    r = 0x3e4;
  }
  return r;
}