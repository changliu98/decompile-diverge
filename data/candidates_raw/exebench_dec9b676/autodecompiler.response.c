void poly1305_mul(uint8_t out[32], const uint8_t p[32]) {
  unsigned int acc = 0;
  unsigned int i;

  for (i = 0; ; i++) {
    if (i < 32) {
      acc += p[i] * 121291;
      out[i] = acc & 255;
      acc >>= 8;
    } else {
      acc += p[31] * 121291;
      out[31] = acc & 127;
      acc = (acc >> 7) * 19;
      break;
    }
  }

  for (i = 0; ; i++) {
    if (i < 32) {
      acc += out[i];
      out[i] = acc & 255;
      acc >>= 8;
    } else {
      acc += out[i];
      out[i] = acc;
      break;
    }
  }
}