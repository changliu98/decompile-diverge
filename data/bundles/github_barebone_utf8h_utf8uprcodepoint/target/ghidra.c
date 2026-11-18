utf8_int32_t utf8uprcodepoint(utf8_int32_t cp)

{
  utf8_int32_t cp_local;
  
  if (((((cp < 0x61) || (0x7a < cp)) && ((cp < 0xe0 || (0xf6 < cp)))) &&
      (((cp < 0xf8 || (0xfe < cp)) && ((cp < 0x3b1 || (0x3c1 < cp)))))) &&
     (((cp < 0x3c3 || (0x3cb < cp)) && ((cp < 0x430 || (0x44f < cp)))))) {
    if ((cp < 0x450) || (0x45f < cp)) {
      if (((((((cp < 0x100) || (0x12f < cp)) && ((cp < 0x132 || (0x137 < cp)))) &&
            ((cp < 0x14a || (0x177 < cp)))) &&
           ((((cp < 0x182 || (0x185 < cp)) && ((cp < 0x1a0 || (0x1a5 < cp)))) &&
            ((cp < 0x1de || (0x1ef < cp)))))) && ((cp < 0x1f8 || (0x21f < cp)))) &&
         (((((cp < 0x222 || (0x233 < cp)) && ((cp < 0x246 || (0x24f < cp)))) &&
           (((cp < 0x3d8 || (0x3ef < cp)) && ((cp < 0x460 || (0x481 < cp)))))) &&
          ((cp < 0x48a || (0x4ff < cp)))))) {
        if ((((cp < 0x139) || (0x148 < cp)) && ((cp < 0x179 || (0x17e < cp)))) &&
           ((((cp < 0x1af || (0x1b0 < cp)) && ((cp < 0x1b3 || (0x1b6 < cp)))) &&
            ((cp < 0x1cd || (0x1dc < cp)))))) {
          if (cp == 0xff) {
            cp_local = 0x178;
          }
          else if (cp == 0x180) {
            cp_local = 0x243;
          }
          else if (cp == 0x188) {
            cp_local = 0x187;
          }
          else if (cp == 0x18c) {
            cp_local = 0x18b;
          }
          else if (cp == 0x192) {
            cp_local = 0x191;
          }
          else if (cp == 0x199) {
            cp_local = 0x198;
          }
          else if (cp == 0x19a) {
            cp_local = 0x23d;
          }
          else if (cp == 0x19e) {
            cp_local = 0x220;
          }
          else if (cp == 0x1a8) {
            cp_local = 0x1a7;
          }
          else if (cp == 0x1ad) {
            cp_local = 0x1ac;
          }
          else if (cp == 0x1b9) {
            cp_local = 0x1b8;
          }
          else if (cp == 0x1bd) {
            cp_local = 0x1bc;
          }
          else if (cp == 0x1bf) {
            cp_local = 0x1f7;
          }
          else if (cp == 0x1c6) {
            cp_local = 0x1c4;
          }
          else if (cp == 0x1c9) {
            cp_local = 0x1c7;
          }
          else if (cp == 0x1cc) {
            cp_local = 0x1ca;
          }
          else if (cp == 0x1dd) {
            cp_local = 0x18e;
          }
          else if (cp == 499) {
            cp_local = 0x1f1;
          }
          else if (cp == 0x1f5) {
            cp_local = 500;
          }
          else if (cp == 0x23c) {
            cp_local = 0x23b;
          }
          else if (cp == 0x242) {
            cp_local = 0x241;
          }
          else if (cp == 0x292) {
            cp_local = 0x1b7;
          }
          else if (cp == 0x371) {
            cp_local = 0x370;
          }
          else if (cp == 0x373) {
            cp_local = 0x372;
          }
          else if (cp == 0x377) {
            cp_local = 0x376;
          }
          else if (cp == 0x37b) {
            cp_local = 0x3fd;
          }
          else if (cp == 0x37c) {
            cp_local = 0x3fe;
          }
          else if (cp == 0x37d) {
            cp_local = 0x3ff;
          }
          else if (cp == 0x3ac) {
            cp_local = 0x386;
          }
          else if (cp == 0x3ad) {
            cp_local = 0x388;
          }
          else if (cp == 0x3ae) {
            cp_local = 0x389;
          }
          else if (cp == 0x3af) {
            cp_local = 0x38a;
          }
          else if (cp == 0x3cc) {
            cp_local = 0x38c;
          }
          else if (cp == 0x3cd) {
            cp_local = 0x38e;
          }
          else if (cp == 0x3ce) {
            cp_local = 0x38f;
          }
          else if (cp == 0x3d1) {
            cp_local = 0x398;
          }
          else if (cp == 0x3d7) {
            cp_local = 0x3cf;
          }
          else if (cp == 0x3f2) {
            cp_local = 0x3f9;
          }
          else if (cp == 0x3f3) {
            cp_local = 0x37f;
          }
          else if (cp == 0x3f8) {
            cp_local = 0x3f7;
          }
          else {
            cp_local = cp;
            if (cp == 0x3fb) {
              cp_local = 0x3fa;
            }
          }
        }
        else {
          cp_local = cp - 1U | 1;
        }
      }
      else {
        cp_local = cp & 0xfffffffe;
      }
    }
    else {
      cp_local = cp + -0x50;
    }
  }
  else {
    cp_local = cp + -0x20;
  }
  return cp_local;
}