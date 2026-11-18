static _Bool next_height(unsigned int height, unsigned int *y, unsigned char *step)
{
  int s = *step;
  *y += s & 0xf;
  if (*y < height)
    return 1;
  switch (s) {
  case 4:
    *y = 2;
    *step = 4;
    if (*y < height)
      return 1;
  case 2:
    *y = 1;
    *step = 2;
    if (*y < height)
      return 1;
  case 1:
    *y = 1;
    *step = 1;
    if (*y < height)
      return 1;
  }
  return 0;
}