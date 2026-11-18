void fcs12(unsigned short *fcs_bit, unsigned short usps_crc)
{
  int i;
  unsigned short usps_crca = usps_crc;
  for (i = 0; i < 13; i++)
    fcs_bit[i] = 0;
  if (usps_crca >= 0x1000) {
    fcs_bit[12] = 1;
    usps_crca = usps_crca - 0x1000;
  }
  if (usps_crca >= 0x800) {
    fcs_bit[11] = 1;
    usps_crca = usps_crca - 0x800;
  }
  if (usps_crca >= 0x400) {
    fcs_bit[10] = 1;
    usps_crca = usps_crca - 0x400;
  }
  if (usps_crca >= 0x200) {
    fcs_bit[9] = 1;
    usps_crca = usps_crca - 0x200;
  }
  if (usps_crca >= 0x100) {
    fcs_bit[8] = 1;
    usps_crca = usps_crca - 0x100;
  }
  if (usps_crca >= 0x80) {
    fcs_bit[7] = 1;
    usps_crca = usps_crca - 0x80;
  }
  if (usps_crca >= 0x40) {
    fcs_bit[6] = 1;
    usps_crca = usps_crca - 0x40;
  }
  if (usps_crca >= 0x20) {
    fcs_bit[5] = 1;
    usps_crca = usps_crca - 0x20;
  }
  if (usps_crca >= 0x10) {
    fcs_bit[4] = 1;
    usps_crca = usps_crca - 0x10;
  }
  if (usps_crca >= 0x08) {
    fcs_bit[3] = 1;
    usps_crca = usps_crca - 0x08;
  }
  if (usps_crca >= 0x04) {
    fcs_bit[2] = 1;
    usps_crca = usps_crca - 0x04;
  }
  if (usps_crca >= 0x02) {
    fcs_bit[1] = 1;
    usps_crca = usps_crca - 0x02;
  }
  if (usps_crca == 1)
    fcs_bit[0] = 1;
}