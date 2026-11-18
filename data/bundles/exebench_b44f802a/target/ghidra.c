void YvVfilterCoef(double sigma,double *filter)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double m2sq;
  double m1sq;
  double m2;
  double m1;
  double m0;
  double b3;
  double b2;
  double b1;
  double B;
  double scale;
  double qsq;
  double q;
  double *filter_local;
  double sigma_local;
  
  dVar1 = DAT_00102018 * DAT_00102018;
  dVar2 = DAT_00102010 * DAT_00102010;
  if (DAT_00102008 <= sigma) {
    q = (sigma - DAT_00102008) * DAT_00102028 + DAT_00102030;
  }
  else {
    q = DAT_00102038 * sigma * sigma + sigma * DAT_00102040 + DAT_00102048;
  }
  dVar3 = q * q;
  dVar4 = (DAT_00102020 + q) * (DAT_00102060 * DAT_00102018 * q + dVar1 + dVar2 + dVar3);
  dVar5 = (-q * (dVar3 * DAT_00102050 +
                (DAT_00102020 + DAT_00102020 + DAT_00102058 * DAT_00102018) * q +
                DAT_00102060 * DAT_00102020 * DAT_00102018 + dVar1 + dVar2)) / dVar4;
  dVar6 = (dVar3 * (q * DAT_00102050 + DAT_00102018 + DAT_00102018 + DAT_00102020)) / dVar4;
  dVar3 = (-dVar3 * q) / dVar4;
  dVar1 = DAT_00102020 * (dVar1 + dVar2);
  *filter = -dVar3;
  filter[1] = -dVar6;
  filter[2] = -dVar5;
  filter[3] = dVar1 / dVar4;
  filter[4] = -dVar5;
  filter[5] = -dVar6;
  filter[6] = -dVar3;
  return;
}