void poly_mul1(double a[], double b[], int Na, int Nb, double ans[], int Nans)
{
  Nans = Na + Nb;
  int i,j,k;

  for(k=0; k < 18; k++)
  {
    ans[k] = 0;
  }

  for(i=0;i <= Na;i++)
  {
    for(j=0;j <= Nb;j++)
    {
      k = i+j;
      ans[k] = ans[k] + a[i]*b[j];
    }
  }
}