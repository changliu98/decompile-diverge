void ltr_int_add_vecs(double *vec1,double *vec2,double *res)

{
  double *res_local;
  double *vec2_local;
  double *vec1_local;
  
  *res = *vec1 + *vec2;
  res[1] = vec1[1] + vec2[1];
  res[2] = vec1[2] + vec2[2];
  return;
}