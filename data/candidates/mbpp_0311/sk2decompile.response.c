int func0(int x) {
  if ((x + 1) & x) {
    int i = 0;
    int y = x;
    int j = 0;
    while (y) {
      if (!(y & 1)) i = j;
      j++;
      y >>= 1;
    }
    x |= (1 << i);
  }
  return x;
}