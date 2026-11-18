static inline int __ffs(unsigned long x) {
  unsigned long tmp = x;
  int cnt = 0;
  if ((tmp & 0xffff0000) == 0) {
    cnt += 16;
  } else {
    tmp >>= 16;
  }
  if ((tmp & 0xff00) == 0) {
    cnt += 8;
  } else {
    tmp >>= 8;
  }
  if ((tmp & 0xf0) == 0) {
    cnt += 4;
  } else {
    tmp >>= 4;
  }
  if ((tmp & 0xc) == 0) {
    cnt += 2;
  } else {
    tmp >>= 2;
  }
  if ((tmp & 0x2) == 0) {
    cnt += 1;
  }
  return cnt;
}