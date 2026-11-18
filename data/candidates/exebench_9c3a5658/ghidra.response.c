void cmatrix_from_frame(double *m,double *v1,double *v2,double *v3)

{
  int i;
  double *v3_local;
  double *v2_local;
  double *v1_local;
  double *m_local;
  
  for (i = 0; i < 3; i = i + 1) {
    m[i * 3] = v1[i];
    m[i * 3 + 1] = v2[i];
    m[i * 3 + 2] = v3[i];
  }
  return;
}