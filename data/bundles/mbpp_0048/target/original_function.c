int func0(int n) {
  int count = 0;
  int res = 0;
  int temp = n;
  while (temp > 0) {
    if (count % 2 == 0) {
      res |= (1 << count);
    }
    count += 1;
    temp >>= 1;
  }
  return (n | res);
}