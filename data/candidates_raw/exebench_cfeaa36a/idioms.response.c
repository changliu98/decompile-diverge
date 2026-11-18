void scc_to_xy(int *x, int *y)
{
  unsigned char sccx = *x;
  unsigned char sccy = *y;
  int xoffset = (sccx < 160) ? 112 : 176;
  int yoffset = (sccy < 159) ? (sccy < 128) ? 32 : 31 : 126;
  *x = sccx - xoffset;
  *x = *x << 1;
  *x = *x - 159;
  *y = sccy - yoffset;
}