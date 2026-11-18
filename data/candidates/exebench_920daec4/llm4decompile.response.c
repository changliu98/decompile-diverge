void hil_s_from_xy(int x, int y, int order, hil_s *s)
{
 int i;
 int state = 0;

 for (i = order - 1; i >= 0; i--) {
  int bit = ((x >> i) & 1) << 1 | (y >> i) & 1;
  *s = (*s << 2) | ((0x361e9cb4 >> (bit << 1)) & 3);
  state = (0x8fe65831 >> (bit << 1)) & 3;
 }
}