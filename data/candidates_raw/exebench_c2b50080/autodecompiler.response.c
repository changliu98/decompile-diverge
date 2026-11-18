double Interpolate_4(double x, double *fx, float *yf) {
 double d[4][4];
 d[0][0] = fx[0] - fx[1];
 d[0][1] = fx[0] - fx[2];
 d[0][2] = fx[0] - fx[3];
 d[1][0] = fx[1] - fx[0];
 d[1][1] = fx[1] - fx[2];
 d[1][2] = fx[1] - fx[3];
 d[2][0] = fx[2] - fx[0];
 d[2][1] = fx[2] - fx[1];
 d[2][2] = fx[2] - fx[3];
 d[3][0] = fx[3] - fx[0];
 d[3][1] = fx[3] - fx[1];
 d[3][2] = fx[3] - fx[2];

 return yf[0] * (x - fx[1]) * (x - fx[2]) * (x - fx[3]) / (d[0][0] * d[0][1] * d[0][2])
   + yf[1] * (x - fx[0]) * (x - fx[2]) * (x - fx[3]) / (d[1][0] * d[1][1] * d[1][2])
   + yf[2] * (x - fx[0]) * (x - fx[1]) * (x - fx[3]) / (d[2][0] * d[2][1] * d[2][2])
   + yf[3] * (x - fx[0]) * (x - fx[1]) * (x - fx[2]) / (d[3][0] * d[3][1] * d[3][2]);
}