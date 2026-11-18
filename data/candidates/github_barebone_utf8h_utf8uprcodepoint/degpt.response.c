utf8_int32_t utf8uprcodepoint(utf8_int32_t code_point)
{
    // Check if the code point is NOT a lowercase letter in Latin, Greek, or Cyrillic scripts.
    // If it is not a lowercase letter, return it unchanged.
    if (((((code_point < 0x61) || (0x7a < code_point)) && ((code_point < 0xe0 || (0xf6 < code_point)))) &&
        (((code_point < 0xf8 || (0xfe < code_point)) && ((code_point < 0x3b1 || (0x3c1 < code_point)))))) &&
       (((code_point < 0x3c3 || (0x3cb < code_point)) && ((code_point < 0x430 || (0x44f < code_point)))))) {
        if ((code_point < 0x450) || (0x45f < code_point)) {
            // Check if the code point is NOT in specific ranges of Latin Extended-A/B and other scripts.
            if (((((((code_point < 0x100) || (0x12f < code_point)) && ((code_point < 0x132 || (0x137 < code_point)))) &&
                  ((code_point < 0x14a || (0x177 < code_point)))) &&
                 ((((code_point < 0x182 || (0x185 < code_point)) && ((code_point < 0x1a0 || (0x1a5 < code_point)))) &&
                  ((code_point < 0x1de || (0x1ef < code_point)))))) && ((code_point < 0x1f8 || (0x21f < code_point)))) &&
               (((((code_point < 0x222 || (0x233 < code_point)) && ((code_point < 0x246 || (0x24f < code_point)))) &&
                 (((code_point < 0x3d8 || (0x3ef < code_point)) && ((code_point < 0x460 || (0x481 < code_point)))))) &&
                ((code_point < 0x48a || (0x4ff < code_point)))))) {
                // Check if the code point is NOT in specific sub-ranges for special case mappings.
                if ((((code_point < 0x139) || (0x148 < code_point)) && ((code_point < 0x179 || (0x17e < code_point)))) &&
                   ((((code_point < 0x1af || (0x1b0 < code_point)) && ((code_point < 0x1b3 || (0x1b6 < code_point)))) &&
                    ((code_point < 0x1cd || (0x1dc < code_point)))))) {
                    // Handle specific single-code-point mappings for uppercase conversion.
                    switch (code_point) {
                        case 0xff: return 0x178;
                        case 0x180: return 0x243;
                        case 0x188: return 0x187;
                        case 0x18c: return 0x18b;
                        case 0x192: return 0x191;
                        case 0x199: return 0x198;
                        case 0x19a: return 0x23d;
                        case 0x19e: return 0x220;
                        case 0x1a8: return 0x1a7;
                        case 0x1ad: return 0x1ac;
                        case 0x1b9: return 0x1b8;
                        case 0x1bd: return 0x1bc;
                        case 0x1bf: return 0x1f7;
                        case 0x1c6: return 0x1c4;
                        case 0x1c9: return 0x1c7;
                        case 0x1cc: return 0x1ca;
                        case 0x1dd: return 0x18e;
                        case 499: return 0x1f1;
                        case 0x1f5: return 500;
                        case 0x23c: return 0x23b;
                        case 0x242: return 0x241;
                        case 0x292: return 0x1b7;
                        case 0x371: return 0x370;
                        case 0x373: return 0x372;
                        case 0x377: return 0x376;
                        case 0x37b: return 0x3fd;
                        case 0x37c: return 0x3fe;
                        case 0x37d: return 0x3ff;
                        case 0x3ac: return 0x386;
                        case 0x3ad: return 0x388;
                        case 0x3ae: return 0x389;
                        case 0x3af: return 0x38a;
                        case 0x3cc: return 0x38c;
                        case 0x3cd: return 0x38e;
                        case 0x3ce: return 0x38f;
                        case 0x3d1: return 0x398;
                        case 0x3d7: return 0x3cf;
                        case 0x3f2: return 0x3f9;
                        case 0x3f3: return 0x37f;
                        case 0x3f8: return 0x3f7;
                        case 0x3fb: return 0x3fa;
                        default: return code_point;
                    }
                }
                else {
                    // Handle pairs of lowercase letters that map to a single uppercase letter (e.g., ligatures).
                    // cp - 1U | 1 effectively maps odd code points to the preceding even one, or handles specific pair logic.
                    return code_point - 1U | 1;
                }
            }
            else {
                // Handle Greek lowercase letters that map to uppercase by clearing the last bit (e.g., final sigma handling or similar bit manipulation).
                return code_point & 0xfffffffe;
            }
        }
        else {
            // Handle Cyrillic lowercase letters (0x450-0x45f) by subtracting 0x50.
            return code_point - 0x50;
        }
    }
    else {
        // Handle standard ASCII and common Latin/Greek/Cyrillic lowercase letters by subtracting 0x20.
        return code_point - 0x20;
    }
}