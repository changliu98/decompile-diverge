int SeekPoint(unsigned char *table, int size, float percent) {
  int i;
  float y2, y1, y;
  if (percent < 0.0) percent = 0.0;
  if (percent > 100.0) percent = 100.0;
  i = (int)percent;
  if (i >= 100) i = 99;
  if (i < 99)
    y2 = (float)table[i + 1];
  else
    y2 = 256.0;
  y1 = (float)table[i];
  y = y1 + (percent - (float)i) * (y2 - y1);
  return (int)(y * 0.00390625 * (float)size);
}