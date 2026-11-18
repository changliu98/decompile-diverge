void chartobit(int c, char *bit) {
  int i;
  for (i = 7; i > 0; i--) {
    bit[i] = (c % 2 == 1) ? '1' : '0';
    c /= 2;
  }
  bit[0] = (c % 2 == 1) ? '1' : '0';
}