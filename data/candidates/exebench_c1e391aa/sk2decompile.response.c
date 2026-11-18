int set_bit(int *num, int bit) {
  int mask = 1;
  mask <<= bit;
  *num |= mask;
  return *num;
}