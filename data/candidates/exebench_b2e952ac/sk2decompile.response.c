void ZVdotU32(int n, double *Z1R, double *Z1I, double *Z2R, double *Z2I,
              double *U1R, double *U1I) {
  double Z1R1, Z1I1, Z1R2, Z1I2, Z1R3, Z1I3, Z1R4, Z1I4, Z1R5, Z1I5, Z1R6, Z1I6,
      Z2R1, Z2R2, Z2I1, Z2I2, Z2R3, Z2I3, Z2R4, Z2I4, Z2R5, Z2I5, Z2R6, Z2I6,
      Z1R11, Z1I11, Z1R22, Z1I22;
  int i, j, k;
  Z1R1 = 0.0;
  Z1I1 = 0.0;
  Z1R2 = 0.0;
  Z1I2 = 0.0;
  Z1R3 = 0.0;
  Z1I3 = 0.0;
  Z1R4 = 0.0;
  Z1I4 = 0.0;
  Z1R5 = 0.0;
  Z1I5 = 0.0;
  Z1R6 = 0.0;
  Z1I6 = 0.0;
  i = 0;
  j = 0;
  k = 1;
  for (j = 0; j < n; j++) {
    Z2R1 = Z1R[i];
    Z2R2 = Z1R[k];
    Z2I1 = Z1I[i];
    Z2I2 = Z1I[k];
    Z2R3 = Z2R[i];
    Z2R4 = Z2R[k];
    Z2I3 = Z2I[i];
    Z2I4 = Z2I[k];
    Z2R5 = U1R[i];
    Z2I5 = U1R[k];
    Z1R1 = Z1R1 + (Z2R1 * Z2I3 - Z2R2 * Z2I4);
    Z1I1 = Z1I1 + (Z2R1 * Z2I4 + Z2R2 * Z2I3);
    Z1R2 = Z1R2 + (Z2I1 * Z2I3 - Z2I2 * Z2I4);
    Z1I2 = Z1I2 + (Z2I1 * Z2I4 + Z2I2 * Z2I3);
    Z1R3 = Z1R3 + (Z2I1 * Z2R5 - Z2I2 * Z2I5);
    Z1I3 = Z1I3 + (Z2I1 * Z2I5 + Z2I2 * Z2R5);
    Z1R4 = Z1R4 + (Z2R3 * Z2I3 - Z2R4 * Z2I4);
    Z1I4 = Z1I4 + (Z2R3 * Z2I4 + Z2R4 * Z2I3);
    Z1R5 = Z1R5 + (Z2R3 * Z2R5 - Z2R4 * Z2I5);
    Z1I5 = Z1I5 + (Z2R3 * Z2I5 + Z2R4 * Z2R5);
    i += 2;
    k += 2;
  }
  Z1R11 = Z1R1;
  Z1I11 = Z1I1;
  Z1R22 = Z1R2;
  Z1I22 = Z1I2;
  U1I[0] = Z1R11;
  U1I[1] = Z1I11;
  U1I[2] = Z1R22;
  U1I[3] = Z1I22;
  Z1R11 = Z1R3;
  Z1I11 = Z1I3;
  Z1R22 = Z1R4;
  Z1I22 = Z1I4;
  U1I[4] = Z1R11;
  U1I[5] = Z1I11;
  U1I[6] = Z1R22;
  U1I[7] = Z1I22;
  Z1R11 = Z1R5;
  Z1I11 = Z1I5;
  U1I[8] = Z1R11;
  U1I[9] = Z1I11;
}