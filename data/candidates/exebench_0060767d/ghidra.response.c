void ltr_int_make_vec(double *pt1,double *pt2,double *res)

{
  double *res_local;
  double *pt2_local;
  double *pt1_local;
  
  *res = *pt1 - *pt2;
  res[1] = pt1[1] - pt2[1];
  res[2] = pt1[2] - pt2[2];
  return;
}