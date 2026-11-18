void heaviside(double *first,double *last,double *res)

{
  bool bVar1;
  int i;
  int dim;
  double *res_local;
  double *last_local;
  double *first_local;
  
  *res = DAT_00102008;
  for (i = 0; i < (int)((long)last - (long)first >> 3) + 1; i = i + 1) {
    bVar1 = false;
    if ((*res == DAT_00102008) && (!NAN(*res) && !NAN(DAT_00102008))) {
      bVar1 = 0.0 <= first[i];
    }
    *res = (double)bVar1;
  }
  return;
}