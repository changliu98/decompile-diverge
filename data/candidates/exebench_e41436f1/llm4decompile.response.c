void htond(double *x)
{
  int *tmp;
  tmp = (int *)x;
  int t1 = tmp[0];
  int t2 = tmp[1];
  tmp[0] = htonl(t2);
  tmp[1] = htonl(t1);
}