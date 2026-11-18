static void wmv2_idct_row_mmi(short *data) {
  int a0, a1, a2, a3, a4, a5, a6, a7;
  a0 = data[0] * COS_PI_8 + data[4] * COS_PI_8;
  a1 = data[1] * COS_3_PI_8 + data[7] * COS_5_PI_8;
  a2 = data[2] * COS_5_PI_8 + data[6] * COS_7_PI_8;
  a3 = data[3] * COS_PI - data[5] * COS_3_PI;
  a4 = data[0] * COS_PI_8 - data[4] * COS_PI_8;
  a5 = data[3] * COS_PI + data[5] * COS_3_PI;
  a6 = data[2] * COS_5_PI_8 - data[6] * COS_7_PI_8;
  a7 = data[1] * COS_3_PI_8 - data[7] * COS_5_PI_8;
  int b1 = (181 * (a1 + a5 - a3 - a7) + 128) >> 8;
  int b2 = (181 * (a1 - a5 + a3 - a7) + 128) >> 8;
  data[0] = (a0 + a2 + a5 + a3 + 128) >> 8;
  data[1] = (a4 + a6 + b1 + 128) >> 8;
  data[2] = (a4 - a6 + b2 + 128) >> 8;
  data[3] = (a0 - a2 + a7 + a3 + 128) >> 8;
  data[4] = (a0 - a2 - a7 - a3 + 128) >> 8;
  data[5] = (a4 - a6 - b2 + 128) >> 8;
  data[6] = (a4 + a6 - b1 + 128) >> 8;
  data[7] = (a0 + a2 - a5 - a3 + 128) >> 8;
}