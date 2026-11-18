void __cdecl ltr_int_add_vecs(double *vec1, double *vec2, double *res)
{
  *res = *vec1 + *vec2;
  res[1] = vec1[1] + vec2[1];
  res[2] = vec1[2] + vec2[2];
}