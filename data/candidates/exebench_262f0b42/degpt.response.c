void breakup(short *fcs_bit,unsigned_short usps_crc)

{
  int i;
  unsigned_short usps_crc_local;
  short *fcs_bit_local;
  
  for (i = 0; i < 0xd; i = i + 1) {
    fcs_bit[i] = 0;
  }
  usps_crc_local = usps_crc;
  if (0xfff < usps_crc) {
    fcs_bit[0xc] = 1;
    usps_crc_local = usps_crc - 0x1000;
  }
  if (0x7ff < usps_crc_local) {
    fcs_bit[0xb] = 1;
    usps_crc_local = usps_crc_local - 0x800;
  }
  if (0x3ff < usps_crc_local) {
    fcs_bit[10] = 1;
    usps_crc_local = usps_crc_local - 0x400;
  }
  if (0x1ff < usps_crc_local) {
    fcs_bit[9] = 1;
    usps_crc_local = usps_crc_local - 0x200;
  }
  if (0xff < usps_crc_local) {
    fcs_bit[8] = 1;
    usps_crc_local = usps_crc_local - 0x100;
  }
  if (0x7f < usps_crc_local) {
    fcs_bit[7] = 1;
    usps_crc_local = usps_crc_local - 0x80;
  }
  if (0x3f < usps_crc_local) {
    fcs_bit[6] = 1;
    usps_crc_local = usps_crc_local - 0x40;
  }
  if (0x1f < usps_crc_local) {
    fcs_bit[5] = 1;
    usps_crc_local = usps_crc_local - 0x20;
  }
  if (0xf < usps_crc_local) {
    fcs_bit[4] = 1;
    usps_crc_local = usps_crc_local - 0x10;
  }
  if (7 < usps_crc_local) {
    fcs_bit[3] = 1;
    usps_crc_local = usps_crc_local - 8;
  }
  if (3 < usps_crc_local) {
    fcs_bit[2] = 1;
    usps_crc_local = usps_crc_local - 4;
  }
  if (1 < usps_crc_local) {
    fcs_bit[1] = 1;
    usps_crc_local = usps_crc_local - 2;
  }
  if (usps_crc_local == 1) {
    *fcs_bit = 1;
  }
  return;
}