int modpars_to_struct(float *valptr, int *varptr, int *maxvar, float *mpptr,
        float *linkvals)
{
  if (*varptr == 1) {
    *valptr = *mpptr;
    return 1;
  }
  else if (*varptr > *maxvar) {
    *valptr = *mpptr;
    *maxvar = *varptr;
    *(linkvals+(*varptr)-2) = *mpptr;
    return 1;
  }
  else if (*varptr > 1) {
    *valptr = *(linkvals+(*varptr)-2);
    return 0;
  }
  else
    return 0;

  return 0;
}