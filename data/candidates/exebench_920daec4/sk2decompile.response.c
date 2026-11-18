void hil_s_from_xy(int x, int y, int n, int *s) {
  int last = 0;
  int i;
  for (i = n - 1; i >= 0; i--) {
    int xi = (x >> i) & 1;
    int yi = (y >> i) & 1;
    int index = (last << 2) | xi | yi;
    int s0 = (0x12345678 >> (index << 1)) & 3;
    int s1 = (0x9abcdef0 >> (index << 1)) & 3;
    *s = (*s << 2) | s0;
    last = s1;
  }
}