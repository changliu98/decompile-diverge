int func0(int x) {
  if (x % 2) return (x + 1) / 2;
  int i, c = 0;
  for (i = 0; i < 32; i++) c += (x >> i) & 1;
  int y = x / 2;
  if (c % 2) y++;
  return y;
}