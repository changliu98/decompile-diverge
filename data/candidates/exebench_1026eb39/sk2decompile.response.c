static inline void ut32_unpack(const unsigned char *buf, unsigned *val) {
  *val = buf[0];
  *val += buf[1] << 8;
  *val += buf[2] << 16;
  *val += buf[3] << 24;
}