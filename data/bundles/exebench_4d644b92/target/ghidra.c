int twiddle1(int *xp,int *yp)

{
  int *yp_local;
  int *xp_local;
  
  *xp = *yp + *xp;
  *xp = *yp + *xp;
  return *xp;
}