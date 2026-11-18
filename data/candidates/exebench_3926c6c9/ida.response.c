void __cdecl ne_pre_filter8_double(double *_y, const double *_x, const int *_f)
{
  double t; // [rsp+0h] [rbp-60h]
  double ta; // [rsp+0h] [rbp-60h]
  double t_8; // [rsp+8h] [rbp-58h]
  double t_8a; // [rsp+8h] [rbp-58h]
  double t_16; // [rsp+10h] [rbp-50h]
  double t_16a; // [rsp+10h] [rbp-50h]
  double t_24; // [rsp+18h] [rbp-48h]
  double t_24a; // [rsp+18h] [rbp-48h]
  double t_32; // [rsp+20h] [rbp-40h]
  double t_32a; // [rsp+20h] [rbp-40h]
  double t_32b; // [rsp+20h] [rbp-40h]
  double t_40; // [rsp+28h] [rbp-38h]
  double t_40a; // [rsp+28h] [rbp-38h]
  double t_40b; // [rsp+28h] [rbp-38h]
  double t_48; // [rsp+30h] [rbp-30h]
  double t_48a; // [rsp+30h] [rbp-30h]
  double t_48b; // [rsp+30h] [rbp-30h]
  double t_56; // [rsp+38h] [rbp-28h]
  double t_56a; // [rsp+38h] [rbp-28h]

  t_56 = *_x - _x[7];
  t_48 = _x[1] - _x[6];
  t_40 = _x[2] - _x[5];
  t_32 = _x[3] - _x[4];
  t_24 = _x[3] - t_32 / 2.0;
  t_16 = _x[2] - t_40 / 2.0;
  t_8 = _x[1] - t_48 / 2.0;
  t = *_x - t_56 / 2.0;
  t_32a = t_32 * (double)*_f / 16.0;
  t_40a = t_40 * (double)_f[1] / 16.0;
  t_48a = t_48 * (double)_f[2] / 16.0;
  t_56a = t_48a * (double)_f[6] / 16.0 + t_56 * (double)_f[3] / 16.0;
  t_48b = t_40a * (double)_f[5] / 16.0 + t_56a * (double)_f[9] / 16.0 + t_48a;
  t_40b = t_32a * (double)_f[4] / 16.0 + t_48b * (double)_f[8] / 16.0 + t_40a;
  t_32b = t_40b * (double)_f[7] / 16.0 + t_32a;
  ta = t_56a / 2.0 + t;
  *_y = ta;
  t_8a = t_48b / 2.0 + t_8;
  _y[1] = t_8a;
  t_16a = t_40b / 2.0 + t_16;
  _y[2] = t_16a;
  t_24a = t_32b / 2.0 + t_24;
  _y[3] = t_24a;
  _y[4] = t_24a - t_32b;
  _y[5] = t_16a - t_40b;
  _y[6] = t_8a - t_48b;
  _y[7] = ta - t_56a;
}