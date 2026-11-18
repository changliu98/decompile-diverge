void ne_pre_filter8_double(double *_y,double *_x,int *_f)

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
  double *_x_local;
  double *_y_local;
  
  dVar8 = _x[3];
  dVar9 = (_x[3] - _x[4]) / DAT_00102010;
  dVar7 = _x[2];
  dVar10 = (_x[2] - _x[5]) / DAT_00102010;
  dVar6 = _x[1];
  dVar11 = (_x[1] - _x[6]) / DAT_00102010;
  dVar1 = ((_x[3] - _x[4]) * (double)*_f) / DAT_00102018;
  dVar2 = ((_x[2] - _x[5]) * (double)_f[1]) / DAT_00102018;
  dVar3 = ((_x[1] - _x[6]) * (double)_f[2]) / DAT_00102018;
  dVar4 = (dVar3 * (double)_f[6]) / DAT_00102018 + ((*_x - _x[7]) * (double)_f[3]) / DAT_00102018;
  dVar3 = (dVar2 * (double)_f[5]) / DAT_00102018 + (dVar4 * (double)_f[9]) / DAT_00102018 + dVar3;
  dVar2 = (dVar1 * (double)_f[4]) / DAT_00102018 + (dVar3 * (double)_f[8]) / DAT_00102018 + dVar2;
  dVar1 = (dVar2 * (double)_f[7]) / DAT_00102018 + dVar1;
  dVar5 = dVar4 / DAT_00102010 + (*_x - (*_x - _x[7]) / DAT_00102010);
  *_y = dVar5;
  dVar6 = dVar3 / DAT_00102010 + (dVar6 - dVar11);
  _y[1] = dVar6;
  dVar7 = dVar2 / DAT_00102010 + (dVar7 - dVar10);
  _y[2] = dVar7;
  dVar8 = dVar1 / DAT_00102010 + (dVar8 - dVar9);
  _y[3] = dVar8;
  _y[4] = dVar8 - dVar1;
  _y[5] = dVar7 - dVar2;
  _y[6] = dVar6 - dVar3;
  _y[7] = dVar5 - dVar4;
  return;
}