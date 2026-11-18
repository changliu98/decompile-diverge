void cpuid(int code, unsigned *a, unsigned *b, unsigned *c, unsigned *d) {
  unsigned _a, _b, _c, _d;
  __asm__ __volatile__(
      "cpuid"
      : "=a"(_a), "=b"(_b), "=c"(_c), "=d"(_d)
      : "a"(code));
  *a = _a;
  *b = _b;
  *c = _c;
  *d = _d;
}