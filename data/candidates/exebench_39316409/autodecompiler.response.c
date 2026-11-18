void geom_matmat4d(double *left, double *right, double *product)
{
  register double rA = left[0];
  register double rB = left[4];
  register double rC = left[8];
  register double rD = left[12];

  product[0] = rA * right[0] + rB * right[1] + rC * right[2] + rD * right[3];
  product[1] = rA * right[4] + rB * right[5] + rC * right[6] + rD * right[7];
  product[2] = rA * right[8] + rB * right[9] + rC * right[10] + rD * right[11];
  product[3] = rA * right[12] + rB * right[13] + rC * right[14] + rD * right[15];

  rA = left[1];
  rB = left[5];
  rC = left[9];
  rD = left[13];

  product[4] = rA * right[0] + rB * right[1] + rC * right[2] + rD * right[3];
  product[5] = rA * right[4] + rB * right[5] + rC * right[6] + rD * right[7];
  product[6] = rA * right[8] + rB * right[9] + rC * right[10] + rD * right[11];
  product[7] = rA * right[12] + rB * right[13] + rC * right[14] + rD * right[15];

  rA = left[2];
  rB = left[6];
  rC = left[10];
  rD = left[14];

  product[8] = rA * right[0] + rB * right[1] + rC * right[2] + rD * right[3];
  product[9] = rA * right[4] + rB * right[5] + rC * right[6] + rD * right[7];
  product[10] = rA * right[8] + rB * right[9] + rC * right[10] + rD * right[11];
  product[11] = rA * right[12] + rB * right[13] + rC * right[14] + rD * right[15];

  rA = left[3];
  rB = left[7];
  rC = left[11];
  rD = left[15];

  product[12] = rA * right[0] + rB * right[1] + rC * right[2] + rD * right[3];
  product[13] = rA * right[4] + rB * right[5] + rC * right[6] + rD * right[7];
  product[14] = rA * right[8] + rB * right[9] + rC * right[10] + rD * right[11];
  product[15] = rA * right[12] + rB * right[13] + rC * right[14] + rD * right[15];
}