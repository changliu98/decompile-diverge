void __cdecl ne_pre_filter16_double(double *_y, const double *_x, const int *_f)
{
  double t; // [rsp+0h] [rbp-A0h]
  double ta; // [rsp+0h] [rbp-A0h]
  double t_8; // [rsp+8h] [rbp-98h]
  double t_8a; // [rsp+8h] [rbp-98h]
  double t_16; // [rsp+10h] [rbp-90h]
  double t_16a; // [rsp+10h] [rbp-90h]
  double t_24; // [rsp+18h] [rbp-88h]
  double t_24a; // [rsp+18h] [rbp-88h]
  double t_32; // [rsp+20h] [rbp-80h]
  double t_32a; // [rsp+20h] [rbp-80h]
  double t_40; // [rsp+28h] [rbp-78h]
  double t_40a; // [rsp+28h] [rbp-78h]
  double t_48; // [rsp+30h] [rbp-70h]
  double t_48a; // [rsp+30h] [rbp-70h]
  double t_56; // [rsp+38h] [rbp-68h]
  double t_56a; // [rsp+38h] [rbp-68h]
  double t_64; // [rsp+40h] [rbp-60h]
  double t_64a; // [rsp+40h] [rbp-60h]
  double t_64b; // [rsp+40h] [rbp-60h]
  double t_72; // [rsp+48h] [rbp-58h]
  double t_72a; // [rsp+48h] [rbp-58h]
  double t_72b; // [rsp+48h] [rbp-58h]
  double t_80; // [rsp+50h] [rbp-50h]
  double t_80a; // [rsp+50h] [rbp-50h]
  double t_80b; // [rsp+50h] [rbp-50h]
  double t_88; // [rsp+58h] [rbp-48h]
  double t_88a; // [rsp+58h] [rbp-48h]
  double t_88b; // [rsp+58h] [rbp-48h]
  double t_96; // [rsp+60h] [rbp-40h]
  double t_96a; // [rsp+60h] [rbp-40h]
  double t_96b; // [rsp+60h] [rbp-40h]
  double t_104; // [rsp+68h] [rbp-38h]
  double t_104a; // [rsp+68h] [rbp-38h]
  double t_104b; // [rsp+68h] [rbp-38h]
  double t_112; // [rsp+70h] [rbp-30h]
  double t_112a; // [rsp+70h] [rbp-30h]
  double t_112b; // [rsp+70h] [rbp-30h]
  double t_120; // [rsp+78h] [rbp-28h]
  double t_120a; // [rsp+78h] [rbp-28h]

  t_120 = *_x - _x[15];
  t_112 = _x[1] - _x[14];
  t_104 = _x[2] - _x[13];
  t_96 = _x[3] - _x[12];
  t_88 = _x[4] - _x[11];
  t_80 = _x[5] - _x[10];
  t_72 = _x[6] - _x[9];
  t_64 = _x[7] - _x[8];
  t_56 = _x[7] - t_64 / 2.0;
  t_48 = _x[6] - t_72 / 2.0;
  t_40 = _x[5] - t_80 / 2.0;
  t_32 = _x[4] - t_88 / 2.0;
  t_24 = _x[3] - t_96 / 2.0;
  t_16 = _x[2] - t_104 / 2.0;
  t_8 = _x[1] - t_112 / 2.0;
  t = *_x - t_120 / 2.0;
  t_64a = t_64 * (double)*_f / 16.0;
  t_72a = t_72 * (double)_f[1] / 16.0;
  t_80a = t_80 * (double)_f[2] / 16.0;
  t_88a = t_88 * (double)_f[3] / 16.0;
  t_96a = t_96 * (double)_f[4] / 16.0;
  t_104a = t_104 * (double)_f[5] / 16.0;
  t_112a = t_112 * (double)_f[6] / 16.0;
  t_120a = t_112a * (double)_f[14] / 16.0 + t_120 * (double)_f[7] / 16.0;
  t_112b = t_104a * (double)_f[13] / 16.0 + t_120a * (double)_f[21] / 16.0 + t_112a;
  t_104b = t_96a * (double)_f[12] / 16.0 + t_112b * (double)_f[20] / 16.0 + t_104a;
  t_96b = t_88a * (double)_f[11] / 16.0 + t_104b * (double)_f[19] / 16.0 + t_96a;
  t_88b = t_80a * (double)_f[10] / 16.0 + t_96b * (double)_f[18] / 16.0 + t_88a;
  t_80b = t_72a * (double)_f[9] / 16.0 + t_88b * (double)_f[17] / 16.0 + t_80a;
  t_72b = t_64a * (double)_f[8] / 16.0 + t_80b * (double)_f[16] / 16.0 + t_72a;
  t_64b = t_72b * (double)_f[15] / 16.0 + t_64a;
  ta = t_120a / 2.0 + t;
  *_y = ta;
  t_8a = t_112b / 2.0 + t_8;
  _y[1] = t_8a;
  t_16a = t_104b / 2.0 + t_16;
  _y[2] = t_16a;
  t_24a = t_96b / 2.0 + t_24;
  _y[3] = t_24a;
  t_32a = t_88b / 2.0 + t_32;
  _y[4] = t_32a;
  t_40a = t_80b / 2.0 + t_40;
  _y[5] = t_40a;
  t_48a = t_72b / 2.0 + t_48;
  _y[6] = t_48a;
  t_56a = t_64b / 2.0 + t_56;
  _y[7] = t_56a;
  _y[8] = t_56a - t_64b;
  _y[9] = t_48a - t_72b;
  _y[10] = t_40a - t_80b;
  _y[11] = t_32a - t_88b;
  _y[12] = t_24a - t_96b;
  _y[13] = t_16a - t_104b;
  _y[14] = t_8a - t_112b;
  _y[15] = ta - t_120a;
}