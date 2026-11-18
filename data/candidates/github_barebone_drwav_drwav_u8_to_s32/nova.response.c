void drwav_u8_to_s32(uint32_t *out, const unsigned char *in, size_t len) {
  size_t i;

  if (out == NULL || in == NULL || len == 0) {
    return;
  }

  for (i = 0; i < len; i++) {
    *out++ = (uint32_t)((unsigned int)in[i] - 128) << 24;
  }
}