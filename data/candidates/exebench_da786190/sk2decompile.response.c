void SetBitInt(int *p, int bit) {
  int mask = 1;
  mask = mask << bit;
  *p = *p | mask;
}