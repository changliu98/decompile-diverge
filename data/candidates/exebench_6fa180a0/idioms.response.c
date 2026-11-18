void sortVrtx(int *vrt)
{
  int i; int tmp; int ok;
  do
  {
    ok = 1;
    for (i = 1; i < 3; i++)
    {
      if (vrt[i-1] > vrt[i])
      {
        tmp = vrt[i];
        vrt[i] = vrt[i-1];
        vrt[i-1] = tmp;
        ok = 0;
      }
    }
  } while (ok == 0);
}