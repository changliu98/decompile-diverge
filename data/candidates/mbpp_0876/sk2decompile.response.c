int func0(int a, int b) {
  int c;
  if (a > b)
    c = a;
  else
    c = b;
  while (c % a != 0 || c % b != 0) c++;
  return c;
}