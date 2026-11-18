double blue_filter(double white,double *buf)

{
  double dVar1;
  double dVar2;
  double blue;
  double *buf_local;
  double white_local;
  
  *buf = white * DAT_00102070 + -(DAT_00102078 * *buf);
  buf[1] = white * DAT_00102060 + -(DAT_00102068 * buf[1]);
  buf[2] = white * DAT_00102050 + -(DAT_00102058 * buf[2]);
  buf[3] = white * DAT_00102040 + -(DAT_00102048 * buf[3]);
  buf[4] = white * DAT_00102030 + -(DAT_00102038 * buf[4]);
  buf[5] = white * DAT_00102020 + DAT_00102028 * buf[5];
  dVar1 = buf[6];
  dVar2 = white * DAT_00102018;
  buf[6] = DAT_00102010 * white;
  return DAT_00102008 * (dVar2 + *buf + buf[1] + buf[2] + buf[3] + buf[4] + buf[5] + dVar1);
}