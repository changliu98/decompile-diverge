double determinant_3x3(float *inp)

{
  double m [3] [3];
  double det;
  int j;
  int i;
  float *inp_local;
  
  memset(m,0,0x48);
  for (i = 0; i < 3; i = i + 1) {
    for (j = 0; j < 3; j = j + 1) {
      m[i][j] = (double)inp[i + j * 3];
    }
  }
  return m[0][2] * (m[1][0] * m[2][1] + -(m[1][1] * m[2][0])) +
         -m[0][1] * (m[1][0] * m[2][2] + -(m[1][2] * m[2][0])) +
         m[0][0] * (m[1][1] * m[2][2] + -(m[1][2] * m[2][1]));
}