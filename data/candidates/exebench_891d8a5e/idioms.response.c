void decdms(double dec, int *d, int *m, float *s)
{
  double temp;
  *d = (int) dec;
  temp = (dec - (double)(int) dec);
  if (temp < 0.0)
    temp = -temp;
  temp = (temp * 60.0);
  *m = (int) temp;
  temp = (temp - (double)(int) temp);
  temp = (temp * 60.0);
  *s = (float) temp;
}