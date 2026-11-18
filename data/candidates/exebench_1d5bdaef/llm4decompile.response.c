int foo(float *dists, int k)
{
  int i;
  int result = k;

  for (i = 0; i < 2; i++)
    {
      if (dists[i] > 0.0f)
 {
   result = 0;
 }
    }

  return result;
}