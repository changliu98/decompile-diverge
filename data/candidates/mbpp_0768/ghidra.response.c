int func0(int x)

{
  int parity;
  int x_local;
  
  parity = 0;
  for (x_local = x; x_local != 0; x_local = x_local & x_local - 1U) {
    parity = parity + 1;
  }
  return (int)(parity % 2 == 1);
}