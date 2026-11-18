void copy(double *from, float *to)
{
 int i;

 for (i = 0; i < 10; i++)
  to[i] = (float) from[i];
}