int func0(unsigned int n) {
  int count = 0;
  while (n) {
    n &= n - 1;
    count++;
  }
  return count % 2 == 1;
}