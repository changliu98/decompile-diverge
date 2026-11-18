void getTransf(double* in, double* N, double* D) {







  D[0] = in[2];
  D[1] = in[3];
  D[2] = 0.;
  D[3] = 0.;
  D[4] = in[4];
  D[5] = 0.;
  D[6] = in[0];
  D[7] = in[1];
  D[8] = 1.;

  N[0] = 1./in[7];
  N[1] = -in[8]/in[7]/in[9];
  N[2] = 0.;
  N[3] = 0.;
  N[4] = 1./in[9];
  N[5] = 0.;
  N[6] = -in[5]/in[7];
  N[7] = (in[5]*in[8]-in[6]*in[7])/in[7]/in[9];
  N[8] = 1.;

}