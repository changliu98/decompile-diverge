int isLegalUTF8(unsigned char *source, int length) {
  unsigned char *thePointer = source + length;
  unsigned char theByte;
  switch (length) {
    case 4:
      theByte = *--thePointer;
      if (theByte < 0x80 || theByte > 0xBF) return 0;
    case 3:
      theByte = *--thePointer;
      if (theByte < 0x80 || theByte > 0xBF) return 0;
    case 2:
      theByte = *--thePointer;
      if (theByte > 0xBF) return 0;
      switch (*source) {
        case 0xE0:
          if (theByte < 0xA0) return 0;
          break;
        case 0xF0:
          if (theByte < 0x90) return 0;
          break;
        case 0xF4:
          if (theByte > 0x8F) return 0;
          break;
        default:
          if (theByte < 0x80) return 0;
      }
    case 1:
      if (*source >= 0x80 && *source < 0xC2) return 0;
      if (*source > 0xF4) return 0;
  }
  return 1;
}