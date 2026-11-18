void Sqrt(float x, float *res)
{
  float y;
  int i = (int) (0.5 * x * (1597463007 - (int)(0.5 * x)));
  y = (float)(i * (i * i + 1.5));
  if (y > 0.0)
    *res = 1.0 / y;
  else
    *res = 0.0;
}