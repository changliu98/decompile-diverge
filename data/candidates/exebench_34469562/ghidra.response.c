void swap(int *xp,int *yp)

{
  int *yp_local;
  int *xp_local;
  
  *xp = *xp + *yp;
  *yp = *xp - *yp;
  *xp = *xp - *yp;
  return;
}