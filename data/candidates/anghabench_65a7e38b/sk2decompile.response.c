static inline int SCALE(long x, int scale, int div) {
  if (x < 0)
    return (x * scale - div / 2) / div;
  else
    return (x * scale + div / 2) / div;
}