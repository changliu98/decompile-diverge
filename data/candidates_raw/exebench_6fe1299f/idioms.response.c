void find_index(float *p_val, int *p_ind, float qmin, float qmax, int nlev)
{
  int i;
  float qbnd; float step;
  step = (qmax - qmin) / (nlev - 1);
  qbnd = qmin + (step * 0.5);
  for (i = 0; i < nlev - 1 && *p_val > qbnd; i++)
    qbnd += step;
  *p_val = qmin + (i * step);
  *p_ind = i;
}