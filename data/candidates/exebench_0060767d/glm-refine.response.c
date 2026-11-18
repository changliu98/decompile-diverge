void __cdecl ltr_int_make_vec(double *pt1, double *pt2, double *res)
{
  res[0] = pt1[0] - pt2[0];
  res[1] = pt1[1] - pt2[1];
  res[2] = pt1[2] - pt2[2];
}