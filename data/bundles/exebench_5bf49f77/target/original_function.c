float catmull_rom_val(int n, float x[], float xval, float y[], float tangents[])
{




  int ival = n - 2;

  for(int i = 0; i < n - 2; i++)
  {
    if(xval < x[i + 1])
    {
      ival = i;
      break;
    }
  }

  const float m0 = tangents[ival];
  const float m1 = tangents[ival + 1];




  const float h = x[ival + 1] - x[ival];
  const float dx = (xval - x[ival]) / h;
  const float dx2 = dx * dx;
  const float dx3 = dx * dx2;

  const float h00 = (2.0 * dx3) - (3.0 * dx2) + 1.0;
  const float h10 = (1.0 * dx3) - (2.0 * dx2) + dx;
  const float h01 = (-2.0 * dx3) + (3.0 * dx2);
  const float h11 = (1.0 * dx3) - (1.0 * dx2);

  return (h00 * y[ival]) + (h10 * h * m0) + (h01 * y[ival + 1]) + (h11 * h * m1);
}