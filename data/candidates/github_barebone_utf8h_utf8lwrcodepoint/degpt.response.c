utf8_int32_t utf8lwrcodepoint(utf8_int32_t codepoint)
{
  // Check if the codepoint is an uppercase letter in specific ranges:
  // ASCII uppercase (A-Z), Latin-1 Supplement uppercase, Greek uppercase,
  // and Cyrillic uppercase. If it is NOT one of these, fall through to the end.
  if (((((codepoint < 0x41) || (0x5a < codepoint)) && ((codepoint < 0xc0 || (0xd6 < codepoint)))) &&
      (((codepoint < 0xd8 || (0xde < codepoint)) && ((codepoint < 0x391 || (0x3a1 < codepoint)))))) &&
     (((codepoint < 0x3a3 || (0x3ab < codepoint)) && ((codepoint < 0x410 || (0x42f < codepoint)))))) {
    // Exclude specific Cyrillic uppercase letters that have special lowercase mappings
    // handled in the switch statement or specific logic below.
    if ((codepoint < 0x400) || (0x40f < codepoint)) {
      // Check if the codepoint is in Latin-1 Supplement or Latin Extended-A/B ranges
      // that are uppercase but not handled by simple arithmetic conversion.
      if (((((((codepoint < 0x100) || (0x12f < codepoint)) && ((codepoint < 0x132 || (0x137 < codepoint)))) &&
            ((codepoint < 0x14a || (0x177 < codepoint)))) &&
           ((((codepoint < 0x182 || (0x185 < codepoint)) && ((codepoint < 0x1a0 || (0x1a5 < codepoint)))) &&
            ((codepoint < 0x1de || (0x1ef < codepoint)))))) && ((codepoint < 0x1f8 || (0x21f < codepoint)))) &&
         (((((codepoint < 0x222 || (0x233 < codepoint)) && ((codepoint < 0x246 || (0x24f < codepoint)))) &&
           (((codepoint < 0x3d8 || (0x3ef < codepoint)) && ((codepoint < 0x460 || (0x481 < codepoint)))))) &&
          ((codepoint < 0x48a || (0x4ff < codepoint)))))) {
        // Further filter for specific Latin Extended characters that need special handling
        // or simple bit manipulation.
        if ((((codepoint < 0x139) || (0x148 < codepoint)) && ((codepoint < 0x179 || (0x17e < codepoint)))) &&
           ((((codepoint < 0x1af || (0x1b0 < codepoint)) && ((codepoint < 0x1b3 || (0x1b6 < codepoint)))) &&
            ((codepoint < 0x1cd || (0x1dc < codepoint)))))) {
          // Handle specific uppercase codepoints that have non-trivial lowercase mappings
          // or require specific bit manipulation not covered by the general cases below.
          switch (codepoint) {
            case 0x178: return 0xff; // Y with diaeresis
            case 0x187: return 0x188; // W with hook
            case 0x18b: return 0x18c; // X with dot above
            case 0x18e: return 0x1dd; // AE with acute
            case 0x191: return 0x192; // F with hook
            case 0x198: return 0x199; // K with hook
            case 0x1a7: return 0x1a8; // L with stroke
            case 0x1ac: return 0x1ad; // L with dot below bar
            case 0x1b7: return 0x292; // J with circumflex
            case 0x1b8: return 0x1b9; // K with acute
            case 0x1bc: return 0x1bd; // K with dot below
            case 0x1c4: return 0x1c6; // DZ with caron
            case 0x1c7: return 0x1c9; // D with small letter
            case 0x1ca: return 0x1cc; // L with caron
            case 0x1f1: return 499; // DZ
            case 500: return 0x1f5; // dz
            case 0x1f7: return 0x1bf; // H with caron
            case 0x220: return 0x19e; // N with long right leg
            case 0x23b: return 0x23c; // S with comma below
            case 0x23d: return 0x19a; // S with dot above
            case 0x241: return 0x242; // G with acute
            case 0x243: return 0x180; // B with hook
            case 0x370: return 0x371; // Greek uppercase alpha with varia
            case 0x372: return 0x373; // Greek uppercase epsilon with varia
            case 0x376: return 0x377; // Greek uppercase upsilon with varia
            case 0x37f: return 0x3f3; // Greek uppercase yot
            case 0x386: return 0x3ac; // Greek uppercase alpha with tonos
            case 0x388: return 0x3ad; // Greek uppercase epsilon with tonos
            case 0x389: return 0x3ae; // Greek uppercase eta with tonos
            case 0x38a: return 0x3af; // Greek uppercase iota with tonos
            case 0x38c: return 0x3cc; // Greek uppercase omicron with tonos
            case 0x38e: return 0x3cd; // Greek uppercase upsilon with tonos
            case 0x38f: return 0x3ce; // Greek uppercase omega with tonos
            case 0x3cf: return 0x3d7; // Greek uppercase kappa symbol
            case 0x3f4: return 0x3b8; // Greek uppercase theta symbol
            case 0x3f7: return 0x3f8; // Greek uppercase digamma
            case 0x3f9: return 0x3f2; // Greek uppercase lunate sigma symbol
            case 0x3fa: return 0x3fb; // Greek uppercase digamma with stroke
            case 0x3fd: return 0x37b; // Greek uppercase small letter iota with dialytika and tonos
            case 0x3fe: return 0x37c; // Greek uppercase small letter upsilon with dialytika and tonos
            case 0x3ff: return 0x37d; // Greek uppercase small letter alpha with dialytika and tonos
            default: return codepoint;
          }
        }
        // For other Latin Extended uppercase letters, convert by setting the last bit to 0
        // (assuming even codepoints are lowercase or handling specific pairs).
        return codepoint + 1U & 0xfffffffe;
      }
      // For Latin-1 Supplement uppercase letters, convert by setting the last bit to 1
      // (assuming odd codepoints are uppercase).
      return codepoint | 1;
    }
    // For specific Cyrillic uppercase letters, add 0x50 to convert to lowercase.
    return codepoint + 0x50;
  }
  // For ASCII uppercase letters (A-Z), add 0x20 to convert to lowercase.
  return codepoint + 0x20;
}