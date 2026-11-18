double lagrange4(double *temp,float *q,double t)

{
  double A3D3;
  double A3D2;
  double A3D1;
  double A2D3;
  double A2D2;
  double A2D1;
  double A1D3;
  double A1D2;
  double A1D1;
  double A0D3;
  double A0D2;
  double A0D1;
  double t_local;
  float *q_local;
  double *temp_local;
  
  return ((double)*q * (t - temp[1]) * (t - temp[2]) * (t - temp[3])) /
         ((*temp - temp[1]) * (*temp - temp[2]) * (*temp - temp[3])) +
         ((double)q[1] * (t - *temp) * (t - temp[2]) * (t - temp[3])) /
         ((temp[1] - *temp) * (temp[1] - temp[2]) * (temp[1] - temp[3])) +
         ((double)q[2] * (t - *temp) * (t - temp[1]) * (t - temp[3])) /
         ((temp[2] - *temp) * (temp[2] - temp[1]) * (temp[2] - temp[3])) +
         ((double)q[3] * (t - *temp) * (t - temp[1]) * (t - temp[2])) /
         ((temp[3] - *temp) * (temp[3] - temp[1]) * (temp[3] - temp[2]));
}