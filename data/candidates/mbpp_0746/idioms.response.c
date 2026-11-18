double func0(int r, int a)
{
  if (a < 360)
    return r * r * (double) a / 360 * 3.1428571428571428571428571428571;
  else
    return -1;
}