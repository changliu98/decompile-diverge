static inline unsigned long long rev64(unsigned long long in) {
  unsigned long long out = in;
  out = (out << 8) & 0xff00ff00ff00ff00ULL | (out >> 8) & 0x00ff00ff00ff00ffULL;
  out = (out << 16) & 0xffff0000ffff0000ULL | (out >> 16) & 0x0000ffff0000ffffULL;
  out = (out << 32) & 0xffffffff00000000ULL | (out >> 32) & 0x00000000ffffffffULL;
  return out;
}