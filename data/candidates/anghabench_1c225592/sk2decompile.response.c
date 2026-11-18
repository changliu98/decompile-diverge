static inline unsigned int DWC_LE32_TO_CPU(const unsigned char *p) {
  unsigned int val;
  val = *p++;
  val |= *p++ << 8;
  val |= *p++ << 16;
  val |= *p++ << 24;
  return val;
}