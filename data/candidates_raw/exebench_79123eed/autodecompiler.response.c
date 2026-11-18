void vert_grid_gen(int lev, float *vert_press, float pres_min, float pres_max, int nlev)
{
  float dp;

  dp = (pres_max - pres_min) / ((float)(nlev-1));

  *vert_press = pres_min + lev * dp;
}