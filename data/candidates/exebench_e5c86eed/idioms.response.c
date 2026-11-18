int SeekPoint(unsigned char *toc, int file_bytes, float percent)
{
  int i;
  float f;
  float f1;
  float f2;
  if (percent < 0.0f)
    percent = 0.0f;
  if (percent > 100.0f)
    percent = 100.0f;
  i = (int)percent;
  if (i > 99)
    i = 99;
  if (i < 100)
    f1 = (float)toc[i+1];
  else
    f1 = 256.0f;
  f2 = (float)toc[i];
  f = f2 + (f1 - f2) * (percent - i);
  return (int)(file_bytes * f * (1.0f / 256.0f) * (1.0f / 256.0f));
}