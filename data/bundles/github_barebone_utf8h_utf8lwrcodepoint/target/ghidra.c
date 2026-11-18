utf8_int32_t utf8lwrcodepoint(utf8_int32_t cp)

{
  utf8_int32_t cp_local;
  
  if (((((cp < 0x41) || (0x5a < cp)) && ((cp < 0xc0 || (0xd6 < cp)))) &&
      (((cp < 0xd8 || (0xde < cp)) && ((cp < 0x391 || (0x3a1 < cp)))))) &&
     (((cp < 0x3a3 || (0x3ab < cp)) && ((cp < 0x410 || (0x42f < cp)))))) {
    if ((cp < 0x400) || (0x40f < cp)) {
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
          if (cp == 0x178) {
            cp_local = 0xff;
          }
          else if (cp == 0x187) {
            cp_local = 0x188;
          }
          else if (cp == 0x18b) {
            cp_local = 0x18c;
          }
          else if (cp == 0x18e) {
            cp_local = 0x1dd;
          }
          else if (cp == 0x191) {
            cp_local = 0x192;
          }
          else if (cp == 0x198) {
            cp_local = 0x199;
          }
          else if (cp == 0x1a7) {
            cp_local = 0x1a8;
          }
          else if (cp == 0x1ac) {
            cp_local = 0x1ad;
          }
          else if (cp == 0x1b7) {
            cp_local = 0x292;
          }
          else if (cp == 0x1b8) {
            cp_local = 0x1b9;
          }
          else if (cp == 0x1bc) {
            cp_local = 0x1bd;
          }
          else if (cp == 0x1c4) {
            cp_local = 0x1c6;
          }
          else if (cp == 0x1c7) {
            cp_local = 0x1c9;
          }
          else if (cp == 0x1ca) {
            cp_local = 0x1cc;
          }
          else if (cp == 0x1f1) {
            cp_local = 499;
          }
          else if (cp == 500) {
            cp_local = 0x1f5;
          }
          else if (cp == 0x1f7) {
            cp_local = 0x1bf;
          }
          else if (cp == 0x220) {
            cp_local = 0x19e;
          }
          else if (cp == 0x23b) {
            cp_local = 0x23c;
          }
          else if (cp == 0x23d) {
            cp_local = 0x19a;
          }
          else if (cp == 0x241) {
            cp_local = 0x242;
          }
          else if (cp == 0x243) {
            cp_local = 0x180;
          }
          else if (cp == 0x370) {
            cp_local = 0x371;
          }
          else if (cp == 0x372) {
            cp_local = 0x373;
          }
          else if (cp == 0x376) {
            cp_local = 0x377;
          }
          else if (cp == 0x37f) {
            cp_local = 0x3f3;
          }
          else if (cp == 0x386) {
            cp_local = 0x3ac;
          }
          else if (cp == 0x388) {
            cp_local = 0x3ad;
          }
          else if (cp == 0x389) {
            cp_local = 0x3ae;
          }
          else if (cp == 0x38a) {
            cp_local = 0x3af;
          }
          else if (cp == 0x38c) {
            cp_local = 0x3cc;
          }
          else if (cp == 0x38e) {
            cp_local = 0x3cd;
          }
          else if (cp == 0x38f) {
            cp_local = 0x3ce;
          }
          else if (cp == 0x3cf) {
            cp_local = 0x3d7;
          }
          else if (cp == 0x3f4) {
            cp_local = 0x3b8;
          }
          else if (cp == 0x3f7) {
            cp_local = 0x3f8;
          }
          else if (cp == 0x3f9) {
            cp_local = 0x3f2;
          }
          else if (cp == 0x3fa) {
            cp_local = 0x3fb;
          }
          else if (cp == 0x3fd) {
            cp_local = 0x37b;
          }
          else if (cp == 0x3fe) {
            cp_local = 0x37c;
          }
          else {
            cp_local = cp;
            if (cp == 0x3ff) {
              cp_local = 0x37d;
            }
          }
        }
        else {
          cp_local = cp + 1U & 0xfffffffe;
        }
      }
      else {
        cp_local = cp | 1;
      }
    }
    else {
      cp_local = cp + 0x50;
    }
  }
  else {
    cp_local = cp + 0x20;
  }
  return cp_local;
}