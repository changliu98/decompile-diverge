void ZVdotU31(int n, double *ZR, double *ZI, double *UR, double *UI,
              double *V) {
  int i, j, k;
  double VR1, VI1, VR2, VI2, VR3, VI3, ZR1, ZI1, ZR2, ZI2, UR1, UI1;
  VR1 = VI1 = VR2 = VI2 = VR3 = VI3 = 0.0;
  i = 0;
  j = 0;
  k = 1;
  for (j = 0; j < n; j++) {
    ZR1 = ZR[i];
    ZI1 = ZR[k];
    ZR2 = ZI[i];
    ZI2 = ZI[k];
    UR1 = UR[i];
    UI1 = UR[k];
    VR2 = UI[i];
    VI2 = UI[k];
    VR1 = VR1 + ZR1 * VR2 - ZI1 * VI2;
    VI1 = VI1 + ZR1 * VI2 + ZI1 * VR2;
    VR3 = VR3 + ZR2 * VR2 - ZI2 * VI2;
    VI3 = VI3 + ZR2 * VI2 + ZI2 * VR2;
    VR1 = VR1 + UR1 * VR2 - UI1 * VI2;
    VI1 = VI1 + UR1 * VI2 + UI1 * VR2;
    i += 2;
    k += 2;
  }
  V[0] = VR1;
  V[1] = VI1;
  V[2] = VR3;
  V[3] = VI3;
  V[4] = VR1;
  V[5] = VI1;
  return;
}