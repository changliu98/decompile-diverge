int _test_even(int x) {
  unsigned char c;

  if ((x % 2) == 0)
    c = 1;
  else
    c = 0;

  return (c & 1);
}