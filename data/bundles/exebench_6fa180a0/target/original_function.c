void sortVrtx(int vrt[])
{
  int i, tmp, o;
  do
  {
    o = 1;
    for (i = 1; i < 3; i++)
    {
      if(vrt[i-1] > vrt[i])
      {
        tmp = vrt[i];
        vrt[i] = vrt[i-1];
        vrt[i-1] = tmp;
        o = 0;
      }
    }
  } while(!o);
}