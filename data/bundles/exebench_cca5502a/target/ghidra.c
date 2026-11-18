int modpars_to_struct(float *valptr,int *varptr,int *maxvar,float *mpptr,float *linkvals)

{
  float *linkvals_local;
  float *mpptr_local;
  int *maxvar_local;
  int *varptr_local;
  float *valptr_local;
  int local_c;
  
  if (*varptr == 1) {
    *valptr = *mpptr;
    local_c = 1;
  }
  else if (*maxvar < *varptr) {
    *valptr = *mpptr;
    *maxvar = *varptr;
    linkvals[(long)*varptr + -2] = *mpptr;
    local_c = 1;
  }
  else if (*varptr < 2) {
    local_c = 0;
  }
  else {
    *valptr = linkvals[(long)*varptr + -2];
    local_c = 0;
  }
  return local_c;
}