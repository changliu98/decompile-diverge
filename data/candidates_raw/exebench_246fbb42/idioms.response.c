int get_color(int r, int g, int b, int white, int *err)
{
  int avg = (r + g + b) / 3;
  int min;
  if (err != ((void *)0)) {
    int rdiff; int gdiff; int bdiff;
    if (r - avg > 0)
      rdiff = r - avg;
    else
      rdiff = avg - r;
    if (g - avg > 0)
      gdiff = g - avg;
    else
      gdiff = avg - g;
    if (rdiff > gdiff) {
      if (r - avg > 0)
        bdiff = r - avg;
      else
        bdiff = avg - r;
    }
    else {
      if (g - avg > 0)
        bdiff = g - avg;
      else
        bdiff = avg - g;
    }
    if (b - avg > 0)
      min = b - avg;
    else
      min = avg - b;
    if (min > bdiff)
      min = bdiff;
    *err = min;
  }
  if (r < white && g < white && b < white)
    return (r + g + b) / 3;
  if (avg > white)
    return (r + g + b) / 3;
  return white;
}