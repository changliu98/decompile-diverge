void rbc_force_stat(float r, float *pArea, float *pVolume)
{
  *pArea = 4.0 * 3.14 * r * r;
  *pVolume = 4.0 * 3.14 * r * r * r / 3.0;
}