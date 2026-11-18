float KBND_REPLICATE(float *image, int width, int height, int x, int y,
                     float nan) {
  int i = x;
  int j = y;
  if (i < 0) i = 0;
  if (i >= width) i = width - 1;
  if (j < 0) j = 0;
  if (j >= height) j = height - 1;
  return image[i + j * width];
}