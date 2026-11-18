int modpars_to_struct(float *val, int *var, int *maxvar, float *mp, float *linkvals)
{
  if (*var == 1)
  {
    *val = *mp;
    return 1;
  }
  if (*var > *maxvar)
  {
    *val = *mp;
    *maxvar = *var;
    linkvals[*var - 2] = *mp;
    return 1;
  }
  if (*var > 1)
  {
    *val = linkvals[*var - 2];
  }
  return 0;
}