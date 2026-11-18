static float KBND_REPLICATE(float *img, int w, int h, int x, int y, float bnd_const)
{
  int i = x; int j = y;
  if (i < 0) i = 0;
  if (i >= w) i = w - 1;
  if (j < 0) j = 0;
  if (j >= h) j = h - 1;
  return img[i + w * j];
}