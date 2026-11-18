void _swap_short(unsigned short *a, unsigned short *b) {
  unsigned short tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}