void SetBit(int *a, int k) {
  int index = k / 32;
  int offset = k % 32;
  a[index] |= (1 << offset);
}