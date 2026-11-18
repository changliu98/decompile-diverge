void ne_pre_filter16_double(double *_y,double *_x,int *_f)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  double t [16];
  int *_f_local;
  double *_x_local;
  double *_y_local;
  
  dVar16 = _x[7];
  dVar17 = (_x[7] - _x[8]) / DAT_00102010;
  dVar15 = _x[6];
  dVar18 = (_x[6] - _x[9]) / DAT_00102010;
  dVar14 = _x[5];
  dVar19 = (_x[5] - _x[10]) / DAT_00102010;
  dVar13 = _x[4];
  dVar20 = (_x[4] - _x[0xb]) / DAT_00102010;
  dVar12 = _x[3];
  dVar21 = (_x[3] - _x[0xc]) / DAT_00102010;
  dVar11 = _x[2];
  dVar22 = (_x[2] - _x[0xd]) / DAT_00102010;
  dVar10 = _x[1];
  dVar23 = (_x[1] - _x[0xe]) / DAT_00102010;
  dVar1 = ((_x[7] - _x[8]) * (double)*_f) / DAT_00102018;
  dVar2 = ((_x[6] - _x[9]) * (double)_f[1]) / DAT_00102018;
  dVar3 = ((_x[5] - _x[10]) * (double)_f[2]) / DAT_00102018;
  dVar4 = ((_x[4] - _x[0xb]) * (double)_f[3]) / DAT_00102018;
  dVar5 = ((_x[3] - _x[0xc]) * (double)_f[4]) / DAT_00102018;
  dVar6 = ((_x[2] - _x[0xd]) * (double)_f[5]) / DAT_00102018;
  dVar7 = ((_x[1] - _x[0xe]) * (double)_f[6]) / DAT_00102018;
  dVar8 = (dVar7 * (double)_f[0xe]) / DAT_00102018 +
          ((*_x - _x[0xf]) * (double)_f[7]) / DAT_00102018;
  dVar7 = (dVar6 * (double)_f[0xd]) / DAT_00102018 +
          (dVar8 * (double)_f[0x15]) / DAT_00102018 + dVar7;
  dVar6 = (dVar5 * (double)_f[0xc]) / DAT_00102018 +
          (dVar7 * (double)_f[0x14]) / DAT_00102018 + dVar6;
  dVar5 = (dVar4 * (double)_f[0xb]) / DAT_00102018 +
          (dVar6 * (double)_f[0x13]) / DAT_00102018 + dVar5;
  dVar4 = (dVar3 * (double)_f[10]) / DAT_00102018 +
          (dVar5 * (double)_f[0x12]) / DAT_00102018 + dVar4;
  dVar3 = (dVar2 * (double)_f[9]) / DAT_00102018 + (dVar4 * (double)_f[0x11]) / DAT_00102018 + dVar3
  ;
  dVar2 = (dVar1 * (double)_f[8]) / DAT_00102018 + (dVar3 * (double)_f[0x10]) / DAT_00102018 + dVar2
  ;
  dVar1 = (dVar2 * (double)_f[0xf]) / DAT_00102018 + dVar1;
  dVar9 = dVar8 / DAT_00102010 + (*_x - (*_x - _x[0xf]) / DAT_00102010);
  *_y = dVar9;
  dVar10 = dVar7 / DAT_00102010 + (dVar10 - dVar23);
  _y[1] = dVar10;
  dVar11 = dVar6 / DAT_00102010 + (dVar11 - dVar22);
  _y[2] = dVar11;
  dVar12 = dVar5 / DAT_00102010 + (dVar12 - dVar21);
  _y[3] = dVar12;
  dVar13 = dVar4 / DAT_00102010 + (dVar13 - dVar20);
  _y[4] = dVar13;
  dVar14 = dVar3 / DAT_00102010 + (dVar14 - dVar19);
  _y[5] = dVar14;
  dVar15 = dVar2 / DAT_00102010 + (dVar15 - dVar18);
  _y[6] = dVar15;
  dVar16 = dVar1 / DAT_00102010 + (dVar16 - dVar17);
  _y[7] = dVar16;
  _y[8] = dVar16 - dVar1;
  _y[9] = dVar15 - dVar2;
  _y[10] = dVar14 - dVar3;
  _y[0xb] = dVar13 - dVar4;
  _y[0xc] = dVar12 - dVar5;
  _y[0xd] = dVar11 - dVar6;
  _y[0xe] = dVar10 - dVar7;
  _y[0xf] = dVar9 - dVar8;
  return;
}