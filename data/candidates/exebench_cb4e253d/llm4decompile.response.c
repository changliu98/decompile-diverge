int sort_omegas(double *omegas)
{
  int i,j,k;
  double temp;
  int order = 0;
  double small[2],big[2];

  if (omegas[0] > omegas[1])
    {
      big[0] = omegas[0];
      small[0] = omegas[1];
      order = 1;
    }
  else
    {
      big[0] = omegas[1];
      small[0] = omegas[0];
      order = 0;
    }

  if (omegas[2] > omegas[3])
    {
      big[1] = omegas[2];
      small[1] = omegas[3];
      order += 2;
    }
  else
    {
      big[1] = omegas[3];
      small[1] = omegas[2];
    }

  if (big[0] > big[1])
    {
      temp = big[0];
      big[0] = big[1];
      big[1] = temp;
      if (order == 1)
 order = 4;
      else if (order == 0)
 order = 5;
    }
  else
    {
      if (order == 0)
 order = 1;
      else if (order == 1)
 order = 5;
    }

  omegas[0] = big[0];
  omegas[1] = small[0];
  omegas[2] = big[1];
  omegas[3] = small[1];

  if (omegas[1] > omegas[2])
    {
      temp = omegas[1];
      omegas[1] = omegas[2];
      omegas[2] = temp;
      if (order == 4)
 order = 2;
      else if (order == 5)
 order = 1;
    }
  else
    {
      if (order == 4)
 order = 1;
      else if (order == 5)
 order = 2;
    }

  return order;
}