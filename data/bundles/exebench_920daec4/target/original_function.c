void
hil_s_from_xy(unsigned int x, unsigned int y, int order, unsigned int *s)
{
  int i = 0;
  unsigned int state = 0;
  unsigned int row;
  for (i = order - 1; i >= 0; i--) {
    row = (4*state) | (2*((x >> i)&1)) | ((y >> i)&1);
    *s = (*s<<2) | ((0x361E9CB4 >> (2*row)) & 3);
    state = (0x8FE65831 >> (2*row)) & 3;
  }
}