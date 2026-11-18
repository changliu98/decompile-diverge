int func0(int x)
{
  int parity = 0;
  while (x) {
    parity += 1;
    x &= x - 1;
  }
  return (parity % 2) == 0;
}