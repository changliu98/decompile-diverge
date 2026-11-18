float spline_cubic_val(int n, float t[], float tval, float y[], float ypp[])
{
  float dt;
  float h;
  int i;
  int ival;
  float yval;




  ival = n - 2;

  for(i = 0; i < n - 1; i++)
  {
    if(tval < t[i + 1])
    {
      ival = i;
      break;
    }
  }




  dt = tval - t[ival];
  h = t[ival + 1] - t[ival];

  yval = y[ival]
         + dt * ((y[ival + 1] - y[ival]) / h - (ypp[ival + 1] / 6.0E+00 + ypp[ival] / 3.0E+00) * h
                 + dt * (0.5E+00 * ypp[ival] + dt * ((ypp[ival + 1] - ypp[ival]) / (6.0E+00 * h))));
# 666 "curve_tools.c"
  return yval;
}