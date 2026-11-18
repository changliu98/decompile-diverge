static inline int clip_f15(int x) {
  if (x < -32767)
    return -32767;
  else if (x > 32767)
    return 32767;
  else
    return x;
}