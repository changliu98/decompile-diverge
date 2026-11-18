void ne_post_filter8_double(double *_x,double *_y,int *_f)

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
  double t [8];
  int *_f_local;
  double *_y_local;
  double *_x_local;
  
  dVar1 = *_y - _y[7];
  dVar2 = _y[1] - _y[6];
  dVar3 = _y[2] - _y[5];
  dVar8 = _y[3];
  dVar9 = (_y[3] - _y[4]) / DAT_00102010;
  dVar7 = _y[2];
  dVar10 = dVar3 / DAT_00102010;
  dVar6 = _y[1];
  dVar11 = dVar2 / DAT_00102010;
  dVar4 = (_y[3] - _y[4]) - (dVar3 * (double)_f[7]) / DAT_00102018;
  dVar3 = (dVar3 - (dVar4 * (double)_f[4]) / DAT_00102018) - (dVar2 * (double)_f[8]) / DAT_00102018;
  dVar2 = (dVar2 - (dVar3 * (double)_f[5]) / DAT_00102018) - (dVar1 * (double)_f[9]) / DAT_00102018;
  dVar5 = (DAT_00102018 * (dVar1 - (dVar2 * (double)_f[6]) / DAT_00102018)) / (double)_f[3];
  dVar2 = (DAT_00102018 * dVar2) / (double)_f[2];
  dVar3 = (DAT_00102018 * dVar3) / (double)_f[1];
  dVar4 = (DAT_00102018 * dVar4) / (double)*_f;
  dVar1 = dVar5 / DAT_00102010 + (*_y - dVar1 / DAT_00102010);
  *_x = dVar1;
  dVar6 = dVar2 / DAT_00102010 + (dVar6 - dVar11);
  _x[1] = dVar6;
  dVar7 = dVar3 / DAT_00102010 + (dVar7 - dVar10);
  _x[2] = dVar7;
  dVar8 = dVar4 / DAT_00102010 + (dVar8 - dVar9);
  _x[3] = dVar8;
  _x[4] = dVar8 - dVar4;
  _x[5] = dVar7 - dVar3;
  _x[6] = dVar6 - dVar2;
  _x[7] = dVar1 - dVar5;
  return;
}