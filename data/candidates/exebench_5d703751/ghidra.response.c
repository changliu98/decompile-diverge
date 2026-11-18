void iw_restrict_to_range(int r1,int r2,int *pvar)

{
  int *pvar_local;
  int r2_local;
  int r1_local;
  
  if (*pvar < r1) {
    *pvar = r1;
  }
  else if (r2 < *pvar) {
    *pvar = r2;
  }
  return;
}