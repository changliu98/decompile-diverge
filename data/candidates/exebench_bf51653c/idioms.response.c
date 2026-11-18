void upzero(int dlt, int *dlti, int *bli)
{
  int i; int wd2;
  if (dlt != 0)
  {
    for (i = 0; i < 6; i++)
    {
      if (dlti[i]*dlt < 0)
        wd2 = -128;
      else
        wd2 = 128;
      bli[i] = (int)(255 * (long)bli[i]/256 + wd2);
    }
  }
  else
  {
    for (i = 0; i < 6; i++)
      bli[i] = (int)(255 * (long)bli[i]/256);
  }
  dlti[5] = dlti[4];
  dlti[4] = dlti[3];
  dlti[3] = dlti[2];
  dlti[1] = dlti[0];
  dlti[0] = dlt;
}