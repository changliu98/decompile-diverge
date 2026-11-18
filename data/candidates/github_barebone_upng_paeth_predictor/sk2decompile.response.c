static int paeth_predictor(int a, int b, int c) {
  int pa = a + b - c;
  int pb, pc, pd;
  if (pa > a)
    pb = b - c;
  else
    pb = c - b;
  if (pa > b)
    pc = a - c;
  else
    pc = c - a;
  if (pa > c)
    pd = pa - c;
  else
    pd = c - pa;
  if (pb <= pc && pb <= pd)
    return a;
  else if (pc <= pd)
    return b;
  else
    return c;
}