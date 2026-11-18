void transpose(float *mat)
{
  int temp = mat[1];
  mat[1] = mat[4];
  mat[4] = temp;
  temp = mat[2];
  mat[2] = mat[8];
  mat[8] = temp;
  temp = mat[3];
  mat[3] = mat[12];
  mat[12] = temp;
  temp = mat[6];
  mat[6] = mat[9];
  mat[9] = temp;
  temp = mat[7];
  mat[7] = mat[13];
  mat[13] = temp;
  temp = mat[11];
  mat[11] = mat[14];
  mat[14] = temp;
}