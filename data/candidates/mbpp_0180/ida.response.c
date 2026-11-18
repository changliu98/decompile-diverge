double __cdecl func0(double slat, double slon, double elat, double elon)
{
  double v4; // xmm3_8
  double v6; // [rsp+8h] [rbp-48h]
  double v7; // [rsp+10h] [rbp-40h]
  double v8; // [rsp+18h] [rbp-38h]
  double v9; // [rsp+20h] [rbp-30h]

  v9 = sin(slat);
  v8 = sin(elat);
  v6 = cos(slat);
  v7 = v6 * cos(elat);
  v4 = cos(slon - elon);
  return 6371.01 * acos(v9 * v8 + v7 * v4);
}